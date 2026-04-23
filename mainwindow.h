#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QStackedWidget>
#include "battlefieldwidget.h"
#include "character.h"
#include "game.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void startGame();
    void exitGame();
    void goToMenu();
    void onGameOver(QString winnerName);

private:
    QStackedWidget    *pages;

    QWidget           *menuPage;
    QLabel            *titleLabel;
    QPushButton       *startBtn;
    QPushButton       *exitBtn;

    QWidget           *battlePage;
    BattlefieldWidget *battlefield;
    QPushButton       *backBtn;
    QPushButton       *restartBtn;
    QLabel            *statusLabel;

    Game              *game;
};
