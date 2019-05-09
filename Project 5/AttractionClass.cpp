#include "AttractionClass.h"
#include "constants.h"
#include "RiderClass.h"
#include "FIFOQueueClass.h"
#include "StatsClass.h"
#include <string>

using namespace std;

AttractionClass::AttractionClass()
{
    name = RIDE_NAME;
    stillHasRiders = false;
}

string AttractionClass::getName()
{
    return name;
}

void AttractionClass::printRidersInLine(int priority)
{
    lines[priority].print();
}

bool AttractionClass::getHasRiders()
{
    stillHasRiders = false;
    int i = 0;
    
    while(i < NUM_PRIORITY_LEVELS)
    {
        if(lines[i].getNumElems() != 0)
        {
            stillHasRiders = true;
        }
        i++;
    }
    return stillHasRiders;
}

int AttractionClass::getCurrNumRiders()
{
    int total = getNumRidersInLine(SFP_PRIORITY) +
                getNumRidersInLine(FP_PRIORITY) +
                getNumRidersInLine(STD_PRIORITY);

    return total;
}

int AttractionClass::getNumRidersInLine(int priority)
{
    return lines[priority].getNumElems();
}

void AttractionClass::addRider(int priority, int riderArrivalTime,
                               StatsClass &stats)
{
    RiderClass rider(stats.getTotalRiders(), riderArrivalTime); 
    
    lines[priority].enqueue(rider);
    updateRiderCounts(priority, stats);
}

void AttractionClass::removeRider(int priority, int carArrivalTime,
                                  StatsClass &stats)
{
    RiderClass rider(DEFAULT_NUM, DEFAULT_TIME);

    lines[priority].dequeue(rider);

    updateWaitTimes(priority, carArrivalTime, rider, stats);
}

void AttractionClass::updateEmptySeats(int numRidersInCar, StatsClass &stats)
{
    int numEmptySeats = NUM_SEATS - numRidersInCar;

    if(numEmptySeats > stats.getMaxEmptySeats())
    {
        stats.setMaxEmptySeats(numEmptySeats);
    }
}

void AttractionClass::updateRiderCounts(int priority, StatsClass &stats)
{
    int numRiders = getNumRidersInLine(priority);

    if(priority == SFP_PRIORITY)
    {
        stats.incrementTotalSFPRiders();

        if(numRiders > stats.getMaxSFPRiders()) 
        {
            stats.setMaxSFPRiders(numRiders);
        }
    }
    else if(priority == FP_PRIORITY)
    {
        stats.incrementTotalFPRiders();

        if(numRiders > stats.getMaxFPRiders())
        {
            stats.setMaxFPRiders(numRiders);
        }
    }
    else
    {
        stats.incrementTotalSTDRiders();

        if(numRiders > stats.getMaxSTDRiders())
        {
            stats.setMaxSTDRiders(numRiders);
        }
    }
}

void AttractionClass::updateWaitTimes(int priority, int carArrivalTime,
                                      RiderClass rider, StatsClass &stats)
{
    int waitTime = carArrivalTime - rider.getArrivalTime(); 
    int totalWaitTime;

    if(priority == SFP_PRIORITY)
    {
        if(waitTime > stats.getMaxSFPWaitTime())
        {
            stats.setMaxSFPWaitTime(waitTime);   
        }
        totalWaitTime = stats.getTotalSFPWaitTime();
        stats.setTotalSFPWaitTime(totalWaitTime + waitTime);
    }
    else if(priority == FP_PRIORITY)
    {
        if(waitTime > stats.getMaxFPWaitTime())
        {
            stats.setMaxFPWaitTime(waitTime);   
        }
        totalWaitTime = stats.getTotalFPWaitTime();
        stats.setTotalFPWaitTime(totalWaitTime + waitTime);
    }
    else
    {
        if(waitTime > stats.getMaxSTDWaitTime())
        {
            stats.setMaxSTDWaitTime(waitTime);   
        }
        totalWaitTime = stats.getTotalSTDWaitTime();
        stats.setTotalSTDWaitTime(totalWaitTime + waitTime);
    }
}

