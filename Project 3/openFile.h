#ifndef _OPENFILE_H_
#define _OPENFILE_H_

#include <iostream>
#include <fstream>
using namespace std;

/*
This global function checks the command line arguments and attempts to
open the PPM file passed in. If the file cannot be opened or if there
are not enough arguments, an error is output to the console and the
program will exit.
*/
void openFile(int argc, char* argv[], int &errorType, ifstream &inFile);

#endif