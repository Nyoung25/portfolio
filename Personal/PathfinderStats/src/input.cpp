#include <iostream>
#include <fstream>
#include <regex>
#include "input.h"
#include "exceptions.h"

using namespace std;

bool isValidDieSize(int i)
{
    switch (i)
    {
    case 4:
    case 6:
    case 8:
    case 10:
    case 12:
        return true;

    default:
        return false;
    }
}

bool inputYesOrNo() {
    string response;
    regex yesResponse ("y|Y|yes|Yes");
    regex noResponse ("n|N|no|No");

    while (true) {
        cout << "type 'y' or 'n' to respond: ";
        cin >> response;

        if (regex_match(response, yesResponse)) {
            return true;
        } else if (regex_match(response, noResponse)) {
            return false;
        } else {
            cout << "\"" << response << "\" is not valid, please respond 'y' or 'n'";
        }
    }
}

// Attempts to parse the string as a series of statistics for a PlayerCharacter.
//
// Throws a BadFormatException when the statistics do not match the expected format.
// Throws an InvalidDataException when the statstics match the format, but are not valid values.
PlayerCharacter parsePlayerLine(string values) throw(BadFormatException, InvalidDataException)
{
    int toHit;
    int dieSize;
    int numDie;
    int damageBonus;

    smatch matches;
    regex expr(" *(toHit=([0-9]+)); *(dieSize=([0-9]+)); *(numDie=([0-9]+)); *(damageBonus=([0-9]+));");

    if (regex_match(values, matches, expr))
    {
        try
        {
            toHit = stoi(matches[2]);
            dieSize = stoi(matches[4]);
            numDie = stoi(matches[6]);
            damageBonus = stoi(matches[8]);

            if (!isValidDieSize(dieSize))
            {
                throw InvalidDataException("Die size \"" + string(matches[4]) 
                    + "\" is invalid, valid die sizes are: 4, 6, 8, 10, 12\n");
            }
            if (numDie <= 0)
            {
                throw InvalidDataException("Number of dice \"" + string(matches[6]) 
                    + "\" is invalid, numDice must be a positive, non-zero integer.\n");
            }
        }
        catch (const out_of_range &e)
        {
            throw InvalidDataException(
                "At least one of the PlayerCharacter's statistics is too large to fit in an int\n toHit= " 
                + string(matches[2]) + " dieSize=" + string(matches[4]) 
                + " numDie=" + string(matches[6]) + " damageBonus=" + string(matches[8]) 
                + "\nsize of an int on this machine: " + to_string(sizeof(int)) + " bytes\n"
                );
        }
    }
    else
    {
        throw BadFormatException("Values don't match expected format\n");
    }

    return PlayerCharacter(toHit, dieSize, numDie, damageBonus);
}

// Attempts to parse the string as a series of statistics for a Target.
//
// Throws a BadFormatException when the statistics do not match the expected format.
// Throws an InvalidDataException if the value provided is too large to fit in an int.
Target parseTargetLine(string values) throw(BadFormatException, InvalidDataException)
{
    int ac;
    smatch matches;
    regex expr(" *(ac=([0-9]+));");

    try
    {
        if (regex_match(values, matches, expr))
        {
            ac = stoi(matches[2]);
        }
        else
        {
            throw BadFormatException("Target: {" + values + "}\n");
        }
    }
    catch (const out_of_range &e)
    {
        throw InvalidDataException("Target ac \"" + string(matches[2]) 
            + "\" is too large to fit in an int\n Size of an int on this machine: " 
            + to_string(sizeof(int)) + " bytes\n"
            );
    }

    return Target(ac);
}

// Attempt to parse the string into an integer value.
//
// Throws a BadFormatException if value is not an integer.
// Throws an InvalidDataException if the value is too large to fit in an int.
int parseIntValue(string value) throw(BadFormatException, InvalidDataException)
{
    int result;

    try
    {
        result = stoi(value);
    }
    catch (const invalid_argument &e)
    {
        // Throw BadFormatException instead of InvalidDataException to follow
        // convention established in parsePlayerLine and parseTargetLine
        throw BadFormatException("Value \"" + value + "\" is not an integer");
    }
    catch (const out_of_range &e)
    {
        throw InvalidDataException("Value \"" + value 
            + "\" is too large to fit in an int\n Size of an int on this machine: " 
            + to_string(sizeof(int)) + " bytes\n"
            );
    }
    return result;
}

SeriesParams parseInputFile(string filename) throw(invalid_argument)
{
    int tempValue = 0;
    bool validPlayer = false;
    bool validTarget = false;
    SeriesParams params;
    ifstream file;
    string line;
    smatch matches;
    regex playerLine("PlayerCharacter: *\\{(.*)\\}");
    regex targetLine("Target: *\\{(.*)\\}");
    regex iterationsLine("rolls: *\\{(.*)\\}");
    regex simulationsLine("simulations: *\\{(.*)\\}");

    file.open(filename);

    if (file.is_open())
    {
        while (getline(file, line))
        {
            // Attempt to parse each line sequentially, ignoring invalid lines.
            try
            {
                // Attempt to match each line with a particular line header,
                // then parses it and assigns to the respective parameter.
                if (regex_match(line, matches, playerLine))
                {
                    params.pc = parsePlayerLine(matches[1]);
                    // will not trigger if exception is thrown by above
                    validPlayer = true;
                }
                else if (regex_match(line, matches, targetLine))
                {
                    params.target = parseTargetLine(matches[1]);
                    // will not trigger if exception is thrown by above
                    validTarget = true;
                }
                else if (regex_match(line, matches, iterationsLine))
                {
                    tempValue = parseIntValue(matches[1]);
                    if (tempValue > 0)
                    {
                        params.rollsPerSimulation = tempValue;
                    }
                    else
                    {
                        throw InvalidDataException(
                            "Simulation iterations must be positive and non-zero\n"
                            );
                    }
                }
                else if (regex_match(line, matches, simulationsLine))
                {
                    tempValue = parseIntValue(matches[1]);
                    if (tempValue > 0)
                    {
                        params.numOfSimulations = tempValue;
                    }
                    else
                    {
                        throw InvalidDataException(
                            "Number of simulations must be positive and non-zero\n"
                            );
                    }
                }
                else
                {
                    throw BadFormatException(
                        "Line start doesn't match any known input type\n"
                        );
                }
            }
            catch (ParsingException e)
            {
                cout << "Skipping line \"" << line 
                    << "\" in file \"" << filename << "\" because:\n";
                cout << e.what();
            }
        }
    }
    else
    {
        throw invalid_argument("File \"" + filename + "\" could not be opened.\n");
    }

    // Check the data we've parsed
    if (!validPlayer || !validTarget)
    {
        // We need a user-defined Target and PlayerCharacter for the simulation
        throw invalid_argument("File \"" + filename 
            + "\" does not contain a valid Target and PlayerCharacter");
    }
    // Notify user if defaults are being used for rolls and simulations
    if (params.rollsPerSimulation == -1)
    {
        cout << "Couldn't find iterations in the file, using default\n";
    }
    if (params.numOfSimulations == -1)
    {
        cout << "Couldn't find number of simulations in the file, using default\n";
    }

    return params;
}