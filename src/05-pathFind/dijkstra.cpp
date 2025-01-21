#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <chrono>
#include <unordered_map>
#include "../../includes/04-load/graph.hpp" // Include the Graph base class

using namespace std;


// Define a structure for priority queue nodes
struct Node {
    int id;            // Node ID
    int gCost;         // Cost from the source to this node
    bool operator>(const Node& other) const {
        return gCost > other.gCost; // Min-heap based on cost
    }
};

// Define a structure for the bidirectional priority queue nodes
struct BiNode {
    int id;            // Node ID
    int cost;          // Cost from source/destination
    bool operator>(const BiNode& other) const {
        return cost > other.cost; // Min-heap based on cost
    }
};

// Class PathFinder extends Graph to include both Dijkstra and Bidirectional Dijkstra algorithms
class PathFinder : public Graph {
public:
    // Standard Dijkstra's algorithm for shortest path
    pair<int, vector<int>> dijkstra(int source, int destination) {
        const auto& adjList = getAdjList(); // Retrieve adjacency list
        int n = adjList.size();

        // Distance and parent vectors
        vector<int> gCost(n, numeric_limits<int>::max());
        vector<int> parent(n, -1);

        // Min-heap priority queue
        priority_queue<Node, vector<Node>, greater<Node>> pq;

        // Initialize source node
        gCost[source] = 0;
        pq.push({source, 0});

        while (!pq.empty()) {
            Node current = pq.top();
            pq.pop();

            // Early exit if we reach the destination
            if (current.id == destination) break;

            // Relax edges
            for (const auto& edge : adjList.at(current.id)) {
                int neighbor = edge.destination;
                int newCost = gCost[current.id] + edge.travel_time;

                // Update if a shorter path is found
                if (newCost < gCost[neighbor]) {
                    gCost[neighbor] = newCost;
                    parent[neighbor] = current.id;
                    pq.push({neighbor, newCost});
                }
            }
        }

        // Reconstruct path
        vector<int> path = reconstructPath(parent, source, destination);

        // Return the shortest path cost and the reconstructed path
        return {gCost[destination], path};
    }

