#include "ai.h"
#include <QtMath>
#include <QRandomGenerator>

AI::AI()
{
    difficulty = Difficulty::Normal;
    currentState = AIState::Approach;
    circleDir = 1;
    circleTimer = 0;
}

float AI::speedScale()
{
    if (difficulty == Difficulty::Easy)   return 0.55f;
    if (difficulty == Difficulty::Hard)   return 1.35f;
    return 1.0f;
}

void AI::tick(Character &opponent, Character &player)
{
    if (!opponent.isAlive() || !player.isAlive()) return;

    opponent.tickCooldown();
    currentState = chooseState(opponent, player);

    if (currentState == AIState::Approach) doApproach(opponent, player);
    if (currentState == AIState::Attack)   doAttack(opponent, player);
    if (currentState == AIState::Retreat)  doRetreat(opponent, player);
    if (currentState == AIState::Circle)   doCircle(opponent, player);
}

AIState AI::chooseState(Character &opponent, Character &player)
{
    float dx = player.position.x() - opponent.position.x();
    float dy = player.position.y() - opponent.position.y();
    float dist = qSqrt(dx * dx + dy * dy);

    float retreatThreshold = 0;
    if (difficulty == Difficulty::Easy)   retreatThreshold = 0.45f;
    if (difficulty == Difficulty::Normal) retreatThreshold = 0.20f;
    if (difficulty == Difficulty::Hard)   retreatThreshold = 0.0f;

    if (opponent.hpPercent() < retreatThreshold)
        return AIState::Retreat;

    if (dist <= opponent.attackRange) {
        if (difficulty == Difficulty::Hard && circleTimer % 40 < 20)
            return AIState::Circle;
        return AIState::Attack;
    }

    return AIState::Approach;
}

void AI::doApproach(Character &opponent, Character &player)
{
    float dx = player.position.x() - opponent.position.x();
    float dy = player.position.y() - opponent.position.y();
    float dist = qSqrt(dx * dx + dy * dy);
    if (dist < 1) return;

    float nx = dx / dist;
    float ny = dy / dist;
    float spd = opponent.speed * speedScale();
    opponent.position += QPointF(nx * spd, ny * spd);
    circleTimer++;

    if (opponent.position.x() < 20) opponent.position.setX(20);
    if (opponent.position.x() > 780) opponent.position.setX(780);
    if (opponent.position.y() < 20) opponent.position.setY(20);
    if (opponent.position.y() > 480) opponent.position.setY(480);
}

void AI::doAttack(Character &opponent, Character &player)
{
    opponent.tryAttack(player);
    circleTimer++;
}

void AI::doRetreat(Character &opponent, Character &player)
{
    float dx = opponent.position.x() - player.position.x();
    float dy = opponent.position.y() - player.position.y();
    float dist = qSqrt(dx * dx + dy * dy);
    if (dist < 1) return;

    float nx = dx / dist;
    float ny = dy / dist;
    float spd = opponent.speed * speedScale() * 0.8f;
    opponent.position += QPointF(nx * spd, ny * spd);

    if (opponent.position.x() < 20) opponent.position.setX(20);
    if (opponent.position.x() > 780) opponent.position.setX(780);
    if (opponent.position.y() < 20) opponent.position.setY(20);
    if (opponent.position.y() > 480) opponent.position.setY(480);
}

void AI::doCircle(Character &opponent, Character &player)
{
    float dx = player.position.x() - opponent.position.x();
    float dy = player.position.y() - opponent.position.y();
    float dist = qSqrt(dx * dx + dy * dy);
    if (dist < 1) return;

    float nx = dx / dist;
    float ny = dy / dist;

    float px = -ny * circleDir;
    float py =  nx * circleDir;

    circleTimer++;
    if (circleTimer % 80 == 0)
        circleDir = -circleDir;

    float spd = opponent.speed * speedScale();
    opponent.position += QPointF(px * spd, py * spd);
    opponent.tryAttack(player);

    if (opponent.position.x() < 20) opponent.position.setX(20);
    if (opponent.position.x() > 780) opponent.position.setX(780);
    if (opponent.position.y() < 20) opponent.position.setY(20);
    if (opponent.position.y() > 480) opponent.position.setY(480);
}
