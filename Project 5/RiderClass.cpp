#include "RiderClass.h"
#include "constants.h"
#include <iostream>

using namespace std;


RiderClass::RiderClass()
{
    arrivalTime = DEFAULT_TIME;
    riderID = DEFAULT_NUM;
}

RiderClass::RiderClass(int inID, int inTime)
{
    arrivalTime = inTime;
    riderID = inID;
}

int RiderClass::getID() const
{
    return riderID;
}

int RiderClass::getArrivalTime()
{
    return arrivalTime;
}

ostream& operator<<(ostream &os, const RiderClass &rider)
{
    os << rider.getID();
    return os;
}