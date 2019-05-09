#include "constants.h"
#include "random.h"
#include "EventClass.h"
#include "StatsClass.h"
#include "RiderClass.h"
#include "LinkedNodeClass.h"
#include "SortedListClass.h"
#include "FIFOQueueClass.h"
#include "AttractionClass.h"
#include "ParkSimulationClass.h"

/*
Jackie Chan
Written during April 13 - April 17, 2019

Purpose: Develop an event-driven simulation for a theme park
attraction (ex. the Space Mountain ride at Disneyland), and 
display potentially useful statistics regarding riders and 
wait times based on their priority access.
*/
int main(int argc, char* argv[])
{
    ParkSimulationClass sim(argc, argv);
    return 0;
}

