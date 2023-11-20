#pragma once

#include <iostream>
#include <limits>
#include <functional>
#include <unordered_map>
#include "binary_heap.h"

template<typename T>
struct Edge 
{
    int id;        // Unique identifier for the edge
    int dest;      // Destination vertex of the edge
    T weight;      // Weight of the edge

    Edge(int id, int dest, T weight) : id(id), dest(dest), weight(weight) {}
};

template<typename T>
class AdjList 
{
public:
    AdjList(int vertices) : adjList(vertices) {}

    void addEdge(int id, int u, int v, int w) {
        adjList[u].push_back(Edge(id, v, w));
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

template<typename T>
std::unordered_map<int, T> dijkstraShortestPath(const AdjList<T>& graph, int start) {
    PriorityQueue<std::pair<T, int>, std::greater<std::pair<T, int>>> pq;
    std::unordered_map<int, T> distances;
    std::vector<bool> visited(graph.getVertices(), false);

    // Initialize all distances as infinite (max value for T)
    for (int i = 0; i < graph.getVertices(); ++i) {
        distances[i] = std::numeric_limits<T>::max();
    }

    // Start with the source vertex
    pq.push({ 0, start });
    distances[start] = 0;

    while (!pq.empty()) {
        int u = pq.pop().second;

        if (visited[u]) {
            continue;
        }

        visited[u] = true;

        for (const auto& edge : graph.getAdjList(u)) {
            int v = edge.dest;
            T weight = edge.weight;

            // Update the distance if a shorter path is found
            if (!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                pq.push({ distances[v], v });
            }
        }
    }

    return distances;
}