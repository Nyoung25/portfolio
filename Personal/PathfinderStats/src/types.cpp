#include "types.h"
#include <iostream>

double averageAttemptedDamage(SimulationStats stats)
{
    return ((double)stats.totalDamage / stats.numberOfRolls);
}

double averageHitDamage(SimulationStats stats)
{
    return ((double)stats.totalDamage / (stats.successes + stats.critSuccesses));
}

DegreeOfSuccess operator++(DegreeOfSuccess &DoS, int)
{
    switch (DoS)
    {
    case critFailure:
        return DoS = failure;
        break;
    case failure:
        return DoS = success;
        break;
    case success:
        return DoS = critSuccess;
        break;
    case critSuccess:
        return DoS = critSuccess;
        break;
    }

    std::cerr << "Unexpected value for DegreeOfSuccess: " << static_cast<int>(DoS);
    // Don't change the value
    return failure;
}

DegreeOfSuccess operator--(DegreeOfSuccess &DoS, int)
{
    switch (DoS)
    {
    case critFailure:
        return DoS = critFailure;
        break;
    case failure:
        return DoS = critFailure;
        break;
    case success:
        return DoS = failure;
        break;
    case critSuccess:
        return DoS = success;
        break;
    }

    std::cerr << "Unexpected value for DegreeOfSuccess: " << static_cast<int>(DoS);
    // Don't change the value
    return failure;
}