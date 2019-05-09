#include <iostream>
#include "console.h"

using namespace std;

// Jackie Chan
// Written during February 7 - 9, 2019

// Purpose: This program utilizes object-oriented programming (OOP) to
// develop simple classes (ColorClass, RowColumnClass, and ColorImageClass
// that represent the basis of colors and images. While there contains no
// user interaction in this program itself, it will serve as the foundation
// for future projects.


//////// Constant Declarations ////////
const int FULL_COLOR = 1000;
const int NO_COLOR = 0;
const int DEFAULT_ROW_COL_VAL = -99999;
const int ARRAY_ROWS = 10;
const int ARRAY_COLS = 18;


//////// Class Definitions ////////

// The ColorClass contains the red, green, blue (RGB) values that define a
// particular color. With varying RGB amounts, you can create any color.
// For example, bright red is represented by the full amount of red (1000
// for this project) and no amount of green or blue (0 for this project).
// Special colors such as black is created with no red, no green, and no
// blue components, whereas white is created with full amounts of each.
// Essentially, each RGB value can range from 0-1000. If RGB values are
// declared outside of this range, they are clipped or rounded to the
// nearest bound (i.e. 0 if negative or 1000 if greater than 1000).
class ColorClass
{
    private:
        int red;
        int green;
        int blue;

        // This helper function checks whether each of the RGB values are
        // within 0-1000. It returns true if it is within the bounds and
        // false otherwise.
        bool isInRange(int rgb);

        // Accepts an RGB value and clips the value (if necessary) such
        // that it is within bounds and returns it.
        int evaluateColor(int rgb);

    public:
        // Explicit default constructor sets the default color to white.
        ColorClass();

        // Value constructor initializes color to have the RGB values passed
        // in by the given parameters.
        ColorClass(int inRed, int inGreen, int inBlue);


        void setToBlack();
        void setToRed();
        void setToGreen();
        void setToBlue();
        void setToWhite();

        // Sets the color to have the RGB values from inRed, inGreen,
        // and inBlue, respectively. Returns true if any clipping was
        // performed and false otherwise.
        bool setTo(int inRed, int inGreen, int inBlue);

        // Similar to the setTo method above and sets the color's RGB values
        // to those in the inColor parameter.
        bool setTo(ColorClass &inColor);

        // Adds rhs's RGB values to the color's and performs clipping such
        // that the values are kept within the valid range. Returns true if
        // clipping was necessary and false otherwise.
        bool addColor(ColorClass &rhs);

        // Similar to the addColor method but rhs's RGB values are subtracted
        // from the color's instead.
        bool subtractColor(ColorClass &rhs);

        // Each of the color's RGB values are scaled by adjFactor and clipped
        // if necessary.
        bool adjustBrightness(double adjFactor);
        void printComponentValues();
};

// The RowColumnClass helps to uniquely identify a specific pixel within an
// image with a row and column value.
class RowColumnClass
{
    private:
        int row;
        int col;

    public:
        RowColumnClass();

        // Sets the row and column values to the corresponding values passed
        // into the constructor.
        RowColumnClass(int inRow, int inCol);

        // Setter functions that directly set the appropriate attribute(s)
        // to the value(s) provided.
        void setRowCol(int inRow, int inCol);
        void setRow(int inRow);
        void setCol(int inCol);

        // Getter functions that simply return the appropriate attribute
        // values.
        int getRow();
        int getCol();

        // Adds the row and column index values in the inRowCol parameter
        // to the row and column index of the object.
        void addRowColTo(RowColumnClass &inRowCol);
        void printRowCol();
};

// An image is simply a collection of color pixels arranged in a rectangle.
// The ColorImageClass represents a small image as a 2D array of ColorClass
// objects composed of some number of rows and columns.
class ColorImageClass
{
    private:
        ColorClass image[ARRAY_ROWS][ARRAY_COLS];

        // Helper function returns true if the location specified by the row
        // and column attributes of the parameter is contained within the
        // image itself; it returns false otherwise.
        bool isValidLocation(RowColumnClass &inRowCol);

    public:
        // Default constructor sets all the pixels in the image to black.
        ColorImageClass();

        // Initializes all image pixels to the color inputted.
        void initializeTo(ColorClass &inColor);

        // Performs pixel-wise addition such that each pixel in the image
        // has the pixel in the corresponding location in rhsImg added to
        // it. If any of the color values require clipping, the function
        // returns true and false otherwise.
        bool addImageTo(ColorImageClass &rhsImg);

