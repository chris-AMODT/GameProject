#include "mainwindow.h"
#include <QApplication>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    game = new Game(this);

    pages = new QStackedWidget(this);
    setCentralWidget(pages);

    menuPage = new QWidget();
    QVBoxLayout *menuLayout = new QVBoxLayout(menuPage);
    menuLayout->setAlignment(Qt::AlignCenter);
    menuLayout->setSpacing(20);

    titleLabel = new QLabel("BATTLE ARENA");
    QFont f = titleLabel->font();
    f.setPointSize(30);
    f.setBold(true);
    titleLabel->setFont(f);
    titleLabel->setAlignment(Qt::AlignCenter);

    startBtn = new QPushButton("Start Game");
    startBtn->setFixedSize(200, 50);

    exitBtn = new QPushButton("Exit");
    exitBtn->setFixedSize(200, 50);

    menuLayout->addStretch();
    menuLayout->addWidget(titleLabel);
    menuLayout->addSpacing(30);
    menuLayout->addWidget(startBtn, 0, Qt::AlignCenter);
    menuLayout->addWidget(exitBtn, 0, Qt::AlignCenter);
    menuLayout->addStretch();

    battlePage = new QWidget();
    QVBoxLayout *battleLayout = new QVBoxLayout(battlePage);
    battleLayout->setContentsMargins(4, 4, 4, 4);

    QHBoxLayout *topBar = new QHBoxLayout();
    backBtn = new QPushButton("Menu");
    restartBtn = new QPushButton("Restart");
    statusLabel = new QLabel("Fighting...");
    statusLabel->setAlignment(Qt::AlignCenter);
    topBar->addWidget(backBtn);
    topBar->addWidget(restartBtn);
    topBar->addStretch();
    topBar->addWidget(statusLabel);
    topBar->addStretch();

    battlefield = new BattlefieldWidget();

    battleLayout->addLayout(topBar);
    battleLayout->addWidget(battlefield);

    pages->addWidget(menuPage);
    pages->addWidget(battlePage);

    connect(startBtn, &QPushButton::clicked, this, &MainWindow::startGame);
    connect(exitBtn, &QPushButton::clicked, this, &MainWindow::exitGame);
    connect(backBtn, &QPushButton::clicked, this, &MainWindow::goToMenu);
    connect(restartBtn, &QPushButton::clicked, game, &Game::restart);
    connect(game, &Game::frameReady, battlefield, QOverload<>::of(&QWidget::update));
    connect(game, &Game::gameOver, this, &MainWindow::onGameOver);
}

void MainWindow::startGame()
{
    game->startGame(CharacterClass::Warrior);
    battlefield->setPlayer(game->player);
    battlefield->setOpponent(game->opponent);
    statusLabel->setText("Fighting...");
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
    statusLabel->setText(winnerName + " wins!");
}
