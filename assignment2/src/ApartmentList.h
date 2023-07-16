#ifndef APARTMENTLIST_H
#define APARTMENTLIST_H
#include "FlatList.h"
#include <string>
#include <vector>
using namespace std;

// Apartment class holds all information about that apartment.
class Apartment {
    public:
        int max_bandwidth;
        int used_bandwidth;
        string name;
        FlatList* flatList;
        Apartment(string name, int max_bandwidth);
        ~Apartment();
};

// Node class is a circular linked list node which used in ApartmentList class.
// Holds corresponding apartment's information and next node.
class Node{
    public:
        Apartment* apartment;
        Node* next;
        Node(Apartment* apartment);
        ~Node();
};

// ApartmentList class is the circular linked list which holds nodes of apartments and contains all command functions.
// Command functions do the specified operations which are stated in the pdf.
class ApartmentList {
    public:
        Node* head;
        Node* tail;
        ApartmentList();
        ~ApartmentList();
        void add_apartment(string apartment_name, string position, int max_bandwidth);
        void add_flat(string apartment_name, int index, int initial_bandwidth, int flat_id);
        ApartmentList* remove_apartment(string apartment_name);
        void make_flat_empty(string apartment_name, int flat_id);
        int find_sum_of_max_bandwidths();
        void merge_two_apartments(string apartment_name_1, string apartment_name_2);
        void relocate_flats_to_same_apartments(string new_apartment_name, int flat_id_to_shift, vector<int> flat_id_list);
};

#endif