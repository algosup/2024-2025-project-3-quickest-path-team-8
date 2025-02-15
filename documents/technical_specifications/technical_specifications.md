# Technical Specifications

<details>
<summary>Table of Contents</summary>

- [Technical Specifications](#technical-specifications)
- [1. Audience](#1-audience)
- [2. Project Overview](#2-project-overview)
- [3. Glossary](#3-glossary)
- [4. Requirements](#4-requirements)
  - [4.1 Core Requirements](#41-core-requirements)
    - [REST API Implementation](#rest-api-implementation)
    - [Algorithm Implementation](#algorithm-implementation)
    - [Dataset Preprocessing](#dataset-preprocessing)
  - [4.2 Performance Goals](#42-performance-goals)
    - [Response Time](#response-time)
    - [Scalability](#scalability)
    - [Resource Efficiency](#resource-efficiency)
    - [Stress Testing](#stress-testing)
  - [4.3 Data Integrity Verification](#43-data-integrity-verification)
    - [Validation Criteria](#validation-criteria)
    - [Importance of Data Integrity](#importance-of-data-integrity)
- [5. System Architecture](#5-system-architecture)
  - [5.1 Technology Stack](#51-technology-stack)
  - [5.2 REST API Design](#52-rest-api-design)
  - [5.3 Algorithm Design](#53-algorithm-design)
    - [Core Algorithm](#core-algorithm)
    - [Role in the System](#role-in-the-system)
      - [Why Adjacency List Over Adjacency Matrix?](#why-adjacency-list-over-adjacency-matrix)
    - [Scalability and Performance](#scalability-and-performance)
    - [Complexity](#complexity)
    - [Optimizations for Dijkstra’s](#optimizations-for-dijkstras)
  - [6.1 Path Calculation](#61-path-calculation)
    - [Overview](#overview)
    - [Workflow](#workflow)
    - [Optimization Techniques](#optimization-techniques)
    - [Edge Cases](#edge-cases)
    - [Diagram](#diagram)
  - [6.2 Data Validation Tool](#62-data-validation-tool)
    - [Overview](#overview-1)
    - [Workflow](#workflow-1)
      - [Example Output](#example-output)
    - [Efficiency Measures](#efficiency-measures)
  - [6.3 Dataset Conversion and Storage](#63-dataset-conversion-and-storage)
    - [Overview](#overview-2)
    - [Conversion Process](#conversion-process)
    - [Benefits of Binary Conversion](#benefits-of-binary-conversion)
    - [Example Structure of the Binary Format](#example-structure-of-the-binary-format)
    - [Integration with the System](#integration-with-the-system)
  - [6.4 Performance Testing](#64-performance-testing)
    - [Overview](#overview-3)
    - [Testing](#testing)
    - [Stress Testing](#stress-testing-1)
    - [Latency Measurement](#latency-measurement)
    - [Failure Rate](#failure-rate)
    - [Automation](#automation)
    - [Scalability Testing](#scalability-testing)
- [7. Non-Functional Requirements](#7-non-functional-requirements)
  - [7.1 Response Time](#71-response-time)
  - [7.2 Scalability](#72-scalability)
  - [7.3 Usability](#73-usability)
  - [7.4 Reliability](#74-reliability)
  - [7.5 Security](#75-security)
  - [7.6 Maintainability](#76-maintainability)
  - [7.7 Data Integrity](#77-data-integrity)
  - [7.8 Compliance](#78-compliance)
- [8. Deliverables](#8-deliverables)
  - [8.1 Source Code](#81-source-code)
  - [8.2 Test Suite](#82-test-suite)
  - [8.3 Data Validation Outputs](#83-data-validation-outputs)
    - [Reference](#reference)
- [9. Development Framework](#9-development-framework)
  - [9.1 Code Design Principles](#91-code-design-principles)
  - [9.2 Challenges](#92-challenges)
  - [9.3 Possible Bugs](#93-possible-bugs)
  - [9.4 Development Process](#94-development-process)

</details>

# 1. Audience

This document is primarily intended for:

- **Software Developers**: To understand user and technical requirements, guiding decision-making and planning. This includes identifying risks and challenges, meeting customer requirements, and understanding additional technical requirements and design choices.

Secondary audiences:

- **Program Managers**: To validate the implementation against functional specifications and client expectations.
- **QA Teams**: To aid in preparing the test plan and validating issues.
- **Project Managers**: To help identify risks, dependencies, and resource needs.

---

# 2. Project Overview

This project involves developing a high-performance C++ software solution to calculate the quickest path between two landmarks in the United States. The solution will be accessible via a REST API, supporting both XML and JSON responses. It will utilize a dataset containing 24 million connections between landmarks, each annotated with travel times.

Key objectives include:

- **Efficiency**: Results must be computed within 1 second for valid queries, even with large datasets.
- **Accuracy**: The calculated path must be within 10% of the shortest possible duration.
- **Reliability**: Data integrity checks are essential to ensure correctness and connectivity of the dataset before usage.

---

# 3. Glossary

| Term                             | Definition                                                                                         |
| -------------------------------- | -------------------------------------------------------------------------------------------------- |
| **Landmark**                     | A point in the graph representing a location in the U.S.                                           |
| **Graph**                        | A network of nodes (landmarks) connected by edges (paths) with associated travel times.            |
| **DAG (Directed Acyclic Graph)** | A graph that doesn’t contain cycles, used to model the landmark connections when applicable.       |
| **REST API**                     | A web service exposing functionality via HTTP endpoints, in this case, to query the shortest path. |
| **Shortest Path Algorithm**      | An algorithm (e.g., Dijkstra’s, A\*) designed to find the minimum cost or time path between nodes. |
| **Connected Graph**              | A graph where every node is reachable from any other node.                                         |
| **Disconnected Subgraph**        | A subset of nodes within a graph that is not connected to the main graph or other subgraphs.       |

---

# 4. Requirements

## 4.1 Core Requirements

The core requirements define the fundamental capabilities and components of the software, outlining its primary purpose and expected behavior. These requirements ensure the project meets functional goals while maintaining alignment with performance and usability expectations.

### REST API Implementation

The REST API provides external access to the quickest path calculation functionality. It supports the following key capabilities:

- **Endpoint**: A single `GET` endpoint at `http://127.0.0.1:8080/quickest_path`.
- **Inputs**:
  - IDs of the source and destination landmarks.
  - Desired output format (`json` or `xml`).
- **Outputs**:
  - Travel time and an ordered list of landmarks in the path.
- **Error Handling**:
  - Return appropriate HTTP error codes for invalid inputs, unsupported formats, or unreachable nodes.
- **Performance Requirements**:
  - Must handle all valid queries within **1 second**.

---

### Algorithm Implementation

- **Shortest Path Calculation**

  - The returned route duration must not exceed the shortest possible duration by more than 10%.

### Dataset Preprocessing

- **Purpose**:
  - Ensure the dataset meets validation criteria for accurate path calculations.
- **Requirements**:
  - The dataset must comply with the validation criteria outlined in **4.3 Data Integrity Verification**.
  - Refer to **6.2 Data Validation Tool** for the detailed workflow and implementation.

![diagram](/documents/images/APIrequest.png)

---

## 4.2 Performance Goals

### Response Time

- The API must respond to all valid queries within **1 second** on a typical laptop, even when handling datasets with millions of nodes and connections.
- Queries for landmarks without a valid path should also return responses within the same time frame.

### Scalability

- If the dataset grows (e.g., expanding from the United States to global coverage), performance should degrade gracefully to maintain usability under increased load.

### Resource Efficiency

- Memory usage and CPU consumption must be optimized to ensure smooth operation on systems with limited resources, such as laptops or entry-level servers.
- Preprocessing steps, such as caching or indexing frequently queried paths, should minimize runtime computation costs.

### Stress Testing

- The system must undergo rigorous testing to evaluate its performance under extreme conditions, such as:
  - Burst traffic scenarios where a high number of requests are received within a short period.
  - Usage of large datasets exceeding typical operational sizes.
- Detailed metrics, such as average response time, maximum response time, and failure rate, will be collected during testing to ensure compliance with performance benchmarks.

---

## 4.3 Data Integrity Verification

To ensure accurate and reliable path calculations, the system must verify the integrity of the input dataset. This verification process ensures the dataset meets the following criteria:

### Validation Criteria

1. **Data Format**:

   - Each row in the CSV dataset must adhere to the required structure: `Landmark_A_ID, Landmark_B_ID, Time`.
   - IDs should be integers, and `Time` must be a positive numeric value.

2. **Duplicate Entries**:

   - Connections between landmarks should be unique, considering both directions (e.g., `A -> B` and `B -> A` are treated as equivalent).

3. **Graph Connectivity**:

   - The graph should form a connected network where all nodes are reachable.
   - Disconnected subgraphs or isolated nodes are flagged for correction.

4. **Graph Validity**:
   - Ensure logical consistency by detecting and resolving cycles in regions expected to be acyclic.

### Importance of Data Integrity

- **Accuracy**: Ensures that the graph reflects real-world connectivity for path calculations.
- **Performance**: Reduces computational overhead by eliminating redundant or invalid data.
- **Reliability**: Guarantees that the dataset can handle large-scale queries without logical inconsistencies.

For the detailed workflow and technical implementation of the data validation process, refer to **Section 6.2: Data Validation Tool**.

# 5. System Architecture

The system architecture defines the technical blueprint for implementing the software.

---

## 5.1 Technology Stack

The following technologies and tools will be used to implement the system:

- **Programming Language**:

  - **C++**: Selected for its high performance and fine-grained control over memory, essential for handling large datasets and optimizing computational tasks.

- **HTTP Server Framework**:

  - The lightweight library **cpp-httplib** will be used to implement the REST API. This library supports multithreaded request handling, ensuring concurrency for high API throughput.

- **Build System**:

  - **CMake**: Facilitates cross-platform build configuration and dependency management, ensuring compatibility and efficiency.

- **Unit and Performance Testing**:

  - **Google Test (GTest)**: For unit testing of algorithms, API logic, and utility functions.
  - **Google Benchmark**: For microbenchmarking performance-critical operations, such as shortest path calculations.

- **API Testing Tools**:

  - **Postman**: For manual API testing to validate inputs, outputs, and error handling.
  - **Apache JMeter**: For simulating concurrent requests and load testing the REST API.

- **Data Preprocessing**:

  - Custom tools written in C++ or Python to perform dataset validation and preprocessing before integration into the main application.

- **Development Machine**:
  - Development and testing will be performed on a **MacBook Air with an Apple M3 chip**, ensuring compatibility with typical modern hardware.

---

## 5.2 REST API Design

The REST API handles requests for the quickest path between landmarks. Design considerations include:

- **Endpoint Details**:

  - **Base URL**: `http://127.0.0.1:8080/quickest_path`
  - **Parameters**:

    - `landmark_1`: Source landmark ID (integer).
    - `landmark_2`: Destination landmark ID (integer).

  - **Input Structure**:
    All inputs must be provided as query parameters in the URL. Example request:
    ```
    GET /quickest_path?landmark_1=100&landmark_2=200
    ```

- **Response Format Examples**:

  - **JSON Format Example**:
    ```json
    {
      "time": 66,
      "steps": [{ "landmark": 322 }, { "landmark": 323 }]
    }
    ```
  - **XML Format Example**:
    ```xml
    <response>
      <time>66</time>
      <steps>
        <step>
          <landmark>322</landmark>
        </step>
        <step>
          <landmark>323</landmark>
        </step>
      </steps>
    </response>
    ```

- **Concurrency**:

  - The HTTP server library ensures scalability by handling concurrent requests using thread pooling or asynchronous processing.

- **Serialization**:

  - JSON and XML responses are serialized using lightweight libraries (e.g., `nlohmann::json`).

- **Error Handling**  
   The API must handle invalid or erroneous inputs:

| Scenario                  | HTTP Code | Description                                                                                                           | Example JSON Response                                                                                               | Example XML Response                                                                                                                                                          |
| ------------------------- | --------- | --------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Valid request             | `200`     | Successfully returns the quickest path.                                                                               | `{"time": 66, "steps": [{"landmark": 322, "distance": 33}, {"landmark": 323, "distance": 33}]}`                     | `<response><time>66</time><steps><step><landmark>322</landmark><distance>33</distance></step><step><landmark>323</landmark><distance>33</distance></step></steps></response>` |
| Identical landmarks       | `200`     | Returns `time` as `0` and an empty `steps` array.                                                                     | `{"time": 0, "steps": []}`                                                                                          | `<response><time>0</time><steps /></response>`                                                                                                                                |
| Missing or invalid inputs | `400`     | One or both landmarks are missing or invalid.                                                                         | `{"error": {"code": 400, "message": "Missing or invalid parameters: 'landmark_1' and 'landmark_2' are required."}}` | `<error><code>400</code><message>Missing or invalid parameters: 'landmark_1', 'landmark_2' and 'format' are required.</message></error>`                                      |
| Nonexistent landmarks     | `404`     | One or both landmarks are not found in the dataset.                                                                   | `{"error": {"code": 404, "message": "No path found between the specified landmarks."}}`                             | `<error><code>404</code><message>No path found between the specified landmarks.</message></error>`                                                                            |
| Internal Server Error     | `500`     | An unhandled error occurred during request processing.                                                                | `{"error": {"code": 500, "message": "A server error occurred while processing your request."}}`                     | `<error><code>500</code><message>A server error occurred while processing your request.</message></error>`                                                                    |
| Service Unavailable       | `503`     | The service is temporarily unable to handle the request due to concurrent requests or the current dataset is loading. | `{"error": {"code": 503, "message": "The server is not available."}}`                                               | `<error><code>503</code><message>The server is not available.</message></error>`                                                                                              |

- **Performance Considerations**:
  - Lightweight HTTP server optimizations ensure that API response times meet the <1-second requirement under typical workloads.

---

## 5.3 Algorithm Design

The algorithm is a core component of the system, responsible for calculating the quickest path between two landmarks. Its design ensures a balance between accuracy, performance, and scalability, aligned with the system’s requirements.

### Core Algorithm

- The **Dijkstra’s algorithm** is selected for its ability to find the shortest path in a weighted graph without negative edges.
- Unlike A\*, **Dijkstra’s does not use a heuristic**, ensuring an optimal solution by systematically exploring the lowest-cost paths.

### Role in the System

- Operates on a **preprocessed dataset** represented as an **adjacency list**, ensuring efficient graph traversal.
- Integrated into the **REST API** to process pathfinding queries dynamically and return results within **1 second** for typical use cases.

#### Why Adjacency List Over Adjacency Matrix?

We use an **adjacency list** instead of an **adjacency matrix** due to the following advantages:

1. **Graph Sparsity**:

   - The dataset consists of **millions of landmarks**, but each landmark connects to only a limited number of others.
   - An adjacency matrix would be mostly **empty (zero values)**, wasting memory.

2. **Memory Efficiency**:

   - An adjacency matrix requires **\(O(V^2)\) space**, while an adjacency list only needs **\(O(V + E)\)**, making it significantly more efficient for sparse graphs.

3. **Traversal Speed**:

   - In an adjacency matrix, iterating over all connections for a node takes **\(O(V)\) time**, even if most connections do not exist.
   - With an adjacency list, traversal is **\(O(\text{degree})\)**, reducing unnecessary computations.

4. **Pathfinding Alignment**:
   - Dijkstra’s algorithm **naturally works with adjacency lists**, as it prioritizes exploring existing edges.

This choice ensures the system remains **efficient and scalable**, aligning with the performance goals in **4.2 Performance Goals**.

### Scalability and Performance

- The algorithm is optimized to handle large datasets with **millions of nodes and edges**.
- Preprocessing steps such as **duplicate removal, graph validation, and sorting** reduce runtime overhead.

### Complexity

1. **Time Complexity**:

   - Using a priority queue (min-heap), Dijkstra’s achieves **\(O((V + E) \log V)\)** time complexity.
   - The use of **bidirectional search** further improves efficiency.
     ![Time Complexity](/documents/images/formula1.png)

1. **Space Complexity**:
   - The adjacency list representation and **priority queue** require **\(O(V + E)\)** space.

These optimizations make the algorithm highly suitable for **large-scale route calculations**.

For the detailed workflow and implementation, refer to **6.1 Path Calculation**.

### Optimizations for Dijkstra’s

To improve performance and **ensure real-time query processing**, the following optimizations are applied:

1. **Heap Optimization**:

   - Instead of a traditional priority queue, a **custom heap implementation** is used to improve insertion and extraction efficiency.

2. **Bidirectional Dijkstra’s**:

   - The search runs **simultaneously from the source and destination**.
   - The algorithm terminates **when both searches meet**, reducing the number of explored nodes.

3. **Path Sorting for Faster Access**:

   - Edges in the adjacency list are **sorted by travel time** to prioritize the most optimal paths first.
   - This reduces unnecessary computations when expanding nodes.

These optimizations allow the system to process queries **efficiently**, even when handling large datasets.

---

## 6.1 Path Calculation

### Overview

The path calculation system implements **Dijkstra’s algorithm** to compute the **quickest** path between two landmarks. The algorithm is optimized to balance **accuracy and speed**, ensuring **sub-second query responses**.

### Workflow

1. **Initialization**:

   - The graph is represented as an **adjacency list**.
   - A **min-heap priority queue** is initialized with the **starting landmark**.
   - The algorithm starts with the **source node** at distance **0**.

2. **Bidirectional Search**:

   - The algorithm runs **simultaneously** from both the **start** and **destination** nodes.
   - Nodes are processed alternately from each side.
   - The search **terminates early** when the two searches meet.

3. **Priority Queue Handling**:

   - The **priority queue** selects the node with the **smallest travel time**.
   - Neighboring nodes are **updated** if a **shorter path** is found.

4. **Path Construction**:
   - Once the **destination** is reached, the shortest path is **reconstructed** using **predecessor tracking**.
   - The result is returned in **JSON/XML format** through the **REST API**.

### Optimization Techniques

- **Heap Optimization**:

  - A **custom heap** is used instead of a standard priority queue, improving extraction efficiency.

- **Sorting of Paths**:

  - **Edges are pre-sorted** to prioritize faster paths in graph traversal.

### Edge Cases

- **Identical Landmarks**:
  - If `landmark_1 == landmark_2`, return `time = 0` with an empty path.

### Diagram

The following diagram illustrates **Bidirectional Dijkstra’s search**:

![Dijkstra Algorithm Workflow](/documents/images/Algorithm.png)

For further details on graph representation, see **5.3 Algorithm Design**.

---

## 6.2 Data Validation Tool

### Overview

The data validation tool ensures the integrity and usability of the dataset before it is integrated into the system. It implements the criteria defined in **4.3** and automates error detection and logging.

### Workflow

1. **Format Validation**:

   - Check that each row adheres to the expected format: `Landmark_A_ID, Landmark_B_ID, Time`.
   - Ensure that IDs are integers and the travel time is a positive number.

2. **Duplicate Removal**:

   - Identify and remove duplicate connections between landmarks, considering both directions (e.g., `A -> B` and `B -> A`).

3. **Connectivity Check**:

   - Use a Breadth-First Search (BFS) to verify that all nodes are reachable from at least one other node, ensuring a fully connected graph.

4. **Cycle Detection**:

   - For subgraphs expected to be acyclic (e.g., in specific regions), detect cycles using a Depth-First Search (DFS).

5. **Output**:
   - The tool outputs a structured report summarizing detected errors, categorized for easy review. Errors are categorized as:
     - Format issues.
     - Duplicate entries.
     - Disconnected nodes.
     - Cycles in acyclic regions.
   - The dataset is flagged as invalid if any errors are found.

#### Example Output

Below is an example of the tool's output in JSON format:

```json
{
  "summary": {
    "total_errors": 5,
    "format_issues": 2,
    "duplicate_entries": 1,
    "disconnected_nodes": 1,
    "cycles_detected": 1
  },
  "details": {
    "format_issues": [
      {
        "row_number": 10,
        "issue": "Invalid time value: 'N/A'",
        "row_data": "123,456,N/A"
      },
      {
        "row_number": 45,
        "issue": "Missing landmark ID",
        "row_data": ",789,25"
      }
    ],
    "duplicate_entries": [
      {
        "entry": "Landmark_A_ID: 123, Landmark_B_ID: 456, Time: 15",
        "occurrences": 2
      }
    ],
    "disconnected_nodes": [
      {
        "node_id": 789,
        "issue": "Node is isolated and has no connections."
      }
    ],
    "cycles_detected": [
      {
        "cycle_path": [123, 456, 789, 123],
        "issue": "Cycle detected in acyclic region."
      }
    ]
  }
}
```

### Efficiency Measures

- Large datasets are processed in chunks to prevent memory overflow.
- Multi-threading is utilized for independent checks (e.g., format validation and duplicate removal).

![Data Validation Workflow](/documents/images/dataValidation.png)

## 6.3 Dataset Conversion and Storage

### Overview

Once the dataset has been validated and processed, it is converted into a custom binary (`.bin`) format to enhance storage efficiency and access speed. This conversion significantly reduces file size and improves data retrieval performance.

### Conversion Process

1. **Data Validation and Preprocessing**:

   - The dataset undergoes validation using the **Data Validation Tool** (see **6.2**) to ensure data integrity.
   - Duplicate entries and disconnected graphs (DSG) are removed.
   - The dataset is **sorted before storage** to optimize search and retrieval.

2. **Binary Format Conversion**:

   - The validated dataset is transformed into a binary format (`.bin`) for **efficient storage and retrieval**.
   - Each record is stored as **16-bit integers**, minimizing memory usage while preserving accuracy.

3. **Optimized Path Sorting**:

   - Paths are **sorted prior to writing** to the binary file, allowing faster lookups.
   - Sorting ensures that queries can be processed with minimal overhead.

4. **Storage and Access Mechanism**:
   - The `.bin` file is written using **raw binary storage** rather than text-based serialization.
   - The data structure is designed for **direct memory access**, eliminating parsing overhead.
   - The **Path Calculation Module** (see **6.1**) loads the binary dataset at startup for quick access.

### Benefits of Binary Conversion

- **Reduced Storage Space**:

  - The `.bin` format is more compact than CSV or JSON.
  - Each entry is stored as raw **16-bit integers**, reducing disk usage.

- **Faster Read and Write Operations**:

  - Binary files allow **direct memory access**, eliminating text parsing.
  - Compared to CSV parsing, binary read/write operations are significantly faster.

- **Optimized Pathfinding Performance**:
  - Sorting paths before storage reduces query time.
  - The binary format enables **instant lookups** during shortest-path calculations.

### Example Structure of the Binary Format

Each record in the `.bin` file consists of:

| Field        | Type     | Size (bits) | Description                           |
| ------------ | -------- | ----------- | ------------------------------------- |
| `landmark_A` | `uint16` | 16          | Source landmark ID                    |
| `landmark_B` | `uint16` | 16          | Destination landmark ID               |
| `time`       | `uint16` | 16          | Travel time between the two landmarks |

Example binary representation:

```plaintext
0000001011010010 0000001100101100 0000000000111110
```

This corresponds to:

- `landmark_A = 722`
- `landmark_B = 812`
- `time = 62`

### Integration with the System

- The **Path Calculation Module** reads from the `.bin` file at startup.
- Queries for shortest paths **directly access preprocessed binary data**, ensuring minimal latency.
- The binary format eliminates **runtime text parsing**, significantly speeding up API response times.

## 6.4 Performance Testing

### Overview

Performance testing validates that the system meets its response time and scalability requirements under realistic conditions.

### Testing

- **General Testing**:
  - Verify correctness of individual components (e.g., Dijkstra’s algorithm, graph construction).
  - Validate that the REST API responds correctly to all input scenarios, including edge cases.

### Stress Testing

Simulate concurrent queries to assess system behavior under load:

- Up to 20 concurrent queries are tested to reflect realistic usage scenarios.
- Metrics are collected for response time and resource usage under different loads.

### Latency Measurement

Measure average and maximum response times for queries with:

- Small datasets (~10,000 nodes).
- Medium datasets (~1 million nodes).
- Large datasets (~24 million nodes).

### Failure Rate

Failures are defined as:

1. Responses exceeding the 1-second response time threshold.
2. Incorrect results due to concurrency issues or resource contention.

The failure rate should remain below 5% under concurrent load scenarios. Higher load may cause failures due to:

- Resource contention (e.g., insufficient threads or memory).
- Latency from increased queuing or thread scheduling.

### Automation

- Tests are automated using **Google Test** and **Apache JMeter**.
- A CI/CD pipeline ensures consistent validation of performance metrics.

### Scalability Testing

- Gradually increase dataset size and query frequency to evaluate performance degradation.
- Identify bottlenecks and suggest potential optimizations for future iterations.

  ![Testing](/documents/images/Testing.png)

---

# 7. Non-Functional Requirements

This section outlines the non-functional requirements that define the quality attributes of the system. These requirements ensure the system is reliable, scalable, secure, and maintainable, while meeting performance and usability expectations.

## 7.1 Response Time

- **Requirement**: The system must respond to valid queries within **1 second** on a standard laptop with medium dataset sizes (~1 million nodes).
- **Rationale**:
  - Users expect quick results for route calculations, even for large datasets.
  - Ensures the system remains practical for real-time applications like logistics or navigation.
- **Metrics**:
  - **Average Response Time**: <1 second for valid queries.
  - **Maximum Response Time**: <1.5 seconds under stress conditions (e.g., 20 concurrent queries).
  - Response times must be consistent regardless of output format (JSON or XML).

---

## 7.2 Scalability

- **Requirement**: The system must handle larger datasets and increased query loads with graceful degradation in performance.
- **Rationale**:
  - As datasets grow (e.g., from U.S. landmarks to global landmarks), the system should remain usable without excessive hardware upgrades.
- **Design Considerations**:
  - Use memory-efficient data structures like adjacency lists for graph representation.
  - Implement multithreading to handle multiple concurrent queries.
  - Support for adding new geographic datasets without requiring extensive reconfiguration.
- **Metrics**:
  - For datasets up to **24 million nodes**:
    - Maintain response times under 1.5 seconds.
  - For **20 concurrent queries**, the failure rate (response time > 1.5 seconds) must remain below 5%.

---

## 7.3 Usability

- **Requirement**: The REST API must be intuitive, well-documented, and easy to integrate with external systems.
- **Rationale**:
  - The API is the primary interface for developers and clients, so clarity and ease of use are critical.
- **Features**:
  - Provide comprehensive API documentation with:
    - Endpoint descriptions.
    - Input/output examples.
    - Error code explanations.
  - Return human-readable error messages for invalid queries.
  - Support common formats (JSON and XML) to meet diverse client requirements.

---

## 7.4 Reliability

- **Requirement**: The system must handle expected usage without crashing or returning incorrect results.
- **Rationale**:
  - Ensures trust and dependability for real-world applications.
- **Design Considerations**:
  - Validate inputs thoroughly to prevent malformed requests from causing failures.
  - Handle edge cases like identical landmarks or disconnected graphs gracefully (see **6.1** and **6.2**).
  - Include retry mechanisms for transient errors in external systems (e.g., dataset loading).

---

## 7.5 Security

- **Requirement**: Protect the system from unauthorized access, data corruption, and denial-of-service attacks.
- **Rationale**:
  - The REST API could be exposed to the public, so basic security measures are essential.
- **Features**:
  - **Rate Limiting**: Prevent excessive query submissions from overloading the system.
  - **Input Validation**: Reject malformed or malicious queries to prevent injection attacks.
  - **Transport Security**: Use HTTPS for all API communications to encrypt data in transit.
  - **Access Control**: Optionally, restrict API usage to authenticated users with API keys.

---

## 7.6 Maintainability

- **Requirement**: The codebase and system architecture must support easy debugging, updates, and expansions.
- **Rationale**:
  - Future developers should be able to adapt or extend the system without significant overhead.
- **Features**:
  - Follow clean coding practices and include sufficient inline comments.
  - Provide clear documentation for:
    - Codebase structure.
    - Build and deployment processes.
  - Modular architecture to allow future enhancements (e.g., adding new algorithms or datasets).

---

## 7.7 Data Integrity

- **Requirement**: The system must maintain the integrity of the input dataset during validation and processing.
- **Rationale**:
  - Reliable route calculations depend on the correctness and consistency of the dataset.
- **Design Considerations**:
  - Ensure dataset preprocessing (see **6.2**) identifies and logs all errors without altering the source data.
  - Include checksums or versioning for datasets to detect accidental modifications.

---

## 7.8 Compliance

- **Requirement**: Adhere to established standards for RESTful APIs and data handling.
- **Rationale**:
  - Ensures compatibility with third-party systems and compliance with industry best practices. (put a link to c standard)
- **Standards**:
  - Use RESTful conventions for endpoint design and HTTP status codes.
  - Adhere to JSON and XML schema standards for output formats.
  - Ensure data handling complies with relevant privacy and security laws (if applicable).

---

# 8. Deliverables

The following deliverables outline the technical outputs developers need to produce or interact with during the project.

## 8.1 Source Code

- **Content**:
  - Complete implementation of:
    - Dijkstra’s algorithm for pathfinding.
    - REST API using `cpp-httplib` or an equivalent framework.
    - Data validation and preprocessing utilities.
  - Modular and well-documented C++ code (with inline comments for maintainability).
- **Purpose**:
  - Provides the core functionality of the system, enabling path calculations and API interactions.

---

## 8.2 Test Suite

- **Content**:
  - Automated tests to validate:
    - Dijkstra’s algorithm correctness and performance.
    - REST API responses, including edge cases.
    - Dataset validation tool outputs.
- **Purpose**:
  - Ensures the system meets functional and non-functional requirements, enabling developers to verify the system's reliability and performance.

---

## 8.3 Data Validation Outputs

- **Content**:
  - Logs and error reports generated by the data validation tool, categorized by:
    - Format issues.
    - Duplicate entries.
    - Disconnected nodes.
    - Cycles in acyclic subgraphs.
- **Purpose**:
  - Ensures the dataset is prepared for use in the system and helps developers identify and resolve dataset-related issues before execution.

---

### Reference

For a comprehensive list of project deliverables, including non-technical outputs such as final presentations and reports, refer to the Functional Specifications.

# 9. Development Framework

This section outlines the principles, challenges, potential risks, and approach for the development of the system. It serves as a guide for developers to ensure alignment with project goals and efficient implementation.

## 9.1 Code Design Principles

The following coding design principles will guide the development of the system:

1. **No Use of Unnecessary Third-Party Libraries**:

   - Prioritize standard C++ libraries and lightweight frameworks (e.g., `cpp-httplib`) to maintain simplicity and control over dependencies.

2. **Focus on Algorithmic Complexity**:

   - Emphasize improving algorithmic efficiency (e.g., Dijkstra’s optimization) over micro-optimizations to ensure scalability for large datasets.

3. **Code Readability and Maintainability**:

   - Write modular, self-explanatory code with clear inline comments.
   - Follow clean coding practices to ensure future developers can easily debug or extend the system.

4. **Testing During Development**:
   - Use unit tests to ensure correctness and prevent regressions during development.

---

## 9.2 Challenges

The project presents several significant challenges that must be addressed during development:

1. **Handling Large Datasets**:

   - Efficiently processing datasets with up to 24 million nodes while ensuring sub-second response times.

2. **Balancing Accuracy and Performance**:

   - Implementing the Dijkstra’s algorithm to achieve results within 10% of the optimal path while meeting performance goals.

3. **Data Validation Complexity**:

   - Identifying and categorizing dataset errors (e.g., disconnected nodes, duplicate entries) without impacting runtime performance.

4. **Concurrency and Scalability**:

   - Managing multiple simultaneous queries (up to 20 concurrent requests) without degrading response times.

5. **Error Handling**:
   - Providing clear, actionable error messages for invalid inputs, unreachable nodes, and other edge cases.

---

## 9.3 Possible Bugs

The following potential bugs or limitations could arise during development:

1. **Handling Extremely Large Datasets**:

   - The system may struggle with datasets exceeding the tested limit (~24 million nodes) due to memory or performance constraints.

2. **Concurrency Issues**:

   - Incorrect handling of concurrent queries may result in thread safety issues or race conditions.

3. **Algorithmic Inaccuracy**:

   - Edge cases, such as incorrect heuristic values, may result in suboptimal path calculations.

4. **Validation Errors**:

   - Dataset validation may fail to detect complex connectivity issues in edge cases.

5. **System Crashes**:

   - Unexpected inputs or malformed requests could lead to crashes if input validation is insufficient.

6. **Performance Degradation**:
   - Under high load, response times may exceed the specified thresholds due to resource contention.

---

## 9.4 Development Process

The development process will follow an incremental approach, focusing on building a working system while gradually expanding its capabilities:

1. **Initial Implementation**:

   - Begin with the Dijkstra’s algorithm and a basic graph representation.
   - Implement the REST API with a single endpoint for path calculations.
   - Create a minimal dataset validation tool to handle basic checks (e.g., format validation and duplicate removal).

2. **Incremental Expansion**:

   - Gradually add more complex dataset validation features (e.g., connectivity checks, cycle detection).
   - Expand REST API functionality to support JSON and XML formats and robust error handling.

3. **Performance Optimization**:

   - Optimize Dijkstra’s algorithm and graph structures for scalability with larger datasets.
   - Add caching or pruning techniques for frequently queried paths.

4. **Testing and Validation**:

   - Develop a comprehensive test suite for unit, integration, and performance testing.
   - Simulate concurrent queries to evaluate system behavior under load.

5. **Finalization**:
   - Address potential bugs and edge cases identified during testing.
   - Prepare the system for delivery with all key features implemented and tested.

---
