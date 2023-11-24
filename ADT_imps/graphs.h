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

template<typename T>
inline std::unordered_map<int, float> dijkstraShortestPath(const AdjList<T>& graph, int start) 
{
    PriorityQueue<Edge<T>, Compare<T>> pq;  // for extract the shortest one in loop
    std::unordered_map<int, float> distances; // key: id, value: distance
    std::vector<bool> visited(graph.getVertices(), false); // helper array to prevent multiple visiting

    // Initialize all distances as infinite
    for (int i = 0; i < graph.getVertices(); ++i) {
        distances[i] = std::numeric_limits<float>::infinity();
    }

    // Start with the source vertex
    pq.push(Edge<T>(-1, start, 0.0f));
    distances[start] = 0.0f;

    // loop will end if no element in priority queue, which means all nodes have been checked
    while (!pq.empty()) {
        Edge<T> currentEdge = pq.top(); // current shortest (that's why it's greedy algorithm)
        pq.pop();
        int u = currentEdge.dest;

        if (visited[u]) {
            continue;
        }

        visited[u] = true;

        // check neibors(u) by get all egdes of the current node v
        for (const Edge<T>& edge : graph.getAdjList(u)) {
            int v = edge.dest;
            T weight = edge.weight;

            // Update the distance if a shorter path is found
            // to understand: 1st iteration: u is start point where distances[start] is 0.0f, 
            // and distances[v] will be updated anyways
            // 2nd iteration and later: update only if shorter path is found
            // finally push v to priority queue for later checking
            if (!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                pq.push(Edge<T>(edge.id, v, distances[v]));
            }
        }
    }

    return distances;
}

#endif 