#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <exception>
#include <string>

// Errors thrown during parsing
class ParsingException : public std::exception
{
protected:
    // Message to be printed when calling what()
    std::string message;

public:
    ParsingException(std::string message) : message(message){};

    char *what();
};

// Thrown to indicate invalid data when parsing
class InvalidDataException : public ParsingException
{
public:
    InvalidDataException(std::string message) : ParsingException(message){};

    char *what();
};

// Thrown to indicate that the input file is improperly formatted when parsing
class BadFormatException : public ParsingException
{
public:
    BadFormatException(std::string message) : ParsingException(message){};

    char *what();
};

#endif