/**
 * @file binary.cpp
 * @brief Handles conversion of road network data from CSV to binary format
 * 
 * This module provides functionality to convert road network data stored in CSV
 * format to a more efficient binary representation. The binary format reduces
 * file size and improves read performance for the path-finding algorithm.
 */

#include "includes/binary.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

/**
 * @brief Converts road network data from CSV format to binary
 * 
 * @param csvFilename Source CSV file path containing road network data
 * @param binaryFilename Destination binary file path
 * 
 * @details
 * The function performs the following operations:
 * 1. Opens source CSV file in text mode
 * 2. Creates/opens destination binary file
 * 3. Processes CSV data line by line
 * 4. Writes structured binary records
 * 
 * @note command to run the file: g++ -std=c++17 -O1 -march=native "binary.cpp" -o binary && ./binary
 * @throws Prints error message to cerr if file operations fail
 */

#include "includes/binary.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

// Function to convert CSV to binary
void convertCSVtoBinary(const std::string& csvFilename, const std::string& binaryFilename) {
    // Open the CSV file for reading
    std::ifstream csvFile(csvFilename);
    if (!csvFile.is_open()) {
        std::cerr << "Error: Could not open CSV file: " << csvFilename << std::endl;
        return;
    }

    // Open the binary file for writing
    std::ofstream binaryFile(binaryFilename, std::ios::binary);
    if (!binaryFile.is_open()) {
        std::cerr << "Error: Could not open binary file for writing: " << binaryFilename << std::endl;
        return;
    }

    std::string line;
    Road road;
    char comma; // To handle the commas in the CSV

    // Read the CSV file line by line
    while (getline(csvFile, line)) {
        std::stringstream ss(line);
        // Parse the line: landmarkA,landmarkB,time
        ss >> road.landmarkA >> comma >> road.landmarkB >> comma >> road.time;

        // Write the Road structure to the binary file
        binaryFile.write(reinterpret_cast<const char*>(&road), sizeof(Road));
    }

    // Close the files
    csvFile.close();
    binaryFile.close();

    std::cout << "Successfully converted CSV file to binary format: " << binaryFilename << std::endl;
}

