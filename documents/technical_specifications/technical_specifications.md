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
    - [Verification Process](#verification-process)
    - [Importance of Data Integrity](#importance-of-data-integrity)
  - [5. System Architecture](#5-system-architecture)
    - [5.1 Technology Stack](#51-technology-stack)
    - [5.2 REST API Design](#52-rest-api-design)
    - [5.3 Algorithm Design](#53-algorithm-design)
  - [6. Implementation and Testing](#6-implementation-and-testing)
    - [6.1 Path Calculation](#61-path-calculation)
      - [Overview](#overview)
      - [Workflow](#workflow)
      - [Optimization Techniques](#optimization-techniques)
      - [Disconnected Graphs](#disconnected-graphs)
      - [Edge Cases](#edge-cases)
    - [6.2 Data Validation Tool](#62-data-validation-tool)
      - [Overview](#overview-1)
      - [Workflow](#workflow-1)
      - [Correction Mechanisms](#correction-mechanisms)
      - [Efficiency Measures](#efficiency-measures)
    - [6.3 Performance Testing](#63-performance-testing)
      - [Overview](#overview-2)
      - [Testing](#testing)
      - [Stress Testing](#stress-testing-1)
      - [Latency Measurement](#latency-measurement)
      - [Failure Rate](#failure-rate)
      - [Automation](#automation)
      - [Scalability Testing](#scalability-testing)
  - [7. Non-Functional Requirements](#7-non-functional-requirements)
    - [7.1 Response Time](#71-response-time)
    - [7.2 Approximation Heuristic](#72-approximation-heuristic)
    - [7.3 Data Integrity](#73-data-integrity)
  - [8. Deliverables](#8-deliverables)
    - [8.1 C++ Source Code](#81-c-source-code)
    - [8.2 Time and Space Complexity](#82-time-and-space-complexity)
    - [8.3 REST API Implementation](#83-rest-api-implementation)
    - [8.4 Test Suite](#84-test-suite)
    - [8.5 Data Validation Tool](#85-data-validation-tool)
  - [9. Development Process](#9-development-process)
    - [9.1 Milestones](#91-milestones)
    - [9.2 Testing and Validation](#92-testing-and-validation)
    - [9.3 Risk Management](#93-risk-management)

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

- **Concurrency Support**
  - The API will handle multiple concurrent queries with minimal impact on performance.

### Dataset Preprocessing

- **Validation Tool**

  - Ensure the dataset is preprocessed to verify graph properties, including:
    - Absence of duplicate connections.
    - Connectivity between all nodes.
    - Validity of the data structure.
    - Detection of cycles in the graph.

- **Precomputed Data**
  - Optionally, precompute frequently used paths to reduce runtime computation.

![diagram](/documents/images/APIrequest.png)

---

## 4.2 Performance Goals

### Response Time

- The API must respond to all vali
- d queries within **1 second** on a typical laptop, even when handling datasets with millions of nodes and connections.
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

### Verification Process

The system employs a dedicated data validation tool to enforce these criteria. The tool:

- Logs errors and categorizes them into format errors, duplicate entries, disconnected nodes, and detected cycles.
- Generates a summary report with actionable recommendations for resolution.

For a detailed explanation of the validation tool’s workflow, refer to **Section 6.2: Data Validation Tool**.

### Importance of Data Integrity

- **Accuracy**: Ensures that the graph reflects real-world connectivity for path calculations.
- **Performance**: Reduces computational overhead by eliminating redundant or invalid data.
- **Reliability**: Guarantees that the dataset can handle large-scale queries without logical inconsistencies.

## 5. System Architecture

The system architecture defines the technical blueprint for implementing the software.

---

### 5.1 Technology Stack

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

### 5.2 REST API Design

The REST API handles requests for the quickest path between landmarks. Design considerations include:

- **Endpoint Details**:

  - **Base URL**: `http://127.0.0.1:8080/quickest_path`
  - **Parameters**:

    - `landmark_1`: Source landmark ID (integer).
    - `landmark_2`: Destination landmark ID (integer).
    - `format`: Desired output format (`json` or `xml`).

  - **Input Structure**:
    All inputs must be provided as query parameters in the URL. Example request:
    ```
    GET /quickest_path?landmark_1=100&landmark_2=200&format=json
    ```

- **Response Format Examples**:

  - **JSON Format Example**:
    ```json
    {
      "time": 66,
      "steps": [
        { "landmark": 322, "distance": 33 },
        { "landmark": 323, "distance": 33 }
      ]
    }
    ```
  - **XML Format Example**:
    ```xml
    <response>
      <time>66</time>
      <steps>
        <step>
          <landmark>322</landmark>
          <distance>33</distance>
        </step>
        <step>
          <landmark>323</landmark>
          <distance>33</distance>
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

### 5.3 Algorithm Design

The algorithm computes the quickest path between two landmarks. Its design focuses on efficiency, accuracy, and scalability:

- **Core Algorithm**:

  - **A\***: Selected for its heuristic-driven approach, which optimizes performance while maintaining compliance with the 10% approximation rule.
    - **Heuristic Function**: Travel time between nodes (landmarks) is used as the heuristic to guide the search efficiently.

- **Graph Representation**:

  - The dataset will be represented using an **adjacency list**. This structure is memory-efficient and allows quick traversal of connections between landmarks.

- **Supporting Data Structures**:

  - **Priority Queue**: A min-heap will be used to efficiently manage nodes during traversal, enabling fast extraction of the next optimal node.

- **Preprocessing**:

  - A dataset preprocessing step will validate and clean the data before usage:
    - Remove duplicate connections.
    - Verify graph connectivity.
    - Detect and handle cycles if applicable.

- **Complexity**:

  - **Time Complexity**:
    ![Time Complexity](/documents/images/formula1.png)

    Where V is the number of vertices (landmarks) and E is the number of edges (connections).

  - **Space Complexity**:

  ![Space Complexity](/documents/images/formula2.png)

  For storing the graph in an adjacency list.

- **Concurrency**:

  - The algorithm processes one query at a time. However, the REST API ensures multiple queries can be handled concurrently by distributing them across available threads.

- **Edge Cases**:
  - Identical `landmark_1` and `landmark_2`: Return a time of `0` with an empty path.
  - Nonexistent landmarks or unreachable nodes: Handled by the REST API with appropriate error responses.

---

## 6. Implementation and Testing

### 6.1 Path Calculation

#### Overview

The path calculation system is the core functionality of the project, leveraging the A* algorithm to compute the quickest path between two landmarks. A* is chosen for its balance of performance and accuracy, with a heuristic-driven approach that ensures compliance with the 10% approximation rule.

#### Workflow

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

   - The heuristic function estimates the cost from a node to the destination. This function is designed to:
     - Underestimate the actual cost (to maintain A\*'s correctness).
     - Prioritize nodes that are closer to the destination based on estimated travel time.
   - For this project, the heuristic could be based on:
     - Straight-line distance (if coordinates are available).
     - Historical average travel times.

4. **Termination**:
   - The algorithm terminates when:
     - The destination node (`landmark_2`) is dequeued, in which case the path is reconstructed using the predecessor list.
     - The priority queue is empty, indicating no valid path exists.

#### Optimization Techniques

- **Graph Pruning**:
  - During preprocessing, unnecessary nodes and connections (e.g., duplicates or isolated subgraphs) are removed to streamline computation.
- **Path Caching**:
  - Frequently queried paths are cached in memory to reduce redundant calculations for commonly requested routes.

#### Disconnected Graphs

Disconnected graphs are identified during preprocessing (see **6.2**) and are flagged as errors. The algorithm itself only operates on validated, connected graphs.

#### Edge Cases

- **Identical Landmarks**:
  - Return a time of `0` with an empty path.

![Algorithm](/documents/images/Algorithm.png)

---

### 6.2 Data Validation Tool

#### Overview

The data validation tool ensures the integrity and usability of the dataset before it is integrated into the system. This includes validating format, removing duplicates, and ensuring graph connectivity.

#### Workflow

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
   - The tool outputs a list of detected errors, categorized as format issues, duplicates, disconnected nodes, or cycles.
   - The dataset is flagged as invalid if any errors are found.

#### Correction Mechanisms

- **Manual Suggestions**:
  - Provide a list of disconnected nodes or improperly formatted rows for manual correction.
- **Automated Fixes**:
  - Remove duplicates automatically.
  - Attempt to connect isolated nodes by linking them to the nearest available neighbor.

#### Efficiency Measures

- Large datasets are processed in chunks to prevent memory overflow.
- Multi-threading is utilized for independent checks (e.g., format validation and duplicate removal).

  ![Data Validation](/documents/images/dataValidation.png)

---

### 6.3 Performance Testing

#### Overview

Performance testing validates that the system meets its response time and scalability requirements under realistic conditions.

#### Testing

- **General Testing**:
  - Verify correctness of individual components (e.g., A\* algorithm, graph construction).
  - Validate that the REST API responds correctly to all input scenarios, including edge cases.

#### Stress Testing

Simulate concurrent queries to assess system behavior under load:

- Up to 20 concurrent queries are tested to reflect realistic usage scenarios.
- Metrics are collected for response time and resource usage under different loads.

#### Latency Measurement

Measure average and maximum response times for queries with:

- Small datasets (~10,000 nodes).
- Medium datasets (~1 million nodes).
- Large datasets (~24 million nodes).

#### Failure Rate

Failures are defined as:

1. Responses exceeding the 1-second response time threshold.
2. Incorrect results due to concurrency issues or resource contention.

The failure rate should remain below 5% under concurrent load scenarios. Higher load may cause failures due to:

- Resource contention (e.g., insufficient threads or memory).
- Latency from increased queuing or thread scheduling.

#### Automation

- Tests are automated using **Google Test** and **Apache JMeter**.
- A CI/CD pipeline ensures consistent validation of performance metrics.

#### Scalability Testing

- Gradually increase dataset size and query frequency to evaluate performance degradation.
- Identify bottlenecks and suggest potential optimizations for future iterations.

  ![Testing](/documents/images/Testing.png)

---

## 7. Non-Functional Requirements

### 7.1 Response Time

### 7.2 Approximation Heuristic

### 7.3 Data Integrity

## 8. Deliverables

### 8.1 C++ Source Code

### 8.2 Time and Space Complexity

### 8.3 REST API Implementation

### 8.4 Test Suite

### 8.5 Data Validation Tool

## 9. Development Process

### 9.1 Milestones

### 9.2 Testing and Validation

### 9.3 Risk Management
