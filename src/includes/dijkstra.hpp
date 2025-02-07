#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include "graph.hpp"
#include <vector>
#include <utility>
#include <limits>
#include <algorithm>
#include <cstdint>

// Keep this struct if you need it as part of the PathFinder interface.
// If it's strictly internal, you can move it to the .cpp.
struct NodeData {
    int forward_cost = std::numeric_limits<int>::max();
    int backward_cost = std::numeric_limits<int>::max();
    bool forward_processed = false;
    bool backward_processed = false;
};

// Templated classes must generally stay in a header (or an inline .hpp) 
// because the compiler needs to see the full definition to instantiate them.
template<int d = 16>
class DaryHeap {
    std::vector<std::pair<int, int>> heap;

    void heapify_up(int index) {
        while (index > 0) {
            int parent = (index - 1) / d;
            if (heap[index].second >= heap[parent].second) break;
            std::swap(heap[index], heap[parent]);
            index = parent;
        }
    }

    void heapify_down(int index) {
        while (true) {
            int first = index * d + 1;
            if (first >= (int)heap.size()) break;
            
            int smallest = index;
            for (int i = 0; i < d && (first + i) < (int)heap.size(); ++i) {
                if (heap[first + i].second < heap[smallest].second) {
                    smallest = first + i;
                }
            }
            
            if (smallest == index) break;
            std::swap(heap[index], heap[smallest]);
            index = smallest;
        }
    }

public:
    size_t size() const { return heap.size(); }

    void push(int id, int cost) {
        heap.emplace_back(id, cost);
        heapify_up((int)heap.size() - 1);
    }

    std::pair<int, int> pop() {
        auto top = heap.front();
        heap[0] = heap.back();
        heap.pop_back();
        heapify_down(0);
        return top;
    }

    bool empty() const { return heap.empty(); }

    int top_cost() const { 
        return heap.empty() ? std::numeric_limits<int>::max() : heap.front().second; 
    }
};

// PathFinder class inherits from Graph, declared in graph.hpp
class PathFinder : public Graph {
public:
    // Declaration of the bidirectionalDijkstra function.
    std::pair<int, std::vector<int>> bidirectionalDijkstra(int source, int dest);
};

#endif // DIJKSTRA_HPP