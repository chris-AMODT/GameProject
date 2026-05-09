#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QComboBox>
#include <QFileDialog>
#include "battlefieldwidget.h"
#include "character.h"
#include "game.h"
#include "inputhandler.h"
#include "scoremanager.h"
#include "savemanager.h"

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
    void nextRound();
    void saveGame();
    void loadGame();

private:
    QStackedWidget    *pages;

    QWidget           *menuPage;
    QLabel            *titleLabel;
    QPushButton       *startBtn;
    QPushButton       *saveBtn;
    QPushButton       *loadBtn;
    QPushButton       *exitBtn;
    QComboBox         *classSelector;
    QComboBox         *diffSelector;
    QLabel            *classLabel;
    QLabel            *diffLabel;

    QWidget           *battlePage;
    BattlefieldWidget *battlefield;
    QPushButton       *backBtn;
    QPushButton       *nextRoundBtn;
    QLabel            *statusLabel;
    QLabel            *scoreLabel;

    Game              *game;
    InputHandler      *input;
    ScoreManager      *scores;
    SaveManager        saver;
};
