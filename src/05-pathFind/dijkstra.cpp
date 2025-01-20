#include "../../includes/05-pathFind/dijkstra.hpp"
#include <unordered_map>
#include <queue>

// Function to find the shortest path between two landmarks using Dijkstra's algorithm
std::pair<int, std::vector<int>> dijkstra(const std::unordered_map<int, std::vector<std::pair<int, double>>> &graph, int start, int end) {

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