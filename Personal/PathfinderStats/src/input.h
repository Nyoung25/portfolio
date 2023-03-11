#ifndef INPUT_H
#define INPUT_H

#include "types.h"
#include "playercharacter.h"
#include "target.h"

// Parameters for series simulation, integers are initialized to a
// sentinel value of -1 by default.
struct SeriesParams
{
    PlayerCharacter pc;
    Target target;
    int rollsPerSimulation = -1;
    int numOfSimulations = -1;
};

// Ask the user to respond yes or no, returns true if they respond yes
// and false if they respond no. Loops until the user provides a valid response.
bool inputYesOrNo();

// Returns true if the integer is a valid damage die size (4, 6, 8, 10, or 12)
// and false otherwise.
bool isValidDieSize(int i);

// Attempts to parse the file with path 'filename' and returns parameters for
// a simulation series if the file is valid.
//
// If the number of rolls per simulation and/or the number of simulations is
// not validly specified in the file, they will remain the default value of -1.
//
// If the file contains no valid PlayerCharacter or Target, throws invalid argument.
// Also throws invalid argument if the file could not be opened.
SeriesParams parseInputFile(std::string filename) throw(std::invalid_argument);

#endif