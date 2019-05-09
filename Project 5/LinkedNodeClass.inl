template < class T >
LinkedNodeClass< T >::LinkedNodeClass(LinkedNodeClass *inPrev,
                                      const T &inVal,
                                      LinkedNodeClass *inNext)
{
    prevNode = inPrev;
    nodeVal = inVal;
    nextNode = inNext;
}

template < class T >
T LinkedNodeClass< T >::getValue() const
{
    return nodeVal;
}

template < class T >
LinkedNodeClass< T >* LinkedNodeClass< T >::getNext() const
{
    return nextNode;
}

template < class T >
LinkedNodeClass< T >* LinkedNodeClass< T >::getPrev() const
{
    return prevNode;
}

template < class T >
void LinkedNodeClass< T >::setNextPointerToNull()
{
    nextNode = 0;
}

template < class T >
void LinkedNodeClass< T >::setPreviousPointerToNull()
{
    prevNode = 0;
}

template < class T >
void LinkedNodeClass< T >::setBeforeAndAfterPointers()
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
