#include "Order.h"

//Initialization of static member.
std::vector<Order*> Order::orderList;

//Creates an order object from given information.
Order::Order(float arrivalTime, float orderTime, float brewTime, float price) : arrivalTime(arrivalTime), orderTime(orderTime), brewTime(brewTime), price(price), turnaroundTime(0){}