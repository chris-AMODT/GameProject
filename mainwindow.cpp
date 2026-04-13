#include "mainwindow.h"
#include <QApplication>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QWidget *center = new QWidget(this);
    setCentralWidget(center);

    QVBoxLayout *layout = new QVBoxLayout(center);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(20);

    titleLabel = new QLabel("BATTLE ARENA", center);
    QFont f = titleLabel->font();
    f.setPointSize(30);
    f.setBold(true);
    titleLabel->setFont(f);
    titleLabel->setAlignment(Qt::AlignCenter);

    startBtn = new QPushButton("Start Game", center);
    startBtn->setFixedSize(200, 50);

    exitBtn = new QPushButton("Exit", center);
    exitBtn->setFixedSize(200, 50);

    layout->addStretch();
    layout->addWidget(titleLabel);
    layout->addSpacing(30);
    layout->addWidget(startBtn, 0, Qt::AlignCenter);
    layout->addWidget(exitBtn, 0, Qt::AlignCenter);
    layout->addStretch();

    connect(startBtn, &QPushButton::clicked, this, &MainWindow::startGame);
    connect(exitBtn, &QPushButton::clicked, this, &MainWindow::exitGame);
}

void MainWindow::startGame()
{
    titleLabel->setText("Game not implemented yet!");
}

void MainWindow::exitGame()
{
    QApplication::quit();
}
