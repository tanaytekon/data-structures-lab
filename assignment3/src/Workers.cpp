#include "Workers.h"

//----------Worker Class Definitions------------------------------

//Returns minimum freeing time in all workers.
float Worker::findMinTime() {
    float minTime = 0;
    for(Cashier* cashier : Cashier::cashiers){
        if(!(cashier->isEmpty())){
            minTime = cashier->freeTime;
            break;
        }
    }
    for(Cashier* cashier : Cashier::cashiers) {
        if((cashier->freeTime < minTime) & (cashier->freeTime!=0)){
            minTime = cashier->freeTime;
        }
    }
    if(minTime==0){
        for(Barista* barista : Barista::baristas){
            if(!(barista->isEmpty())){
                minTime = barista->freeTime;
                break;
            }
        }
    }

    for(Barista* barista : Barista::baristas) {
        if((barista->freeTime < minTime) & (barista->freeTime!=0)) {
            minTime = barista->freeTime;
        }
    }
    return minTime;
}

//Runs for given time for all workers.
void Worker::run(const float& time, const int& model){
    Barista::run(time,model);
    Cashier::run(time,model);
    //Runs again for baristas in case a cashier give an order.
    Barista::run(time,model);
}

//Checks the worker has an order or not.
bool Worker::isEmpty() const{
    return(order==nullptr);
}


//----------Cashier Class Definitions------------------------------

//Initialization of static members for Cashier class.
std::vector<Cashier*> Cashier::cashiers;
Queue<Order>* Cashier::cashierQueue;

//Runs for given time for all cashiers.
void Cashier::run(const float& time, const int& model) {
    for(Cashier* cashier : Cashier::cashiers) {
        //If cashier has no order
        if(cashier->isEmpty()) {
            //If there is an order in the cashierQueue
            if(!(cashierQueue->isEmpty())){
                cashier->order = cashierQueue->dequeue();
                cashier->freeTime = time + cashier->order->orderTime;
                cashier->totalBusyTime += cashier->order->orderTime;
            }
            else {
                continue;
            }
        }
        //If cashier already has an order
        //If the order will be finished
        if(time == cashier->freeTime) {
            //Give order to barista queue with selected model
            if(model==1){
                Barista::enqueue(cashier->order);
            }
            else if(model==2){
                int baristaId = (cashier->id)/3;
                if(((cashier->id) % 3) != 0){
                    baristaId++;
                }
                Barista::enqueue(cashier->order,baristaId);
            }
            cashier->order = nullptr;
            cashier->freeTime = 0;
            //Take new order
            if(!(cashierQueue->isEmpty())) {
                cashier->order = cashierQueue->dequeue();
                cashier->freeTime = time + cashier->order->orderTime;
                cashier->totalBusyTime += cashier->order->orderTime;
                continue;
            }
            continue;
        }
        //Order will not be finished
    }
}

//Creates a cashier.
Cashier::Cashier(int id) {
    this->id = id;
    this->order = nullptr;
    this->freeTime = 0;
    this->totalBusyTime = 0;
}


//----------Barista Class Definitions------------------------------

//Initialization of static members for Barista class.
std::vector<Barista*> Barista::baristas;
Queue<Order>* Barista::baristaQueue;

//Runs for given time for all baristas.
void Barista::run(const float& time, const int& model) {
    Queue<Order>* currentQueue = nullptr;
    if(model==1){
        currentQueue = baristaQueue;
    }
    for(Barista* barista : Barista::baristas) {
        if(model==2){
            currentQueue = barista->queue;
        }
        // If barista has no order
        if(barista->isEmpty()){
            // If there is an order in the baristaQueue
            if(!(currentQueue->isEmpty())){
                barista->order = currentQueue->dequeue();
                barista->freeTime = time +  barista->order->brewTime;
                barista->totalBusyTime += barista->order->brewTime;
            }
            else {
                continue;
            }
        }
        //If barista already has an order
        //If the order will be finished
        if(time == barista->freeTime) {
            barista->order->turnaroundTime = time - barista->order->arrivalTime;
            barista->order = nullptr;
            barista->freeTime = 0;
            //Take new order
            if(!(currentQueue->isEmpty())) {
                barista->order = currentQueue->dequeue();
                barista->freeTime = time + barista->order->brewTime;
                barista->totalBusyTime += barista->order->brewTime;
                continue;
            }
            continue;
        }
        //Order will not be finished
    }
}

//Enqueues given order to corresponding barista list.
void Barista::enqueue(Order *order, int id) {

    Queue<Order>* currentQueue = nullptr;
    //If the model is first model(provided no id argument)
    if(id==-1){
        currentQueue = baristaQueue;
    }
    //If the model is second model(provided an id argument)
    else{
        // Find corresponding barista
        Barista* barista = nullptr;
        for(Barista* b : Barista::baristas){
            if(b->id==id){
                barista = b;
                break;
            }
        }
        currentQueue = barista->queue;
    }

    // Size operations for maxSize statistic
    currentQueue->size++;
    if(currentQueue->size > currentQueue->maxSize){
        currentQueue->maxSize = currentQueue->size;
    }

    //If currentQueue is empty
    if(currentQueue->isEmpty()) {
        currentQueue->enqueue(order);
        return;
    }
    Node<Order>* newNode = new Node<Order>(order);
    //Insert to head
    if(currentQueue->head->data->price < order->price) {
        newNode->next = currentQueue->head;
        currentQueue->head = newNode;
        return;
    }

    //Insert between nodes or tail
    Node<Order>* curNode = currentQueue->head;
    Node<Order>* prevNode;
    while(curNode!= nullptr) {
        if(curNode->data->price < order->price) {
            break;
        }
        prevNode = curNode;
        curNode = curNode->next;
    }
    prevNode->next = newNode;
    newNode->next = curNode;
    //Insert to tail
    if(curNode==nullptr) {
        prevNode->next = newNode;
        currentQueue->rear = newNode;
    }
}

//Creates a barista
Barista::Barista(int id) {
    this->id = id;
    this->order = nullptr;
    this->freeTime = 0;
    this->totalBusyTime = 0;
    this->queue = new Queue<Order>();
}

//Destructor of Barista class, deletes queue attribute.
Barista::~Barista() {
    delete queue;
}