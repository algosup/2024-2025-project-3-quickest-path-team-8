/*

    「 ✦ USA QuickPath Algorithm by TEAM 8 ✦ 」

༺☆༻____________☾✧ ✩ ✧☽____________༺☆༻

    STEP: 2/6 - EXTRACT
    The files in the "extract" directory are responsible for converting the CSV data to binary format for faster processing.

*/
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
        double time;

        // Default constructor
        Road() : landmarkA(0), landmarkB(0), time(0) {}

        // Parameterized constructor
        Road(int a, int b, double t) : landmarkA(a), landmarkB(b), time(t) {}
    };

    /**
     * @brief Read the roads from a CSV file
     * @param filename The name of the file to read from
     */
    std::vector<Road> readCSV(const std::string &filename);

    #endif