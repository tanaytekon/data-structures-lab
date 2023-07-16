#ifndef QUEUE_H
#define QUEUE_H

//Generic Node class
template<class T>
class Node{
    public:
        T* data;
        Node<T>* next;
        explicit Node(T* data);
};

//Generic Queue class
template<class T>
class Queue {
    public:
        Node<T>* head;
        Node<T>* rear;
        int size;
        int maxSize;
        Queue();
        ~Queue();
        void enqueue(T* data);
        T* dequeue();
        bool isEmpty() const;
};

#endif