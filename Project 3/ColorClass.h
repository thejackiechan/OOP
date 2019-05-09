#ifndef _COLORCLASS_H_
#define _COLORCLASS_H_

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "constants.h"
using namespace std;


/*  
The ColorClass contains the red, green, blue (RGB) values that define a
particular color. With varying RGB amounts, you can create any color.
For example, bright red is represented by the full amount of red (1000
for this project) and no amount of green or blue (0 for this project).
Special colors such as black is created with no red, no green, and no
blue components, whereas white is created with full amounts of each.
Essentially, each RGB value can range from 0-255. If RGB values are
declared outside of this range, they are clipped or rounded to the
nearest bound (i.e. 0 if negative or 255 if greater than 255).
*/
class ColorClass
{
    private:
        int red;
        int green;
        int blue;
        bool isProperlyInitialized;

        // These functions change the RGB values slightly to encode various
        // colors.
        void encodeBlack();
        void encodeRed();
        void encodeGreen();
        void encodeBlue();
        void encodeWhite();
        void encodeYellow();
        void encodeMagenta();
        void encodeCyan();
	    
        // This helper function checks whether each of the RGB values are
        // within 0-255. It returns true if it is within the bounds and
        // false otherwise.
        bool isInRange(int rgb);
	    
        // Accepts an RGB value and clips the value (if necessary) such
        // that it is within bounds and returns it.
        int evaluateColor(int rgb);

        string evalOddEven(int rgb);
	    
        void printErrorMsg();
    
    public:
        // Explicit default constructor sets the default color to white.
        ColorClass();

        void setToBlack();
        void setToRed();
        void setToGreen();
        void setToBlue();
        void setToWhite();
	    
        // Getter function that returns isProperlyInitialized.
        bool isInitialized();

        // Sets the RGB values using the input stringstream buffer.
        void setTo(istringstream &iss);
	    
        // Sets the color to have the RGB values from inRed, inGreen,
        // and inBlue, respectively. Returns true if any clipping was
        // performed and false otherwise.
        bool setTo(int inRed, int inGreen, int inBlue);
	    
        // Similar to the setTo method above and sets the color's RGB values
        // to those in the inColor parameter.
        bool setTo(ColorClass &inColor);

        // Alters the RGB values to either no color or the full amount.
        void decodePixel(); 

        // Calls the encode function for a specific color based on encVal.
        void encodePixel(int encVal);
	    
        // Writes the RGB values to a file.
        void printComponentValues(ofstream &outFile);
};


#endif