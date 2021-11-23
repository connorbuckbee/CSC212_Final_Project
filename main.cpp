#include <iostream>
#include "node.h"
#include "btree.h"

int main() {

    // create BTree object with degree of (3)  
    std::cout << "Creating BTree..." << std::endl;
    BTree BTree(3);

    // read in text file to string vector
    std::cout << "Reading file into vector..." << std::endl;
    std::vector<std::string> stringElems = BTree.readInString("input.txt");


    // insert vector string elements into btree
    std::cout << "Inserting keys..." << std::endl;
    for (int i = 0; i < stringElems.size(); i++) {
        BTree.insert(stringElems.at(i));  
    }
    
    std::cout << "Insertion complete!" << std::endl;

    std::cout << "Traversal of the constucted tree is: " << std::endl;
    BTree.display();

    std::string key1 = "Lorem";
	(BTree.search(key1) != nullptr) ? std::cout << "\nPresent" : std::cout << "\nNot Present";

    std::string key2 = "ipsum";
	(BTree.search(key2) != nullptr) ? std::cout << "\nPresent" : std::cout << "\nNot Present";
	
    std::string key3 = "nonsense";
	(BTree.search(key1) != nullptr) ? std::cout << "\nPresent" : std::cout << "\nNot Present";

    return 0;

}
