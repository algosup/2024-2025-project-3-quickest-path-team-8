/*

    「 ✦ USA QuickPath Algorithm by TEAM 8 ✦ 」

༺☆༻____________☾✧ ✩ ✧☽____________༺☆༻

    Input : USA-roads.csv
    Output : extractedDataset.bin
    The goal of this program is to convert the CSV data to binary format for faster processing.

*/

// ‿︵‿୨ Linking ୧‿︵‿

    #include "csv_reader.hpp"
    #include "binary_writer.hpp"
    #include <chrono>
    #include <iostream>

// ‿︵‿୨  Main Function ୧‿︵‿

    int main() {

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
        return 0;
    }