#include "Operations.h"

int main(int argc, char *argv[]){
    ofstream outputFile(argv[2]);
    //Run fist model
    runModel(argv[1], outputFile, 1);
    outputFile << "\n\n";

    //Run second model
    runModel(argv[1], outputFile, 2);
    outputFile.close();
    return 0;
}