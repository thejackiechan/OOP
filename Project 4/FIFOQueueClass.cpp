#include "FIFOQueueClass.h"
#include "LinkedNodeClass.h"
#include <iostream>
using namespace std;

FIFOQueueClass::FIFOQueueClass()
{
    head = 0;
    tail = 0;
}

FIFOQueueClass::~FIFOQueueClass()
{
    clear();
}

void FIFOQueueClass::enqueue(const int &newItem)
{
    if(head == 0) // empty list
    {
        LinkedNodeClass *newNode = new LinkedNodeClass(0, newItem, 0);
        head = newNode;
        tail = newNode;
    }
    else // not empty
    {
    	LinkedNodeClass *newNode = new LinkedNodeClass(tail, newItem, 0);
    	tail = newNode;
    	tail->setBeforeAndAfterPointers();
    }
}

bool FIFOQueueClass::dequeue(int &outItem)
{
    bool wasRemoved = false;
    
    if(head != 0) // list is not empty
    {
        outItem = head->getValue();
        
        if(head == tail) // head and tail pointing to same node
        {
            delete head;
            head = 0;
            tail = 0;
        }
        else // more than one node in list
        {
            head = head->getNext();
            delete head->getPrev();
            head->setPreviousPointerToNull();
        }
        wasRemoved = true;
    }
    return wasRemoved;
}

void FIFOQueueClass::print() const
{
    LinkedNodeClass *temp = head;
    
    while(temp != 0)
    {
        cout << temp->getValue() << " ";
        temp = temp->getNext();
    }
    cout << endl;
}

int FIFOQueueClass::getNumElems() const
{
    int size = 0;
    LinkedNodeClass *temp = head;
    
    while(temp != 0)
    {
        size++;
        temp = temp->getNext();
    }
    return size;	
}

void FIFOQueueClass::clear()
{
    while(head != 0 && head != tail)
    {
        head = head->getNext();
        delete head->getPrev();
    }
    delete head;
    head = 0;
    tail = 0;
}

