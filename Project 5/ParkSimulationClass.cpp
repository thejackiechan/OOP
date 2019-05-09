#include "ParkSimulationClass.h"
#include "constants.h"
#include "random.h"
#include "EventClass.h"
#include "StatsClass.h"
#include "AttractionClass.h"
#include "SortedListClass.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


ParkSimulationClass::ParkSimulationClass(int argc, char* argv[])
{
    openFile(argc, argv);
    
    if(isValidInput)
    {
        initSimulation();
        runSimulation();
        stats.displayStatistics();
    }
    cout << "Thanks for using this simulation." << endl;
}

void ParkSimulationClass::openFile(int argc, char*argv[])
{
    isValidInput = true;
    
    if(argc != NUM_FILES)
    {
        cout << "Usage: " << argv[EXE_FILE] << " <File name>" << endl;
        isValidInput = false;
    }
    else if(argc == NUM_FILES)
    {
        inFile.open(argv[TXT_FILE]);
        
        if(inFile.fail())
        {
            cout << "Error: Unable to open: " << argv[TXT_FILE] << endl;
            isValidInput = false;
        }
        cout << "Reading simulation parameters from: " << argv[TXT_FILE] 
             << endl;
    }
}

void ParkSimulationClass::initSimulation()
{
    stillHasEvents = true;
    
    inFile >> closingTime >> meanRiderArrival >> stdDevRiderArrival
    >> minCarArrival >> maxCarArrival >> percentSuperFast
    >> percentFast >> numSuperFast >> numFast;

    numStandard = NUM_SEATS - numSuperFast - numFast;
    
    inFile.close();

    cout << "Welcome to " << ride.getName() << "!" << endl;
    
    isValidInput = false;
    
    while(!isValidInput)
    {
        cout << "Please enter the seed you would like to use: ";
        cin >> seedVal;
        
        if(!cin.fail())
        {
            isValidInput = true;
        }
        else
        {
            cout << "Please enter an integer." << endl;
            cin.clear();
        }
    }
    setSeed(seedVal);
}

void ParkSimulationClass::runSimulation()
{
    riderArrivalTime = 0; // assume there is a rider at time 0
    carArrivalTime = calcCarArrivalTime(0);
    scheduleEvent(riderArrivalTime, RIDER_TYPE);
    scheduleEvent(carArrivalTime, CAR_TYPE);
    
    while(ride.getHasRiders() || stillHasEvents)
    {
        handleEvent();
        
        if(eventList.getNumElems() == 0)
        {
            stillHasEvents = false;
        }
        
        if(ride.getHasRiders() || riderArrivalTime < closingTime)
        {
            EventClass firstEvent;
            eventList.getElemAtIndex(0, firstEvent);
                
            if(firstEvent.getType() == CAR_TYPE)
            {
                riderArrivalTime = calcRiderArrivalTime(riderArrivalTime);
                    
                if(riderArrivalTime < closingTime)
                {
                    scheduleEvent(riderArrivalTime, RIDER_TYPE);
                }
                else
                {
                    printParkClosing();
                    carArrivalTime = calcCarArrivalTime(carArrivalTime);
                }
            }
            if(firstEvent.getType() == RIDER_TYPE || 
              (!stillHasEvents && ride.getHasRiders()))
            {
                carArrivalTime = calcCarArrivalTime(carArrivalTime);
                scheduleEvent(carArrivalTime, CAR_TYPE);
            }
        }
    }
    carArrivalTime = calcCarArrivalTime(carArrivalTime);
    stats.setClosingTime(carArrivalTime);
    cout << endl << "The park is now officially closed." << endl;
}

void ParkSimulationClass::scheduleEvent(int eventTime, string eventType)
{
    EventClass event(eventTime, eventType);
    eventList.insertValue(event);
}

int ParkSimulationClass::calcRiderArrivalTime(int currTime)
{
    return currTime + getNormal(meanRiderArrival, stdDevRiderArrival);
}

int ParkSimulationClass::calcCarArrivalTime(int currTime)
{
    return currTime + getUniform(minCarArrival, maxCarArrival);
}

void ParkSimulationClass::handleEvent()
{
    EventClass event;
    string eventType;
    int numSeatsFilled;
    int priority = DEFAULT_PRIORITY;
    int numRidersInCar = 0;
    int numSuperFastInCar = 0;
    int numFastInCar = 0;
    int numStandardInCar = 0;

    eventList.removeFront(event);
    eventType = event.getType();
    
    if(eventType == RIDER_TYPE)
    {
        priority = assignPriority();
        ride.addRider(priority, riderArrivalTime, stats);
    }
    else if(eventType == CAR_TYPE) // CAR_TYPE
    {   
        stats.incrementTotalCars();
        fillCarWithRiders(numRidersInCar, numSuperFast, SFP_PRIORITY);
        numSuperFastInCar = numRidersInCar;

        fillCarWithRiders(numRidersInCar, numSuperFastInCar + numFast,
                          FP_PRIORITY);

        numFastInCar = numRidersInCar - numSuperFastInCar;

        fillCarWithRiders(numRidersInCar, numSuperFastInCar + numFastInCar + 
                                          numStandard, STD_PRIORITY);

        numStandardInCar = numRidersInCar - numFastInCar - numSuperFastInCar;

        if(numRidersInCar < NUM_SEATS) // add according to highest priority
        {
            numSeatsFilled = numRidersInCar;
            fillCarWithRiders(numRidersInCar, NUM_SEATS, SFP_PRIORITY);
            numSuperFastInCar += (numRidersInCar - numSeatsFilled);

            numSeatsFilled = numRidersInCar;
            fillCarWithRiders(numRidersInCar, NUM_SEATS, FP_PRIORITY);
            numFastInCar += (numRidersInCar - numSeatsFilled);

            numSeatsFilled = numRidersInCar;
            fillCarWithRiders(numRidersInCar, NUM_SEATS, STD_PRIORITY);
            numStandardInCar += (numRidersInCar - numSeatsFilled);
        }

        if(numRidersInCar < NUM_SEATS)
        {
            ride.updateEmptySeats(numRidersInCar, stats);
        }    
    }
    printEventHandlingOutput(eventType, priority, numRidersInCar,
                             numSuperFastInCar, numFastInCar,
                             numStandardInCar);
}

