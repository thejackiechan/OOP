#include "SortedListClass.h"
#include "LinkedNodeClass.h"
#include <iostream>
using namespace std;


SortedListClass::SortedListClass()
{
    head = 0;
    tail = 0;
}

SortedListClass::SortedListClass(const SortedListClass &rhs)
{   
    head = rhs.head;
    tail = rhs.tail; // added this for edgecase (cloning empty list)
    LinkedNodeClass *temp = head;
    
    if(temp != 0)
    {
        LinkedNodeClass *prevNode = new LinkedNodeClass(0,
                                                        temp->getValue(),
                                                        0);
        head = prevNode;
        
        while(temp->getNext() != 0) // check
        {
            temp = temp->getNext();
            LinkedNodeClass *newNode = new LinkedNodeClass(prevNode,
                                                           temp->getValue(),
                                                           0);
            newNode->setBeforeAndAfterPointers();
            prevNode = newNode;
        }
        tail = prevNode; // points to last newNode
    }
}

SortedListClass::~SortedListClass()
{
    clear();
}

void SortedListClass::clear()
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

void SortedListClass::insertValue(const int &valToInsert)
{
    if(head == 0) // empty list
    {
        LinkedNodeClass *newNode = new LinkedNodeClass(0,
                                                       valToInsert,
                                                       0);
        head = newNode;
        tail = newNode;
    }
    else // not empty
    {
        LinkedNodeClass *temp = head;
        int currVal = temp->getValue();
        
        if(valToInsert < currVal) // insert at head
        {
            LinkedNodeClass *newNode = new LinkedNodeClass(0,
                                                           valToInsert,
                                                           head);
            head = newNode;
            head->setBeforeAndAfterPointers();
        }
        else // insert after head or at end
        {	
            while(valToInsert >= currVal && temp->getNext() != 0) 
            {
                temp = temp->getNext();
                currVal = temp->getValue();
            }
            // CHANGES: added condition to check whether valToInsert is 
            // actually larger than currVal; without it, it is hard to
            // differentiate between adding 20 or 43 after {1,42}.
            // Both would add to end of list if this change was not made.
            if(temp->getNext() == 0 && valToInsert >= currVal) // after tail
            {
                LinkedNodeClass *newNode = new LinkedNodeClass(tail,
                                                               valToInsert,
                                                               0);
                tail = newNode;
                newNode->setBeforeAndAfterPointers();
            }
            else // insert between head and tail
            {
                LinkedNodeClass *newNode = new LinkedNodeClass(temp->getPrev(),
                                                               valToInsert,
                                                               temp);
                newNode->setBeforeAndAfterPointers();
            }
        }
    }
}

void SortedListClass::printForward() const
{
    LinkedNodeClass *temp = head;
    cout << "Forward List Contents Follow:" << endl;
    
    while(temp != 0)
    {
        cout << "  " << temp->getValue() << endl;
        temp = temp->getNext();
    }
    cout << "End Of List Contents" << endl;
}

void SortedListClass::printBackward() const
{
    LinkedNodeClass *temp = tail;
    cout << "Backward List Contents Follow:" << endl;
    
    while(temp != 0)
    {
        cout << "  " << temp->getValue() << endl;
        temp = temp->getPrev();
    }
    cout << "End Of List Contents" << endl;
}

bool SortedListClass::removeFront(int &theVal)
{
    bool wasRemoved = false;
    
    if(head != 0) // list is not empty
    {
        theVal = head->getValue();

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

bool SortedListClass::removeLast(int &theVal)
{
    bool wasRemoved = false;
    
    if(head != 0) // list is not empty
    {
        theVal = tail->getValue();

        if(head == tail) // head and tail pointing to same node
        {
            delete head;
            head = 0;
            tail = 0;
        }
        else // more than one node in list
        {
            tail = tail->getPrev();
            delete tail->getNext();
            tail->setNextPointerToNull();
        }
        wasRemoved = true;
    }
    return wasRemoved;
}

int SortedListClass::getNumElems() const
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

bool SortedListClass::getElemAtIndex(const int index, int &outVal) const
{
    bool isIndexValid = false;
    int currIndex = 0;
    LinkedNodeClass *temp = head;
    
    if(head != 0) // if not empty
    {
        while(currIndex < index && temp->getNext() != 0) 
        {
            temp = temp->getNext();
            currIndex++;
        }
        if(currIndex == index)
        {
            outVal = temp->getValue();
            isIndexValid = true;
        }
    }
    return isIndexValid;
}
