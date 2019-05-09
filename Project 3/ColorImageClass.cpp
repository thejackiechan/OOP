#include "ColorImageClass.h"
#include "constants.h"
#include "ColorClass.h"
#include "MessageClass.h"
#include "RowColumnClass.h"
#include "trimLine.h"


//////// ColorImageClass Constructor and Member Functions ////////
ColorImageClass::ColorImageClass(ifstream &inFile)
{
    isProperlyInitialized = true;
    int currRow = 0;
    int currCol = 0;
    istringstream iss;
    string lineStr;

    readImageHeader(inFile);

    // Now Read in Image
    if(isProperlyInitialized) 
    {
        createImage(imgDimensions.getRow(), imgDimensions.getCol());

        while(isProperlyInitialized && currRow < imgDimensions.getRow()) 
        {
            extractAndCheckRow(inFile, iss, currCol, IMG_TYPE);
                
            while(isProperlyInitialized && currCol < imgDimensions.getCol())
            {
                readPixelRow(iss, currRow, currCol);
            } 
            evaluateAndAdvanceRow(iss, currRow, currCol);
        }
        checkIfEndOfFile(inFile);
    }
    printStatus(currRow, currCol);
}

bool ColorImageClass::isProperImage()
{
    return isProperlyInitialized;
}

void ColorImageClass::printImage(ofstream &outFile)
{
    ostringstream oss;
    string strObj;
    
    for(int i = 0; i < imgDimensions.getRow(); i++)
    {
        for(int j = 0; j < imgDimensions.getCol(); j++)
        {
            image[i][j].printComponentValues(outFile);
        }
        outFile << endl;
    }
}

/* 
1. Reads in user input for where to begin encoding the message (row/column).
2. Checks the message dimensions (line 1 of file) to see if it is formatted 
   correctly. If so, begin reading in the message.
3. Dynamically allocate memory to store a pixel array according to the
   dimension values.
4. Read a line of the message and check for improper values.
5. If the line contains valid input, copy over the image pixels according to
   the placement values over to the message pixel array and encode them.
6. When the entire message is read in, check if there is more input after
   the specified row dimension.
7. If the end of the file is indeed reached, replace the image pixels with
   the encoded ones. If there is any overflow (i.e. the message placement
   causes the encoding to go out of bounds), then only those within the bounds
   are modified.
8. Delete the message pixel array to free up the memory associated with it.
*/
void ColorImageClass::encodeMessage(ifstream &inFile)
{
    istringstream iss;
    int msgRowStart;
    int msgColStart;
    int numMsgRows;
    int numMsgCols;
    int currRow = 0;
    int currCol = 0;
    bool isInBounds = false;
    MessageClass message;

    getMessagePlacement(msgRowStart, msgColStart);
    getMessageDimensions(inFile, numMsgRows, numMsgCols);

    if(isProperlyInitialized)
    {
        createMessageImage(numMsgRows, numMsgCols);

        while(isProperlyInitialized && currRow < numMsgRows) 
        {
            extractAndCheckRow(inFile, iss, currCol, MSG_TYPE);

            while(isProperlyInitialized && currCol < numMsgCols)
            {       
                encodePixelRow(message, iss, msgRowStart, msgColStart,
                               currRow, currCol);
            }
            evaluateAndAdvanceRow(iss, currRow, currCol);
        }
        checkIfEndOfFile(inFile);

        if(!isProperlyInitialized){
            cout << "Error: Reading message value at row/col: " 
                 << currRow << " " << currCol << endl;
            cout << "Message encode successful: No" << endl;
        }
        else
        {
            cout << "Message encode successful: Yes" << endl;
            encodeImageFromMsgImage(msgRowStart, msgColStart, numMsgRows,
                                    numMsgCols, isInBounds);

            if(!isInBounds)
            {
                cout << "The image was not edited based on the placement "
                        "values." << endl;
            }
        }
        deleteMsgImage(numMsgRows);
    } 
}

void ColorImageClass::decodeMessage()
{
    for(int i = 0; i < imgDimensions.getRow(); i++)
    {
        for(int j = 0; j < imgDimensions.getCol(); j++)
        {
            image[i][j].decodePixel();
        }
    }
    cout << "Image modified to decoded image contents" << endl;
}

void ColorImageClass::saveImageToFile(ofstream &outFile)
{
    ostringstream oss;
    string strObj;

    oss << MAGIC_NUM << endl;
    oss << imgDimensions.getCol() << " " << imgDimensions.getRow() << endl;
    oss << FULL_COLOR << endl;
    strObj = oss.str();
    outFile << strObj;
    
    printImage(outFile);
}

