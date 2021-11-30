#include "node.h"

// Node constructor, initialize with max children and 
// whether or not this is a leaf Node
Node::Node(int degree, bool leaf) {
	this->degree = degree;
	this->leaf = leaf;
}

// insert a new key in given Node
// if child of this node is split, we have to insert *key
// into keyVec and newNode pointer into childVec
// note: string* = pass by value, Node*& = pass by reference
void Node::insert(std::string newKey, std::string* key, Node*& newNode) {
 
    // non-leaf Node
    if (leaf == false) {
        int i = 0;
 
        // find first key greater than *key
        while (i < keyVec.size() && newKey > keyVec.at(i))
            i++;
 
        // insert newKey into left child of Node with index i
        childVec.at(i)->insert(newKey, key, newNode);
 
        // no split needed
        if (newNode == nullptr) return;

	// we have enough space in child Node    
        if (keyVec.size() < 2 * degree - 1) {
 
            // ...so this Node can accommodate a new key and child pointer entry
            // insert *key into key vector
            keyVec.insert(keyVec.begin() + i, *key);
 
            // insert newNode into childVec
            childVec.insert(childVec.begin() + i + 1, newNode);
 
            // this Node was not split, so set newNode to nullptr
            newNode = nullptr;
        }

	// not enough space
        else {
 
            // current Node now has (2 * degree) keys...
            keyVec.insert(keyVec.begin() + i, *key);
            childVec.insert(childVec.begin() + i + 1, newNode);
 
            // ...so split it
            split(key, newNode);
        }
    }
	
    // leaf Node	
    else {
 	
        // insert newKey in this node
        std::vector<std::string>::iterator it;
 
        // find correct position
	// need to explain this better <~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        it = lower_bound(keyVec.begin(), keyVec.end(), newKey);
 
        // insert in correct position
        keyVec.insert(it, newKey);
 
        // Node is full of keys
        if (keyVec.size() == 2 * degree) {
 
            // create new Node
            newNode = new Node(degree, true);
 
            // set (degree + 1) key as parent
            *key = this->keyVec[degree];
 
            // insert last (degree - 1) keys into new Node
            for (int i = degree + 1; i < 2 * degree; i++) {
                newNode->keyVec.push_back(this->keyVec.at(i));
            }
 
            // this->Node stores first (degree) keys
            this->keyVec.resize(degree);
        }
    }
}

// utility function to split the child of this node
// split the current Node and store the new parent value 
// in *key, and new child pointer in &newNode
// called only for splitting non-leaf Nodes
// note: string* = pass by value, Node*& = pass by reference
void Node::split(std::string* key, Node*& newNode)
{
 
    // create new non-leaf Node
    newNode = new Node(degree, false);
 
    // (degree + 1)th Node becomes parent
    *key = this->keyVec.at(degree);
 
    // last (degree - 1) entries will go to newNode
    for (int i = degree + 1; i < 2 * degree; i++) {
        newNode->keyVec.push_back(this->keyVec.at(i));
    }
 
    // this node stores first (degree) entries
    this->keyVec.resize(degree);
 
    // last (degree) entries will go to newNode
    for (int i = degree + 1; i <= 2 * degree; i++) {
        newNode->childVec.push_back(this->childVec.at(i));
    }
 
    // this Node stores first (degree + 1) entries
    this->childVec.resize(degree + 1);
}

// function to create a new root
// set current Node as its child
Node* Node::makeNewRoot(std::string key, Node* newNode)
{
    // create new root
    Node* root = new Node(degree, false);
 
    // store key value in keyVec
    root->keyVec.push_back(key);
 
    // push child pointers to childVec
    root->childVec.push_back(this);
    root->childVec.push_back(newNode);
    return root;
}

// print the keys of B-Tree
void Node::traverse()
{
    int i;
    for (i = 0; i < keyVec.size(); i++) {
 
        // if this is not a leaf, then before printing keyVec.at(i)
        // traverse the subtree rooted with childVec.at(i)
        if (leaf == false)
            childVec.at(i)->traverse();
            std::cout << " " << keyVec.at(i);
    }
 
    // recursively go to the next child Node
    if (leaf == false) {
        childVec.at(i)->traverse();
    }
}

// function to search for key in subtree rooted with this Node
// return true if key is present in BTree
Node *Node::search(std::string key) {

    int i = 0;
    int numKeys = 0;

    // find number of keys in current Node
    for(int i = 0; i < keyVec.size(); i++) 
	numKeys++;	

    // find the first key greater than or equal to key 
    while (i < numKeys && key > keyVec[i])
        i++;

    // if the found key is equal to key, return this Node
    if (keyVec[i] == key)
		return this;

    // if the key is not found here and this is a leaf node
    if (leaf == true)
        return nullptr;

    // recursively search child Nodes
    return childVec.at(i)->search(key);
}
