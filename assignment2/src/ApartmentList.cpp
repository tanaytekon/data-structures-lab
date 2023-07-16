#include "ApartmentList.h"

// Constructor of Apartment class, creates an apartment with given arguments and creates an empty FlatList for that apartment.
Apartment::Apartment(string name, int max_bandwidth) : name(name), max_bandwidth(max_bandwidth), flatList(new FlatList()), used_bandwidth(0) {};

// Destructor of Apartment class, deletes the flatList of that apartment.
// Deletion of flatList leads the deletion of all flats in that flatList.
Apartment::~Apartment() {
    if(flatList!=nullptr) {
        delete flatList;
    }
};

// Constructor of Node class, creates an unlinked Node with given apartment information for ApartmentList.
Node::Node(Apartment* apartment) : apartment(apartment), next(nullptr) {};

// Destructor of Node class, deletes the apartment information.
Node::~Node() {
    delete apartment;
}

// Constructor of ApartmentList class, creates an empty ApartmentList.
ApartmentList::ApartmentList() : head(nullptr), tail(nullptr) {};

// Destructor of ApartmentList class, deletes all apartments in the ApartmentList.
// Time complexity O(n)
ApartmentList::~ApartmentList() {
    Node* curNode = head;
    while(curNode!=tail) {
        Node* next = curNode->next;
        delete curNode;
        curNode = next;
    }
    if(curNode!=nullptr) {
        delete curNode;
    }
};

// Adds an apartment to the given position with given name and max bandwidth.
// Time complexity: O(n) (corresponding operations are stated below with comments).
void ApartmentList::add_apartment(string apartment_name, string position, int max_bandwidth) {

    // Interprets position
    Node* newNode = new Node(new Apartment(apartment_name, max_bandwidth));
    if(position=="head") {
        // Insert to empty apartmentList
        if(head== nullptr) {
            newNode->next = newNode;
            head = tail = newNode;
            return;
        }
        position = "before_" + head->apartment->name;
    }
    string indicator = position.substr(0, position.find("_"));
    string place = position.substr(position.find("_")+1);

    // Find placeNode and prevPlaceNode
    // Time complexity for finding corresponding apartment is O(n).
    Node* prevPlaceNode = head;
    Node* placeNode = prevPlaceNode->next;
    while(prevPlaceNode->next->apartment->name!=place) {
        prevPlaceNode = prevPlaceNode->next;
        placeNode = prevPlaceNode->next;
    }

    // Insertions take O(1) time.
    // Insert before
    if(indicator=="before"){
        newNode->next = placeNode;
        prevPlaceNode->next = newNode;
        if(head==placeNode) {
            head=newNode;
        }
        return;
    }
    // Insert after
    if(indicator=="after"){
        newNode->next=placeNode->next;
        placeNode->next=newNode;
        if(tail==placeNode) {
            tail = newNode;
        }
        return;
    }
}

