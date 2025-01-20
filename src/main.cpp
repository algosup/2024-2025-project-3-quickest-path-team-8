/*

    「 ✦ USA QuickPath Algorithm by TEAM 8 ✦ 」

༺☆༻____________☾✧ ✩ ✧☽____________༺☆༻

    Main Program
    This program will...

*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <limits>
#include <chrono>

#include "../includes/02-extract/csv_reader.hpp"
#include "../includes/02-extract/binary_writer.hpp"
#include "../includes/04-load/load.hpp"
#include "../includes/05-pathFind/dijkstra.hpp"
#include "../includes/06-restApi/httplib.h"
#include "../includes/06-restApi/rest_api.hpp"

/*
int main() {

    /// EXTRACTION PROCESS

        // Start the timer
        auto start = std::chrono::high_resolution_clock::now();
        
        // Read the CSV file and write the binary file
        std::vector<Road> roads = readCSV("../data/USA-roads.csv");

        writeBinary("../data/extractedDataset.bin", roads);


        // End the timer
        auto end = std::chrono::high_resolution_clock::now();

        // Calculate the duration
        std::chrono::duration<double> duration = end - start;

        // Print the time taken
        std::cout << "Time taken for extraction: " << duration.count() << " seconds" << std::endl;
        std::cout << "CSV data has been converted to binary format." << std::endl;



    /// LOAD PROCESS

        // binary path
        const std::string binFilename = "../../data/extractedDataset.bin";

        // Start the timer
        auto start = std::chrono::high_resolution_clock::now();
        
        // Load the roads from the binary file
        std::vector<Road> roads = loadRoadsFromBinary(binFilename);

        // End the timer
        auto end = std::chrono::high_resolution_clock::now();

        // Calculate the duration
        std::chrono::duration<double> duration = end - start;

        // Print the time taken
        std::cout << "Time taken to load dataset: " << duration.count() << " seconds" << std::endl;

        // Check if roads were loaded
        if (roads.empty()) {

            // If not, print an error message and return
            std::cerr << "Error: No roads loaded from the binary file." << std::endl;
            return 1;
        }

        // Otherwise, print the number of roads loaded
        std::cout << "Number of roads loaded: " << roads.size() << std::endl;

        // ... and build the graph
        auto graph = buildGraph(roads);

        // Start the server
        startServer(graph);

    return 0;
}
*/

int main() {

    // 2/6 - EXTRACTION PROCESS

        // Start the timer
        auto start = std::chrono::high_resolution_clock::now();

        // Read the CSV file and write the binary file
        std::vector<Road> roads = readCSV("../data/USA-roads.csv");
        writeBinary("../data/extractedDataset.bin", roads);

        // End the timer
        auto end = std::chrono::high_resolution_clock::now();

        // Calculate the duration
        std::chrono::duration<double> duration = end - start;

        // Print the time taken and tell the user that the CSV data has been converted to binary format
        std::cout << "Time taken for extraction: " << duration.count() << " seconds" << std::endl;
        std::cout << "CSV data has been converted to binary format." << std::endl;


    // 4/6 - LOAD PROCESS

        // Load the roads from the binary file
        const std::string binFilename = "../data/extractedDataset.bin";

        // Start the timer
        start = std::chrono::high_resolution_clock::now();

        // Load the roads from the binary file
        roads = loadRoadsFromBinary(binFilename);
        // std::vector<Road> roads = loadRoadsFromBinary(binFilename);

        // End the timer and calculate the duration
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        std::cout << "Time taken to load dataset: " << duration.count() << " seconds" << std::endl;

        // Check if there was an error loading the roads
        if (roads.empty()) {

            // If there was an error, print an error message and return
            std::cerr << "Error: No roads loaded from the binary file." << std::endl;
            return 1;
        }

        // Otherwise, print the number of roads loaded
        std::cout << "Number of roads loaded: " << roads.size() << std::endl;

        // Build the graph from the roads
        auto graph = buildGraph(roads);

    // 6/6 - REST API

        // Start the server
        startServer(graph);


    return 0;
}
