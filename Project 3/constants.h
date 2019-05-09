#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#include <string>
using namespace std;


///// READING IN FILE /////
const int MAGIC_NUM_LINE = 1;
const int IMG_DIM_LINE = 2;
const int MAX_COLOR_LINE = 3;
const string MAGIC_NUM = "P3";
const int NUM_FILES = 2;
const string IMG_TYPE = "IMAGE";
const string MSG_TYPE = "MESSAGE";
const int EXE_FILE = 0;
const int PPM_FILE = 1;

/////// Exit Values ///////
const int NUM_FILES_ERROR = 2;
const int FILE_READ_ERROR = 3;

////////// MENU //////////
const int ENCODE_OPTION = 1;
const int DECODE_OPTION = 2;
const int WRITE_TO_FILE_OPTION = 3;
const int EXIT_OPTION = 4;

///// ENCODING/DECODING /////
const string BLACK_ENC_SEQ = "EEE"; // even even even
const string RED_ENC_SEQ = "OEE";
const string GREEN_ENC_SEQ = "EOE"; 
const string BLUE_ENC_SEQ = "EEO"; 
const string YELLOW_ENC_SEQ = "OOE"; 
const string MAGENTA_ENC_SEQ = "OEO";
const string CYAN_ENC_SEQ = "EOO"; 
const string DENOTE_EVEN = "E";
const string DENOTE_ODD = "O"; 
const int MIN_ENC_VAL = 0;
const int MAX_ENC_VAL = 7;
const int ENC_BLACK_OPTION = 0;
const int ENC_RED_OPTION = 1;
const int ENC_GREEN_OPTION = 2;
const int ENC_BLUE_OPTION = 3;
const int ENC_WHITE_OPTION = 4;
const int ENC_YELLOW_OPTION = 5;
const int ENC_MAGENTA_OPTION = 6;

///// ERROR CHECKING /////
const int MIN_ROW_COL_IDX = 0;
const int MIN_ROW_COL_VAL = 1;
const string VALID_CHAR_LIST = " 0123456789";
const int START_POSITION = 0;
const char SPACE_CHAR = ' ';
const int NO_POSITION = string::npos; // cast from size_t to int
const string EMPTY_STRING = "";
const int NO_ERROR = 0;
const int FULL_COLOR = 255;
const int NO_COLOR = 0;
const int NUM_INTS_IN_PXL = 3;


#endif

