#pragma once

#include <QObject>
#include <QKeyEvent>
#include <QSet>
#include "game.h"

class InputHandler : public QObject
{
    Q_OBJECT

public:
    explicit InputHandler(Game *g, QObject *parent = nullptr);

    void keyPressed(QKeyEvent *event);
    void keyReleased(QKeyEvent *event);
    void processTick();

private:
    Game *game;
    QSet<int> heldKeys;
};
