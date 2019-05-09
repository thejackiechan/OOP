#include "ColorClass.h"
#include "constants.h"


//////// ColorClass Constructors and Member Functions ////////
ColorClass::ColorClass()
{
    red = FULL_COLOR;
    green = FULL_COLOR;
    blue = FULL_COLOR;  
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

bool ColorClass::isInitialized()
{
    return isProperlyInitialized;
}

void ColorClass::setTo(istringstream &iss)
{
    iss >> red >> green >> blue;
    
    if(iss.fail() || setTo(red, green, blue))
    {
        isProperlyInitialized = false;
        printErrorMsg();
    }
    else
    {
        isProperlyInitialized = true;
    }
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

void ColorClass::decodePixel() 
{
    string redResult = evalOddEven(red);
    string greenResult = evalOddEven(green);
    string blueResult = evalOddEven(blue);
    string result = redResult + greenResult + blueResult;

    if(result == BLACK_ENC_SEQ)
    {
        setToBlack();
    }
    else if(result == RED_ENC_SEQ)
    {
        setToRed();
    }
    else if(result == GREEN_ENC_SEQ)
    {
        setToGreen();
    }
    else if(result == BLUE_ENC_SEQ)
    {
        setToBlue();
    }
    else 
    {
        setToWhite();

        if(result == YELLOW_ENC_SEQ)
        {
            blue = NO_COLOR;
        }
        else if(result == MAGENTA_ENC_SEQ)
        {
            green = NO_COLOR;
        }
        else if(result == CYAN_ENC_SEQ)
        { 
            red = NO_COLOR;
        }
    }
}

void ColorClass::encodePixel(int encVal)
{
    if(encVal == ENC_BLACK_OPTION)
    {
        encodeBlack();
    }
    else if(encVal == ENC_RED_OPTION)
    {
        encodeRed();
    }
    else if(encVal == ENC_GREEN_OPTION)
    {
        encodeGreen();
    }   
    else if(encVal == ENC_BLUE_OPTION)
    {
        encodeBlue();
    }
    else if(encVal == ENC_WHITE_OPTION)
    {
        encodeWhite();
    }   
    else if(encVal == ENC_YELLOW_OPTION)
    {
        encodeYellow();
    }
    else if(encVal == ENC_MAGENTA_OPTION)
    {
        encodeMagenta();
    }
    else
    {
        encodeCyan();
    }
}

void ColorClass::printComponentValues(ofstream &outFile) 
{
    ostringstream oss;
    string strObj;
    oss << red << " " << green << " " << blue <<  " ";
    strObj = oss.str();
    outFile << strObj;
}

///////// Helper Functions for ColorClass ////////
void ColorClass::encodeBlack()
{
    if(evalOddEven(red) == DENOTE_ODD)
    {
        red--;
    }
    if(evalOddEven(green) == DENOTE_ODD)
    {
        green--;
    }
    if(evalOddEven(blue) == DENOTE_ODD)
    {
        blue--;
    }
}
    
void ColorClass::encodeRed()
{
    encodeBlack();
    red++;
}

void ColorClass::encodeGreen()
{
    encodeBlack();
    green++;
}

void ColorClass::encodeBlue()
{
    encodeBlack();
    blue++;
}

void ColorClass::encodeWhite()
{
    if(evalOddEven(red) == DENOTE_EVEN)
    {
        red++;
    }
    if(evalOddEven(green) == DENOTE_EVEN)
    {
        green++;
    }
    if(evalOddEven(blue) == DENOTE_EVEN)
    {
        blue++;
    }
}

void ColorClass::encodeYellow()
{
    encodeWhite();
    blue--;
}

void ColorClass::encodeMagenta()
{
    encodeWhite();
    green--;
}

void ColorClass::encodeCyan()
{
    encodeWhite();
    red--;
}

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

string ColorClass::evalOddEven(int rgb)
{   
    string result = DENOTE_ODD; 

    if(rgb % 2 == 0){
        result = DENOTE_EVEN;
    }
    return result;
}

void ColorClass::printErrorMsg()
{
    cout << "Error: Reading color from file" << endl;
}
