#include "scoremanager.h"

ScoreManager::ScoreManager(QObject *parent) : QObject(parent)
{
    playerWins = 0;
    cpuWins = 0;
    currentRound = 1;
    winsNeeded = 3;
}

void ScoreManager::reset()
{
    playerWins = 0;
    cpuWins = 0;
    currentRound = 1;
}

void ScoreManager::recordRound(bool playerWon)
{
    if (playerWon) playerWins++;
    else           cpuWins++;
    currentRound++;
}

bool ScoreManager::isMatchOver()
{
    return playerWins >= winsNeeded || cpuWins >= winsNeeded;
}

QString ScoreManager::matchWinner()
{
    if (playerWins >= winsNeeded) return "Player";
    if (cpuWins    >= winsNeeded) return "CPU";
    return "";
}

QString ScoreManager::scoreLine()
{
    return "Player " + QString::number(playerWins) +
           " — CPU " + QString::number(cpuWins) +
           "  (Round " + QString::number(currentRound) + ")";
}
