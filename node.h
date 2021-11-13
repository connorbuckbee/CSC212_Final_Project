#ifndef NODE_H
#define NODE_H

#include <string>

class Node {
	
        std::string *keyArr;     // array of keys
	    int degree;              // minimum degree
	    Node **childArr;         // array of pointers to child nodes
	    int numKeys;             // current number of keys
	    bool leaf;               // true when node is a leaf, else false

    public:

		// Node constructor
	    Node(int degree, bool leaf);

		// BTree::insert helper function
		// insert key into node that has fewer than maximum (degree) keys 
	    void insertNonFull(std::string key);

		// BTree::insert helper function
		// split child node that has reached maximum (degree) keys
	    void splitChild(int index, Node *y); // <--- change y to something that makes sense
	    
		// traverse tree
		void traverse();

		// search for key in tree structure
	    Node *search(std::string key);

		// allow Node class access to BTree data members 
	    friend class BTree;

};

#endif