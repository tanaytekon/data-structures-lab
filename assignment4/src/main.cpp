#include "Webstore.h"

int main(int argc, char *argv[]){
    string inputFileName = argv[1];
    string outputFileName = argv[2];
    //Need to initialize an empty BST.
    BST* bst = nullptr;
    run(bst,inputFileName,outputFileName);
    return 0;
}