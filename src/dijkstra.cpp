#include <iostream>
#include <vector>
#include <limits>
#include <chrono>
#include "graph.cpp"

using namespace std;

struct NodeData {
    int forward_cost = numeric_limits<int>::max();
    int backward_cost = numeric_limits<int>::max();
    bool forward_processed = false;
    bool backward_processed = false;
};

template<int d=16>
class DaryHeap {

    vector<pair<int, int>> heap;
    
    void heapify_up(int index) {
        while (index > 0) {
            int parent = (index - 1) / d;
            if (heap[index].second >= heap[parent].second) break;
            swap(heap[index], heap[parent]);
            index = parent;
        }
    }

    void heapify_down(int index) {
        while (true) {
            int first = index * d + 1;
            if (first >= heap.size()) break;
            
            int smallest = index;
            for (int i = 0; i < d && (first+i) < heap.size(); ++i) {
                if (heap[first+i].second < heap[smallest].second)
                    smallest = first+i;
            }
            
            if (smallest == index) break;
            swap(heap[index], heap[smallest]);
            index = smallest;
        }
    }

public:

    size_t size() const { return heap.size(); }

    void push(int id, int cost) {
        heap.emplace_back(id, cost);
        heapify_up(heap.size()-1);
    }

    pair<int, int> pop() {
        auto top = heap.front();
        heap[0] = heap.back();
        heap.pop_back();
        heapify_down(0);
        return top;
    }

    bool empty() const { return heap.empty(); }
    int top_cost() const { return heap.empty() ? numeric_limits<int>::max() : heap.front().second; }
};

class PathFinder : public Graph {
public:
    pair<int, vector<int>> bidirectionalDijkstra(int source, int dest) {
        const int mapped_source = getMappedId(source);
        const int mapped_dest = getMappedId(dest);
        if (mapped_source == mapped_dest) return {0, {source}};

        const auto& edges = getEdges();
        const auto& offsets = getOffsets();
        const int numNodes = offsets.size() - 1;
        
        vector<NodeData> nodeData(numNodes);
        vector<int> parentForward(numNodes, -1);
        vector<int> parentBackward(numNodes, -1);
        DaryHeap<16> forwardHeap, backwardHeap;
        int best_known = numeric_limits<int>::max();
        int meeting_node = -1;

        // Initialize
        nodeData[mapped_source].forward_cost = 0;
        nodeData[mapped_dest].backward_cost = 0;
        forwardHeap.push(mapped_source, 0);
        backwardHeap.push(mapped_dest, 0);

        while (!forwardHeap.empty() && !backwardHeap.empty()) {
            // Alternate direction based on frontier size
            bool expand_forward = forwardHeap.size() <= backwardHeap.size();
            
            if (expand_forward) {
                auto [current, f_cost] = forwardHeap.pop();
                if (nodeData[current].forward_processed) continue;
                nodeData[current].forward_processed = true;

                // Process forward edges
                for (size_t i = offsets[current]; i < offsets[current+1]; ++i) {
                    
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
                for (size_t i = offsets[current]; i < offsets[current+1]; ++i) {
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

            // Enhanced early termination
            if (forwardHeap.top_cost() + backwardHeap.top_cost() >= best_known * 1.05) {
                break;
            }
            if (best_known < numeric_limits<int>::max() && 
                forwardHeap.top_cost() > best_known / 2 &&
                backwardHeap.top_cost() > best_known / 2) {
                break;
            }
        }

        if (meeting_node == -1) return {-1, {}};

        // Reconstruct path with original IDs
        vector<int> path;
        path.reserve(1000);
        int current = meeting_node;
        while (current != -1) {
            path.push_back(getOriginalId(current));
            current = parentForward[current];
        }
        reverse(path.begin(), path.end());
        
        current = parentBackward[meeting_node];
        while (current != -1) {
            path.push_back(getOriginalId(current));
            current = parentBackward[current];
        }

        return {best_known, path};
    }
};
