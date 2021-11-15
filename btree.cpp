#include "btree.h"

void BTree::insert(std::string key) {

	// if tree is empty (it probably is)
	if (root == nullptr) {

		// allocate memory for root
		root = new Node(degree, true); // Node(int degree, bool leaf);
		root->keyVec.at(0) = key;  // insert key
		root->numKeys = 1;  // update number of keys in root Node
	}

    // tree is not empty
	else { 

		// if root is full, then tree grows in height
        // "full" means max keys is reached, max keys = (m-1)
		if (root->numKeys == 2 * degree - 1) {

			// allocate memory for new root
            // leaf-node bool set to false because we have become
            // root or interior node
			Node *newRoot = new Node(degree, false);

			// make old root child of new root
			newRoot->childVec.at(0) = root;

			// split old root and move key to the new root
			newRoot->splitChild(0, root);

			// new root has two children, decide which of the
			// two children is going to have new key
			int i = 0;
			if (newRoot -> keyVec.at(0) < key) 
				i++;
			newRoot->childVec.at(i)->insertNonFull(key);

			// swap root
			root = newRoot;
		}

		else  // root is not full, call insertNonFull on root
			root->insertNonFull(key);

	}
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
