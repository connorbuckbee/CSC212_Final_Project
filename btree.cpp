#include "btree.h"

// BTree constuctor, initialize with maximum (degree) child Nodes
BTree::BTree(int degree) {
    root = new Node(degree, true);
}

// main insertion function
void BTree::insert(std::string newKey) {
    
    // make space for newNode and key
    Node* newNode = nullptr;
    std::string key = "";
	
    // insert key into BTree
    root->insert(newKey, &key, newNode);
 
    // if newNode is not nullptr, then root needs to be
    // split - let us create new root
    if (newNode != nullptr) {
        root = root->makeNewRoot(key, newNode);
    }
}

// traverse BTree starting at root Node, print as we go 
void BTree::display() {
    root->traverse(0);
}

std::vector<std::string> BTree::readInString(std::string filename) {

    // create input stream and open file
    std::fstream inputF;
    inputF.open(filename.c_str());

    // create input string and vector;
    std::string line;
    std::vector<std::string> array;

	// push strings to vector until complete
    while (inputF >> line) {
        array.push_back(line);
    }

    return array;
}
