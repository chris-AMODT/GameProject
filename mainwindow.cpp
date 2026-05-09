#include "mainwindow.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    game = new Game(this);
    input = new InputHandler(game, this);
    scores = new ScoreManager(this);

    pages = new QStackedWidget(this);
    setCentralWidget(pages);

    menuPage = new QWidget();
    QVBoxLayout *menuLayout = new QVBoxLayout(menuPage);
    menuLayout->setAlignment(Qt::AlignCenter);
    menuLayout->setSpacing(14);

    titleLabel = new QLabel("BATTLE ARENA");
    QFont f = titleLabel->font();
    f.setPointSize(30);
    f.setBold(true);
    titleLabel->setFont(f);
    titleLabel->setAlignment(Qt::AlignCenter);

    classLabel = new QLabel("Choose your character:");
    classLabel->setAlignment(Qt::AlignCenter);
    classSelector = new QComboBox();
    classSelector->addItem("Warrior  (HP 150 | ATK 25 | Melee)");
    classSelector->addItem("Mage     (HP  80 | ATK 35 | Ranged)");
    classSelector->addItem("Rogue    (HP 100 | ATK 20 | Fast)");
    classSelector->setFixedWidth(280);

    diffLabel = new QLabel("Difficulty:");
    diffLabel->setAlignment(Qt::AlignCenter);
    diffSelector = new QComboBox();
    diffSelector->addItem("Easy");
    diffSelector->addItem("Normal");
    diffSelector->addItem("Hard");
    diffSelector->setCurrentIndex(1);
    diffSelector->setFixedWidth(280);

    startBtn = new QPushButton("Start Game");
    startBtn->setFixedSize(200, 50);

    QHBoxLayout *fileRow = new QHBoxLayout();
    saveBtn = new QPushButton("Save");
    loadBtn = new QPushButton("Load");
    saveBtn->setFixedSize(90, 36);
    loadBtn->setFixedSize(90, 36);
    fileRow->addStretch();
    fileRow->addWidget(saveBtn);
    fileRow->addWidget(loadBtn);
    fileRow->addStretch();

    exitBtn = new QPushButton("Exit");
    exitBtn->setFixedSize(200, 50);

    menuLayout->addStretch();
    menuLayout->addWidget(titleLabel);
    menuLayout->addSpacing(20);
    menuLayout->addWidget(classLabel);
    menuLayout->addWidget(classSelector, 0, Qt::AlignCenter);
    menuLayout->addWidget(diffLabel);
    menuLayout->addWidget(diffSelector, 0, Qt::AlignCenter);
    menuLayout->addSpacing(10);
    menuLayout->addWidget(startBtn, 0, Qt::AlignCenter);
    menuLayout->addLayout(fileRow);
    menuLayout->addWidget(exitBtn, 0, Qt::AlignCenter);
    menuLayout->addStretch();

    battlePage = new QWidget();
    QVBoxLayout *battleLayout = new QVBoxLayout(battlePage);
    battleLayout->setContentsMargins(4, 4, 4, 4);

    QHBoxLayout *topBar = new QHBoxLayout();
    backBtn = new QPushButton("Menu");
    nextRoundBtn = new QPushButton("Next Round");
    nextRoundBtn->setVisible(false);
    statusLabel = new QLabel("WASD = move  |  Space = attack  |  P = pause");
    statusLabel->setAlignment(Qt::AlignCenter);
    scoreLabel = new QLabel("Player 0 — CPU 0  (Round 1)");
    scoreLabel->setAlignment(Qt::AlignRight);
    QFont sf = scoreLabel->font();
    sf.setBold(true);
    scoreLabel->setFont(sf);

    topBar->addWidget(backBtn);
    topBar->addWidget(nextRoundBtn);
    topBar->addStretch();
    topBar->addWidget(statusLabel);
    topBar->addStretch();
    topBar->addWidget(scoreLabel);

    battlefield = new BattlefieldWidget();
    battlefield->setInputHandler(input);
    battlefield->setAnimations(&game->anim);

    battleLayout->addLayout(topBar);
    battleLayout->addWidget(battlefield);

    pages->addWidget(menuPage);
    pages->addWidget(battlePage);

    connect(startBtn,    &QPushButton::clicked, this, &MainWindow::startGame);
    connect(exitBtn,     &QPushButton::clicked, this, &MainWindow::exitGame);
    connect(backBtn,     &QPushButton::clicked, this, &MainWindow::goToMenu);
    connect(nextRoundBtn,&QPushButton::clicked, this, &MainWindow::nextRound);
    connect(saveBtn,     &QPushButton::clicked, this, &MainWindow::saveGame);
    connect(loadBtn,     &QPushButton::clicked, this, &MainWindow::loadGame);
    connect(game, &Game::frameReady, [this]() {
        input->processTick();
        battlefield->update();
    });
    connect(game, &Game::gameOver, this, &MainWindow::onGameOver);
}

