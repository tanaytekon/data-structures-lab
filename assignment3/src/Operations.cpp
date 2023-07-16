#include "Operations.h"
#include "Workers.h"
#include <iomanip>

//Generic runModel function, performs a complete run for given model.
//Runs the program, writes the output and does the memory deallocation.
void runModel(const string& inputFileName, ofstream& outputFile, const int& model){
    run(inputFileName,outputFile, model);
    writeOutput(outputFile, model);
    cleanUp();
}

//Generic run function, only runs the program for given model.
void run(const string& inputFileName, ofstream& outputFile, const int& model) {

    //Read all lines from input file
    ifstream inputFile(inputFileName);
    string line;
    int lineCounter = 0;
    Cashier::cashierQueue = new Queue<Order>();
    Barista::baristaQueue = new Queue<Order>();
    while(getline (inputFile,line)) {
        //Delete "\r" character
        line = line.substr(0,line.find('\r'));

        //First line determines cashier and barista number
        if(lineCounter==0) {
            //Add cashiers
            Cashier::cashiers.reserve(stoi(line));
            for(int i=0; i < stoi(line); i++) {
                Cashier::cashiers.push_back(new Cashier(i+1));
            }
            //Add baristas
            Barista::baristas.reserve(stoi(line)/3);
            for(int i=0; i < stoi(line)/3; i++) {
                Barista::baristas.push_back(new Barista(i+1));
            }
            lineCounter++;
            continue;
        }

        //Second line determines number of orders
        if(lineCounter==1) {
            Order::orderList.reserve(stoi(line));
            lineCounter++;
            continue;
        }

        //Other lines: order information
        //Split line to order
        char delimiter = ' ';
        float arrivalTime_ = stof(line.substr(0, line.find(delimiter)));
        line = line.substr(line.find(delimiter)+1);
        float orderTime = stof(line.substr(0, line.find(delimiter)));
        line = line.substr(line.find(delimiter)+1);
        float brewTime = stof(line.substr(0, line.find(delimiter)));
        line = line.substr(line.find(delimiter)+1);
        float price = stof(line);

        //Add order to orders vector
        Order* order = new Order(arrivalTime_,orderTime,brewTime,price);
        Order::orderList.push_back(order);

        //Arrival of current order
        float arrivalTime = order->arrivalTime;
        float minTime = Worker::findMinTime();
        //Work until arrivalTime
        while(minTime <= arrivalTime){
            if(arrivalTime==0){
                break;
            }
            Worker::run(minTime,model);
            float prevMinTime = minTime;
            minTime = Worker::findMinTime();
            if(prevMinTime == minTime) {
                break;
            }
        }
        Worker::run(arrivalTime,model);
        //If there is an empty cashier, give order
        Cashier* cashier = nullptr;
        for(Cashier* c : Cashier::cashiers){
            if(c->isEmpty()){
                cashier = c;
                break;
            }
        }
        //If the cashier is empty
        if((cashier!= nullptr) & (Cashier::cashierQueue->isEmpty())) {
            cashier->order = order;
            cashier->freeTime = order->arrivalTime + order->orderTime;
            cashier->totalBusyTime += order->orderTime;
        }
        //If there is no empty cashier, add to cashier queue
        else{
            Cashier::cashierQueue->enqueue(order);
            Cashier::cashierQueue->size++;
            if(Cashier::cashierQueue->size > Cashier::cashierQueue->maxSize) {
                Cashier::cashierQueue->maxSize = Cashier::cashierQueue->size;
            }
        }
    }
    inputFile.close();

    // After all customers gave their orders, run until all orders finished
    float minTime = Worker::findMinTime();
    while(minTime!=0){
        Worker::run(minTime,model);
        minTime = Worker::findMinTime();
    }
}

//Generic writeOutput function, writes to output for given model.
void writeOutput(ofstream& outputFile, const int& model) {
    //Output
    outputFile << setprecision(2);
    outputFile << fixed;
    //Total running time
    float totalRunningTime = 0;
    for(Order* order : Order::orderList){
        if((order->turnaroundTime + order->arrivalTime) > totalRunningTime){
            totalRunningTime = order->turnaroundTime + order->arrivalTime;
        }
    }
    outputFile << totalRunningTime << '\n';
    //Max size of cashier queue
    outputFile << Cashier::cashierQueue->maxSize << '\n';
    //Max sizes of barista queues
    if(model==1){
        outputFile << Barista::baristaQueue->maxSize << '\n';
    }
    else if(model==2){
        for(Barista* barista : Barista::baristas){
            outputFile << barista->queue->maxSize << '\n';
        }
    }
    //Cashier utilization
    for(Cashier* cashier : Cashier::cashiers) {
        outputFile << (cashier->totalBusyTime / totalRunningTime) << '\n';
    }
    //Barista utilization
    for(Barista* barista : Barista::baristas) {
        outputFile << (barista->totalBusyTime / totalRunningTime) << '\n';
    }
    //Order turnarounds
    for(Order* order : Order::orderList) {
        if(order==Order::orderList.back()){
            outputFile << order->turnaroundTime;
            break;
        }
        outputFile << order->turnaroundTime << '\n';
    }
    outputFile.flush();
}

//Does the necessary memory deallocation in order to run another model and prevent memory leaks.
void cleanUp(){
    //Deletes all workers.
    for(Cashier* cashier : Cashier::cashiers) {
        delete cashier;
    }
    for(Barista* barista : Barista::baristas) {
        delete barista;
    }
    //Cleans cashier and barista list vectors.
    Cashier::cashiers.clear();
    Barista::baristas.clear();

    //Deletes static members(cashier and barista queues).
    delete Cashier::cashierQueue;
    delete Barista::baristaQueue;

    //Deletes all orders and cleans order list vector.
    for(Order* order : Order::orderList) {
        delete order;
    }
    Order::orderList.clear();
}