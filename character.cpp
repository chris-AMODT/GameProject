#include "character.h"
#include <QtMath>
#include <algorithm>

Character::Character()
{
    hp = 0; maxHp = 0; attack = 0; defense = 0;
    speed = 0; attackRange = 0; attackCooldown = 0; cooldownLeft = 0;
    isPlayer = false;
    charClass = CharacterClass::Warrior;
}

Character::Character(QString n, CharacterClass cls, bool player)
{
    name = n;
    charClass = cls;
    isPlayer = player;
    cooldownLeft = 0;

    if (cls == CharacterClass::Warrior) {
        maxHp = 150; attack = 25; defense = 10;
        speed = 2.5f; attackRange = 50; attackCooldown = 20;
    } else if (cls == CharacterClass::Mage) {
        maxHp = 80; attack = 35; defense = 3;
        speed = 3.0f; attackRange = 200; attackCooldown = 30;
    } else {
        maxHp = 100; attack = 20; defense = 5;
        speed = 4.5f; attackRange = 60; attackCooldown = 15;
    }

    hp = maxHp;
}

bool Character::isAlive()
{
    return hp > 0;
}

float Character::hpPercent()
{
    if (maxHp == 0) return 0;
    return (float)hp / maxHp;
}

void Character::takeDamage(int rawDamage)
{
    int dmg = rawDamage - defense;
    if (dmg < 1) dmg = 1;
    hp -= dmg;
    if (hp < 0) hp = 0;
}

bool Character::tryAttack(Character &target)
{
    if (cooldownLeft > 0) return false;

    float dx = target.position.x() - position.x();
    float dy = target.position.y() - position.y();
    float dist = qSqrt(dx * dx + dy * dy);

    if (dist > attackRange) return false;

    target.takeDamage(attack);
    cooldownLeft = attackCooldown;
    return true;
}

void Character::tickCooldown()
{
    if (cooldownLeft > 0) cooldownLeft--;
}

QString Character::className()
{
    if (charClass == CharacterClass::Warrior) return "Warrior";
    if (charClass == CharacterClass::Mage)    return "Mage";
    return "Rogue";
}
