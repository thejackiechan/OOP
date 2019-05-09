#ifndef _PARKSIMULATIONCLASS_H_
#define _PARKSIMULATIONCLASS_H_

#include "constants.h"
#include "random.h"
#include "EventClass.h"
#include "StatsClass.h"
#include "SortedListClass.h"
#include "AttractionClass.h"
#include <fstream>
#include <string>

using namespace std;

// The ParkSimulationClass is the primary class responsible for running
// the entire simulation from end to end. Upon calling the constructor,
// it will read in the simulation parameters from the file passed in
// run the simulation, and finally display some useful statistics to
// the console.

class ParkSimulationClass
{
    private:
        int seedVal;
        bool isValidInput;
        bool stillHasEvents;
        ifstream inFile;
        int closingTime;
        double meanRiderArrival;
        double stdDevRiderArrival;
        int minCarArrival;
        int maxCarArrival;
        int percentSuperFast;
        int percentFast;
        int numSuperFast;
        int numFast;
        int numStandard;
        int riderArrivalTime;
        int carArrivalTime;
        SortedListClass<EventClass> eventList;
        AttractionClass ride;
        StatsClass stats;
        
        // Performs error checking on the file and opens it if valid.
        void openFile(int argc, char* argv[]);

        // Reads in the file parameters and assigns them to their
        // respective values.
        void initSimulation();
        void runSimulation();

        // Takes in an event time and type (rider or car arrival) and
        // schedules an event for the future. 
        void scheduleEvent(int eventTime, string eventType);

        // Computes rider arrival time according to a normal distribution.
        int calcRiderArrivalTime(int currTime);

        // Computes car arrival time according to a uniform distribution.
        int calcCarArrivalTime(int currTime);

        // Handles the event at the top of the list and schedules a new event
        // depending on that event.
        void handleEvent();

        // When a rider arrival event is scheduled, a rider is randomly
        // assigned a priority based on the percentage parameters read in
        // from the file.
        int assignPriority();

        // Returns the string representation of the integer priority.
        string getPriorityAsStr(int priority);

        // Prints the number of riders in each priority line currently.
        void printNumRidersInEachLine();

        // Prints the number of riders aboard the ride car currently.
        void printNumRidersInCar(int numSuperFastInCar, int numFastInCar,
                                 int numStandardInCar);

        // Umbrella function that calls the various printing functions in
        // this class depending on the event.
        void printEventHandlingOutput(string eventType,
                                      int priority,
                                      int numRidersInCar, 
                                      int numSuperFastInCar, 
                                      int numFastInCar,
                                      int numStandardInCar);

        // Removes riders from the line indicated by priority.
        void fillCarWithRiders(int &numRidersInCar, int idealNumRiders,
                               int priority);

        // A statement is printed to the console to indicate the park is
        // closing.
        void printParkClosing();

        // Displays the riders (by ID) in each line currently.
        void displayLines();

        // Prints the total number of riders in line currently.
        void printTotalRidersInLine();
    
    public:
        // The only constructor, which is responsible for running the
        // entire simulation.
        ParkSimulationClass(int argc, char* argv[]);
};


#endif