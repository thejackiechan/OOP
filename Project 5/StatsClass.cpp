#include "StatsClass.h"
#include "constants.h"
#include <iostream>

using namespace std;

StatsClass::StatsClass()
{
    finalClosingTime = 0;
    totalCarsDeployed = 0;
    totalSFPRiders = 0;
    totalFPRiders = 0;
    totalSTDRiders = 0;
    maxSFPRiders = 0;
    maxFPRiders = 0;
    maxSTDRiders = 0;
    maxEmptySeats = 0;
    totalSFPWaitTime = 0;
    totalFPWaitTime = 0;
    totalSTDWaitTime = 0;
    maxSFPWaitTime = 0;
    maxFPWaitTime = 0;
    maxSTDWaitTime = 0;
}

void StatsClass::setClosingTime(int inTime)
{
    finalClosingTime = inTime;
}

void StatsClass::incrementTotalCars()
{
    totalCarsDeployed++;
}

void StatsClass::incrementTotalSFPRiders()
{
    totalSFPRiders++;
}

void StatsClass::incrementTotalFPRiders()
{
    totalFPRiders++;
}

void StatsClass::incrementTotalSTDRiders()
{
    totalSTDRiders++;
}

int StatsClass::getMaxSFPRiders()
{
    return maxSFPRiders;
}

int StatsClass::getMaxFPRiders()
{
    return maxFPRiders;
}

int StatsClass::getMaxSTDRiders()
{
    return maxSTDRiders;
}

int StatsClass::getTotalRiders()
{
    return totalSFPRiders + totalFPRiders + totalSTDRiders;
}

void StatsClass::setMaxSFPRiders(int inRiders)
{
    maxSFPRiders = inRiders;
}

void StatsClass::setMaxFPRiders(int inRiders)
{
    maxFPRiders = inRiders;
}

void StatsClass::setMaxSTDRiders(int inRiders)
{
    maxSTDRiders = inRiders;
}

int StatsClass::getMaxSFPWaitTime()
{
    return maxSFPWaitTime;
}

int StatsClass::getMaxFPWaitTime()
{
    return maxFPWaitTime;
}

int StatsClass::getMaxSTDWaitTime()
{
    return maxSTDWaitTime;
}

void StatsClass::setMaxSFPWaitTime(int inTime)
{
    maxSFPWaitTime = inTime;
}

void StatsClass::setMaxFPWaitTime(int inTime)
{
    maxFPWaitTime = inTime;
}

void StatsClass::setMaxSTDWaitTime(int inTime)
{
    maxSTDWaitTime = inTime;
}

int StatsClass::getMaxEmptySeats()
{
    return maxEmptySeats;
}

void StatsClass::setMaxEmptySeats(int inSeats)
{
    maxEmptySeats = inSeats;
}

int StatsClass::getTotalSFPWaitTime()
{
    return totalSFPWaitTime;
}

int StatsClass::getTotalFPWaitTime()
{
    return totalFPWaitTime;
}

int StatsClass::getTotalSTDWaitTime()
{
    return totalSTDWaitTime;
}

void StatsClass::setTotalSFPWaitTime(int inTime)
{
    totalSFPWaitTime = inTime;
}

void StatsClass::setTotalFPWaitTime(int inTime)
{
    totalFPWaitTime = inTime;
}

void StatsClass::setTotalSTDWaitTime(int inTime)
{
    totalSTDWaitTime = inTime;
}

void StatsClass::displayStatistics() 
{
    cout << endl;
    cout << "-- Simulation Statistics --" << endl;
    cout << "Official Closing Time: " << finalClosingTime << endl;
    cout << "Total Cars Deployed: " << totalCarsDeployed << endl; 
    cout << "Total Passengers: " << getTotalRiders() << endl;
    cout << "Total " << SFP_STR << " riders: " << totalSFPRiders << endl;
    cout << "Total " << FP_STR << " riders: " << totalFPRiders << endl;
    cout << "Total " << STD_STR << " riders: " << totalSTDRiders << endl;
    cout << "Longest " << SFP_STR << " line: " << maxSFPRiders << endl;
    cout << "Longest " << FP_STR << " line: " << maxFPRiders << endl;
    cout << "Longest " << STD_STR << " line: " << maxSTDRiders << endl;
    cout << "Maximum number of empty seats: " << maxEmptySeats << endl;
    cout << "Maximum " << SFP_STR << " rider wait time: " 
    	 << maxSFPWaitTime << endl;

    cout << "Maximum " << FP_STR << " rider wait time: " 
    	 << maxFPWaitTime << endl;

    cout << "Maximum " << STD_STR << " rider wait time: " 
    	 << maxSTDWaitTime << endl;

    if(totalSFPRiders > 0)
    {
        cout << "Average " << SFP_STR << " rider wait time: " 
         << totalSFPWaitTime / totalSFPRiders << endl;
    }
    
    if(totalFPRiders > 0)
    {
        cout << "Average " << FP_STR << " rider wait time: " 
         << totalFPWaitTime / totalFPRiders << endl;
    }
    
    if(totalSTDRiders > 0)
    {
        cout << "Average " << STD_STR << " rider wait time: " 
         << totalSTDWaitTime / totalSTDRiders << endl;
    }
    cout << endl;
}




