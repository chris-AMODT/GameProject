#include "game.h"
#include <QRandomGenerator>
#include <QtMath>

Game::Game(QObject *parent) : QObject(parent)
{
    player = nullptr;
    opponent = nullptr;
    state = GameState::Menu;
    connect(&timer, &QTimer::timeout, this, &Game::tick);
}

void Game::startGame(CharacterClass playerClass)
{
    delete player;
    delete opponent;

    player = new Character("Player", playerClass, true);
    player->position = QPointF(150, 250);

    int randClass = QRandomGenerator::global()->bounded(3);
    CharacterClass oppClass = (CharacterClass)randClass;
    opponent = new Character("CPU", oppClass, false);
    opponent->position = QPointF(650, 250);

    winner = "";
    state = GameState::Playing;
    timer.start(16);
}

void Game::pauseResume()
{
    if (state == GameState::Playing) {
        state = GameState::Paused;
        timer.stop();
    } else if (state == GameState::Paused) {
        state = GameState::Playing;
        timer.start(16);
    }
}

void Game::restart()
{
    timer.stop();
    startGame(player->charClass);
}

void Game::tick()
{
    player->tickCooldown();
    opponent->tickCooldown();
    runAI();
    checkWin();
    emit frameReady();
}

void Game::runAI()
{
    if (!opponent->isAlive()) return;

    float dx = player->position.x() - opponent->position.x();
    float dy = player->position.y() - opponent->position.y();
    float dist = qSqrt(dx * dx + dy * dy);

    if (dist > opponent->attackRange) {
        float nx = dx / dist;
        float ny = dy / dist;
        opponent->position += QPointF(nx * opponent->speed, ny * opponent->speed);
    } else {
        opponent->tryAttack(*player);
    }
}

void Game::checkWin()
{
    if (!player->isAlive()) {
        winner = "CPU";
        state = GameState::GameOver;
        timer.stop();
        emit gameOver(winner);
    } else if (!opponent->isAlive()) {
        winner = "Player";
        state = GameState::GameOver;
        timer.stop();
        emit gameOver(winner);
    }
}
