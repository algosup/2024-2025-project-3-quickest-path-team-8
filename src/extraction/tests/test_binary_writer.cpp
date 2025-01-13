/*

    「 ✦ USA QuickPath Algorithm by TEAM 8 ✦ 」

༺☆༻____________☾✧ ✩ ✧☽____________༺☆༻

    Unit Tests - Extraction Process: Binary Writer
    The goal of this test is to ensure that the binary writer is functioning correctly
    by writing and reading binary data and checking that the data is consistent.

*/

// ‿︵‿୨ Linking ୧‿︵‿

    #include <gtest/gtest.h>
    #include "../binary_writer.hpp"
    #include "../csv_reader.hpp"
    #include <fstream>
    #include <vector>

// ‿︵‿୨ Function Definition ୧‿︵‿

    // Function to read a vector of Road objects from a binary file
    std::vector<Road> readBinary(const std::string &filename) {

        // Vector to store the read Road objects
        std::vector<Road> roads;

        // Open the binary file for reading
        std::ifstream file(filename, std::ios::binary);

        // Check if the file was opened successfully
        if (!file) {

            // Print an error message if the file could not be opened
            std::cerr << "Error: Unable to open binary file for reading: " << filename << std::endl;

            return roads;
        }

        // Temporary Road object to read data into
        Road road;

        // Read the binary file into the vector of Road objects
        while (file.read(reinterpret_cast<char*>(&road), sizeof(Road))) {
            roads.push_back(road);
        }

        // Check if no data was read from the file
        if (roads.empty()) {

            // Print an error message if no data was read
            std::cerr << "Error: No data read from binary file " << filename << std::endl;
        }

        // Return the vector of Road objects
        return roads;
    }

    // Test case for writing and reading binary data
    TEST(BinaryWriterTest, WritesAndReadsBinaryData) {

        // Create a vector of Road objects to write to the binary file
        std::vector<Road> roads = {{1, 2, 10}, {2, 3, 20}};
        
        // Define the path for the test binary file
        std::string testFilePath = "testfile.bin";

        // Write the roads to a binary file
        writeBinary(testFilePath, roads);

        // Read the roads back from the binary file
        auto loaded_roads = readBinary(testFilePath);

        // Check that the number of roads read is the same as the number written
        ASSERT_EQ(loaded_roads.size(), roads.size());

        // Check that the data read is the same as the data written
        for (size_t i = 0; i < roads.size(); ++i) {
            EXPECT_EQ(loaded_roads[i].landmarkA, roads[i].landmarkA);
            EXPECT_EQ(loaded_roads[i].landmarkB, roads[i].landmarkB);
            EXPECT_EQ(loaded_roads[i].time, roads[i].time);
        }

        // Clean up the test file by removing it
        std::remove(testFilePath.c_str());
    }