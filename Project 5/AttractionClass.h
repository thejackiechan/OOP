#ifndef _ATTRACTIONCLASS_H_
#define _ATTRACTIONCLASS_H_

#include "constants.h"
#include "StatsClass.h"
#include "RiderClass.h"
#include "FIFOQueueClass.h"
#include <string>

using namespace std;

// The AttractionClass represents the Space Mountain ride for this simulation.
// It is responsible for maintaining the several priority lines and removing
// or adding riders from them.
class AttractionClass
{
    private:
        string name;
        bool stillHasRiders;
        FIFOQueueClass<RiderClass> lines[NUM_PRIORITY_LEVELS];
    
    public:
        AttractionClass();
        string getName();
        void printRidersInLine(int priority);
        bool getHasRiders();
        int getCurrNumRiders();
        int getNumRidersInLine(int priority);
        void addRider(int priority, int riderArrivalTime, StatsClass &stats);
        void removeRider(int priority, int carArrivalTime, StatsClass &stats);

        // These update methods are solely responsible for aiding the
        // StatsClass in garnering statistics.
        void updateEmptySeats(int numRidersInCar, StatsClass &stats);
        void updateRiderCounts(int priority, StatsClass &stats);
        void updateWaitTimes(int priority, int carArrivalTime, 
                             RiderClass rider, StatsClass &stats);
};


#endif