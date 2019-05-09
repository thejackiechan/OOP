#include <iostream>
using namespace std;

template < class T >
FIFOQueueClass< T >::FIFOQueueClass()
{
    head = 0;
    tail = 0;
}

template < class T >
FIFOQueueClass< T >::~FIFOQueueClass()
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

template < class T >
void FIFOQueueClass< T >::enqueue(const T &newItem)
{
    if(head == 0) // empty list
    {
        LinkedNodeClass< T > *newNode = new LinkedNodeClass< T >(0, newItem,
                                                                 0);
        head = newNode;
        tail = newNode;
    }
    else // not empty
    {
    	LinkedNodeClass< T > *newNode = new LinkedNodeClass< T >(tail, newItem,
                                                                 0);
    	tail = newNode;
    	tail->setBeforeAndAfterPointers();
    }
}

template < class T >
bool FIFOQueueClass< T >::dequeue(T &outItem)
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

template < class T >
void FIFOQueueClass< T >::print() const
{
    LinkedNodeClass< T > *temp = head;
    
    while(temp != 0)
    {
        cout << temp->getValue() << " ";
        temp = temp->getNext();
    }
    cout << endl;
}

template < class T >
int FIFOQueueClass< T >::getNumElems() const
{
    int size = 0;
    LinkedNodeClass< T > *temp = head;
    
    while(temp != 0)
    {
        size++;
        temp = temp->getNext();
    }
    return size;	
}

