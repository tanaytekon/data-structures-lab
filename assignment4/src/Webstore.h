#ifndef WEBSTORE_H
#define WEBSTORE_H
#include "BST.h"

void command_insert(BST* &bst, const string &category, const string &name, const int &price);

void command_printAllItems(BST* &bst, ofstream &outputFile);

void command_printAllItemsInCategory(BST* &bst, const string &category, ofstream &outputFile);

void command_printItem(BST* &bst, const string &category, const string &name, ofstream &outputFile);

void command_updateData(BST* &bst, const string &category, const string &name, const int &newPrice);

void run(BST* &bst,const string &inputFileName, const string &outputFileName);

#endif