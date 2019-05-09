#include "EventClass.h"
#include "constants.h"
#include <string>

using namespace std;

EventClass::EventClass()
{
    eventTime = DEFAULT_TIME;
    eventType = DEFAULT_TYPE;
}

EventClass::EventClass(int inTime, string inType)
{
    eventTime = inTime;
    eventType = inType;
}

int EventClass::getTime() const
{
    return eventTime;
}

string EventClass::getType()
{
    return eventType;
}

bool EventClass::operator<(const EventClass &event) const
{
    bool result = true;

    if(eventTime >= event.eventTime){
        result = false;
    }
    return result;
}

bool EventClass::operator>=(const EventClass &event) const
{
    bool result = true;

    if(eventTime < event.eventTime){
        result = false;
    }
    return result;
}