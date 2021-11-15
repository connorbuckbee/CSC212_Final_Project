#include "node.h"

Node::Node(int degree, bool leaf) {

	this->degree = degree;
	this->leaf = leaf;
	
	//*****************************************************************************
	// 11/9:
	// this whole block below is used if we were to use arrays for storage
	// not needed since we are using vectors, but i dont know if we need 
	// to replace these commands with other ones
        //*****************************************************************************
	// 11/11:
	// something like this instead?
	// vector<Type> *vect = new vector<Type>;
        //*****************************************************************************
	
	// allocate memory for maximum number of possible keys and child pointers
        // root has 2 minimum children, all nodes have max (degree - 1) keys
	//keyVec = new std::string [2 * degree - 1]; 
    
        // root has 2 minimum children, all nodes have max (degree) children 
	//childVec = new Node* [2 * degree];
	//*****************************************************************************

	// initialize keys as 0
	numKeys = 0;
}


// utility function to split the child of this node
// note that fullNode must be full when this function is called
void Node::splitChild(int childIndex, Node *fullNode) {
	 
	// create new node which is going to store (degree-1) keys of fullNode
	Node *childNode = new Node(fullNode->degree, fullNode->leaf);
	childNode->numKeys = degree - 1;

	// copy the last (degree -1) keys of fullNode to childNode
	for (int j = 0; j < degree - 1; j++)
		childNode->keyVec.at(j) = fullNode->keyVec.at(j + degree);

	// copy the last (degree) children of fullNode to childNode
		if (fullNode->leaf == false) {
		for (int j = 0; j < degree; j++)
			childNode->childVec.at(j) = fullNode->childVec.at(j + degree);
	}

	// reduce the number of keys in fullNode
	fullNode->numKeys = degree - 1;

	// create space for new child
	for (int j = numKeys; j >= childIndex + 1; j--)
		childVec.at(j + 1) = childVec.at(j);

	// link the new child to this node
	childVec.at(childIndex + 1) = childNode;

	// key of fullNode will move to this node 
	// find location of new key and move all greater keys one space ahead
	for (int j = numKeys - 1; j >= childIndex; j--)
		keyVec.at(j + 1) = keyVec.at(j);

	// copy the middle key of fullNode to this node
	keyVec.at(childIndex) = fullNode->keyVec.at(degree - 1); // << this makes it right biased?

	// increment count of keys in this node
	numKeys = numKeys + 1;
}


// utility function to insert new key in node
// node must be non-full when this function is called 
void Node::insertNonFull(std::string key)
{
	// initialize index as rightmost element
	int idx = numKeys - 1;

	// if this is a leaf node
	if (leaf == true)
	{
		// finds the location of new key to be inserted
		// move all greater keys to one place ahead
		while (idx >= 0 && keyVec.at(idx) > key)
		{
			keyVec.at(idx + 1) = keyVec.at(idx);
			idx--;
		}

		// insert new key at found location
		keyVec.at(idx + 1) = key;
		numKeys = numKeys + 1;
	}
	else // this node is not leaf
	{
		// find the child which will have the new key
		while (idx >= 0 && keyVec.at(idx) > key)
			idx--;

		// check if the found child is full
		if (childVec.at(idx + 1)->numKeys == 2 * degree - 1)
		{
			// if child is full, then split it
			splitChild(idx + 1, childVec.at(idx + 1));

			// after split, the middle key of childVec[idx] goes up and
			// childVec[idx] is split in two
			// see which of the two is going to have the new key
			if (keyVec.at(idx + 1) < key)
				idx++;
		}
		childVec.at(idx + 1)->insertNonFull(key);
	}
}


// traverse all nodes in a subtree rooted with this node
void Node::traverse() {

	//traverse through n keys and first n children
	int j;
	for (j = 0; j < numKeys; j++) {
		
		// if this is not leaf, then before printing keyVec.at(j),
		// traverse the subtree rooted with child childVec.at(j)
		if (leaf == false)
			childVec.at(j)->traverse();
			std::cout << " " << keyVec.at(j);
	}

	// print the subtree rooted with last child
	if (leaf == false)
		childVec.at(j)->traverse();
}


// function to search for key in subtree rooted with this node
Node *Node::search(std::string key) {

	// find first key greater than or equal to key
	int j = 0;
	while (j < numKeys && key > keyVec.at(j))
		j++;

	// if found key is equal to key, return this node
	if (keyVec.at(j) == key)
		return this;

	// if key is not found here and this is a leaf node
	if (leaf == true)
		return nullptr;

	// recursively check other child nodes
	return childVec.at(j)->search(key);
}
