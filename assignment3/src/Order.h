#ifndef ORDER_H
#define ORDER_H
#include <vector>

//Order class holds information of every given order.
class Order {
    public:
        static std::vector<Order*> orderList; //Holds all the orders. Used for statistics.
        float arrivalTime;
        float orderTime;
        float brewTime;
        float price;
        float turnaroundTime;
        Order(float arrivalTime, float orderTime, float brewTime, float price);
};

#endif