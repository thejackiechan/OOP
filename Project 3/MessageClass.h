#ifndef _MESSAGECLASS_H_
#define _MESSAGECLASS_H_

#include <sstream>
using namespace std;


// This class reads in the encoding values from the message file provided
// by the user and checks if they are in the proper range (0-7).
class MessageClass
{
    private:
        int encodeVal;
	    bool isValidEncode;
	    
    public:
        MessageClass();
        void evaluateValue(istringstream &iss);
        int getEncodeVal();
        bool getIsValidEncode();
};


#endif