#ifndef FLATLIST_H
#define FLATLIST_H

// Flat class holds all information about that flat.
class Flat {
    public:
        int initial_bandwidth;
        int ID;
        bool is_empty;
        Flat(int initial_bandwidth, int flat_id, bool is_empty);
};

// DoubleNode class is a doubly linked list node which used in FlatList class.
// Holds corresponding flat's information, next node and previous node.
class DoubleNode{
    public:
        Flat* flat;
        DoubleNode* next;
        DoubleNode* prev;
        DoubleNode(Flat* flat);
        ~DoubleNode();
};

// FlatList class is the doubly linked list which holds nodes of flats.
class FlatList {
    public:
        DoubleNode* head;
        FlatList();
        ~FlatList();
};

#endif