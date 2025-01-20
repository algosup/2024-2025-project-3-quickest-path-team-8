/*

    「 ✦ USA QuickPath Algorithm by TEAM 8 ✦ 」

༺☆༻____________☾✧ ✩ ✧☽____________༺☆༻

    STEP: 4/6 - LOAD
    The files in the "load" directory are responsible for the final loading of the data into the program for processing.

*/

// ‿︵‿୨ Linking ୧‿︵‿

    #ifndef LOAD_HPP
    #define LOAD_HPP

    #include <vector>
    #include <unordered_map>
    #include "../02-extract/csv_reader.hpp"

// ‿︵‿୨ Definition ୧‿︵‿

    /**
     * @brief Load road data from a binary file
     * @param filename The name of the file to read from
     * @return A vector containing all the roads
     */
    std::vector<Road> loadRoadsFromBinary(const std::string &filename);


    /**
     * @brief Build a graph from the road data
     * @param roads The roads to build the graph from
     * @return A graph representation of the roads
     */
    std::unordered_map<int, std::vector<std::pair<int, double>>> buildGraph(const std::vector<Road> &roads);

    /**
     * @brief ( ⚠️ Deprecated) - Load road data from a CSV file.
     * @param filename The name of the file to read from
     * @return A vector containing all the roads
     * @note This function is deprecated. Use loadRoadsFromBinary instead.
     */
    // std::vector<Road> loadRoads(const std::string &filename);

    #endif // LOAD_HPP