        // Similar to the addImageTo method, but assigns the sum of the
        // corresponding pixels in each image in the imagesToAdd array to
        // each of the image's pixel values. If any of the pixel additions
        // require color value clipping, it returns true.
        bool addImages(int numImgsToAdd, ColorImageClass imagesToAdd []);

        // Sets the pixel at the location specified by inRowCol to the color
        // specified by the inColor parameter. If the location is a valid
        // location for the image, the pixel value is modified and the
        // function returns true. Otherwise, it returns false;
        bool setColorAtLocation(RowColumnClass &inRowCol,
                                ColorClass &inColor);

        // If the row and column values in inRowCol specify a valid location,
        // outColor is set to the pixel at that location and returns true.
        bool getColorAtLocation(RowColumnClass &inRowCol,
                                ColorClass &outColor);
        // Prints the contents of the image (RGB values of each pixel) onto
        // the console.
        void printImage();
};

#ifdef ANDREW_TEST
#include "andrewTest.h"
#else

int main()
{
     /* Test ColorClass */
    bool clippedOrNah;
    ColorClass color1;
    ColorClass color2(1, -1, 1);
    ColorClass temp;

    cout << "Let's create some values." << endl;
    cout << "Color 1 has values: ";
    color1.printComponentValues();
    cout << endl;
    cout << "Expected: R: 1000 G: 1000 B:1000" << endl;
    cout << "Color 2 has values: ";
    color2.printComponentValues();
    cout << endl;
    cout << "Expected: R: 1 G: 0 B: 1" << endl;
    cout << "Temp has values: ";
    temp.printComponentValues();
    cout << endl;
    cout << "Expected: R: 1000 G: 1000 B: 1000" << endl;
    cout << endl;

    cout << "Gonna modify Color 1 real quick." << endl;
    for(int i = 0; i < 5; i++)
    {
        color1.subtractColor(color2);
    }
    cout << "Color 1 has values: ";
    color1.printComponentValues();
    cout << endl;
    cout << "Expected: R: 995 G: 1000 B: 995" << endl;
    cout << endl;


    clippedOrNah = color1.setTo(909, 32, -32);
    cout << "Color 1 has values: ";
    color1.printComponentValues();
    cout << endl;
    cout << "Expected R: 909 G: 32 B: 0";
    cout << " and was clipped (1): " << clippedOrNah << endl;
    temp = color2;
    cout << "Temp has values: ";
    temp.printComponentValues();
    cout << endl;
    cout << "Expected: R: 1 G: 0 B: 1" << endl;
    color2.setTo(color1);
    cout << "Color 2 has values: ";
    color2.printComponentValues();
    cout << endl;
    cout << "Expected: R: 909 G: 32 B: 0" << endl;
    color1.addColor(temp);
    cout << "After adding Temp, Color 1 has values: ";
    color1.printComponentValues();
    cout << endl;
    cout << "Expected R: 910 G: 32 B: 1" << endl;
    cout << endl;

    cout << "Let's adjust the brightness!" << endl;
    clippedOrNah = color2.adjustBrightness(1.1);
    cout << "Color 2 now has values: ";
    color2.printComponentValues();
    cout << " and was not clipped (0): " << clippedOrNah << endl;
    cout << "Expected: R: 999 G: 35 B: 0" << endl;
    clippedOrNah = color1.adjustBrightness(1.1);
    cout << "Color 1 now has values: ";
    color1.printComponentValues();
    cout << " and was clipped (1): " << clippedOrNah << endl;
    cout << "Expected: R: 1000 G: 35 B: 1" << endl;
    cout << endl;

    /* Test RowColumnClass */
    RowColumnClass RC1;
    RowColumnClass RC2(-420, 420);
    cout << "Let's test the RowColumnClass" << endl;
    cout << "RC1 has row and columns: ";
    RC1.printRowCol();
    cout << endl;
    cout << "Expected: [-99999,-99999]" << endl;
    cout << "RC2 has row and columns: ";
    RC2.printRowCol();
    cout << endl;
    cout << "Expected: [-420,420]" << endl;
    RC1.setRowCol(-10,0);
    cout << "RC1 has row and columns: ";
    RC1.printRowCol();
    cout << endl;
    cout << "Expected: [-10,0]" << endl;
    cout << "Let's test the getter functions." << endl;
    int row = RC1.getRow();
    cout << "RC1 has -10 rows? " << row << endl;
    int col = RC1.getCol();
    cout << "RC1 has 0 cols? " << col << endl;
    cout << endl;

    /* Test ColorImageClass */
    ColorImageClass allBlack, allWhite;
    ColorClass white;
    ColorImageClass images[1];

    cout << "We're gonna create an allBlack and allWhite "
            "image and add them together." << endl;
    bool isBlack = true;
    cout << "Let's check that allBlack is all black." << endl;
    for(int i = 0; i < ARRAY_ROWS; i++)
    {
        for(int j = 0; j < ARRAY_COLS; j++)
        {
            RC1.setRowCol(i, j);
            if(!allBlack.getColorAtLocation(RC1, color1))
            {
                if(color1.subtractColor(temp))
                {
                    // color 1 was clipped and image should still be black
                    isBlack = false;
                }
            }
        }
    }
    cout << "Running for loop...allBlack was all black (1): " << isBlack << endl;
    cout << endl;
    cout << "Let's now make a white image and add the black image to it." << endl;
    allWhite.initializeTo(white);
    images[0] = allWhite;
    clippedOrNah = allBlack.addImages(1, images);
    cout << "There should be no clipping: " << clippedOrNah << endl;
    cout << "This should be a white image." << endl;
    cout << endl;
    allBlack.printImage();
    cout << endl;

    return 0;
}

