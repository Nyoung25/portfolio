#include <iostream>
#include "playercharacter.h"

PlayerCharacter::PlayerCharacter(int toHit, int dieSize, int numDie, int damageBonus)
    : toHit(toHit), dieSize(dieSize), numDie(numDie), damageBonus(damageBonus) {}

PlayerCharacter::PlayerCharacter()
    : toHit(0), dieSize(0), numDie(0), damageBonus(0) {}

RollResult PlayerCharacter::rollToHit()
{
    int naturalRoll = 1 + (rand() % 20);
    int totalRoll = naturalRoll + toHit;

    DegreeOfSuccessMod Dosm = normal;
    // Note if this is a special case roll
    if (naturalRoll == 20)
    {
        Dosm = nat20;
    }
    else if (naturalRoll == 1)
    {
        Dosm = nat1;
    }

    return {totalRoll, Dosm};
}

int PlayerCharacter::rollDamage(bool isCritSuccess)
{
    int damage = 0;

    // simulate each damage dice rolling
    for (int i = 0; i < numDie; i++)
    {
        damage += 1 + (rand() % (dieSize - 1));
    }

    damage += damageBonus;

    if (isCritSuccess)
    {
        damage *= 2;
    }

    return damage;
}

void PlayerCharacter::incrementToHit()
{
    toHit++;
}

int PlayerCharacter::getToHit()
{
    return toHit;
}

int PlayerCharacter::getDieSize()
{
    return dieSize;
}

int PlayerCharacter::getNumDie()
{
    return numDie;
}

int PlayerCharacter::getDamageBonus()
{
    return damageBonus;
}