    // Bidirectional Dijkstra algorithm for shortest path
    pair<int, vector<int>> bidirectionalDijkstra(int source, int destination) {
        const auto& adjList = getAdjList(); // Retrieve adjacency list
        int n = adjList.size();

        // Forward and backward distances
        vector<int> forwardCost(n, numeric_limits<int>::max());
        vector<int> backwardCost(n, numeric_limits<int>::max());

        // Parent vectors for path reconstruction
        vector<int> parentForward(n, -1);
        vector<int> parentBackward(n, -1);

        // Priority queues for forward and backward searches
        priority_queue<BiNode, vector<BiNode>, greater<BiNode>> forwardQueue;
        priority_queue<BiNode, vector<BiNode>, greater<BiNode>> backwardQueue;

        // Initialize forward and backward searches
        forwardCost[source] = 0;
        backwardCost[destination] = 0;
        forwardQueue.push({source, 0});
        backwardQueue.push({destination, 0});

        // Set to keep track of processed nodes
        vector<bool> processedForward(n, false);
        vector<bool> processedBackward(n, false);

        int shortestPath = numeric_limits<int>::max();
        int meetingNode = -1;

        while (!forwardQueue.empty() && !backwardQueue.empty()) {
            // Forward step
            if (!forwardQueue.empty()) {
                BiNode currentF = forwardQueue.top();
                forwardQueue.pop();

                if (processedForward[currentF.id]) continue;
                processedForward[currentF.id] = true;

                // Relax edges
                for (const auto& edge : adjList.at(currentF.id)) {
                    int neighbor = edge.destination;
                    int newCost = forwardCost[currentF.id] + edge.travel_time;

                    if (newCost < forwardCost[neighbor]) {
                        forwardCost[neighbor] = newCost;
                        parentForward[neighbor] = currentF.id;
                        forwardQueue.push({neighbor, newCost});
                    }

                    // Check if neighbor is processed in backward search
                    if (processedBackward[neighbor]) {
                        int totalCost = forwardCost[currentF.id] + edge.travel_time + backwardCost[neighbor];
                        if (totalCost < shortestPath) {
                            shortestPath = totalCost;
                            meetingNode = neighbor;
                        }
                    }
                }
            }

            // Backward step
            if (!backwardQueue.empty()) {
                BiNode currentB = backwardQueue.top();
                backwardQueue.pop();

                if (processedBackward[currentB.id]) continue;
                processedBackward[currentB.id] = true;

                // Relax edges
                for (const auto& edge : adjList.at(currentB.id)) {
                    int neighbor = edge.destination;
                    int newCost = backwardCost[currentB.id] + edge.travel_time;

                    if (newCost < backwardCost[neighbor]) {
                        backwardCost[neighbor] = newCost;
                        parentBackward[neighbor] = currentB.id;
                        backwardQueue.push({neighbor, newCost});
                    }

                    // Check if neighbor is processed in forward search
                    if (processedForward[neighbor]) {
                        int totalCost = backwardCost[currentB.id] + edge.travel_time + forwardCost[neighbor];
                        if (totalCost < shortestPath) {
                            shortestPath = totalCost;
                            meetingNode = neighbor;
                        }
                    }
                }
            }

            // Termination condition
            if (!forwardQueue.empty() && !backwardQueue.empty() &&
                forwardCost[forwardQueue.top().id] + backwardCost[backwardQueue.top().id] >= shortestPath) {
                break;
            }
        }

        // Reconstruct path
        vector<int> path = reconstructBidirectionalPath(parentForward, parentBackward, source, destination, meetingNode);

        return {shortestPath, path};
    }

private:
    // Helper to reconstruct the path in unidirectional Dijkstra
    vector<int> reconstructPath(const vector<int>& parent, int source, int destination) {
        vector<int> path;
        int current = destination;
        while (current != -1) {
            path.push_back(current);
            current = parent[current];
        }
        reverse(path.begin(), path.end());
        return (path.front() == source) ? path : vector<int>{}; // Return empty if no path exists
    }

    // Helper to reconstruct the path in bidirectional Dijkstra
    vector<int> reconstructBidirectionalPath(const vector<int>& parentForward, const vector<int>& parentBackward, int source, int destination, int meetingNode) {
        if (meetingNode == -1) return {}; // No path exists

        vector<int> forwardPath, backwardPath;

        // Build the forward part of the path
        int current = meetingNode;
        while (current != -1) {
            forwardPath.push_back(current);
            current = parentForward[current];
        }
        reverse(forwardPath.begin(), forwardPath.end());

        // Build the backward part of the path
        current = parentBackward[meetingNode];
        while (current != -1) {
            backwardPath.push_back(current);
            current = parentBackward[current];
        }

        // Combine both parts
        forwardPath.insert(forwardPath.end(), backwardPath.begin(), backwardPath.end());
        return forwardPath;
    }
};

// Test function: Entry point for the program
int main() {
    PathFinder graph;

    // Load the graph from the binary file
    auto start = chrono::high_resolution_clock::now();
    graph.loadGraphFromBinary("../../data/extractedDataset.bin");
    auto end = chrono::high_resolution_clock::now();
    auto loadTime = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Time to load graph: " << loadTime << " ms\n";

    // Define source and destination
    int source = 1;
    int destination = 20000000;

    // Measure time for Bidirectional Dijkstra
    start = chrono::high_resolution_clock::now();
    auto result = graph.bidirectionalDijkstra(source, destination);
    end = chrono::high_resolution_clock::now();
    auto dijkstraTime = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Time to execute Bidirectional Dijkstra: " << dijkstraTime << " ms\n";

    // Output the results
    int travelTime = result.first;
    vector<int> path = result.second;

    cout << "Shortest travel time: " << travelTime << "\n";
    cout << "Path: ";
    for (int landmark : path) {
        cout << landmark << " ";
    }
    cout << "\n";

    return 0;
}