// Adds a flat to the given position with given id and initial bandwidth.
// Time complexity: O(n) (corresponding operations are stated below with comments).
void ApartmentList::add_flat(string apartment_name, int index, int initial_bandwidth, int flat_id) {

    // Find corresponding apartment and flatList
    // Time complexity for finding corresponding apartment is O(n).
    Node* apartmentNode = head;
    while(apartmentNode->apartment->name!=apartment_name) {
        apartmentNode = apartmentNode->next;
    }
    FlatList* flatList = apartmentNode->apartment->flatList;

    // Check bandwidths
    bool is_empty = 0;
    int used_bandwidth = apartmentNode->apartment->used_bandwidth;
    int max_bandwidth = apartmentNode->apartment->max_bandwidth;
    if(used_bandwidth+initial_bandwidth > max_bandwidth) {
        initial_bandwidth = max_bandwidth-used_bandwidth;
        if(initial_bandwidth==0) {
            is_empty = 1;
        }
    }
    apartmentNode->apartment->used_bandwidth += initial_bandwidth;

    // Create newFlatNode
    DoubleNode* newFlatNode = new DoubleNode(new Flat(initial_bandwidth, flat_id, is_empty));

    // Insertions take O(1) time.
    // Insert to empty FlatList
    if(flatList->head==nullptr) {
        flatList->head = newFlatNode;
        return;
    }
    // Insert to beginning
    if(index==0) {
        newFlatNode->next = flatList->head;
        flatList->head->prev = newFlatNode;
        flatList->head = newFlatNode;
        return;
    }

    // Find prevFlatNode
    // Time complexity for finding place of insertion is O(n).
    int curIndex = 1;
    DoubleNode* prevFlatNode = flatList->head;
    while (index != curIndex) {
        prevFlatNode = prevFlatNode->next;
        curIndex++;
    }

    // Insert to last
    if(prevFlatNode->next==nullptr) {
        newFlatNode->prev = prevFlatNode;
        prevFlatNode->next = newFlatNode;
        return;
    }
    // Insert between the elements
    newFlatNode->prev = prevFlatNode;
    newFlatNode->next = prevFlatNode->next;
    prevFlatNode->next->prev = newFlatNode;
    prevFlatNode->next = newFlatNode;
}

// Removes the given apartment from ApartmentList.
ApartmentList* ApartmentList::remove_apartment(string apartment_name) {

    // If there is one apartment
    if(head==tail) {
        delete head;
        head = tail = nullptr;
        return this;
    }

    // Remove between elements and remove tail
    // Find prevApartmentNode and curApartmentNode
    // Time complexity is O(n) for finding corresponding apartment.
    Node* prevApartmentNode = head;
    while(prevApartmentNode->next->apartment->name!=apartment_name) {
        prevApartmentNode = prevApartmentNode->next;
    }
    Node* curApartmentNode = prevApartmentNode->next;

    // Change links
    prevApartmentNode->next = curApartmentNode->next;
    // Remove tail
    if(curApartmentNode==tail) {
        tail = prevApartmentNode;
    }
    // Remove head
    if(curApartmentNode==head) {
        head = curApartmentNode->next;
    }

    // Class destructors take care of deletion of the flats.
    // Time complexity for deleting all flats is O(n).
    delete curApartmentNode;
    return this;
}

// Makes given flat's is_empty flag true.
void ApartmentList::make_flat_empty(string apartment_name, int flat_id) {

    // Find corresponding apartment and flat
    Node* apartmentNode = head;
    while(apartmentNode->apartment->name != apartment_name) {
        apartmentNode = apartmentNode->next;
    }
    DoubleNode* flatNode = apartmentNode->apartment->flatList->head;
    while(flatNode->flat->ID!=flat_id) {
        flatNode = flatNode->next;
    }

    flatNode->flat->is_empty = 1;
    apartmentNode->apartment->used_bandwidth -= flatNode->flat->initial_bandwidth;
    flatNode->flat->initial_bandwidth = 0;
}

// Finds sum of max bandwidth of all apartments.
int ApartmentList::find_sum_of_max_bandwidths() {

    // Find corresponding apartment and take sum
    Node* apartmentNode = head;
    int sum_of_max_bandwidth = 0;
    while(apartmentNode!=tail) {
        sum_of_max_bandwidth += apartmentNode->apartment->max_bandwidth;
        apartmentNode = apartmentNode->next;
    }
    sum_of_max_bandwidth += apartmentNode->apartment->max_bandwidth;

    return sum_of_max_bandwidth;
}