void MainWindow::startGame()
{
    int classIndex = classSelector->currentIndex();
    CharacterClass chosen = (CharacterClass)classIndex;

    int diffIndex = diffSelector->currentIndex();
    game->ai.difficulty = (Difficulty)diffIndex;

    scores->reset();
    scoreLabel->setText(scores->scoreLine());
    nextRoundBtn->setVisible(false);
    game->startGame(chosen);
    battlefield->setPlayer(game->player);
    battlefield->setOpponent(game->opponent);
    battlefield->setAnimations(&game->anim);
    statusLabel->setText("WASD = move  |  Space = attack  |  P = pause");
    pages->setCurrentWidget(battlePage);
    battlefield->setFocus();
}

void MainWindow::exitGame()
{
    QApplication::quit();
}

void MainWindow::goToMenu()
{
    game->state = GameState::Menu;
    pages->setCurrentWidget(menuPage);
}

void MainWindow::onGameOver(QString winnerName)
{
    scores->recordRound(winnerName == "Player");
    scoreLabel->setText(scores->scoreLine());

    if (scores->isMatchOver()) {
        statusLabel->setText(scores->matchWinner() + " wins the match!");
        nextRoundBtn->setVisible(false);
    } else {
        statusLabel->setText(winnerName + " wins round " + QString::number(scores->currentRound - 1) + "!");
        nextRoundBtn->setVisible(true);
    }
}

void MainWindow::nextRound()
{
    nextRoundBtn->setVisible(false);
    int classIndex = classSelector->currentIndex();
    game->startGame((CharacterClass)classIndex);
    battlefield->setPlayer(game->player);
    battlefield->setOpponent(game->opponent);
    battlefield->setAnimations(&game->anim);
    statusLabel->setText("WASD = move  |  Space = attack  |  P = pause");
    battlefield->setFocus();
}

void MainWindow::saveGame()
{
    QString path = QFileDialog::getSaveFileName(this, "Save Game", "", "Save Files (*.txt)");
    if (path.isEmpty()) return;

    SaveData data;
    data.playerWins   = scores->playerWins;
    data.cpuWins      = scores->cpuWins;
    data.currentRound = scores->currentRound;
    data.winsNeeded   = scores->winsNeeded;
    data.difficulty   = diffSelector->currentIndex();
    data.playerClass  = classSelector->currentIndex();

    if (saver.save(path, data))
        QMessageBox::information(this, "Saved", "Game saved successfully.");
    else
        QMessageBox::warning(this, "Error", "Could not save file.");
}

void MainWindow::loadGame()
{
    QString path = QFileDialog::getOpenFileName(this, "Load Game", "", "Save Files (*.txt)");
    if (path.isEmpty()) return;

    SaveData data;
    if (!saver.load(path, data)) {
        QMessageBox::warning(this, "Error", "Could not load file.");
        return;
    }

    scores->playerWins   = data.playerWins;
    scores->cpuWins      = data.cpuWins;
    scores->currentRound = data.currentRound;
    scores->winsNeeded   = data.winsNeeded;
    classSelector->setCurrentIndex(data.playerClass);
    diffSelector->setCurrentIndex(data.difficulty);
    scoreLabel->setText(scores->scoreLine());

    QMessageBox::information(this, "Loaded", "Game loaded. Press Start to continue.");
}
