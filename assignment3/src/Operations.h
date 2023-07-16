#ifndef OPERATIONS_H
#define OPERATIONS_H
#include <string>
#include <fstream>
using namespace std;

//Generic runModel function, performs a complete run for given model.
//Runs the program, writes the output and does the memory deallocation.
void runModel(const string& inputFileName, ofstream& outputFile, const int& model);

//Generic run function, only runs the program for given model.
void run(const string& inputFileName, ofstream& outputFile, const int& model);

//Generic writeOutput function, writes to output for given model.
void writeOutput(ofstream& outputFile, const int& model);

//Does the necessary memory deallocation in order to run another model and prevent memory leaks.
void cleanUp();

#endif