#include "httplib.h"
#include "../05-pathFind/dijkstra.hpp"
#include "../../includes/06-restApi/rest_api.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

void startServer(const std::unordered_map<int, std::vector<std::pair<int, double>>> &graph) {
    httplib::Server svr;

    svr.Get("/quickest_path", [&](const httplib::Request &req, httplib::Response &res) {
        try {
            if (!req.has_param("format") || !req.has_param("landmark_1") || !req.has_param("landmark_2")) {
                res.status = 400;
                res.set_content("Missing query parameters", "text/plain");
                return;
            }

            std::string format = req.get_param_value("format");
            int landmark_1 = std::stoi(req.get_param_value("landmark_1"));
            int landmark_2 = std::stoi(req.get_param_value("landmark_2"));

            auto [distance, path] = dijkstra(graph, landmark_1, landmark_2);

            if (format == "json") {
                std::ostringstream response;
                response << "{ \"distance\": " << distance << ", \"path\": [";
                for (size_t i = 0; i < path.size(); ++i) {
                    response << path[i];
                    if (i < path.size() - 1) response << ", ";
                }
                response << "] }";
                res.set_content(response.str(), "application/json");
            } else if (format == "xml") {
                std::ostringstream response;
                response << "<response><distance>" << distance << "</distance><path>";
                for (const auto &node : path) {
                    response << "<landmark>" << node << "</landmark>";
                }
                response << "</path></response>";
                res.set_content(response.str(), "application/xml");
            } else {
                res.status = 400;
                res.set_content("Unsupported format", "text/plain");
            }
        } catch (const std::exception &e) {
            res.status = 500;
            res.set_content(std::string("Internal Server Error: ") + e.what(), "text/plain");
        }
    });

    std::cout << "Server running on http://localhost:8080/quickest_path" << std::endl;
    svr.listen("localhost", 8080);
}