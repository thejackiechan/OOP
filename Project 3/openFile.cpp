#include "openFile.h"
#include "constants.h"


void openFile(int argc, char* argv[], int &errorType, ifstream &inFile)
{

    if(argc != NUM_FILES)
    {
        cout << "Usage: " << argv[EXE_FILE] << " <startPPM.ppm>" << endl;
        errorType = NUM_FILES_ERROR;
    }
    else if(argc == NUM_FILES)
    {
        inFile.open(argv[PPM_FILE]);
    
        if(inFile.fail())
        {
            cout << "Error: Unable to open: " << argv[PPM_FILE] << endl;
            errorType = FILE_READ_ERROR;
        }
        cout << "Reading initial image from: " << argv[PPM_FILE] << endl; 
    }    
}