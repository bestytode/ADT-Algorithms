#include <algorithm>
#include <vector>

#include "ADT_imps/hashtable_open_address.h"
#include "ADT_imps/hashtable_seperate_chaining.h"
#include "ADT_imps/rbtree.h"

void test_hash_table_open_address()
{
    // hash table open address testing
    HashTableOA<std::string, int> hashTable;

    hashTable.insert("apple", 3);
    hashTable.insert("banana", 2);
    hashTable.insert("orange", 4);
    hashTable.insert("mango", 1);
    hashTable.print();

    // Search for an item and check if it exists
    auto appleValue = hashTable.search("apple");
    if (appleValue) {
        std::cout << "The value for 'apple' is: " << *appleValue << std::endl;
    }
    else {
        std::cout << "'apple' not found." << std::endl;
    }

    // Remove an item
    hashTable.remove("banana");
    std::cout << "Removed 'banana' from the hash table." << std::endl;
    hashTable.print();
}

void test_red_black_tree()
{
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

int main() 
{
    //test_hash_table_open_address();
    //test_red_black_tree();

    std::vector<int> v = { 1,2,3,4,5,6,7,8,9,10,12,11,13,14,15 };
    std::make_heap(v.begin(), v.end());
    std::cout << "max value: " << v.front() << "\n";

    for (int n : v) {
        std::cout << n << " ";
    }
}