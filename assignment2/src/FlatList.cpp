#include "FlatList.h"

// Constructor of Flat class, creates a flat with given arguments.
Flat::Flat(int initial_bandwidth, int flat_id, bool is_empty) : initial_bandwidth(initial_bandwidth), ID(flat_id), is_empty(is_empty) {};

// Constructor of DoubleNode class, creates an unlinked DoubleNode with given flat information for FlatList.
DoubleNode::DoubleNode(Flat* flat) : flat(flat), next(nullptr), prev(nullptr) {};

// Destructor of DoubleNode class, deletes the flat information.
DoubleNode::~DoubleNode() {
    delete flat;
}

// Constructor of FlatList class, creates an empty FlatList.
FlatList::FlatList() : head(nullptr) {};

// Destructor of FlatList class, deletes all flats in the FlatList.
// Time complexity O(n)
FlatList::~FlatList() {
    DoubleNode* curNode = head;

    while(curNode!=nullptr) {
        DoubleNode* nextNode = curNode->next;
        delete curNode;
        curNode = nextNode;
    }
}