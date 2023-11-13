#include "ADT_implementations/hashtableSC_OA.h"
#include "ADT_implementations/RBTree.h"

int main() 
{
    HashTableSC<std::string, int> hashTable(8);

    hashTable.insert("apple", 3);
    hashTable.insert("banana", 2);
    hashTable.insert("orange", 4);
    hashTable.insert("mango", 1);
    hashTable.print();

    // Search for an item
    std::cout << "The value for 'apple' is: " << *hashTable.search("apple") << std::endl;

    // Remove an item
    hashTable.remove("banana");
    std::cout << "Removed 'banana' from the hash table." << std::endl;
    hashTable.print();

    // Example usage with int and double
    HashTableSC<int, double> hashTableIntDouble(10);
    hashTableIntDouble.insert(1, 1.1);
    hashTableIntDouble.insert(2, 2.2);
    hashTableIntDouble.insert(3, 3.3);
    hashTableIntDouble.print();

    RBTree<int> tree;

    tree.insert(7);
    tree.insert(3);
    tree.insert(18);
    tree.insert(10);
    tree.insert(22);
    tree.insert(8);
    tree.insert(11);
    tree.insert(26);
    tree.insert(2);
    tree.insert(6);
    tree.insert(13);

    std::cout << "Inorder traversal: ";
    tree.inorder();
    std::cout << std::endl;
}