///////// Helper Functions for ColorImageClass ////////

// Error checking to read in first 3 lines of PPM file
void ColorImageClass::readImageHeader(ifstream &inFile)
{
    string lineStr;
    istringstream iss;
    int currRow = MAGIC_NUM_LINE;
    int numRows = MIN_ROW_COL_VAL;
    int numCols = MIN_ROW_COL_VAL;
    int maxColor;

    while(isProperlyInitialized && currRow <= MAX_COLOR_LINE)
    {
        getline(inFile, lineStr);
        trimLine(lineStr);
        iss.str(lineStr);
        
        if(currRow == MAGIC_NUM_LINE)
        {
            iss >> lineStr;
            if(iss.fail() || !iss.eof() || lineStr != MAGIC_NUM)
            {
                cout << "Error: expected P3 in line 1" << endl;
                isProperlyInitialized = false;
            }
        }
        else if(currRow == IMG_DIM_LINE)
        {
            iss >> numCols >> numRows;

            if(iss.fail() || !iss.eof() || numCols <= MIN_ROW_COL_VAL
                                        || numRows <= MIN_ROW_COL_VAL)
            {
                cout << "Error: expected 2 positive ints in line 2" << endl;
                cout << "Format should be <intCols> <intRows>." << endl;
                isProperlyInitialized = false;
            }
        }
        else if(currRow == MAX_COLOR_LINE)
        {
            iss >> maxColor;
            if(iss.fail() || !iss.eof() || maxColor != FULL_COLOR)
            {
                cout << "Error: expected 255 in line 3" << endl;
                isProperlyInitialized = false;
            }
        }
        iss.clear();
        currRow++;
    }
    imgDimensions.setRowCol(numRows, numCols);
}

void ColorImageClass::createImage(int numRows, int numCols)
{
    image = new ColorClass*[numRows];

    for(int i = 0; i < numRows; i++)
    {
        image[i] = new ColorClass[numCols];
    }
}

void ColorImageClass::readPixelRow(istringstream &iss, int currRow, 
                                                       int &currCol)
{
    image[currRow][currCol].setTo(iss);

    if(image[currRow][currCol].isInitialized())
    {
        currCol++;
    }
    else
    {
        isProperlyInitialized = false;
    }
}

void ColorImageClass::printStatus(int currRow, int currCol)
{
    if(isProperlyInitialized)
    {
        cout << "Image read successful: Yes" << endl;
    }
    else
    {	
        cout << "Error: Reading image pixel at row: " << currRow 
             << " col: " << currCol << endl;
        cout << "Image read successful: No" << endl;
        cout << "Error: While reading the image, an error was encountered. "
                "Exiting the program!" << endl;
    }
}

// Read in user input for starting message row/column and check for bad input.
void ColorImageClass::getMessagePlacement(int &msgRowStart, int &msgColStart)
{
    string lineStr;
    istringstream iss;
    isProperlyInitialized = false;

    while(!isProperlyInitialized)
    {
        cout << "Enter row and column for message placement: ";
        getline(cin, lineStr);
        trimLine(lineStr);
        iss.str(lineStr);
        iss >> msgRowStart >> msgColStart;

        if(!iss.fail() && iss.eof())
        {
            isProperlyInitialized = true;
        }
        else
        {
            cout << "Error: format should be <intRow> <intCol>." << endl;
        }
        iss.clear();
    }
}

// Read in first line of the message file and check for bad input.
void ColorImageClass::getMessageDimensions(ifstream &inFile, int &numMsgRows,
                                                             int &numMsgCols)
{
    string lineStr;
    istringstream iss;

    getline(inFile, lineStr);
    trimLine(lineStr);
    iss.str(lineStr);

    iss >> numMsgCols >> numMsgRows;

    if(iss.fail() || !iss.eof() || numMsgCols <= MIN_ROW_COL_VAL
                                || numMsgRows <= MIN_ROW_COL_VAL)
    {
        cout << "Error: expected 2 positive integers in line 1." << endl;
        cout << "Format should be <intCols> <intRows>." << endl;
        isProperlyInitialized = false;
    }
    iss.clear();
}

void ColorImageClass::createMessageImage(int numMsgRows, int numMsgCols)
{
    msgImage = new ColorClass*[numMsgRows];

    for(int i = 0; i < numMsgRows; i++)
    {
        msgImage[i] = new ColorClass[numMsgCols];
    } 
}

