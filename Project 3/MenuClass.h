#ifndef _MENUCLASS_H_
#define _MENUCLASS_H_

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include "constants.h"
#include "ColorImageClass.h"
#include "trimLine.h"
using namespace std;


// After reading in the image, this class displays the list of user choices
// which includes encoding, decoding, or writing the image to a file.	
class MenuClass
{
    private:
        int menuOption;
        bool validInputFound;

    public:
        /* 
        When the constructor is called, the member functions are called
        accordingly. It displays the menu options to the user, prompts
        the user for input, and performs one of actions below. The encode
        option encodes the image passed in with a message file that the
        user provides. The decode option decodes the current image, and the
        write to file option exports the image to the file provided by the
        user.
        */
        MenuClass(ColorImageClass &image);
        void displayMenu();
        void getMenuOption();
        void encodeOption(ColorImageClass &image);
        void decodeOption(ColorImageClass &image);
        void writeToFileOption(ColorImageClass &image);
};


#endif