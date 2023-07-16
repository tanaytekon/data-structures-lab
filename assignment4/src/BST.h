#ifndef BST_H
#define BST_H
#include "AVL.h"

class BST {
private:
    BST* left;
    BST* right;
public:
    static BST* search(BST* root, const string &key);
    string key;
    AVL* secondaryTree;
    BST(string key);
    void insert(const string &key);
    void levelOrderTraversal(ofstream &outputFile);
};

#endif