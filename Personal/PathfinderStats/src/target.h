#ifndef TARGET_H
#define TARGET_H
#include "types.h"

// Represents a target that the player will attack.
class Target
{
private:
    // The target's "armor class", which represents how difficult they are to hit.
    int ac;

public:
    Target(int ac);
    Target();

    // Compares the roll to the target's armor class and returns how successful it was.
    DegreeOfSuccess compareAttackRoll(RollResult roll);

    int getAc();
};

#endif