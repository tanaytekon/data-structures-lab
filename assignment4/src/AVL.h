#ifndef AVL_H
#define AVL_H
#include <string>
#include <fstream>
#include <queue>
using namespace std;

class AVL {
private:
    static int getHeight(AVL* root);
    AVL* left;
    AVL* right;
    int height;
    AVL* rightRotation();
    AVL* leftRotation();
public:
    static AVL* insert(AVL* &root, const string &key, const int &price);
    static AVL* search(AVL* root, const string &key);
    string key;
    int price;
    AVL(string key, int price);
    void levelOrderTraversal(ofstream &outputFile);
};

#endif