void ParkSimulationClass::fillCarWithRiders(int &numRidersInCar, 
                                            int idealNumRiders, 
                                            int priority)
{
    while(numRidersInCar < idealNumRiders &&
          ride.getNumRidersInLine(priority) != 0)
    {
        ride.removeRider(priority, carArrivalTime, stats);
        numRidersInCar++;
    }
}

int ParkSimulationClass::assignPriority()
{
    int randNum = getUniform(MIN_PERCENT, MAX_PERCENT);
    int priority = STD_PRIORITY;
    
    if(randNum >= MIN_PERCENT && randNum <= percentSuperFast)
    {
        priority = SFP_PRIORITY;
    }
    else if(randNum >= percentSuperFast &&
            randNum <= percentFast + percentSuperFast)
    {
        priority = FP_PRIORITY;
    }
    return priority;
}

void ParkSimulationClass::printNumRidersInEachLine()
{
    cout << "There is/are " << ride.getNumRidersInLine(SFP_PRIORITY)
         << " rider(s) in the " << SFP_STR << " line, "
         << ride.getNumRidersInLine(FP_PRIORITY) << " rider(s) in the "
         << FP_STR << " line, and " 
         << ride.getNumRidersInLine(STD_PRIORITY) <<  " rider(s) in the "
         << STD_STR << " line." << endl;
}

string ParkSimulationClass::getPriorityAsStr(int priority)
{
    string priorityAsStr = STD_STR;

    if(priority == FP_PRIORITY)
    {
        priorityAsStr = FP_STR;
    }
    else if(priority == SFP_PRIORITY)
    {
        priorityAsStr = SFP_STR;
    }
    return priorityAsStr;
}

void ParkSimulationClass::printNumRidersInCar(int numSuperFastInCar,
                                              int numFastInCar,
                                              int numStandardInCar)
{
    cout << "Of these passengers, " << numSuperFastInCar << " was/were "
         << SFP_STR << ", " << numFastInCar
         << " was/were " << FP_STR << ", and " 
         << numStandardInCar << " was/were " << STD_STR 
         << "." << endl;
}

void ParkSimulationClass::printEventHandlingOutput(string eventType, 
                                                   int priority,
                                                   int numRidersInCar,
                                                   int numSuperFastInCar,
                                                   int numFastInCar,
                                                   int numStandardInCar)
{
    cout << endl;
    if(eventType == RIDER_TYPE)
    {
        cout << "------- Time " << riderArrivalTime << " -------" << endl;
        cout << "A " << getPriorityAsStr(priority) <<  " rider has arrived."
             << endl;
        printTotalRidersInLine();
        displayLines();
    }
    else
    {
        cout << "------- Time " << carArrivalTime << " -------" << endl;
        cout << "A car has arrived and " << numRidersInCar 
             << " passenger(s) have boarded." << endl;

        if(numRidersInCar < NUM_SEATS)
        {
            cout << "There are " << NUM_SEATS - numRidersInCar 
                 << " empty seats." << endl;
        }

        if(numRidersInCar > 0)
        {
            printNumRidersInCar(numSuperFastInCar, numFastInCar,
                                numStandardInCar);
        }
        cout << "The ride is about to start. Enjoy!" << endl << endl;
        printTotalRidersInLine();
        printNumRidersInEachLine();
        displayLines();
    }
}

void ParkSimulationClass::displayLines()
{
    cout << SFP_STR << " Riders: ";
    ride.printRidersInLine(SFP_PRIORITY);

    cout << FP_STR << " Riders: ";
    ride.printRidersInLine(FP_PRIORITY);

    cout << STD_STR << " Riders: "; 
    ride.printRidersInLine(STD_PRIORITY);
}

void ParkSimulationClass::printParkClosing()
{
    cout << endl;
    cout << "------- Time " << closingTime << " -------" << endl;
    cout << "The park is now closing. The ride will no longer accept new "
         << "arrivals but it will continue to service waiting riders." << endl;
    cout << "There are " << ride.getCurrNumRiders() << " riders left." << endl;
}

void ParkSimulationClass::printTotalRidersInLine()
{
    cout << "Currently, there is/are " << ride.getCurrNumRiders()
         << " total rider(s) in line." << endl;
}

