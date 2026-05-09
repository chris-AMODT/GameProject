#pragma once

#include <QString>
#include "character.h"
#include "ai.h"

struct SaveData {
    int playerWins;
    int cpuWins;
    int currentRound;
    int winsNeeded;
    int difficulty;
    int playerClass;
};

class SaveManager
{
public:
    SaveManager();

    bool save(QString filePath, SaveData data);
    bool load(QString filePath, SaveData &data);
};
