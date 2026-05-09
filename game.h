#pragma once

#include <QObject>
#include <QTimer>
#include "character.h"
#include "ai.h"
#include "animationmanager.h"

enum class GameState {
    Menu,
    Playing,
    Paused,
    GameOver
};

class Game : public QObject
{
    Q_OBJECT

public:
    explicit Game(QObject *parent = nullptr);

    void startGame(CharacterClass playerClass);
    void pauseResume();
    void restart();

    GameState        state;
    Character       *player;
    Character       *opponent;
    QString          winner;
    AI               ai;
    AnimationManager anim;

signals:
    void frameReady();
    void gameOver(QString winnerName);

private slots:
    void tick();

private:
    QTimer timer;
    void checkWin();
};
