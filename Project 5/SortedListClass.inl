#include <iostream>
using namespace std;

template < class T >
SortedListClass< T >::SortedListClass()
{
    head = 0;
    tail = 0;
}

template < class T >
SortedListClass< T >::SortedListClass(const SortedListClass< T > &rhs)
{   
    head = rhs.head;
    tail = rhs.tail; // added this for edgecase (cloning empty list)
    LinkedNodeClass< T > *temp = head;
    
    if(temp != 0)
    {
        LinkedNodeClass< T > *prevNode = new LinkedNodeClass< T >
                                                    (0, temp->getValue(), 0);
        head = prevNode;
        
        while(temp->getNext() != 0) // check
        {
            temp = temp->getNext();
            LinkedNodeClass< T > *newNode = new LinkedNodeClass< T >
                                                        (prevNode,
                                                         temp->getValue(),
                                                         0);
            newNode->setBeforeAndAfterPointers();
            prevNode = newNode;
        }
        tail = prevNode; // points to last newNode
    }
}

template < class T >
SortedListClass< T >::~SortedListClass()
{
    clear();
}

template < class T >
void SortedListClass< T >::clear()
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
void SortedListClass< T >::insertValue(const T &valToInsert)
{
    if(head == 0) // empty list
    {
        LinkedNodeClass< T > *newNode = new LinkedNodeClass< T >
                                                    (0, 
                                                     valToInsert,
                                                     0);
        head = newNode;
        tail = newNode;
    }
    else // not empty
    {
        LinkedNodeClass< T > *temp = head;
        T currVal = temp->getValue();
        
        if(valToInsert < currVal) // insert at head
        {
            LinkedNodeClass< T > *newNode = new LinkedNodeClass< T >
                                                        (0,
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
            if(temp->getNext() == 0 && valToInsert >= currVal) // after tail
            {
                LinkedNodeClass< T > *newNode = new LinkedNodeClass< T >
                                                            (tail,
                                                             valToInsert,
                                                             0);
                tail = newNode;
                newNode->setBeforeAndAfterPointers();
            }
            else // insert between head and tail
            {
                LinkedNodeClass< T > *newNode = new LinkedNodeClass< T >
                                                            (temp->getPrev(),
                                                             valToInsert,
                                                             temp);
                newNode->setBeforeAndAfterPointers();
            }
        }
    }
}

template < class T >
void SortedListClass< T >::printForward() const
{
    LinkedNodeClass< T > *temp = head;
    cout << "Forward List Contents Follow:" << endl;
    
    while(temp != 0)
    {
        cout << "  " << temp->getValue() << endl;
        temp = temp->getNext();
    }
    cout << "End Of List Contents" << endl;
}

template < class T >
void SortedListClass< T >::printBackward() const
{
    LinkedNodeClass< T > *temp = tail;
    cout << "Backward List Contents Follow:" << endl;
    
    while(temp != 0)
    {
        cout << "  " << temp->getValue() << endl;
        temp = temp->getPrev();
    }
    cout << "End Of List Contents" << endl;
}

template < class T >
bool SortedListClass< T >::removeFront(T &theVal)
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

template < class T >
bool SortedListClass< T >::removeLast(T &theVal)
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

template < class T >
int SortedListClass< T >::getNumElems() const
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

template < class T >
bool SortedListClass< T >::getElemAtIndex(const int index, T &outVal) const
{
    bool isIndexValid = false;
    int currIndex = 0;
    LinkedNodeClass< T > *temp = head;
    
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
