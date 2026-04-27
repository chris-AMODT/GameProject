#include "inputhandler.h"
#include <QtMath>

InputHandler::InputHandler(Game *g, QObject *parent) : QObject(parent)
{
    game = g;
}

void InputHandler::keyPressed(QKeyEvent *event)
{
    if (event->isAutoRepeat()) return;
    heldKeys.insert(event->key());

    if (event->key() == Qt::Key_Space) {
        if (game->state == GameState::Playing)
            game->player->tryAttack(*game->opponent);
    }

    if (event->key() == Qt::Key_P) {
        game->pauseResume();
    }

    if (event->key() == Qt::Key_R) {
        if (game->state == GameState::GameOver)
            game->restart();
    }
}

void InputHandler::keyReleased(QKeyEvent *event)
{
    if (event->isAutoRepeat()) return;
    heldKeys.remove(event->key());
}

void InputHandler::processTick()
{
    if (game->state != GameState::Playing) return;

    float dx = 0;
    float dy = 0;

    if (heldKeys.contains(Qt::Key_A)) dx -= 1;
    if (heldKeys.contains(Qt::Key_D)) dx += 1;
    if (heldKeys.contains(Qt::Key_W)) dy -= 1;
    if (heldKeys.contains(Qt::Key_S)) dy += 1;

    if (dx != 0 || dy != 0) {
        float len = qSqrt(dx * dx + dy * dy);
        dx /= len;
        dy /= len;

        float spd = game->player->speed;
        float nx = game->player->position.x() + dx * spd;
        float ny = game->player->position.y() + dy * spd;

        if (nx < 20) nx = 20;
        if (nx > 780) nx = 780;
        if (ny < 20) ny = 20;
        if (ny > 480) ny = 480;

        game->player->position = QPointF(nx, ny);
    }
}
