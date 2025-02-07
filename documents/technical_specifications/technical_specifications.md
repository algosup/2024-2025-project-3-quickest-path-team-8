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
    - [Optimizations for A\*](#optimizations-for-a)
- [6. Implementation and Testing](#6-implementation-and-testing)
  - [6.1 Path Calculation](#61-path-calculation)
    - [Overview](#overview)
    - [Workflow](#workflow)
    - [Diagram](#diagram)
    - [Optimization Techniques](#optimization-techniques)
    - [Edge Cases](#edge-cases)
  - [6.2 Data Validation Tool](#62-data-validation-tool)
    - [Overview](#overview-1)
    - [Workflow](#workflow-1)
      - [Example Output](#example-output)
    - [Efficiency Measures](#efficiency-measures)
  - [6.3 Dataset Conversion and Storage](#63-dataset-conversion-and-storage)
    - [Overview](#overview-2)
    - [Conversion Process](#conversion-process)
    - [Benefits of Binary Conversion](#benefits-of-binary-conversion)
    - [Example Structure of Binary Format](#example-structure-of-binary-format)
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

- **Software Developers**: To understand the user and technical requirements and guide decision-making and planning. This includes identifying risks and challenges, meeting customer requirements, and understanding additional technical requirements and design choices.

Secondary audiences:

- **Program Managers**: To validate the implementation against the functional specification and client expectations.
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

| Term                             | Definition                                                                                           |
| -------------------------------- | ---------------------------------------------------------------------------------------------------- |
| **Landmark**                     | A point in the graph representing a location in the U.S.                                             |
| **Graph**                        | A network of nodes (landmarks) connected by edges (paths) with associated travel times.              |
| **DAG (Directed Acyclic Graph)** | A graph that doesn’t contain cycles, used to model the landmark connections when applicable.         |
| **REST API**                     | A web service exposing functionality via HTTP endpoints, in this case, to query the shortest path.   |
| **Shortest Path Algorithm**      | An algorithm (e.g., Dijkstra's or A\*) designed to find the minimum cost or time path between nodes. |
| **Connected Graph**              | A graph where every node is reachable from any other node.                                           |
| **Disconnected Subgraph**        | A subset of nodes within a graph that are not connected to the main graph or other subgraphs.        |

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

  - A heuristic approximation algorithm (e.g., A\* or Dijkstra’s algorithm) will be used to balance speed and accuracy.
  - The returned route duration must not exceed the shortest possible duration by more than 10%.

### Dataset Preprocessing

- **Purpose**:
  - Ensure the dataset meets validation criteria for accurate path calculations.
- **Requirements**:
  - The dataset must adhere to validation criteria outlined in **4.3 Data Integrity Verification**.
  - Refer to **6.2 Data Validation Tool** for the detailed workflow and implementation.

![diagram](/documents/images/APIrequest.png)

---

## 4.2 Performance Goals

### Response Time

- The API must respond to all valid queries within **1 second** on a typical laptop, even when handling datasets with millions of nodes and connections.
- Queries to landmarks with no valid path should also return responses within the same time frame.

### Scalability

- If the dataset grows (e.g., expanding from the United States to global coverage), the performance will need to degrade gracefully, to maintain usability under the increased load.

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

To ensure accurate and reliable path calculations, the system must validate the integrity of the input dataset. This verification process ensures the dataset meets the following criteria:

### Validation Criteria

1. **Data Format**:

   - Each row in the CSV dataset must follow the required structure: `Landmark_A_ID, Landmark_B_ID, Time`.
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

  | Case                      | HTTP Code | Description                                             |
  | ------------------------- | --------- | ------------------------------------------------------- |
  | Missing parameters        | 400       | Invalid or incomplete query parameters.                 |
  | Unsupported output format | 406       | Format not supported (e.g., anything besides JSON/XML). |
  | Disconnected graph        | 404       | No route exists between the provided landmarks.         |
  | Nonexistent landmarks     | 404       | One or both landmarks are not present in the dataset.   |

- **Performance Considerations**:
  - Lightweight HTTP server optimizations ensure that API response times meet the <1-second requirement under typical workloads.

---

## 5.3 Algorithm Design

The algorithm is a core component of the system, responsible for calculating the quickest path between two landmarks. Its design ensures a balance between accuracy, performance, and scalability, aligned with the system’s requirements.

### Core Algorithm

- The A\* algorithm is selected for its heuristic-driven approach, combining efficient exploration with guaranteed pathfinding.
- The heuristic function helps prioritize nodes closer to the destination, optimizing search performance.

### Role in the System

- Operates on a preprocessed dataset represented as an adjacency list, ensuring efficient traversal of landmark connections.
- Integrated into the REST API to dynamically process pathfinding queries and return results within 1 second for typical use cases.

#### Why Adjacency List Over Adjacency Matrix?

We use an adjacency list to represent the graph instead of an adjacency matrix for the following reasons:

1. **Dimensionality of the Graph**:

   - The graph is sparse, meaning each landmark connects to only a subset of other landmarks. An adjacency matrix would waste memory as most entries would be `0` after the first dimension.

2. **Memory Efficiency**:

   - For a graph with `V` vertices and `E` edges:
     - An adjacency matrix requires \(O(V^2)\) space, regardless of the number of edges.
     - An adjacency list requires \(O(V + E)\), making it far more efficient for sparse graphs.
   - Given the dataset’s scale (millions of landmarks with limited connections per landmark), the adjacency list minimizes memory usage.

3. **Traversal Speed**:

   - In an adjacency matrix, traversing all possible connections for a vertex requires \(O(V)\) time, even for unconnected vertices.
   - With an adjacency list, traversal is proportional to the vertex's degree (\(O(\text{degree})\)), significantly improving performance.

4. **Alignment with Pathfinding**:
   - Pathfinding algorithms like A\* prioritize traversing edges between connected nodes. An adjacency list directly stores these edges, avoiding unnecessary computations on unconnected nodes.

This choice ensures the system remains efficient and scalable, aligning with the performance goals defined in **4.2 Performance Goals**.

### Scalability and Performance

- The algorithm is optimized to handle large datasets containing millions of nodes and edges.
- Preprocessing steps, such as duplicate removal and graph validation, reduce runtime overhead.

### Complexity

1. **Time Complexity**:

   - For a graph with `V` vertices (landmarks) and `E` edges (connections), A\* has a worst-case time complexity of:
     ![Time Complexity](/documents/images/formula1.png)

2. **Space Complexity**:
   - The adjacency list representation and additional data structures (e.g., priority queue, visited nodes) result in a space complexity of:
     ![Space Complexity](/documents/images/formula2.png)

These formulas illustrate the algorithm’s efficiency for large-scale graphs, emphasizing its suitability for the project.

For the detailed workflow and implementation, refer to **6.1 Path Calculation**.

### Optimizations for A\*

The A\* algorithm is further optimized to improve performance and scalability while maintaining accuracy. The following enhancements are implemented:

1. **Heuristic Refinement**:

   - To improve the efficiency of the A\* algorithm, we implement a heuristic function using a strength-based 3D representation of the nodes.
   - During preprocessing, nodes are mapped to a 3D space where their positions reflect their connectivity and relationships to other nodes in the graph.
   - The Euclidean distance between nodes in this 3D space is used as the heuristic function (\(h(n)\)).
     - This heuristic is admissible (does not overestimate costs) and consistent (satisfies the triangle inequality), ensuring the correctness of the algorithm.
   - If preprocessing is unavailable, the algorithm can fall back to a heuristic-free approach, equivalent to Dijkstra’s algorithm, at the cost of reduced performance.

2. **Bidirectional A\***:

   - The search process is executed simultaneously from the source and destination nodes. The algorithm terminates when the two searches meet, reducing the search space significantly.

3. **Weighted A\***:

   - A weighted heuristic (\(f(n) = g(n) + \epsilon \cdot h(n)\)) is introduced to prioritize exploration of likely paths more aggressively. This reduces the search time while slightly relaxing the accuracy constraint.

4. **Priority Queue Optimization**:

   - A bucket-based priority queue replaces the standard implementation, reducing computational overhead for node selection.

5. **Parallelization**:
   - The algorithm is parallelized to leverage multi-core processors. Node evaluations are distributed across threads, significantly accelerating the search process.

These optimizations enable the system to handle larger datasets efficiently, ensuring rapid responses even under high-concurrency scenarios or for geographically dispersed datasets.

# 6. Implementation and Testing

## 6.1 Path Calculation

### Overview

The path calculation system implements the A\* algorithm to compute the quickest path between two landmarks. This approach ensures compliance with the system’s accuracy and performance goals.

### Workflow

1. **Initialization**:

   - The graph is represented as an adjacency list, derived from the dataset during preprocessing. Each node (landmark) is connected to its neighbors with associated travel times.
   - The priority queue (min-heap) is initialized with the starting landmark (`landmark_1`) and its heuristic value (estimated travel time to `landmark_2`).

2. **Exploration**:

   - At each step, the node with the lowest estimated cost (actual cost + heuristic) is dequeued, and its neighbors are evaluated.
   - For each neighbor:
     - Calculate the tentative cost (current cost + edge weight to neighbor).
     - If the tentative cost is lower than the previously recorded cost for the neighbor, update the cost and set the current node as the predecessor.
     - Add the neighbor to the priority queue with its updated cost.
   - Track visited nodes to prevent re-evaluating paths unnecessarily.

3. **Heuristic Evaluation**:

   - The heuristic function estimates the cost from a node to the destination. It:
     - Underestimates the actual cost (to maintain A\*'s correctness).
     - Prioritizes nodes closer to the destination based on estimated travel time.
   - Examples of heuristics for this project include:
     - Straight-line distance (if coordinates are available).
     - Historical average travel times.

4. **Termination**:
   - The algorithm terminates when:
     - The destination node (`landmark_2`) is dequeued, and the path is reconstructed using the predecessor list.
     - The priority queue is empty, indicating no valid path exists.

### Diagram

The following diagram illustrates the workflow of the A\* algorithm:

![A* Algorithm Workflow](/documents/images/Algorithm.png)

### Optimization Techniques

- **Graph Pruning**:
  - During preprocessing, unnecessary nodes and connections are removed to streamline computation.
- **Path Caching**:
  - Frequently queried paths are cached in memory to reduce redundant calculations for commonly requested routes.

### Edge Cases

- **Identical Landmarks**:
  - Return a time of `0` with an empty path.

For a high-level explanation of the algorithm’s role in the system, refer to **5.3 Algorithm Design**.

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

Once the dataset has been validated and processed, the system converts it into a custom binary (`.bin`) format to improve storage efficiency and access speed. This format reduces the dataset's memory footprint and optimizes query performance.

### Conversion Process

1. **Data Validation and Preprocessing**:

   - The dataset undergoes verification through the **Data Validation Tool** (see **6.2**) to ensure correctness.
   - Duplicate entries and disconnected graphs (DSG) are removed.
   - The dataset is sorted to optimize storage and retrieval.

2. **Binary Format Conversion**:

   - The validated dataset is transformed into a binary format (`.bin`).
   - Each record is stored in **16-bit encoding**, reducing storage requirements while maintaining precision.

3. **Sorting Paths for Optimized Access**:

   - Path entries are sorted to enhance search and retrieval efficiency.
   - Sorting enables faster lookups and improves performance in path calculations.

4. **Storage Mechanism**:
   - The `.bin` file is stored in a structured format to allow rapid access by the **Path Calculation Module** (see **6.1**).
   - The data structure is designed to be memory-efficient while allowing direct access to required paths.

### Benefits of Binary Conversion

- **Space Optimization**:
  - The `.bin` format reduces the dataset’s size compared to CSV or JSON, improving memory efficiency.
- **Faster Read and Write Operations**:

  - Binary files are significantly faster to read compared to text-based formats.

- **Optimized Pathfinding Performance**:
  - The sorted paths improve lookup speeds for the A\* algorithm.

### Example Structure of Binary Format

Each record in the `.bin` file consists of:

| Field        | Type     | Size (bits) | Description                           |
| ------------ | -------- | ----------- | ------------------------------------- |
| `landmark_A` | `uint16` | 16          | Source landmark ID                    |
| `landmark_B` | `uint16` | 16          | Destination landmark ID               |
| `time`       | `uint16` | 16          | Travel time between the two landmarks |

Example of a binary representation:

```plaintext
0000001011010010 0000001100101100 0000000000111110
```

## 6.4 Performance Testing

### Overview

Performance testing validates that the system meets its response time and scalability requirements under realistic conditions.

### Testing

- **General Testing**:
  - Verify correctness of individual components (e.g., A\* algorithm, graph construction).
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
  - Follow JSON and XML schema standards for output formats.
  - Ensure data handling complies with relevant privacy and security laws (if applicable).

---

# 8. Deliverables

The following deliverables outline the technical outputs developers need to produce or interact with during the project.

## 8.1 Source Code

- **Content**:
  - Complete implementation of:
    - A\* algorithm for pathfinding.
    - REST API using `cpp-httplib` or an equivalent framework.
    - Data validation and preprocessing utilities.
  - Modular and well-documented C++ code (with inline comments for maintainability).
- **Purpose**:
  - Provides the core functionality of the system, enabling path calculations and API interactions.

---

## 8.2 Test Suite

- **Content**:
  - Automated tests to validate:
    - A\* algorithm correctness and performance.
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

For a comprehensive list of project deliverables, including non-technical outputs such as final presentations or reports, refer to the Functional Specifications.

# 9. Development Framework

This section outlines the principles, challenges, potential risks, and approach for the development of the system. It serves as a guide for developers to ensure alignment with project goals and efficient implementation.

## 9.1 Code Design Principles

The following coding design principles will guide the development of the system:

1. **No Use of Unnecessary Third-Party Libraries**:

   - Prioritize standard C++ libraries and lightweight frameworks (e.g., `cpp-httplib`) to maintain simplicity and control over dependencies.

2. **Focus on Algorithmic Complexity**:

   - Emphasize improving algorithmic efficiency (e.g., A\* optimization) over micro-optimizations to ensure scalability for large datasets.

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

   - Implementing the A\* algorithm to achieve results within 10% of the optimal path while meeting performance goals.

3. **Data Validation Complexity**:

   - Identifying and categorizing dataset errors (e.g., disconnected nodes, duplicate entries) without impacting runtime performance.

4. **Concurrency and Scalability**:

   - Managing multiple simultaneous queries (up to 20 concurrent requests) without degrading response times.

5. **Error Handling**:
   - Providing clear, actionable error messages for invalid inputs, unreachable nodes, and other edge cases.

---

## 9.3 Possible Bugs

The following potential bugs or limitations could arise during development:

1. **Handling Very Large Datasets**:

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

   - Begin with the A\* algorithm and a basic graph representation.
   - Implement the REST API with a single endpoint for path calculations.
   - Create a minimal dataset validation tool to handle basic checks (e.g., format validation and duplicate removal).

2. **Incremental Expansion**:

   - Gradually add more complex dataset validation features (e.g., connectivity checks, cycle detection).
   - Expand REST API functionality to support JSON and XML formats and robust error handling.

3. **Performance Optimization**:

   - Optimize A\* algorithm and graph structures for scalability with larger datasets.
   - Add caching or pruning techniques for frequently queried paths.

4. **Testing and Validation**:

   - Develop a comprehensive test suite for unit, integration, and performance testing.
   - Simulate concurrent queries to evaluate system behavior under load.

5. **Finalization**:
   - Address potential bugs and edge cases identified during testing.
   - Prepare the system for delivery with all key features implemented and tested.

---
