#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include "constants.h"
#include "trimLine.h"
#include "openFile.h"
#include "ColorClass.h"
#include "MessageClass.h"
#include "RowColumnClass.h"
#include "ColorImageClass.h"
#include "MenuClass.h"

using namespace std;

/* 
Jackie Chan
Written during March 16 - 23, 2019

Purpose: This program utilizes file input/output and OOP to implement
steganography, the art of hiding information in the midst of unsuspicious
data, in digital images. More specifically, the user will be able to encode
and decode secret messages into an image, such that the modified image could
 be sent to an acquaintance or distributed publicly, and would likely only 
 be decoded by someone who knows it contains a hidden message.
*/

int main(int argc, char* argv[])
{
    ifstream inFile;
    int errorType = NO_ERROR;

    openFile(argc, argv, errorType, inFile);

    if(errorType != NO_ERROR)
    {
        exit(errorType);
    }

    ColorImageClass image(inFile);
    inFile.close();

    if(!image.isProperImage())
    {
        exit(FILE_READ_ERROR);
    }
    MenuClass menu(image);
    return 0;
}





