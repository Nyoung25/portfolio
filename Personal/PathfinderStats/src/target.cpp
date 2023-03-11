#include "target.h"

Target::Target(int ac) : ac(ac) {}
Target::Target() : ac(10) {}

DegreeOfSuccess Target::compareAttackRoll(RollResult roll)
{
    DegreeOfSuccess DoS;

    // Determine the degree of success of the attack according to the rules
    // of Pathfinder 2nd Edition.
    if (roll.result >= ac + 10)
    {
        DoS = critSuccess;
    }
    else if (roll.result >= ac)
    {
        DoS = success;
    }
    else if (roll.result <= ac - 10)
    {
        DoS = critFailure;
    }
    else
    {
        DoS = failure;
    }

    if (roll.Dosm == nat20)
    {
        // Rolling a 20 on a 20-sided die increases the degree of success
        DoS++;
    }
    else if (roll.Dosm == nat1)
    {
        // Rolling a 1 on a 20-sided die decreases the degree of success
        DoS--;
    }

    return DoS;
}

int Target::getAc()
{
    return ac;
}