/**
 * @file rest_api.cpp
 * @brief RESTful API implementation for path-finding service
 * 
 * Provides HTTP endpoints for:
 * - Path finding between landmarks using bidirectional Dijkstra
 * - Distance calculations between points
 * - Multiple response formats (JSON/XML)
 * 
 * Error handling includes:
 * - Input validation
 * - Format validation
 * - Node existence checks
 * - Exception handling
 */

#include "includes/httplib.h"
#include "includes/dijkstra.hpp"
#include <iostream>
#include <sstream> 
#include <string>

using namespace std;

/**
 * @brief Structure for standardized API error responses
 * 
 * Provides consistent error formatting across all endpoints
 * following REST API best practices
 */
struct ApiError {
    int status_code;     // HTTP status code
    string message;      // Short error description
    string details;      // Detailed error information
};

/**
 * @brief Formats API errors into JSON or XML response
 * 
 * @param error ApiError struct containing error details
 * @param format Response format ("json" or "xml")
 * @return Formatted error string
 * 
 * @example JSON output:
 * {
 *   "error": {
 *     "code": 400,
 *     "message": "Invalid Format",
 *     "details": "Supported formats: json, xml"
 *   }
 * }
 */
string formatError(const ApiError& error, const string& format) {
    if (format == "json") {
        return "{\n  \"error\": {\n    \"code\": " + to_string(error.status_code) + 
               ",\n    \"message\": \"" + error.message + "\",\n    \"details\": \"" + 
               error.details + "\"\n  }\n}";
    }
    return "<error>\n  <code>" + to_string(error.status_code) + "</code>\n  <message>" + 
           error.message + "</message>\n  <details>" + error.details + "</details>\n</error>";
}

// Define common API errors
const ApiError MISSING_PARAMETERS = {400, "Missing Parameters", "Required parameters: format, landmark_1, landmark_2"};
const ApiError INVALID_FORMAT = {400, "Invalid Format", "Supported formats: json, xml"};
const ApiError INVALID_LANDMARK = {400, "Invalid Landmark", "Landmark IDs must be valid integers"};
const ApiError LANDMARK_NOT_FOUND = {404, "Landmark Not Found", "Specified landmark ID does not exist"};
const ApiError SERVER_ERROR = {500, "Internal Server Error", "An unexpected error occurred"};


void startServer(PathFinder &graph) {
    httplib::Server svr;

    svr.Get("/quickest_path", [&](const httplib::Request &req, httplib::Response &res) {
    res.set_header("Access-Control-Allow-Origin", "*");
        try {
            if (!req.has_param("format") || !req.has_param("landmark_1") || !req.has_param("landmark_2")) {
                res.status = MISSING_PARAMETERS.status_code;
                res.set_content(formatError(MISSING_PARAMETERS, "json"), "application/json");
                return;
            }

            string format = req.get_param_value("format");
            if (format != "json" && format != "xml") {
                res.status = INVALID_FORMAT.status_code;
                res.set_content(formatError(INVALID_FORMAT, format), 
                    format == "json" ? "application/json" : "application/xml");
                return;
            }

            int landmark_1, landmark_2;
            try {
                landmark_1 = stoi(req.get_param_value("landmark_1"));
                landmark_2 = stoi(req.get_param_value("landmark_2"));
            } catch (const std::invalid_argument&) {
                res.status = INVALID_LANDMARK.status_code;
                res.set_content(formatError(INVALID_LANDMARK, format),
                    format == "json" ? "application/json" : "application/xml");
                return;
            }

            // Perform path-finding
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
            } 
        } catch (const exception &e) {
            res.status = SERVER_ERROR.status_code;
            ApiError error = SERVER_ERROR;
            error.details = e.what();
            res.set_content(formatError(error, "json"), "application/json");
        }
    });

    cout << "Server running on http://localhost:8080/quickest_path" << endl;
    svr.listen("localhost", 8080);
}