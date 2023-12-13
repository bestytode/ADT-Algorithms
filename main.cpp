#include <iostream>
#include <algorithm>
#include <vector>

#include "ADT_imps/hashtable_open_address.h"
#include "ADT_imps/hashtable_seperate_chaining.h"
#include "ADT_imps/rbtree.h"
#include "ADT_imps/binary_heap.h"
#include "ADT_imps/graphs.h"
#include "algorithm_technics/dynamic_programming.h"

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangle_3.h>
#include <CGAL/Boolean_set_operations_2/do_intersect.h>

void test_hash_table_open_address();
void test_red_black_tree();
void test_shortest_path_algorithm();

using Kernel = CGAL::Exact_predicates_inexact_constructions_kernel;
using Point_3 = Kernel::Point_3;
using Triangle_3 = CGAL::Triangle_3<Kernel>;

int main() 
{
    // test_hash_table_open_address();
    // test_red_black_tree();
    // test_binary_heap();
    // test_shortest_path_algorithm();

    // std::vector<int> price = { 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };
    // int n = 9; // Length of the rod.
    // std::cout << "Maximum obtainable value is " << cutRod(price, n) << std::endl;

    // Define two triangles in 3D space
    Triangle_3 triangle1(Point_3(0, 0, 0), Point_3(1, 0, 0), Point_3(0, 1, 0));
    Triangle_3 triangle2(Point_3(0, 0, 1), Point_3(1, 0, 1), Point_3(0, 1, 1));

    // Check if the two triangles intersect
    if (CGAL::do_intersect(triangle1, triangle2)) 
        std::cout << "The triangles intersect." << std::endl;
    else 
        std::cout << "The triangles do not intersect." << std::endl;
}

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

    std::cout << "maxHeap extract: " << maxHeap.pop() << " minHeap extract: " << minHeap.pop();
}

void test_shortest_path_algorithm()
{
    // Create a graph with 5 vertices
    AdjList<int> graph(5);

    // Add edges to the graph (Edge ID, Source, Destination, Weight)
    graph.addEdge(1, 0, 1, 4);  // Edge from vertex 0 to 1 with weight 4
    graph.addEdge(2, 0, 2, 1);  // Edge from vertex 0 to 2 with weight 1
    graph.addEdge(3, 1, 2, 2);  // Edge from vertex 1 to 2 with weight 2
    graph.addEdge(4, 1, 3, 7);  // Edge from vertex 1 to 3 with weight 7
    graph.addEdge(5, 2, 3, 3);  // Edge from vertex 2 to 3 with weight 3
    graph.addEdge(6, 3, 4, 5);  // Edge from vertex 3 to 4 with weight 5

    // Run Dijkstra's algorithm
    auto distances = dijkstraShortestPath(graph, 0);
    for (const auto& distance : distances) {
        std::cout << "Distance from 0 to " << distance.first << " is " << distance.second << std::endl;
    }
}