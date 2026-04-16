#pragma once

#include <QString>
#include <QPointF>

enum class CharacterClass {
    Warrior,
    Mage,
    Rogue
};

class Character
{
public:
    Character();
    Character(QString name, CharacterClass cls, bool isPlayer);

    QString name;
    CharacterClass charClass;
    bool isPlayer;

    int hp;
    int maxHp;
    int attack;
    int defense;
    float speed;
    int attackRange;
    int attackCooldown;
    int cooldownLeft;

    QPointF position;

    bool isAlive();
    float hpPercent();
    void takeDamage(int rawDamage);
    bool tryAttack(Character &target);
    void tickCooldown();
    QString className();
};
