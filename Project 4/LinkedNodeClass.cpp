#include "LinkedNodeClass.h"


LinkedNodeClass::LinkedNodeClass(LinkedNodeClass *inPrev,
                                 const int &inVal,
                                 LinkedNodeClass *inNext)
{
    prevNode = inPrev;
    nodeVal = inVal;
    nextNode = inNext;
}

int LinkedNodeClass::getValue() const
{
    return nodeVal;
}

LinkedNodeClass* LinkedNodeClass::getNext() const
{
    return nextNode;
}

LinkedNodeClass* LinkedNodeClass::getPrev() const
{
    return prevNode;
}

void LinkedNodeClass::setNextPointerToNull()
{
    nextNode = 0;
}

void LinkedNodeClass::setPreviousPointerToNull()
{
    prevNode = 0;
}

void LinkedNodeClass::setBeforeAndAfterPointers()
{
    if(prevNode != 0)
    {
        prevNode->nextNode = this;
    }
    if(nextNode != 0)
    {
        nextNode->prevNode = this; 
    }
}
