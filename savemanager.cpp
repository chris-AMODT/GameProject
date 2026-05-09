#include "savemanager.h"
#include <QFile>
#include <QTextStream>

SaveManager::SaveManager() {}

bool SaveManager::save(QString filePath, SaveData data)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&file);
    out << data.playerWins   << "\n";
    out << data.cpuWins      << "\n";
    out << data.currentRound << "\n";
    out << data.winsNeeded   << "\n";
    out << data.difficulty   << "\n";
    out << data.playerClass  << "\n";
    file.close();
    return true;
}

bool SaveManager::load(QString filePath, SaveData &data)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&file);
    in >> data.playerWins;
    in >> data.cpuWins;
    in >> data.currentRound;
    in >> data.winsNeeded;
    in >> data.difficulty;
    in >> data.playerClass;
    file.close();
    return true;
}
