#pragma once

#include <QObject>
#include <QString>

class ScoreManager : public QObject
{
    Q_OBJECT

public:
    explicit ScoreManager(QObject *parent = nullptr);

    void reset();
    void recordRound(bool playerWon);

    int playerWins;
    int cpuWins;
    int currentRound;
    int winsNeeded;

    bool isMatchOver();
    QString matchWinner();
    QString scoreLine();
};
