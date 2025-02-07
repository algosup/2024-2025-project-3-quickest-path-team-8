#include "includes/httplib.h"
#include "includes/dijkstra.hpp"
#include <iostream>
#include <sstream>
#include <string>


using namespace std;

void startServer(PathFinder &graph) {
    httplib::Server svr;

    svr.Get("/quickest_path", [&](const httplib::Request &req, httplib::Response &res) {
    res.set_header("Access-Control-Allow-Origin", "*");
        try {
            if (!req.has_param("format") || !req.has_param("landmark_1") || !req.has_param("landmark_2")) {
                res.status = 400;
                res.set_content("Missing query parameters", "text/plain");
                return;
            }

            string format = req.get_param_value("format");
            int landmark_1 = stoi(req.get_param_value("landmark_1"));
            int landmark_2 = stoi(req.get_param_value("landmark_2"));

            auto [distance, path] = graph.bidirectionalDijkstra(landmark_1, landmark_2);

            if (format == "json") {
                ostringstream response;
                response << "{ \"distance\": " << distance << ", \"path\": [";
                for (size_t i = 0; i < path.size(); ++i) {
                    response << path[i];
                    if (i < path.size() - 1) response << ", ";
                }
                response << "] }";
                res.set_content(response.str(), "application/json");
            } else if (format == "xml") {
                ostringstream response;
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
        } catch (const exception &e) {
            res.status = 500;
            res.set_content(string("Internal Server Error: ") + e.what(), "text/plain");
        }
    });

    cout << "Server running on http://localhost:8080/quickest_path" << endl;
    svr.listen("localhost", 8080);
}