#endif

//////// ColorClass Constructors and Member Functions ////////
ColorClass::ColorClass()
{
    red = FULL_COLOR;
    green = FULL_COLOR;
    blue = FULL_COLOR;
}

ColorClass::ColorClass(int inRed, int inGreen, int inBlue)
{
    setTo(inRed, inGreen, inBlue);
}

void ColorClass::setToBlack()
{
    red = NO_COLOR;
    green = NO_COLOR;
    blue = NO_COLOR;
}

void ColorClass::setToRed()
{
    red = FULL_COLOR;
    green = NO_COLOR;
    blue = NO_COLOR;
}

void ColorClass::setToGreen()
{
    red = NO_COLOR;
    green = FULL_COLOR;
    blue = NO_COLOR;
}

void ColorClass::setToBlue()
{
    red = NO_COLOR;
    green = NO_COLOR;
    blue = FULL_COLOR;
}

void ColorClass::setToWhite()
{
    red = FULL_COLOR;
    green = FULL_COLOR;
    blue = FULL_COLOR;
}

bool ColorClass::setTo(int inRed, int inGreen, int inBlue)
{
    ColorClass rgbPkg;

    rgbPkg.red = inRed;
    rgbPkg.green = inGreen;
    rgbPkg.blue = inBlue;
    return setTo(rgbPkg);
}

bool ColorClass::setTo(ColorClass &inColor)
{
    bool isClipped = false;

    if(!isInRange(inColor.red) || !isInRange(inColor.green) ||
       !isInRange(inColor.blue))
    {
        isClipped = !isClipped;
    }
    red = evaluateColor(inColor.red);
    green = evaluateColor(inColor.green);
    blue = evaluateColor(inColor.blue);
    return isClipped;
}

bool ColorClass::addColor(ColorClass &rhs)
{
    ColorClass rgbPkg;

    rgbPkg.red = red + rhs.red;
    rgbPkg.green = green + rhs.green;
    rgbPkg.blue = blue + rhs.blue;
    return setTo(rgbPkg);
}

bool ColorClass::subtractColor(ColorClass &rhs)
{
    ColorClass rgbPkg;

    rgbPkg.red = red - rhs.red;
    rgbPkg.green = green - rhs.green;
    rgbPkg.blue = blue - rhs.blue;
    return setTo(rgbPkg);
}

bool ColorClass::adjustBrightness(double adjFactor)
{
    ColorClass rgbPkg;

    rgbPkg.red = (int)(adjFactor * red);
    rgbPkg.green = (int)(adjFactor * green);
    rgbPkg.blue = (int)(adjFactor * blue);
    return setTo(rgbPkg);
}

void ColorClass::printComponentValues()
{
    cout << "R: " << red << " G: " << green << " B: " << blue;
}

///////// Helper Functions for ColorClass ////////
bool ColorClass::isInRange(int rgb)
{
    bool isWithin = true;

    if(rgb > FULL_COLOR || rgb < NO_COLOR)
    {
        isWithin = !isWithin;
    }
    return isWithin;
}

