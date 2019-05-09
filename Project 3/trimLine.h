#ifndef _TRIMLINE_H_
#define _TRIMLINE_H_

#include <string>
using namespace std;

/*
This global function is used extensively for error checking to trim any
whitespace at the end of a line/string. This is motivated by the fact that
eof() will return false if there is whitespace at the end of a line even if
there are no more values to be read.
*/
void trimLine(string &line);

#endif

