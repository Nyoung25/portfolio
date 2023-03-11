#include <iostream>
#include <fstream>
#include <time.h>

#include "playercharacter.h"
#include "target.h"
#include "input.h"

using namespace std;

// Returns the percent change between two values. If oldValue is zero
// the function will return NaN.
double percentChange(double newValue, double oldValue)
{
    return ((newValue - oldValue) / oldValue) * 100;
}

// Derives summary statistics from stats and prints them out
// Throws invalid_argument if stats.numberOfRolls is <= 0
void printSimulationResults(SimulationStats stats) throw(invalid_argument)
{
    if (stats.numberOfRolls <= 0)
    {
        throw invalid_argument("Number of numRolls must be greater than zero to print results");
    }

    cout << "Critical Failure rate: "
         << ((double)stats.critFailures / stats.numberOfRolls * 100) << "%\n";
    cout << "Failure rate: "
         << ((double)stats.failures / stats.numberOfRolls * 100) << "%\n";
    cout << "Success rate: "
         << ((double)stats.successes / stats.numberOfRolls * 100) << "%\n";
    cout << "Critical Success rate: "
         << ((double)stats.critSuccesses / stats.numberOfRolls * 100) << "%\n";
    cout << "Average damage per attempted attack: "
         << (averageAttemptedDamage(stats)) << "\n";
    cout << "Average damage on hit: "
         << (averageHitDamage(stats)) << "\n";
}

// Character pc attempts numRolls attacks against the target and then returns the raw statistics.
// Throws invalid_argument if numRolls are <= 0
SimulationStats runSimulation(PlayerCharacter pc, Target target, int numRolls) throw(invalid_argument)
{
    if (numRolls <= 0)
    {
        throw invalid_argument("Simulation numRolls must be greater than zero");
    }

    SimulationStats stats{numRolls};
    RollResult roll;
    DegreeOfSuccess DoS;

    for (int i = 0; i < numRolls; i++)
    {
        roll = pc.rollToHit();
        DoS = target.compareAttackRoll(roll);

        switch (DoS)
        {
        case critFailure:
            stats.critFailures++;
            break;
        case failure:
            stats.failures++;
            break;
        case success:
            stats.successes++;
            stats.totalDamage += pc.rollDamage(false);
            break;
        case critSuccess:
            stats.critSuccesses++;
            stats.totalDamage += pc.rollDamage(true);
            break;
        }
    }

    return stats;
}

// Run a series of simulations to gather additional stats and prints results,
// simulations must be a positive, non-zero integer to print .
void runSimulationSeries(PlayerCharacter pc, Target target, int iterationsPerBonus, int simulations)
{
    SimulationStats currStats;
    double initAvgAtmpDmg = 0;
    double prevAvgAtmpDmg;
    double currAvgAtmpDmg;

    // Print Header
    cout << "\nStarting Series with parameters: \n";
    cout << "toHit: " << pc.getToHit()
         << ", dieSize: " << pc.getDieSize()
         << ", numDie: " << pc.getNumDie()
         << ", damageBonus: " << pc.getDamageBonus() << "\n"
         << "Target ac: " << target.getAc() << "\n"
         << "numRolls: " << iterationsPerBonus << "\n"
         << "simulations: " << simulations << "\n\n";

    // Run each simulation, increasing the player's toHit bonus by 1 each time
    for (int i = 0; i < simulations; i++)
    {
        cout << "---- Simulation " << i << " ----\n";
        cout << "Bonus: " << pc.getToHit() << "\n";

        // Generate basic stats
        currStats = runSimulation(pc, target, iterationsPerBonus);
        printSimulationResults(currStats);

        currAvgAtmpDmg = averageAttemptedDamage(currStats);

        if (i != 0)
        {
            // Calculate and print percent increases
            cout << "\nPercent increase in damage for attempted attacks over previous: "
                 << percentChange(currAvgAtmpDmg, prevAvgAtmpDmg) << "%\n";
            cout << "Percent increase in damage for attempted attacks overall: "
                 << percentChange(currAvgAtmpDmg, initAvgAtmpDmg) << "%\n";
        }
        else
        {
            initAvgAtmpDmg = currAvgAtmpDmg;
        }
        cout << "\n\n";

        prevAvgAtmpDmg = currAvgAtmpDmg;
        pc.incrementToHit();
    }
}

int main()
{
    const char *OUTPUT_FILE = "io/output.txt";
    const char *INPUT_FILE = "io/input.txt";
    const int DEFAULT_ITERATIONS = 100000;
    const int DEFAULT_SIMULATIONS = 5;

    int numRolls = DEFAULT_ITERATIONS;
    int simulations = DEFAULT_SIMULATIONS;
    PlayerCharacter pc;
    Target target;
    SeriesParams params;

    cout << "Would you like file output? (this is best unless running from console)\n";
    if (inputYesOrNo()) {
        // redirect std output to file
        freopen(OUTPUT_FILE, "w", stdout);
    }

    try
    {
        params = parseInputFile(INPUT_FILE);
        pc = params.pc;
        target = params.target;

        // Check if rolls and simulations were specified in input file
        if (params.rollsPerSimulation != -1)
        {
            numRolls = params.rollsPerSimulation;
        }
        if (params.numOfSimulations != -1)
        {
            simulations = params.numOfSimulations;
        }

        // seed random number generation with time
        srand((unsigned)time(NULL));

        runSimulationSeries(pc, target, numRolls, simulations);
    }
    catch (const invalid_argument &e)
    {
        cout << "File error: " << e.what() << "\n";
    }
}