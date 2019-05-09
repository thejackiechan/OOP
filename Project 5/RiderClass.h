#ifndef _RIDERCLASS_H_
#define _RIDERCLASS_H_

#include <iostream>

using namespace std;

// The RiderClass represents a rider object, whose attributes
// include the arrival time and ID (based on how many riders
// had arrived before them).
class RiderClass
{
    private:
        int arrivalTime;
        int riderID;
        
    public:
        RiderClass();
        RiderClass(int inID, int inTime);
        int getID() const;
        int getArrivalTime();
};

// The extraction operator is overloaded so that the riderID
// is displayed when a RiderClass object is extracted.
ostream& operator<<(ostream &os, const RiderClass &rider);


#endif