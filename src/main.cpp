/*

    「 ✦ USA QuickPath Algorithm by TEAM 8 ✦ 」

༺☆༻____________☾✧ ✩ ✧☽____________༺☆༻

    Main Program
    This program will...

*/

// ---------------------- Includes ---------------------- //

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <limits>
#include <queue>
#include <stack>
#include <chrono>

// ---------------------- Definitions ---------------------- //

// Each edge in the adjacency list is (neighbor, distance).
struct Edge {
    int neighbor;
    double distance;
};

// The adjacency list: landmark -> vector of (neighbor, distance).
using AdjacencyList = std::unordered_map<int, std::vector<Edge>>;


/// @brief Reads a CSV file and populates the adjacency list (only forward edges). 
/// @param filename is the path to the CSV file.
/// @param adjList is the adjacency list to populate.
/// @return a boolean indicating success or failure.
/// @note Assumes CSV format: landmark1,landmark2,distance
bool readCSV(const std::string& filename, AdjacencyList& adjList) {

    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return false;
    }

    std::string line;
    bool isFirstLine = true;

    // For each line in the CSV file
    while (std::getline(file, line)) {

        // If there's a header, skip it (assuming the very first line is a header).
        if (isFirstLine) {
            isFirstLine = false;

            // Attempt a naive check: if the line contains non-numeric,
            // assume it's a header and skip this iteration.
            if (line.find_first_not_of("0123456789.,- ") != std::string::npos) {
                continue; 
            }
        }

        // Parse the line
        std::stringstream ss(line);
        std::string fromStr, toStr, distStr;
        
        // Parse "landmark1,landmark2,distance"
        if (!std::getline(ss, fromStr, ',')) continue;
        if (!std::getline(ss, toStr, ',')) continue;
        if (!std::getline(ss, distStr, ',')) continue;

        // Convert strings to appropriate types
        try {
            int from = std::stoi(fromStr);
            int to   = std::stoi(toStr);
            double dist = std::stod(distStr);

            // Add forward edge
            adjList[from].push_back({to, dist});
        } catch (const std::exception& e) {
            std::cerr << "Warning: Failed to parse line: " << line << "\n";
            continue;
        }
    }
    
    file.close();
    return true;
}


