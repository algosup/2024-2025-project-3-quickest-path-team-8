/*

    「 ✦ USA QuickPath Algorithm by TEAM 8 ✦ 」

༺☆༻____________☾✧ ✩ ✧☽____________༺☆༻

    STEP 6/6 - REST API
    The files in the "restApi" directory are responsible for setting up the REST API server and exposing it to the user.

*/

// ‿︵‿୨ Linking ୧‿︵‿

    #ifndef REST_API_HPP
    #define REST_API_HPP

    #include <unordered_map>
    #include <vector>

// ‿︵‿୨ Function Definition ୧‿︵‿

    /**
     * @brief Start the REST API server
     * @param graph The graph to use for pathfinding
     */
    void startServer(const std::unordered_map<int, std::vector<std::pair<int, double>>> &graph);

    #endif // REST_API_HPP
