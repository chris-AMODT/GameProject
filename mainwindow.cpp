#include "mainwindow.h"
#include <QApplication>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
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
    battleLayout->setContentsMargins(0, 0, 0, 0);

    backBtn = new QPushButton("Back to Menu");
    backBtn->setFixedWidth(120);

    battlefield = new BattlefieldWidget();

    battleLayout->addWidget(backBtn);
    battleLayout->addWidget(battlefield);

    pages->addWidget(menuPage);
    pages->addWidget(battlePage);

    player = new Character("Player", CharacterClass::Warrior, true);
    opponent = new Character("CPU", CharacterClass::Mage, false);
    player->position = QPointF(150, 250);
    opponent->position = QPointF(650, 250);

    battlefield->setPlayer(player);
    battlefield->setOpponent(opponent);

    connect(startBtn, &QPushButton::clicked, this, &MainWindow::startGame);
    connect(exitBtn, &QPushButton::clicked, this, &MainWindow::exitGame);
    connect(backBtn, &QPushButton::clicked, this, &MainWindow::goToMenu);
}

void MainWindow::startGame()
{
    pages->setCurrentWidget(battlePage);
}

void MainWindow::exitGame()
{
    QApplication::quit();
}

void MainWindow::goToMenu()
{
    pages->setCurrentWidget(menuPage);
}
