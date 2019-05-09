#include "MessageClass.h"
#include "constants.h"


//////// MenuClass Constructor and Member Functions ////////
MessageClass::MessageClass()
{
    isValidEncode = false;
}

void MessageClass::evaluateValue(istringstream &iss)
{ 
    iss >> encodeVal;

    if(!iss.fail() && encodeVal >= MIN_ENC_VAL && encodeVal <= MAX_ENC_VAL)
    {
        isValidEncode = true;
    }
    else
    {
        isValidEncode = false;
    }
}

int MessageClass::getEncodeVal()
{
    return encodeVal;
}

bool MessageClass::getIsValidEncode()
{
    return isValidEncode;
}