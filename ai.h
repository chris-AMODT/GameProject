#pragma once

#include "character.h"

enum class Difficulty {
    Easy,
    Normal,
    Hard
};

enum class AIState {
    Approach,
    Attack,
    Retreat,
    Circle
};

class AI
{
public:
    AI();

    Difficulty difficulty;

    void tick(Character &opponent, Character &player);

private:
    AIState currentState;
    int circleDir;
    int circleTimer;

    AIState chooseState(Character &opponent, Character &player);
    void doApproach(Character &opponent, Character &player);
    void doAttack(Character &opponent, Character &player);
    void doRetreat(Character &opponent, Character &player);
    void doCircle(Character &opponent, Character &player);
    float speedScale();
};
