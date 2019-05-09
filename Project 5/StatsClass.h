#ifndef _STATSCLASS_H_
#define _STATSCLASS_H_

// The StatsClass accumulates some potentially useful 
// statistics and prints them to the console at the end
// of the simulation.
class StatsClass
{
    private:
        int finalClosingTime;
        int totalCarsDeployed;
        int totalRiders;
        int totalSFPRiders;
        int totalFPRiders;
        int totalSTDRiders;
        int maxSFPRiders;
        int maxFPRiders;
        int maxSTDRiders;
        int maxEmptySeats;
        int totalSFPWaitTime;
        int totalFPWaitTime;
        int totalSTDWaitTime;
        int maxSFPWaitTime;
        int maxFPWaitTime;
        int maxSTDWaitTime;

    public:
        StatsClass();
        void setClosingTime(int inTime);
        void incrementTotalCars();
        void incrementTotalSFPRiders();
        void incrementTotalFPRiders();
        void incrementTotalSTDRiders();
        int getTotalRiders();
        int getMaxSFPRiders();
        int getMaxFPRiders();
        int getMaxSTDRiders();
        void setMaxSFPRiders(int inRiders);
        void setMaxFPRiders(int inRiders);
        void setMaxSTDRiders(int inRiders);
        int getMaxSFPWaitTime();
        int getMaxFPWaitTime();
        int getMaxSTDWaitTime();
        void setMaxSFPWaitTime(int inTime);
        void setMaxFPWaitTime(int inTime);
        void setMaxSTDWaitTime(int inTime);
        int getTotalSFPWaitTime();
        int getTotalFPWaitTime();
        int getTotalSTDWaitTime();
        void setTotalSFPWaitTime(int inTime);
        void setTotalFPWaitTime(int inTime);
        void setTotalSTDWaitTime(int inTime);
        int getMaxEmptySeats();
        void setMaxEmptySeats(int inSeats);
        void displayStatistics();
};


#endif