// Merges given two apartments.
void ApartmentList::merge_two_apartments(string apartment_name_1, string apartment_name_2) {

    // Find corresponding apartments
    Node* apartmentNode1 = head;
    while(apartmentNode1->apartment->name!=apartment_name_1) {
        apartmentNode1= apartmentNode1->next;
    }
    Node* apartmentNode2 = head;
    while(apartmentNode2->apartment->name!=apartment_name_2) {
        apartmentNode2 = apartmentNode2->next;
    }
    apartmentNode1->apartment->max_bandwidth += apartmentNode2->apartment->max_bandwidth;
    apartmentNode1->apartment->used_bandwidth += apartmentNode2->apartment->used_bandwidth;

    // Find needed flatNodes
    DoubleNode* apartment2HeadFlatNode = apartmentNode2->apartment->flatList->head;
    // If the second apartment is empty
    if(apartment2HeadFlatNode==nullptr) {
        remove_apartment(apartment_name_2);
        return;
    }

    DoubleNode* apartment1LastFlatNode = apartmentNode1->apartment->flatList->head;
    // If the first apartment is empty
    if(apartment1LastFlatNode==nullptr) {
        apartmentNode1->apartment->flatList->head = apartment2HeadFlatNode;
        apartmentNode2->apartment->flatList->head = nullptr;
        remove_apartment(apartment_name_2);
        return;
    }
    while(apartment1LastFlatNode->next!= nullptr) {
        apartment1LastFlatNode = apartment1LastFlatNode->next;
    }

    // Link operations
    apartment1LastFlatNode->next = apartment2HeadFlatNode;
    apartment2HeadFlatNode->prev = apartment1LastFlatNode;

    apartmentNode2->apartment->flatList->head = nullptr;
    remove_apartment(apartment_name_2);
}

// Relocates the given flats to the same given apartment.
void ApartmentList::relocate_flats_to_same_apartments(string new_apartment_name, int flat_id_to_shift, vector<int> flat_id_list) {

    // Find new apartment
    Node* newApartmentNode = head;
    while(newApartmentNode->apartment->name != new_apartment_name) {
        newApartmentNode = newApartmentNode->next;
    }
    // Find corresponding flat
    DoubleNode* flatToShift = newApartmentNode->apartment->flatList->head;
    while(flatToShift->flat->ID != flat_id_to_shift) {
        flatToShift = flatToShift->next;
    }

    // Insert each flat in flat_id_list
    for(int curFlatId: flat_id_list) {

        // Find flat
        Node* curApartmentNode = head;
        DoubleNode* curFlatNode;
        bool isFlatFound = 0;
        // Traverse in apartmentList
        while(curApartmentNode != nullptr and !isFlatFound) {
            // Traverse in flatList
            curFlatNode = curApartmentNode->apartment->flatList->head;
            while(curFlatNode != nullptr){
                // If the flat is found, end the loops
                if(curFlatNode->flat->ID == curFlatId) {
                    curApartmentNode->apartment->max_bandwidth -= curFlatNode->flat->initial_bandwidth;
                    curApartmentNode->apartment->used_bandwidth -= curFlatNode->flat->initial_bandwidth;
                    newApartmentNode->apartment->max_bandwidth += curFlatNode->flat->initial_bandwidth;
                    newApartmentNode->apartment->used_bandwidth += curFlatNode->flat->initial_bandwidth;
                    isFlatFound = 1;
                    break;
                }
                curFlatNode = curFlatNode->next;
            }
            // Continue
            curApartmentNode = curApartmentNode->next;
        }

        // Unlink flat
        if(curFlatNode->prev!=nullptr) {
            curFlatNode->prev->next = curFlatNode->next;
        }
        else {
            curApartmentNode->apartment->flatList->head = curFlatNode->next;
        }
        if(curFlatNode->next!=nullptr) {
            curFlatNode->next->prev = curFlatNode->prev;
        }

        // Link to new location
        DoubleNode* prevFlatNode = flatToShift->prev;
        curFlatNode->next = flatToShift;
        curFlatNode->prev = prevFlatNode;
        if(prevFlatNode!=nullptr) {
            prevFlatNode->next = curFlatNode;
        }
        flatToShift->prev = curFlatNode;

        // Set flatList's head.
        while(curFlatNode->prev != nullptr) {
            curFlatNode = curFlatNode->prev;
        }
        newApartmentNode->apartment->flatList->head = curFlatNode;
    }
}