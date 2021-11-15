#include <iostream>
#include "node.h"
#include "btree.h"

int main() {

    // create btree object with degree of (3)  
    BTree BTree(3);

    // read in text file to string vector
    std::vector<std::string> stringElems = BTree.readInString("input.txt");

    // insert vector string elements into btree 
   // for (int i = 0; i < stringElems.size(); i++) {
        BTree.insert(stringElems.at(0));  
    //}

    
    std::cout << stringElems.size() << std::endl;
    for (int i = 0; i < stringElems.size(); i++) {
        std::cout << stringElems.at(i) << std::endl;  
    }
	
    
   // std::cout << "Traversal of the constucted tree is ";
	//BTree.traverse();

    /*
	//std::string key = "sixty";
	//(t.search(key) != nullptr) ? std::cout << "\nPresent" : std::cout << "\nNot Present";

	//key = "seven";
	//(t.search(key) != nullptr) ? std::cout << "\nPresent" : std::cout << "\nNot Present";
    */

	//getchar();

	return 0;
}