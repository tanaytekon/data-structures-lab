#include "Queue.h"

//Creates an empty Node with given data.
template<class T>
Node<T>::Node(T* data) : data(data), next(nullptr){}

//Creates an empty Queue.
template<class T>
Queue<T>::Queue() : head(nullptr), rear(nullptr), size(0), maxSize(0){}

//Destructor of Queue class, deletes queue object and all nodes inside.
//Does not delete data inside. It must be deleted manually.
template<class T>
Queue<T>::~Queue() {
    Node<T>* curNode = head;
    while (curNode!=nullptr) {
        Node<T>* nextNode = curNode->next;
        delete curNode;
        curNode = nextNode;
    }
}

//Enqueues to the queue.
template<class T>
void Queue<T>::enqueue(T* data) {
    Node<T>* newNode = new Node<T>(data);

    // If the queue is empty
    if((head==nullptr) and (rear==nullptr)) {
        head = rear = newNode;
        return;
    }

    // If the queue is not empty
    rear->next = newNode;
    rear = newNode;
}

//Dequeues from the queue.
template<class T>
T* Queue<T>::dequeue() {
    // If the queue is empty
    if(head==nullptr) {
        return nullptr;
    }

    // If the queue is not empty
    size--;
    Node<T>* deletedNode = head;
    T* returnValue = deletedNode->data;
    head = head->next;
    if(head==nullptr){
        rear = nullptr;
    }
    delete deletedNode;
    return returnValue;
}

//Checks the queue if it is empty or not.
template<class T>
bool Queue<T>::isEmpty() const {
    return (head == nullptr);
}