/** @file IntList.cpp
    @date 2013-01-29
    @brief Class to hold list of int values
*/

#include <iostream>
using namespace std;

#include "IntList.h"

//---------- IntListNode declaration ----------//

struct IntListNode
{
    int          data;
    IntListNode* next;

    IntListNode(int d, IntListNode* n) : data(d), next(n)
    {
        cout << "\n--created node with " << d << "--";
    }
    ~IntListNode()
    {
        // JUST TO PRINT THIS MESSAGE
        cout << "\n--destroyed node with " << data << "--";
    }
};


//---------- local functions using IntListNodes ----------//

// make a deep copy of list starting at origNode
IntListNode* copyNodes(IntListNode* origNode);

// delete all nodes in list starting at origNode and set origNode to 0
void deleteNodes(IntListNode*& origNode);

// return the pointer variable to the node that find is in
IntListNode*& findNode(IntListNode*& start, int find);


//---------- IntList definitions ----------//

IntList::IntList() : head(0) {}

IntList::IntList(const IntList& orig)
{
    head = copyNodes(orig.head);
}

IntList& IntList::operator=(const IntList& rhs)
{
    if (this != &rhs)
    {
        deleteNodes(head);
        head = copyNodes(rhs.head);
    }
    return *this;
}

IntList::~IntList()
{
    deleteNodes(head);
}

int addRec(IntListNode* h, int d)
{
    //if h points to null create new node with data.
    if(!h->next) h->next = new IntListNode(d, 0);
    else addRec(h->next, d);
}

void IntList::add(int n)
{
    addRec(head, n);
}

void IntList::remove(int d)
{
    // get the pointer to the node d is in (if it exists)
    IntListNode*& itsNode = findNode(head, d);

    // if there is any such node
    if (itsNode != 0)
    {
        IntListNode* old = itsNode; // copy the pointer
        itsNode = itsNode->next;    // unlink the node
        delete old;                 // return the node to the heap
    }
}

void IntList::display() const
{
    cout << "[";
    if (head != 0)
    {
        IntListNode* cur = head;
        while (cur->next != 0)
        {
            cout << cur->data << ", ";
            cur = cur->next;
        }
        cout << cur->data;
    }
    cout << "]";
}


//---------- definitions of local functions ----------//

IntListNode* copyNodes(IntListNode* origNode)
{
    if (origNode == 0)
        return 0;

    IntListNode* result = new IntListNode(origNode->data, 0);
    result->next = copyNodes(origNode->next);
    return result;

    // could be combined into one line:
    // return new IntListNode(origNode->data, copyNodes(origNode->next));
}

void deleteNodes(IntListNode*& origNode)
{
    // if there are no nodes, there's nothing to do!
    if (origNode == 0)
        return;

    // delete following nodes
    deleteNodes(origNode->next);
    // delete this node
    delete origNode;
    // set this pointer to 0
    origNode = 0;
}

IntListNode*& findNode(IntListNode*& start, int find)
{
    if (start == 0 || start->data == find) return start;

    return findNode(start->next, find);
}

