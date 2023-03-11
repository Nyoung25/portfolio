#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H
#include "types.h"

// Represents a player character with the ability to make attacks and roll damage.
class PlayerCharacter
{
private:
    // Added to 20-sided die rolls to determine if the player hits.
    int toHit;
    // The number of sides on the player's damage dice.
    // Valid sizes are 4, 6, 8, 10, and 12.
    int dieSize;
    // The number of damage dice to roll if an attack hits.
    int numDie;
    // A flat bonus to the player's damage, added once after all dice are rolled.
    int damageBonus;

public:
    PlayerCharacter(int toHit, int dieSize, int numDie, int damageBonus);
    PlayerCharacter();

    // Simulates a 20-sided die roll for an attack, returns the numeric result
    // and whether it was a special case roll (a natural 20 or a natural 1) 
    RollResult rollToHit();

    // Rolls the damage for an attack, doubling the damage on a critical success
    int rollDamage(bool isCritSuccess);

    // Increase the toHit bonus by 1
    void incrementToHit();

    int getToHit();
    int getDieSize();
    int getNumDie();
    int getDamageBonus();
};
#endif