/// @brief Adds reverse edges to the adjacency list.
/// @param adjList 
/// @note This function modifies the input adjacency list by adding reverse edges, so that A->B with distance d also implies B->A with distance d.
void addReverseEdges(AdjacencyList& adjList) {
    
    // Collect all edges in a temporary structure first
    // so we don’t add reverse edges repeatedly in one pass.
    std::vector<std::pair<int, Edge>> reverseEdges;
    reverseEdges.reserve(10'000);

    // For each landmark, for each edge, if the reverse edge doesn't exist, plan to add it.
    for (const auto& [from, edges] : adjList) {
        for (const auto& edge : edges) {
            int to = edge.neighbor;
            double dist = edge.distance;

            // We want to see if to->from already exists.
            // We'll do a quick linear search (could also do a map/set if performance is an issue).
            // If it doesn't exist, we add it to reverseEdges.
            bool reverseExists = false;
            if (adjList.find(to) != adjList.end()) {
                for (const auto& revEdge : adjList.at(to)) {
                    if (revEdge.neighbor == from) {
                        reverseExists = true;
                        break;
                    }
                }
            }

            if (!reverseExists) {
                reverseEdges.push_back({to, {from, dist}});
            }

        }
    }

    // Now add the new reverse edges
    for (auto& rev : reverseEdges) {
        
        // the "to" node from the original edge
        int from = rev.first;

        // the reversed edge {original_from, distance}
        Edge e = rev.second;
        adjList[from].push_back(e);
    }
}

/// @brief Dijkstra's algorithm to find the shortest path from 'start' to 'destination'.
/// @param adjList is the graph represented as an adjacency list.
/// @param start is the starting landmark ID.
/// @param destination is the destination landmark ID.
/// @param path is an output parameter that will be filled with the sequence of landmarks on the shortest path.
/// @return the total distance of the shortest path from 'start' to 'destination'.
/// @note If no path is found, the return value will be infinity.
double dijkstra(const AdjacencyList& adjList, int start, int destination, std::vector<int>& path) {
    // Distances map: landmark -> current best distance from 'start'
    std::unordered_map<int, double> dist;
    // Predecessor map to reconstruct path
    std::unordered_map<int, int> parent;

    // Initialize distances to "infinity"
    for (const auto& entry : adjList) {
        dist[entry.first] = std::numeric_limits<double>::infinity();
    }

    // If the start node doesn’t exist in adjList, return immediately
    if (adjList.find(start) == adjList.end()) {
        return std::numeric_limits<double>::infinity();
    }

    // Distance to start is 0
    dist[start] = 0.0;
    parent[start] = -1; // No predecessor

    // Priority queue storing pairs (distance, node),
    // so the node with the smallest distance is always on top.
    using PQItem = std::pair<double, int>;
    std::priority_queue<PQItem, std::vector<PQItem>, std::greater<PQItem>> pq;

    // Push the start node
    pq.push({0.0, start});

    // Dijkstra's main loop
    while (!pq.empty()) {
        auto [currentDist, currentNode] = pq.top();
        pq.pop();

        // If this distance is outdated, skip
        if (currentDist > dist[currentNode]) continue;

        // If we've reached the destination, we can stop early (typical Dijkstra optimization)
        if (currentNode == destination) {
            break;
        }

        // Explore neighbors
        if (adjList.find(currentNode) != adjList.end()) {
            for (const auto& edge : adjList.at(currentNode)) {
                int neighbor = edge.neighbor;
                double weight = edge.distance;
                double newDist = currentDist + weight;

                // Relaxation
                if (newDist < dist[neighbor]) {
                    dist[neighbor] = newDist;
                    parent[neighbor] = currentNode;
                    pq.push({newDist, neighbor});
                }
            }
        }
    }

    // If destination was never updated, it means no path was found
    if (dist[destination] == std::numeric_limits<double>::infinity()) {
        return dist[destination]; // still inf
    }

    // Reconstruct the shortest path from 'destination' back to 'start'
    {
        std::stack<int> st;
        int curr = destination;
        while (curr != -1) {
            st.push(curr);
            curr = parent[curr];
        }

        // Now pop from stack to get path in correct order
        while (!st.empty()) {
            path.push_back(st.top());
            st.pop();
        }
    }

    // Return the total distance of the path
    return dist[destination];
}

// ------------------------- main() ------------------------- //

int main() {
    // --- 1. Read CSV and build adjacency list --- //
    AdjacencyList adjList;
    std::string csvFile = "../data/USA-roads.csv";

    if (!readCSV(csvFile, adjList)) {
        std::cerr << "Failed to load CSV data. Exiting.\n";
        return 1;
    }

    // --- 2. Add reverse edges explicitly --- //
    addReverseEdges(adjList);

    // --- 3. Prompt for two landmark IDs and run Dijkstra --- //
    int start, destination;
    std::cout << "Enter start landmark ID: ";
    std::cin >> start;
    std::cout << "Enter destination landmark ID: ";
    std::cin >> destination;

    // --- 4. Find shortest path --- //
    std::vector<int> path;
    auto start_time = std::chrono::high_resolution_clock::now();
    double shortestDist = dijkstra(adjList, start, destination, path);
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end_time - start_time;

    // --- 5. Print result --- //
    if (shortestDist == std::numeric_limits<double>::infinity()) {
        std::cout << "No path found from " << start << " to " << destination << ".\n";
    } else {
        std::cout << "Shortest distance from " << start << " to " << destination
                  << " is " << shortestDist << ".\n";
        std::cout << "Path: ";
        for (size_t i = 0; i < path.size(); ++i) {
            std::cout << path[i];
            if (i + 1 < path.size()) std::cout << " -> ";
        }
        std::cout << "\n";
    }

    std::cout << "Dijkstra algorithm took " << duration.count() << " seconds.\n";

    return 0;
}