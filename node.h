#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <vector>

class Node {
    
        int degree;                           // minimum degree
        bool leaf;                            // true when node is a leaf, else false
        std::vector<std::string> keyVec;      // vector of keys
        std::vector<Node*> childVec;          // vector of pointers to child nodes

    public:

        // Node constructor
        Node(int degree, bool leaf);

        // BTree::insert helper function
        // insert key into given Node - if child is split, insert *key entry 
        // into key vector, and newNode pointer into childVec vector of this->node 
        void insert(std::string newKey, std::string* key, Node*& newNode);

        // BTree::insert helper function
        // split Node that has reached maximum (degree) keys
        void split(std::string* key, Node*& newNode);
    
        // BTree::insert helper function       
        // make new root, set current root as its child
        Node* makeNewRoot(std::string key, Node* newEntry);
        
        // traverse Nodes 
        void traverse(int numNodes);

        // search for key in tree structure
        Node *search(std::string key);

        // allow Node class access to BTree data members 
        friend class BTree;

};

#endif
