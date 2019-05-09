#ifndef _COLORIMAGECLASS_H_
#define _COLORIMAGECLASS_H_

#include <string>
#include <fstream>
#include <sstream>
#include "ColorClass.h"
#include "RowColumnClass.h"
#include "MessageClass.h"
using namespace std;

/*
An image is simply a collection of color pixels arranged in a rectangle.
The ColorImageClass represents a small image as a 2D array of ColorClass
objects composed of some number of rows and columns.
*/
class ColorImageClass
{
    private:
        /*  
        The image in the PPM file is stored dynamically on the heap as
        image, and its dimensions (height and width) are stored in
        imgDimensions. msgImage stores the encoded pixel values of image
        starting at the row/column message placement values input by and
        the user. The encoding pattern is performed according to the 
        message file also given by the user.
        */

        ColorClass **image;
        RowColumnClass imgDimensions;
        ColorClass **msgImage;

        bool isProperlyInitialized;
        
        /*  
        The various member functions are called primarily by the public
        member functions below for reading in the image/file or encoding
        the image while performing error checking along the way. Further
        details of some of these functions are discussed in the cpp file.
        */
        void readImageHeader(ifstream &inFile);
        void createImage(int numRows, int numCols);
        void readPixelRow(istringstream &iss, int currRow, int &currCol);
        void printStatus(int currRow, int currCol);
        int getColWithBadChar(string line, string fileType);
        void getMessagePlacement(int &msgRowStart, int &msgColStart);
        void getMessageDimensions(ifstream &inFile, int &numMsgRows,
                                  int &numMsgCols);

        void createMessageImage(int numMsgRows, int numMsgCols);
        void extractAndCheckRow(ifstream &inFile, istringstream &iss, 
                                int &currCol, string fileType);

        void encodePixelRow(MessageClass &message, istringstream &iss, 
                            int msgRowStart, int msgColStart, int currRow,
                            int &currCol);

        void evaluateAndAdvanceRow(istringstream &iss, int &currRow, 
                                   int &currCol);

        void checkIfEndOfFile(ifstream &inFile);
        void encodeImageFromMsgImage(int msgRowStart, int msgColStart,
                                     int numMsgRows, int numMsgCols, 
                                     bool &isInBounds);

        void deleteMsgImage(int numMsgRows);
        
    public:
        // Constructor reads in image data from a input file stream.
        ColorImageClass(ifstream &inFile);
        
        // Getter function that returns whether the image had been read in
        // successfully.
        bool isProperImage();

        // Calls printComponentValues (ColorClass member function) to write
        // an image to a file.
        void printImage(ofstream &outFile);

        // Translates the encoding values from the message file into the 
        // proper pixel modifications of the image.
        void encodeMessage(ifstream &inFile);

        // Edits the encoded image so that the message can be visualized.
        void decodeMessage();

        // Creates the header for the PPM file and calls printImage to print
        // the pixel values to a file.
        void saveImageToFile(ofstream &outFile);
};


#endif