int ColorClass::evaluateColor(int rgb)
{
    int resultColor = rgb;

    if(rgb < NO_COLOR)
    {
        resultColor = NO_COLOR;
    }
    else if(rgb > FULL_COLOR)
    {
        resultColor = FULL_COLOR;
    }
    return resultColor;
}


//////// RowColumnClass Constructors and Member Functions ////////
RowColumnClass::RowColumnClass()
{
    row = DEFAULT_ROW_COL_VAL;
    col = DEFAULT_ROW_COL_VAL;
}

RowColumnClass::RowColumnClass(int inRow, int inCol)
{
    row = inRow;
    col = inCol;
}

void RowColumnClass::setRowCol(int inRow, int inCol)
{
    setRow(inRow);
    setCol(inCol);
}

void RowColumnClass::setRow(int inRow)
{
    row = inRow;
}

void RowColumnClass::setCol(int inCol)
{
    col = inCol;
}

int RowColumnClass::getRow()
{
    return row;
}

int RowColumnClass::getCol()
{
    return col;
}

void RowColumnClass::addRowColTo(RowColumnClass &inRowCol)
{
    row += inRowCol.row;
    col += inRowCol.col;
}

void RowColumnClass::printRowCol()
{
    cout << "[" << row << "," << col << "]";
}


//////// ColorImageClass Constructor and Member Functions ////////
ColorImageClass::ColorImageClass()
{
    for(int i = 0; i < ARRAY_ROWS; i++)
    {
        for(int j = 0; j < ARRAY_COLS; j++)
        {
            image[i][j].setToBlack();
        }
    }
}

void ColorImageClass::initializeTo(ColorClass &inColor)
{
    for(int i = 0; i < ARRAY_ROWS; i++)
    {
        for(int j = 0; j < ARRAY_COLS; j++)
        {
            image[i][j].setTo(inColor);
        }
    }
}

bool ColorImageClass::addImageTo(ColorImageClass &rhsImg)
{
    bool isPixelClipped = false;
    bool isColorClipped;

    for(int i = 0; i < ARRAY_ROWS; i++)
    {
        for(int j = 0; j < ARRAY_COLS; j++)
        {
            isColorClipped = image[i][j].addColor(rhsImg.image[i][j]);

            if(isColorClipped)
            {
                isPixelClipped = true; // will always stay true once true
            }
        }
    }
    return isPixelClipped;
}

bool ColorImageClass::addImages(int numImgsToAdd,
                                ColorImageClass imagesToAdd [])
{
    bool isPixelClipped = false;
    ColorClass black;
    black.setToBlack();
    initializeTo(black); // creates black image

    for(int i = 0; i < numImgsToAdd; i++)
    {
        if(addImageTo(imagesToAdd[i]))
        {
            isPixelClipped = true;
        }
    }
    return isPixelClipped;
}

bool ColorImageClass::setColorAtLocation(RowColumnClass &inRowCol,
                                         ColorClass &inColor)
{
    if(isValidLocation(inRowCol))
    {
        image[inRowCol.getRow()][inRowCol.getCol()] = inColor;
    }
    return isValidLocation(inRowCol);
}

bool ColorImageClass::getColorAtLocation(RowColumnClass &inRowCol,
                                         ColorClass &outColor)
{
    if(isValidLocation(inRowCol))
    {
        outColor = image[inRowCol.getRow()][inRowCol.getCol()];
    }
    return isValidLocation(inRowCol);
}

void ColorImageClass::printImage()
{
    for(int i = 0; i < ARRAY_ROWS; i++)
    {
        for(int j = 0; j < ARRAY_COLS; j++)
        {
            image[i][j].printComponentValues();

            if(j < ARRAY_COLS - 1)
            {
                cout << "--";
            }
            else{ // at end of row
                cout << endl;
            }
        }
    }
}

//////// ColorImageClass Helper Functions ////////
bool ColorImageClass::isValidLocation(RowColumnClass &inRowCol)
{
    bool isValid = false;

    if(inRowCol.getRow() >= 0 && inRowCol.getRow() < ARRAY_ROWS &&
       inRowCol.getCol() >= 0 && inRowCol.getCol() < ARRAY_COLS)
    {
        isValid = !isValid;
    }
    return isValid;
}

