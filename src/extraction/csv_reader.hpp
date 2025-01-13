// ‿︵‿୨ Linking ୧‿︵‿

    #ifndef CSV_READER_H
    #define CSV_READER_H

    #include <vector>
    #include <string>

// ‿︵‿୨ Definition ୧‿︵‿

    // Define a structure to represent a road connecting two landmarks
        struct Road {
            int landmarkA;
            int landmarkB;
            int time;
        };

    // This function reads a CSV file and returns a vector of Road objects
        std::vector<Road> readCSV(const std::string &filename);

    #endif