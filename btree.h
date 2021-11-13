#ifndef BTREE_H
#define BTREE_H

#include <string>
#include "node.h"

class BTree {
	    
        Node *root;     // pointer to root node
	    int degree;     // minimum degree

    public:

		// BTree constructor 
        BTree(int degree) {
		    root = nullptr;  
            this->degree = degree;
	    }

		// main insert function
	    void insert(std::string key);
	    
		// if root is not nullptr, allow traversal		
        void traverse() {
		    if (root != nullptr) root->traverse();
	    }
		
		// condition ? result1 : result2
		// check if root is nullptr, else search for key
	    Node* search(std::string key) {
		    return (root == nullptr) ? nullptr : root->search(key); // condition ? result1 : result2
	    }

};

#endif