void ColorImageClass::extractAndCheckRow(ifstream &inFile, istringstream &iss,
                                         int &currCol, string fileType)
{
    string lineStr;

    getline(inFile, lineStr);
    currCol = getColWithBadChar(lineStr, MSG_TYPE);

    if(currCol != NO_POSITION) 
    {
        isProperlyInitialized = false;
    }
    else
    {   
        trimLine(lineStr);
        iss.str(lineStr);
        currCol = 0;
    }
}

void ColorImageClass::encodePixelRow(MessageClass &message, istringstream &iss,
                                     int msgRowStart, int msgColStart, 
                                     int currRow, int &currCol)
{
    message.evaluateValue(iss);
    
    if(message.getIsValidEncode()) 
    {   
        if(msgRowStart + currRow >= MIN_ROW_COL_IDX && 
           msgRowStart + currRow < imgDimensions.getRow() && 
           msgColStart + currCol >= MIN_ROW_COL_IDX && 
           msgColStart + currCol < imgDimensions.getCol())
        {
            msgImage[currRow][currCol] = image[msgRowStart + currRow]
                                              [msgColStart + currCol];

            msgImage[currRow][currCol].encodePixel(message.getEncodeVal());
        } 
        currCol++;    
    }
    else
    {
        isProperlyInitialized = false;
    }
}

void ColorImageClass::evaluateAndAdvanceRow(istringstream &iss, int &currRow,
                                                                int &currCol)
{
    if(!iss.eof())
    {
        isProperlyInitialized = false;
    }
    if(isProperlyInitialized)
    {
        iss.clear();
        currRow++;
        currCol = 0;
    }
}

void ColorImageClass::checkIfEndOfFile(ifstream &inFile)
{
    string lineStr;

    getline(inFile, lineStr);
    trimLine(lineStr);
    if(lineStr != EMPTY_STRING)
    {
        isProperlyInitialized = false;
    }
}

void ColorImageClass::encodeImageFromMsgImage(int msgRowStart, int msgColStart,
                                              int numMsgRows, int numMsgCols, 
                                              bool &isInBounds)
{
    for(int i = msgRowStart; i < msgRowStart + numMsgRows; i++)
    {
        for(int j = msgColStart; j < msgColStart + numMsgCols; j++)
        {
            if(i >= MIN_ROW_COL_IDX && i < imgDimensions.getRow() 
               && j >= MIN_ROW_COL_IDX && j < imgDimensions.getCol())
            {
                image[i][j] = msgImage[i - msgRowStart][j - msgColStart];
                isInBounds = true;
            }
        }
    }
}

// Deletes Message
void ColorImageClass::deleteMsgImage(int numMsgRows)
{
    for(int i = 0; i < numMsgRows; i++)
    {
        delete [] msgImage[i];
    }
    delete [] msgImage;
}

/*
This function receives a line of data from getline and screens if the string
contains any characters outside of those stored in VALID_CHAR_LIST (numbers
and whitespace). If such a character exists, the column (1 set of RGB = 1 col)
containing that character is returned.

Motivation:
The issue with using an input string stream directly is that
if a double is encountered, it will be split (the numbers before the decimal
will be read in as an int) and thus any resetting of the stream state 
(to get out of the fail state) will result in an extra "int" on that line.
Though the fail() function catches this error, there are cases in which the
error position (column of the pixel) will be off by one, such as when the 
double is positioned to be read in as B (3rd for RGB). Obviously, this is a
minor error and most likely acceptable as it localizes the error to +/- one
column though it bothered me enough to do something about it. However, this
function ONLY checks for non-whitespace and non-numeric characters. It will
NOT trigger an error if there are too many or too few ints on the line; the 
empty string will return good input. This check will be handled elsewhere.
I would also like to add that size_t string::npos is cast to an int which
may result in a loss of precision. In cases outside of this project, size_t
should be used instead.
*/
int ColorImageClass::getColWithBadChar(string line, string fileType)
{   
    int columnIdx = 0;
    int badInputIdx = line.find_first_not_of(VALID_CHAR_LIST, START_POSITION);
    int numInts = 0;
    
    // NO_POSITION or string::npos indicates that bad chars were not found
    if(badInputIdx == NO_POSITION)
    {
        columnIdx = NO_POSITION;
    }
    else // iterate through the string to determine the column with bad char
    {       
        for(int i = 0; i < badInputIdx - 1; i++)
        {
            if(line[i] - SPACE_CHAR != 0 && line[i + 1] - SPACE_CHAR == 0)
            {
                numInts++;
            }
            if(numInts == NUM_INTS_IN_PXL && fileType == IMG_TYPE)
            {
                numInts = 0;
                columnIdx++;
            }
            else if(fileType == MSG_TYPE)
            {
                columnIdx = numInts;
            }
        }
    }
    return columnIdx;
}


