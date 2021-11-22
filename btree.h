#ifndef BTREE_H
#define BTREE_H

#include <string>
#include <fstream>
#include "node.h"

class BTree {
        
        Node *root;     // pointer to root node
        int degree;     // minimum degree

    public:

        // BTree constructor
        BTree(int degree);
 
        // main insert function 
        void insert(std::string key);
 
        // traverse and display the tree
        void display();

        // condition ? result1 : result2
        // check if root is nullptr, else search for key
        Node* search(std::string key) {
            return (root == nullptr) ? nullptr : root->search(key);
        }
        
        // read in text file for insertion
        std::vector<std::string> readInString(std::string filename);

};

#endif
