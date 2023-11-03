#include "hashtable_seperate_chaining.h"

int main() {
    HashTableSC<std::string, int> hashTable(8);

    hashTable.insert("apple", 3);
    hashTable.insert("banana", 2);
    hashTable.insert("orange", 4);
    hashTable.insert("mango", 1);

    hashTable.print();

    // Search for an item
    try {
        std::cout << "The value for 'apple' is: " << hashTable.search("apple") << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }

    // Remove an item
    try {
        hashTable.remove("banana");
        std::cout << "Removed 'banana' from the hash table." << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }

    hashTable.print();

    // Example usage with int and double
    HashTableSC<int, double> hashTableIntDouble(10);
    hashTableIntDouble.insert(1, 1.1);
    hashTableIntDouble.insert(2, 2.2);
    hashTableIntDouble.insert(3, 3.3);
    hashTableIntDouble.print();

    return 0;
}