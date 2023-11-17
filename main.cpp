#include <algorithm>
#include <vector>

#include "ADT_imps/hashtable_open_address.h"
#include "ADT_imps/hashtable_seperate_chaining.h"
#include "ADT_imps/rbtree.h"
#include "ADT_imps/binary_heap.h"

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

void test_binary_heap()
{
    // Create a max-heap
    BinaryHeap<int, std::less<int>> maxHeap;
    maxHeap.insert(10);
    maxHeap.insert(20);
    maxHeap.insert(15);

    // Create a min-heap
    BinaryHeap<int, std::greater<int>> minHeap;
    minHeap.insert(10);
    minHeap.insert(20);
    minHeap.insert(15);

    std::cout << "maxHeap extract: " << maxHeap.extract() << " minHeap extract: " << minHeap.extract();
}

int main() 
{
    //test_hash_table_open_address();
    //test_red_black_tree();

    test_binary_heap();
}