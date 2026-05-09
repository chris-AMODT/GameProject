#include "game.h"
#include <QRandomGenerator>

Game::Game(QObject *parent) : QObject(parent), anim(this)
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
    int playerHpBefore   = player->hp;
    int opponentHpBefore = opponent->hp;

    player->tickCooldown();
    ai.tick(*opponent, *player);

    if (opponent->hp < opponentHpBefore) {
        int dmg = opponentHpBefore - opponent->hp;
        anim.spawnHit(opponent->position, dmg);
    }
    if (player->hp < playerHpBefore) {
        int dmg = playerHpBefore - player->hp;
        anim.spawnHit(player->position, dmg);
    }

    anim.tick();
    checkWin();
    emit frameReady();
}

void Game::checkWin()
{
    if (!player->isAlive()) {
        anim.spawnDeath(player->position, QColor(70, 130, 210));
        winner = "CPU";
        state = GameState::GameOver;
        timer.stop();
        emit gameOver(winner);
    } else if (!opponent->isAlive()) {
        anim.spawnDeath(opponent->position, QColor(210, 70, 70));
        winner = "Player";
        state = GameState::GameOver;
        timer.stop();
        emit gameOver(winner);
    }
}
