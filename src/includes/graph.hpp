#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>

// Define Edge struct
struct Edge {
    int32_t destination;
    int32_t travel_time;
} __attribute__((packed));

class Graph {
public:
    // Public data members (CSR structure)
    alignas(64) std::vector<Edge> edges;
    alignas(64) std::vector<size_t> offsets;
    std::vector<int> degrees;
    std::unordered_map<int, int> id_map;  // Maps original IDs to contiguous indices
    std::vector<int> reverse_id_map;      // Maps contiguous indices back to original IDs
    
    // Public member functions
    void loadGraphFromBinary(const std::string& filename);

    // Accessors
    const std::vector<Edge>& getEdges() const;
    const std::vector<size_t>& getOffsets() const;
    int getMappedId(int original_id) const;
    int getOriginalId(int mapped_id) const;

private:
    // Private helper functions
    void insertIfNew(int landmark, std::unordered_map<int, int>& temp_map);
    void addEdgeCSR(int src, int dest, int time);
};

#endif // GRAPH_HPP