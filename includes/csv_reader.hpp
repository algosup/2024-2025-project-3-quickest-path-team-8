// ‿︵‿୨ Linking ୧‿︵‿

    #ifndef CSV_READER_H
    #define CSV_READER_H

    #include <vector>
    #include <string>

// ‿︵‿୨ Definition ୧‿︵‿

    /**
     * @brief A struct to represent a road
     */
    struct Road {
        int landmarkA;
        int landmarkB;
        int time;

        // Default constructor
        Road() : landmarkA(0), landmarkB(0), time(0) {}

        // Parameterized constructor
        Road(int a, int b, int t) : landmarkA(a), landmarkB(b), time(t) {}
    };

    /**
     * @brief Read the roads from a CSV file
     * @param filename The name of the file to read from
     */
    std::vector<Road> readCSV(const std::string &filename);

    #endif