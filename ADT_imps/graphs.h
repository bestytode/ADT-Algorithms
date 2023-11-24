#ifndef GRAPHS_H
#define GRAPHS_H

#include <iostream>
#include <limits>
#include <functional>
#include <unordered_map>
#include <queue>
#include <list>
#include "binary_heap.h"

template<typename T>
struct Edge 
{
    int id;        // Unique identifier for the edge
    int dest;      // Destination vertex of the edge
    T weight;  // Weight of the edge

    Edge(int id, int dest, T weight) : id(id), dest(dest), weight(weight) {}
};

template<typename T>
class AdjList 
{
public:
    AdjList(int vertices) : adjList(vertices) {}

    void addEdge(int id, int u, int v, float w) {
        adjList[u].push_back(Edge<T>(id, v, w));
        // For undirected graph, add an edge in the opposite direction as well
        // adjList[v].push_back(Edge(id, u, w));
    }

    const std::list<Edge<T>>& getAdjList(int vertex) const {
        return adjList[vertex];
    }

    int getVertices() const {
        return adjList.size();
    }

private:
    std::vector<std::list<Edge<T>>> adjList; // Adjacency list of edges
};

// this simple struct makes sure the pq pop the min weight one
template<typename T>
struct Compare {
    bool operator()(const Edge<T>& a, const Edge<T>& b) {
        return a.weight > b.weight;
    }
};


// Implements Dijkstra's algorithm to find the shortest paths from a single source node to all other nodes in a graph.
// The graph is represented as an adjacency list where each edge has a weight of type T.
// The algorithm uses a priority queue to efficiently determine the next node to process based on the shortest distance.
//
// @param graph The graph represented as an adjacency list with weighted edges of type T.
// @param start The starting node's index from which to calculate shortest paths.
//
// @return A map of node indices to their shortest distance from the start node.
//
// @tparam T The data type of the weights of the edges, which can be any numeric type (e.g., int, float, double).
template<typename T>
inline std::unordered_map<int, float> dijkstraShortestPath(const AdjList<T>& graph, int start) 
{
    // Priority queue to manage nodes during the search, ensuring the node with the shortest distance is processed next.
    PriorityQueue<Edge<T>, Compare<T>> pq;  
    std::unordered_map<int, float> distances; // key: id, value: shortest distance
    std::vector<bool> visited(graph.getVertices(), false); // helper array to indicate whether visited

    // Initialize all distances as infinite
    for (int i = 0; i < graph.getVertices(); ++i) {
        distances[i] = std::numeric_limits<float>::infinity();
    }

    // Start with the source vertex
    pq.push(Edge<T>(-1, start, 0.0f));
    distances[start] = 0.0f;

    // Continue processing nodes until the priority queue is empty.
    while (!pq.empty()) {
        Edge<T> currentEdge = pq.top(); // current shortest
        pq.pop();
        int u = currentEdge.dest; // current node (u)

        // process helper array visited[]
        if (visited[u]) 
            continue;
        visited[u] = true;

        // Iterate through the edges of the current node to update distances.
        for (const Edge<T>& edge : graph.getAdjList(u)) {
            int v = edge.dest;
            T weight = edge.weight;

            // If an unvisited node 'v' is found with a shorter path from 'u', update its distance.
            if (!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                pq.push(Edge<T>(edge.id, v, distances[v])); // Add 'v' to the queue to process its neighbors later.
            }
        }
    }

    return distances;
}

#endif 