#include <cstring>
#include "exceptions.h"

char *ParsingException::what()
{
    const int length = message.length();
    char *result = new char[length + 1];

    std::strcpy(result, message.c_str());

    return result;
}