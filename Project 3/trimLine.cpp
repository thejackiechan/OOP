#include "trimLine.h"
#include "constants.h"

void trimLine(string &line)
{
    while(line[line.length() - 1] == SPACE_CHAR)
    {
        line = line.substr(START_POSITION, line.length() - 1);
    }
}