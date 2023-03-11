#ifndef TYPES_H
#define TYPES_H

// Statistics gathered from simulations
struct SimulationStats
{
    int numberOfRolls = 0;
    int critFailures = 0;
    int failures = 0;
    int successes = 0;
    int critSuccesses = 0;
    int totalDamage = 0;
};

// Returns the average damage per attempted attack
double averageAttemptedDamage(SimulationStats stats);
// Returns the average damage per hit
double averageHitDamage(SimulationStats stats);

// Represents the degree of success of a particular roll
enum DegreeOfSuccess
{
    critFailure = -2,
    failure = -1,
    success = 1,
    critSuccess = 2,
};

// Increases the degree of success by one step, unless it is already a critical success.
DegreeOfSuccess operator++(DegreeOfSuccess &DoS, int);
// Reduces the degree of success by one step, unless it is already a critical failure.
DegreeOfSuccess operator--(DegreeOfSuccess &DoS, int);

// Represents special case die rolls that modify the degree of success of the roll.
enum DegreeOfSuccessMod
{
    nat1 = -1,
    normal = 0,
    nat20 = 1,
};

// Contains the final numeric result of a die roll along with whether or not it was a
// special case roll.
struct RollResult
{
    int result;
    DegreeOfSuccessMod Dosm;
};

#endif