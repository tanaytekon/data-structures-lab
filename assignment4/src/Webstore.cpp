#include "Webstore.h"
#include <fstream>
#include <vector>

void command_insert(BST* &bst, const string &category, const string &name, const int &price){
    //Search for category in BST
    if(bst == nullptr) {
        bst = new BST(category);
    }
    //Search for category in BST
    BST* primaryNode = BST::search(bst, category);
    //If category does not exist, create the category
    if(primaryNode == nullptr) {
        bst->insert(category);
        primaryNode = BST::search(bst, category);
    }
    //Insert name
    //Root node can change during the rotations, so it needs to be assigned every time.
    primaryNode->secondaryTree = AVL::insert(primaryNode->secondaryTree, name, price);
}

void command_printAllItems(BST* &bst, ofstream &outputFile) {
    //If BST is empty.
    if(bst == nullptr) {
        outputFile << "{}" << endl;
        return;
    }
    //If BST is not empty, print with levelOrderTraversal.
    outputFile << "{" << endl;
    bst->levelOrderTraversal(outputFile);
    outputFile << "}" << endl;
}

void command_printAllItemsInCategory(BST* &bst, const string &category, ofstream &outputFile) {
    //If BST is empty.
    if(bst == nullptr) {
        outputFile << "{}" << endl;
        return;
    }
    //If BST is not empty.
    //Find category primaryNode and corresponding secondaryTree
    BST* primaryNode = BST::search(bst,category);
    AVL* secondaryTree = primaryNode->secondaryTree;
    //Print the key
    outputFile << "{" << endl;
    outputFile << "\"" << primaryNode->key << "\":";
    //If secondaryTree is empty.
    if(secondaryTree == nullptr) {
        outputFile << "{}" << endl << "}";
        return;
    }
    //If secondaryTree is not empty, print with levelOrderTraversal.
    outputFile << endl;
    secondaryTree->levelOrderTraversal(outputFile);
    outputFile << "}" << endl;
}

void command_printItem(BST* &bst, const string &category, const string &name, ofstream &outputFile) {
    //Find category primaryNode.
    BST* primaryNode = BST::search(bst, category);
    //If the category does not exist.
    if(primaryNode == nullptr) {
        outputFile << "{}" << endl;
        return;
    }
    //If the category exist.
    //Find name secondaryNode.
    AVL* secondaryNode = AVL::search(primaryNode->secondaryTree, name);
    //If the name not found.
    if(secondaryNode == nullptr) {
        outputFile << "{}" << endl;
        return;
    }
    //If the name found, print category, name and price of given item.
    outputFile << "{" << endl;
    outputFile << "\"" << primaryNode->key << "\":" << endl;
    outputFile << "\t\"" << secondaryNode->key << "\":\"" << secondaryNode->price << "\"" << endl;
    outputFile << "}" << endl;
}

void command_updateData(BST* &bst, const string &category, const string &name, const int &newPrice) {
    //Find the corresponding secondaryTree and secondaryNode.
    AVL* secondaryTree = BST::search(bst,category)->secondaryTree;
    AVL* secondaryNode = AVL::search(secondaryTree, name);
    //Update the price.
    secondaryNode->price = newPrice;
}

void run(BST* &bst,const string &inputFileName, const string &outputFileName) {
    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFileName);
    string line;
    //Read all lines
    while(getline (inputFile,line)) {
        // Command and its arguments to vector
        vector<string> arguments;
        // Delete "\r" character if exist
        line = line.substr(0,line.find('\r'));
        // Separate command and each argument, and add them to vector.
        while(line.find('\t') < line.size()) {
            arguments.push_back(line.substr(0, line.find('\t')));
            line = line.substr(line.find('\t')+1);
        }
        arguments.push_back(line);

        string command = arguments.front();
        if(command=="insert"){
            string category = arguments[1];
            string name = arguments[2];
            int price = stoi(arguments[3]);
            command_insert(bst,category,name,price);
        }
        else if(command=="printAllItems"){
            outputFile << "command:printAllItems" << endl;
            command_printAllItems(bst, outputFile);
        }
        else if(command=="printAllItemsInCategory") {
            string category = arguments[1];
            outputFile << "command:printAllItemsInCategory" << "\t" << category << endl;
            command_printAllItemsInCategory(bst, category, outputFile);
        }
        else if(command=="printItem") {
            string category = arguments[1];
            string name = arguments[2];
            outputFile << "command:printItem" << "\t" << category << "\t" << name << endl;
            command_printItem(bst, category, name, outputFile);
        }
        else if(command=="find"){
            string category = arguments[1];
            string name = arguments[2];
            outputFile << "command:find" << "\t" << category << "\t" << name << endl;
            command_printItem(bst, category, name, outputFile);
        }
        else if(command=="updateData"){
            string category = arguments[1];
            string name = arguments[2];
            int newPrice = stoi(arguments[3]);
            command_updateData(bst, category, name, newPrice);
        }
    }
    inputFile.close();
    outputFile.close();
}