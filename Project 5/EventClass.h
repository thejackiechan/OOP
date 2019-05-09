#ifndef _EVENTCLASS_H_
#define _EVENTCLASS_H_

#include "constants.h"
#include <string>

using namespace std;

// The EventClass represents either a rider or car arrival.
class EventClass
{
    private:
        int eventTime;     // Time at which the event begins
        string eventType;

    public:
        EventClass();
        EventClass(int inTime, string inType);
        int getTime() const;
        string getType();

        // Overloading is required so that events are sorted
        // by eventTime in the SortedListClass.
        bool operator<(const EventClass &event) const;
        bool operator>=(const EventClass &event) const;
};


#endif