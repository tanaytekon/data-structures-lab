#include "BST.h"

//Constructor
BST::BST(string key) : key(key), left(nullptr), right(nullptr), secondaryTree(nullptr){}

//Recursive insert function
void BST::insert(const string &key) {
    //If key is smaller than root's key
    if (key < this->key){
        if(left != nullptr) {
            left->insert(key);
        }
        else {
            left = new BST(key);
        }
    }
    //If given key is greater than node's key
    if (key > this->key) {
        if(right != nullptr) {
            right->insert(key);
        }
        else {
            right = new BST(key);
        }
    }
}

//Recursive search function
//Returns the found node
BST* BST::search(BST* root, const string &key) {
    //If key not found.
    if (root == nullptr) {
        return nullptr;
    }
    //If key found.
    if (root->key == key) {
        return root;
    }
    //If key is smaller than root's key, search left subtree.
    if (key < root->key) {
        return search(root->left, key);
    }
    //If key is greater than node's key, search right subtree.
    if (key > root->key) {
        return search(root->right, key);
    }
    return nullptr;
}

void BST::levelOrderTraversal(ofstream &outputFile) {
    //If root is not empty, create a queue and enqueue the root.
    queue<BST*> nodes;
    nodes.push(this);

    //Print until no nodes left in the queue.
    while (!nodes.empty()) {
        BST* node = nodes.front();
        //Print category name.
        outputFile << "\"" << node->key << "\":" << endl;

        //If secondaryTree is empty.
        if(node->secondaryTree == nullptr){
            outputFile << "{}" << endl;
        }

        node->secondaryTree->levelOrderTraversal(outputFile);
        nodes.pop();

        //If node has a left child, enqueue it.
        if (node->left != nullptr) {
            nodes.push(node->left);
        }
        //If node has a right child, enqueue it.
        if (node->right != nullptr) {
            nodes.push(node->right);
        }
    }
}