#include "AVL.h"

AVL::AVL(string key, int price) : key(key), price(price), left(nullptr), right(nullptr), height(1){}

AVL* AVL::insert(AVL* &root, const string &key, const int &price) {
    // If root is null, create a new node and return it
    if(root == nullptr) {
        root = new AVL(key, price);
        return root;
    }
    // If key is smaller than root's key, insert into left subtree
    if (key < root->key){
        root->left = insert(root->left, key, price);
    }
    // If key is greater than root's key, insert into right subtree
    if (key > root->key) {
        root->right = insert(root->right, key, price);
    }
    // Update the height and calculate the balance
    root->height = 1 + ((getHeight(root->left) > getHeight(root->right)) ? getHeight(root->left) : getHeight(root->right));
    int balance = getHeight(root->left) - getHeight(root->right);
    // Rotations
    // Single rotation cases:
    // Insertion into the left subtree of the left child
    if ((balance > 1) && (key < root->left->key)) {
        return root->rightRotation();
    }
    // Insertion into the right subtree of the right child
    if ((balance < -1) && (key > root->right->key)) {
        return root->leftRotation();
    }
    // Double rotation cases:
    // Insertion into the right subtree of the left child
    // Left-right double rotation
    if ((balance > 1) && (key > root->left->key)) {
        root->left = root->left->leftRotation();
        return root->rightRotation();
    }
    // Insertion into the left subtree of the right child
    // Right-left double rotation
    if ((balance < -1) && (key < root->right->key)) {
        root->right = root->right->rightRotation();
        return root->leftRotation();
    }
    return root;
}

int AVL::getHeight(AVL* root) {
    return (root != nullptr) ? root->height : 0;
}

AVL* AVL::rightRotation() {
    //root = k2
    AVL* k1 = left;
    AVL* B = k1->right;

    k1->right = this;
    left = B;

    // Update heights
    height = 1 + ((getHeight(left) > getHeight(right)) ? getHeight(left) : getHeight(right));
    k1->height = 1 + ((getHeight(k1->left) > getHeight(k1->right)) ? getHeight(k1->left) : getHeight(k1->right));

    // Return new root
    return k1;
}

AVL* AVL::leftRotation() {
    //root = k1
    AVL* k2 = right;
    AVL* B = k2->left;

    k2->left = this;
    right = B;

    // Update heights
    height = 1 + ((getHeight(left) > getHeight(right)) ? getHeight(left) : getHeight(right));
    k2->height = 1 + ((getHeight(k2->left) > getHeight(k2->right)) ? getHeight(k2->left) : getHeight(k2->right));

    // Return new root
    return k2;
}

AVL* AVL::search(AVL* root, const string &key) {
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

void AVL::levelOrderTraversal(ofstream &outputFile) {
    //If root is not empty, create a queue and enqueue the root.
    queue<AVL*> nodes;
    nodes.push(this);

    //Print until no nodes left in the queue.
    while (!nodes.empty()) {
        AVL* node = nodes.front();
        //Print item name and price.
        outputFile << "\t\"" << node->key << "\":\"" << node->price << "\"" << endl;
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