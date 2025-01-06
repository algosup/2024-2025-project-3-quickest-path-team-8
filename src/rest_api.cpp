#include "httplib.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <limits>

////////////////////////////////////////////////////////////////
// DATA STRUCTURES
////////////////////////////////////////////////////////////////

// Structure to hold road data
struct Road {
    int landmarkA;
    int landmarkB;
    int time;
};

////////////////////////////////////////////////////////////////
// FUNCTIONS
////////////////////////////////////////////////////////////////

// Function to load roads from the CSV file
std::vector<Road> loadRoads(const std::string &filename) {

    // Open the CSV file and put it in a vector of roads
    std::vector<Road> roads;
    std::ifstream file(filename);
    std::string line;

    // Skip the header
    std::getline(file, line);

    // Read the data line by line
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string landmarkA, landmarkB, time;

        std::getline(ss, landmarkA, ',');
        std::getline(ss, landmarkB, ',');
        std::getline(ss, time, ',');

        roads.push_back({std::stoi(landmarkA), std::stoi(landmarkB), std::stoi(time)});
    }

    return roads;
}


// Build an adjency list representation of the graph for easy traversal
std::unordered_map<int, std::vector<std::pair<int, int>>> buildGraph(const std::vector<Road> &roads) {
    std::unordered_map<int, std::vector<std::pair<int, int>>> graph;

    // Add the roads to the graph
    for (const auto &road : roads) {
        graph[road.landmarkA].emplace_back(road.landmarkB, road.time);
        graph[road.landmarkB].emplace_back(road.landmarkA, road.time);
    }

    return graph;
}

// Simple implementation of Dijkstra's algorithm
std::pair<int, std::vector<int>> dijkstra(

    // Graph representation
    const std::unordered_map<int, std::vector<std::pair<int, int>>> &graph, int start, int end) {

        // Initialize the distance and previous maps
        std::unordered_map<int, int> distances;
        std::unordered_map<int, int> previous;
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;

        // Initialize the distances
        for (const auto &node : graph) {
            distances[node.first] = std::numeric_limits<int>::max();
        }
        distances[start] = 0;
        pq.push({0, start});

        // Main Algorithm. While the priority queue is not empty
        while (!pq.empty()) {

            // Get the node with the smallest distance
            int currentDistance = pq.top().first;
            int currentNode = pq.top().second;
            // And remove it from the priority queue
            pq.pop();

            // If we reached the end node, we can stop
            if (currentNode == end) break;

            // Otherwise, check the neighbors of the current node
            for (const auto &neighbor : graph.at(currentNode)) {

                // Calculate the new distance
                int neighborNode = neighbor.first;

                // And update the distance if it's smaller than the current one
                int weight = neighbor.second;

                // If the new distance is smaller, update the distance and the previous node
                int newDistance = currentDistance + weight;

                // If the new distance is smaller, update the distance and the previous node
                if (newDistance < distances[neighborNode]) {
                    distances[neighborNode] = newDistance;
                    previous[neighborNode] = currentNode;
                    pq.push({newDistance, neighborNode});
                }
            }
        }

        /// Reconstruct the path
        std::vector<int> path;
        // If we didn't reach the end node, return an empty path
        int current = end;
        // Otherwise, reconstruct the path from the previous map
        while (current != start) {
            path.push_back(current);
            current = previous[current];
        }
        // Add the start node
        path.push_back(start);
        // Reverse the path
        std::reverse(path.begin(), path.end());

        // Return the distance and the path
        return {distances[end], path};
}

////////////////////////////////////////////////////////////////
// MAIN FUNCTION
////////////////////////////////////////////////////////////////

int main() {

    // Load the roads from the CSV file
    const std::string filename = "val_de_loire_roads.csv";

    // Build the graph
    std::vector<Road> roads = loadRoads(filename);
    auto graph = buildGraph(roads);

    // Create the server
    httplib::Server svr;

    // Define the endpoint to get the quickest path
    svr.Get("/quickest_path", [&](const httplib::Request &req, httplib::Response &res) {

        // Parse query parameters
        if (!req.has_param("format") || !req.has_param("landmark_1") || !req.has_param("landmark_2")) {
            
            // Bad request
            res.status = 400;
            res.set_content("Missing query parameters", "text/plain");
            return;
        }

        // Get the query parameters
        std::string format = req.get_param_value("format");
        int landmark_1 = std::stoi(req.get_param_value("landmark_1"));
        int landmark_2 = std::stoi(req.get_param_value("landmark_2"));

        // Find the shortest path by calling Dijkstra's algorithm
        auto [distance, path] = dijkstra(graph, landmark_1, landmark_2);

        // Format the response
        if (format == "json") {
            std::ostringstream response;
            response << "{ \"distance\": " << distance << ", \"path\": [";
            for (size_t i = 0; i < path.size(); ++i) {
                response << path[i];
                if (i < path.size() - 1) response << ", ";
            }
            response << "] }";
            res.set_content(response.str(), "application/json");
        } else {
            res.status = 400; // Bad request
            res.set_content("Unsupported format", "text/plain");
        }
    });

    // Display a message to the user
    std::cout << "Server running on http://localhost:8080/quickest_path" << std::endl;

    // Run the server
    svr.listen("localhost", 8080);

    return 0;
}