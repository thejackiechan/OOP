#ifndef _LINKEDNODECLASS_H_
#define _LINKEDNODECLASS_H_

// The list node class will be the data type for individual nodes of a
// doubly-linked data structure.
class LinkedNodeClass
{
    private:
        LinkedNodeClass *prevNode; // Will point to the node that comes
                                   // before this node in the data structure.
                                   // Will be NULL if this is the first node.
        int nodeVal;               // The value contained within this node.
        LinkedNodeClass *nextNode; // Will point to the node that comes after
                                   // this node in the data structure. Will
                                   // be NULL if this is the last node.
    public:
        // The ONLY constructor for the linked node class - it takes in the
        // newly created node's previous pointer, value, and next pointer,
        // and assigns them.
        LinkedNodeClass(
        LinkedNodeClass *inPrev, // Address of node that comes before this
        const int &inVal,        // Value to be contained in this node
        LinkedNodeClass *inNext  // Address of node that comes after this
        );
    
    // Returns the value stored within this node.
    int getValue() const;
    
    // Returns the address of the node that follows this node.
    LinkedNodeClass* getNext() const;
    
    // Returns the address of the node that comes before this node.
    LinkedNodeClass* getPrev() const;
    
    // Sets the object's next pointer to NULL.
    void setNextPointerToNull();
    
    // Sets the object's previous pointer to NULL.
    void setPreviousPointerToNull();
    
    void setBeforeAndAfterPointers();
};


#endif