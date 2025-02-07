#include "includes/dijkstra.hpp"
#include <iostream>
#include <chrono>

/**
 * @brief Implements bidirectional Dijkstra's shortest path algorithm
 * 
 * @param source Starting node ID
 * @param dest Destination node ID
 * @return std::pair<int, std::vector<int>> {total_cost, path_nodes}
 * 
 * @details
 * Performs simultaneous forward and backward searches from source and destination.
 * Maintains two priority queues and explores nodes until searches meet.
 * Uses D-ary heap optimization for improved performance.
 */

std::pair<int, std::vector<int>> PathFinder::bidirectionalDijkstra(int source, int dest) 
{
    // Use local aliases for clarity
    const int mapped_source = getMappedId(source);
    const int mapped_dest = getMappedId(dest);
    if (mapped_source == mapped_dest) return {0, {source}};

    const auto& edges = getEdges();
    const auto& offsets = getOffsets();
    const int numNodes = (int)offsets.size() - 1;

    // Create arrays/vectors for node data
    std::vector<NodeData> nodeData(numNodes);
    std::vector<int> parentForward(numNodes, -1);
    std::vector<int> parentBackward(numNodes, -1);

    // Min-heaps for forward and backward searches
    DaryHeap<16> forwardHeap, backwardHeap;

    // Initialize
    nodeData[mapped_source].forward_cost = 0;
    nodeData[mapped_dest].backward_cost = 0;
    forwardHeap.push(mapped_source, 0);
    backwardHeap.push(mapped_dest, 0);

    int best_known = std::numeric_limits<int>::max();
    int meeting_node = -1;

    // Main loop
    while (!forwardHeap.empty() && !backwardHeap.empty()) {
        // Decide which frontier to expand based on heap sizes
        bool expand_forward = forwardHeap.size() <= backwardHeap.size();

        if (expand_forward) {
            auto [current, f_cost] = forwardHeap.pop();
            if (nodeData[current].forward_processed) continue;
            nodeData[current].forward_processed = true;

            // Process forward edges
            for (size_t i = offsets[current]; i < offsets[current + 1]; ++i) {
                const Edge& e = edges[i];
                int new_cost = f_cost + e.travel_time;
                
                if (new_cost < nodeData[e.destination].forward_cost) {
                    nodeData[e.destination].forward_cost = new_cost;
                    parentForward[e.destination] = current;
                    forwardHeap.push(e.destination, new_cost);
                }

                // Check for intersection
                if (nodeData[e.destination].backward_processed) {
                    int total = new_cost + nodeData[e.destination].backward_cost;
                    if (total < best_known) {
                        best_known = total;
                        meeting_node = e.destination;
                    }
                }
            }
        } else {
            auto [current, b_cost] = backwardHeap.pop();
            if (nodeData[current].backward_processed) continue;
            nodeData[current].backward_processed = true;

            // Process backward edges
            for (size_t i = offsets[current]; i < offsets[current + 1]; ++i) {
                const Edge& e = edges[i];
                int new_cost = b_cost + e.travel_time;
                
                if (new_cost < nodeData[e.destination].backward_cost) {
                    nodeData[e.destination].backward_cost = new_cost;
                    parentBackward[e.destination] = current;
                    backwardHeap.push(e.destination, new_cost);
                }

                // Check for intersection
                if (nodeData[e.destination].forward_processed) {
                    int total = new_cost + nodeData[e.destination].forward_cost;
                    if (total < best_known) {
                        best_known = total;
                        meeting_node = e.destination;
                    }
                }
            }
        }

        // Possible early termination checks
        if (forwardHeap.top_cost() + backwardHeap.top_cost() >= best_known * 1.05) {
            break;
        }
        if (best_known < std::numeric_limits<int>::max() &&
            forwardHeap.top_cost() > best_known / 2 &&
            backwardHeap.top_cost() > best_known / 2) {
            break;
        }
    }

    // If no connection found:
    if (meeting_node == -1) {
        return {-1, {}};
    }

    // Reconstruct path with original IDs
    std::vector<int> path;
    path.reserve(1000);
    int current = meeting_node;
    // Walk backward through parentForward
    while (current != -1) {
        path.push_back(getOriginalId(current));
        current = parentForward[current];
    }
    std::reverse(path.begin(), path.end());

    // Then walk forward through parentBackward
    current = parentBackward[meeting_node];
    while (current != -1) {
        path.push_back(getOriginalId(current));
        current = parentBackward[current];
    }

    return {best_known, path};
}