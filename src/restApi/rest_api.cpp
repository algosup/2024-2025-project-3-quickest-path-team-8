/*

The goal of this program is to expose a REST API for calculating the shortest path between two given landmarks
on a Directed Acyclic Graph database of nodes representing a map of USA landmarks.

Usage: Compile the program, run it locally and query it as follows from a client:

GET http://localhost:8080/quickest_path?format=XXX&landmark_YYY=2&landmark_2=ZZZ

where XXX is the format (json/xml), YYY the ID of the first landmark and zzz the id of the second landmark.

Output: The output consists of the time of the proposed path, followed by the path itself, which is serquence (list) of landmarks.


*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Linking Section
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "httplib.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <limits>
#include <chrono>

////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Definition Section
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DATA_CHOICE 1
#define DEBUG 0

////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Global Declaration
////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// Define a structure to represent a road connecting two landmarks
struct Road {
    int landmarkA;
    int landmarkB;
    int time;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Function Declaration
////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// Function to load road data from a CSV file
std::vector<Road> loadRoads(const std::string &filename) {

    // Create a container to store all the roads
    std::vector<Road> roads;

    // Open input file for reading
    std::ifstream file(filename);

    // Temporary string to hold each line in the file
    std::string line;

    // Read and discard the header line of the CSV file
    std::getline(file, line);

    // Read the remaining lines in the file
    while (std::getline(file, line)) {

        // Create a string stream to parse the line
        std::istringstream ss(line);

        // Temporary variables to hold parsed values
        std::string landmarkA, landmarkB, time;

        // Extract first value (landmarkA) from the string stream
        std::getline(ss, landmarkA, ',');

        // Extract second value (landmarkB) from the string stream
        std::getline(ss, landmarkB, ',');

        // Extract third value (time) from the string stream
        std::getline(ss, time, ',');

        // Convert parsed values to integers and add a Road object to vector
        roads.push_back({std::stoi(landmarkA), std::stoi(landmarkB), std::stoi(time)});
    }

    // Return the vector containing all roads
    return roads;
}

/// Function to load road data from a binary file
std::vector<Road> loadRoadsFromBinary(const std::string &filename) {
    std::vector<Road> roads;
    std::ifstream file(filename, std::ios::binary);

    if (!file) {
        std::cerr << "Error: Unable to open binary file " << filename << std::endl;
        return roads;
    }

    Road road;

    while (file.read(reinterpret_cast<char*>(&road), sizeof(Road))) {
        roads.push_back(road);
    }

    if (roads.empty()) {
        std::cerr << "Error: No data read from binary file " << filename << std::endl;
    }

    return roads;
}

/// Function to build a graph from the list of roads
std::unordered_map<int, std::vector<std::pair<int, int>>> buildGraph(const std::vector<Road> &roads) {

    // Create an adjacency list representation of the graph
    std::unordered_map<int, std::vector<std::pair<int, int>>> graph;

    // Iterates through all roads to populate the graph
    for (const auto &road : roads) {

        // Adds an edge from landmarkA to landmarkB with travel time
        graph[road.landmarkA].emplace_back(road.landmarkB, road.time);

        // Adds an edge from landmarkB to landmarkA with the same travel time
        graph[road.landmarkB].emplace_back(road.landmarkA, road.time);
    }

    // Returns the graph as an adjacency list
    return graph;
}

// Function to find the shortest path between two landmarks using Dijkstra's algorithm
std::pair<int, std::vector<int>> dijkstra(

    const std::unordered_map<int, std::vector<std::pair<int, int>>> &graph, int start, int end) {

        // Add error handling for case when start or end node is not in the graph
        #if DEBUG == 1

            if (graph.find(start) == graph.end()) {
                throw std::runtime_error("Start landmark not found in the graph");
            }
            if (graph.find(end) == graph.end()) {
                throw std::runtime_error("End landmark not found in the graph");
            }
            
        #endif

        // Map to store shortest distances from start node
        std::unordered_map<int, int> distances;

        // Map to store previous node in shortest path for each node
        std::unordered_map<int, int> previous;

        // Min-heap priority queue to process nodes with smallest distance
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;

        // Initialize all distances to infinity for nodes in graph
        for (const auto &node : graph) {
            distances[node.first] = std::numeric_limits<int>::max();
        }

        // Set distance to the start node as zero
        distances[start] = 0;

        // Add start node to priority queue with a distance of zero
        pq.push({0, start});

        // Process nodes in priority queue until it becomes empty
        while (!pq.empty()) {

            // Retrieve node with the smallest distance from queue
            int currentDistance = pq.top().first;
            int currentNode = pq.top().second;

            // Remove processed node from queue
            pq.pop();

            // +++++ DEBUG: Print current node being processed +++++
            #if DEBUG == 1

                std::cout << "Processing node: " << currentNode << " with current distance: " << currentDistance << std::endl;

            #endif

            // Stop processing if destination node is reached
            if (currentNode == end) break;

            // Iterate through all neighbors of current node
            for (const auto &neighbor : graph.at(currentNode)) {

                // Retrieve neighbor node
                int neighborNode = neighbor.first;

                // Retrieve weight (travel time) of the edge to neighbor
                int weight = neighbor.second;

                // Calculate new distance to neighbor
                int newDistance = currentDistance + weight;

                // Update distance if a shorter path is found
                if (newDistance < distances[neighborNode]) {
                    distances[neighborNode] = newDistance;

                    // Update previous node in path for neighbor
                    previous[neighborNode] = currentNode;

                    // Add neighbor to priority queue with updated distance
                    pq.push({newDistance, neighborNode});

                    // ++++++ DEBUG: Print updated distance for neighbor +++++
                    #if DEBUG == 1

                        std::cout << "Updated distance for node: " << neighborNode << " to: " << newDistance << std::endl;

                    #endif
                }
            }
        }

        // Construct shortest path by backtracking from end node
        std::vector<int> path;
        int current = end;
        while (current != start) {
            path.push_back(current);
            current = previous[current];
        }

        // Add start node to path
        path.push_back(start);

        // Reverse path to get correct order from start to end
        std::reverse(path.begin(), path.end());

        // Return total distance and shortest path as a pair
        return {distances[end], path};
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// MAIN
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {

    // Define the filename based on the data choice
    #if DATA_CHOICE == 1
    
        const std::string binFilename = "../../data/extractedDataset.bin";

    #endif

    // Start timing the dataset loading
    auto start = std::chrono::high_resolution_clock::now();

    // Load roads from binary file
    std::vector<Road> roads = loadRoadsFromBinary(binFilename);

    // End timing the dataset loading
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    // Print the time taken to load the dataset
    std::cout << "Time taken to load dataset: " << duration.count() << " seconds" << std::endl;

    // Validate the loaded data
    if (roads.empty()) {

        std::cerr << "Error: No roads loaded from the binary file." << std::endl;
        return 1;

    }

    std::cout << "Number of roads loaded: " << roads.size() << std::endl;

    // +++++ DEBUG: Print current node being processed +++++
    #if DEBUG == 1

        std::cout << "Sample data:" << std::endl;
        for (size_t i = 0; i < std::min(roads.size(), size_t(5)); ++i) {
            std::cout << "Road " << i + 1 << ": "
                      << "landmarkA = " << roads[i].landmarkA << ", "
                      << "landmarkB = " << roads[i].landmarkB << ", "
                      << "time = " << roads[i].time << std::endl;
        }

    #endif

    // Build the graph from loaded roads
    auto graph = buildGraph(roads);

    // Create an HTTP server instance
    httplib::Server svr;

    // Define an endpoint to calculate the quickest path
    svr.Get("/quickest_path", [&](const httplib::Request &req, httplib::Response &res) {

        try {

            // Validate that all required query parameters are provided
            if (!req.has_param("format") || !req.has_param("landmark_1") || !req.has_param("landmark_2")) {

                res.status = 400;
                res.set_content("Missing query parameters", "text/plain");
                return;

            }

            // Retrieve query parameters for request
            std::string format = req.get_param_value("format");
            int landmark_1 = std::stoi(req.get_param_value("landmark_1"));
            int landmark_2 = std::stoi(req.get_param_value("landmark_2"));

            // Run Dijkstra's algorithm to find shortest path
            auto [distance, path] = dijkstra(graph, landmark_1, landmark_2);

            // Respond in JSON format if requested
            if (format == "json") {
                std::ostringstream response;
                response << "{ \"distance\": " << distance << ", \"path\": [";
                for (size_t i = 0; i < path.size(); ++i) {
                    response << path[i];
                    if (i < path.size() - 1) response << ", ";
                }
                response << "] }";
                res.set_content(response.str(), "application/json");

            // Respond in XML format if requested
            } else if (format == "xml") {
                std::ostringstream response;
                response << "<response><distance>" << distance << "</distance><path>";
                for (const auto &node : path) {
                    response << "<landmark>" << node << "</landmark>";
                }
                response << "</path></response>";
                res.set_content(response.str(), "application/xml");

            // Handle unsupported formats
            } else {
                res.status = 400;
                res.set_content("Unsupported format", "text/plain");
            }
        } catch (const std::exception &e) {
            res.status = 500;
            res.set_content(std::string("Internal Server Error: ") + e.what(), "text/plain");
        }
    });

    // Output a message indicating server is running
    std::cout << "Server running on http://localhost:8080/quickest_path" << std::endl;

    // Start the HTTP server, listening on localhost:8080
    svr.listen("localhost", 8080);

    // Return 0 to indicate successful execution
    return 0;
}
