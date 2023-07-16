#ifndef WORKERS_H
#define WORKERS_H
#include "Order.h"
#include "Queue.h"
#include "Queue.cpp"
// Instantiation of the templates.
template class Node<Order>;
template class Queue<Order>;

class Worker {
    public:
        static float findMinTime(); // Returns minimum freeing time in all workers.
        static void run(const float& time, const int& model); // Runs for given time for all workers.
        int id;
        Order* order; // Current order of the worker.
        float totalBusyTime;
        float freeTime;
        bool isEmpty() const; // Checks the worker has an order or not.
};

class Cashier : public Worker{
    public:
        static std::vector<Cashier*> cashiers; // List of cashiers.
        static Queue<Order>* cashierQueue; // Single cashier queue for both models.
        static void run(const float& time, const int& model); // Runs for given time for all cashiers.
        explicit Cashier(int id);
};

class Barista : public Worker{
    public:
        static std::vector<Barista*> baristas; // List of baristas.
        static Queue<Order>* baristaQueue; // Single barista queue for first model.
        static void run(const float& time, const int& model); // Runs for given time for all baristas.
        static void enqueue(Order* order, int id=-1); // Enqueues given order to corresponding barista list.
        Queue<Order>* queue; // There is a queue for each barista for second model.
        explicit Barista(int id);
        ~Barista();
};

#endif