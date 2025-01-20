/*

    「 ✦ USA QuickPath Algorithm by TEAM 8 ✦ 」

༺☆༻____________☾✧ ✩ ✧☽____________༺☆༻

    STEP: 5/6 - PathFind
    The files in the "pathFind" represent the main pathfinding algorithm used in the program.

*/

// ‿︵‿୨ Linking ୧‿︵‿

    #ifndef DIJKSTRA_HPP
    #define DIJKSTRA_HPP

    #include <vector>
    #include <unordered_map>

// ‿︵‿୨ Definition ୧‿︵‿

    /**
     * @brief Perform Dijkstra's algorithm to find the shortest path between two nodes
     * @param graph The graph represented as an adjacency list
     * @param start The starting node
     * @param end The ending node
     * @return A pair containing the shortest distance and the path
     */
    std::pair<int, std::vector<int>> dijkstra(const std::unordered_map<int, std::vector<std::pair<int, double>>> &graph, int start, int end);

    #endif // DIJKSTRA_HPP