#ifndef GRAPHS_H
#define GRAPHS_H

#include <iostream>
#include <limits>
#include <functional>
#include <unordered_map>
#include <queue>
#include <list>
#include "binary_heap.h"

struct Edge 
{
    int id;        // Unique identifier for the edge
    int dest;      // Destination vertex of the edge
    float weight;  // Weight of the edge

    Edge(int id, int dest, float weight) : id(id), dest(dest), weight(weight) {}
};

class AdjList 
{
public:
    AdjList(int vertices) : adjList(vertices) {}

    void addEdge(int id, int u, int v, float w) {
        adjList[u].push_back(Edge(id, v, w));
        // For undirected graph, add an edge in the opposite direction as well
        // adjList[v].push_back(Edge(id, u, w));
    }

    const std::list<Edge>& getAdjList(int vertex) const {
        return adjList[vertex];
    }

    int getVertices() const {
        return adjList.size();
    }

private:
    std::vector<std::list<Edge>> adjList; // Adjacency list of edges
};

// this simple struct makes sure the pq pop the min weight one
struct Compare {
    bool operator()(const Edge& a, const Edge& b) {
        return a.weight > b.weight;
    }
};

inline std::unordered_map<int, float> dijkstraShortestPath(const AdjList& graph, int start) 
{
    PriorityQueue<Edge, Compare> pq;  // for extract the shortest one in loop
    std::unordered_map<int, float> distances; // key: id, value: distance
    std::vector<bool> visited(graph.getVertices(), false); // helper array to prevent multiple visiting

    // Initialize all distances as infinite
    for (int i = 0; i < graph.getVertices(); ++i) {
        distances[i] = std::numeric_limits<float>::infinity();
    }

    // Start with the source vertex
    pq.push(Edge(-1, start, 0.0f));
    distances[start] = 0.0f;

    while (!pq.empty()) {
        Edge currentEdge = pq.top();
        pq.pop();
        int u = currentEdge.dest;

        if (visited[u]) {
            continue;
        }

        visited[u] = true;

        for (const Edge& edge : graph.getAdjList(u)) {
            int v = edge.dest;
            float weight = edge.weight;

            // Update the distance if a shorter path is found
            if (!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                pq.push(Edge(edge.id, v, distances[v]));
            }
        }
    }

    return distances;
}

#endif 