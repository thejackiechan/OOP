#include "MenuClass.h"
#include "constants.h"
#include "ColorImageClass.h"
#include "trimLine.h"


//////// MenuClass Constructor and Member Functions ////////
MenuClass::MenuClass(ColorImageClass &image)
{    
    menuOption = ENCODE_OPTION;
    validInputFound = false;

    while(menuOption != EXIT_OPTION)
    {
        displayMenu();
        getMenuOption();
        
        if(menuOption == ENCODE_OPTION)
        {   
            encodeOption(image);
        }
        else if(menuOption == DECODE_OPTION)
        {
            decodeOption(image);
        }
        else if(menuOption == WRITE_TO_FILE_OPTION)
        {
            writeToFileOption(image);
        }
    }
    cout << "Thanks for using this program!" << endl;
}

void MenuClass::displayMenu()
{
    cout << "1.  Encode a message from file" << endl;
    cout << "2.  Perform decode" << endl;
    cout << "3.  Write current image to file" << endl;
    cout << "4.  Exit the program" << endl;
    cout << "Enter your choice: ";
}

void MenuClass::getMenuOption()
{
    string lineStr;
    istringstream iss;
    validInputFound = false;
    
    while(!validInputFound)
    {   
        getline(cin, lineStr);
        trimLine(lineStr);
        iss.str(lineStr);
        iss >> menuOption;
        
        if(!iss.fail() && iss.eof() && menuOption >= ENCODE_OPTION
                                    && menuOption <= EXIT_OPTION)
        {
            validInputFound = true;
        }
        else
        {
            cout << "Please enter an integer from 1-4." << endl;
        }
        iss.clear();
    }
}

void MenuClass::encodeOption(ColorImageClass &image)
{
    string lineStr;
    string fileName;
    ifstream inFile;
    istringstream iss;
    validInputFound = false;

    while(!validInputFound)
    {           
        cout << "Enter name of file containing message: ";
        getline(cin, lineStr);
        trimLine(lineStr);
        iss.str(lineStr);
        iss >> fileName;
                
        if(iss.eof())
        {
            inFile.open(fileName.c_str());

            if(inFile.fail())
            {
                cout << "Unable to open file. Try again." << endl;
            }
            else
            {
                validInputFound = true;
            }
        }
        else 
        {
            cout << "Please enter only one file." << endl;
        }
        iss.clear();
    }
    image.encodeMessage(inFile);
    inFile.close();    
}

void MenuClass::decodeOption(ColorImageClass &image)
{
    image.decodeMessage();
}

void MenuClass::writeToFileOption(ColorImageClass &image)
{
    string lineStr;
    string fileName;
    ofstream outFile;
    istringstream iss;
    validInputFound = false;

    while(!validInputFound)
    {
        cout << "Enter name of file to write image to: ";
        getline(cin, lineStr);
        trimLine(lineStr); 
        iss.str(lineStr);
        iss >> fileName;

        if(iss.eof())
        {
            validInputFound = true;
        }
        else
        {
            cout << "Please enter only one file name." << endl;
        }
        iss.clear();
    }
    outFile.open(fileName.c_str());
    image.saveImageToFile(outFile);
    outFile.close();
    cout << "Image write successful: Yes" << endl;
}
