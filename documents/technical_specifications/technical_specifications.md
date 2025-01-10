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
    - [Error Detection and Reporting](#error-detection-and-reporting)
    - [Correction Recommendations](#correction-recommendations)
    - [Integrity Assurance](#integrity-assurance)
  - [5. System Architecture](#5-system-architecture)
    - [5.1 Technology Stack](#51-technology-stack)
    - [5.2 REST API Design](#52-rest-api-design)
    - [5.3 Algorithm Design](#53-algorithm-design)
  - [6. Key Features and Functions](#6-key-features-and-functions)
    - [6.1 Path Calculation](#61-path-calculation)
    - [6.2 Data Validation Tool](#62-data-validation-tool)
    - [6.3 Performance Testing](#63-performance-testing)
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

- **Endpoint Description**

  - **Base URL:** `http://127.0.0.1:8080/quickest_path`
  - **HTTP Method:** `GET`
  - **Supported Response Formats:** JSON, XML.

- **Query Parameters**  
   The endpoint accepts the following parameters:

  | Parameter Name | Type    | Expected Value      | Description                          |
  | -------------- | ------- | ------------------- | ------------------------------------ |
  | `format`       | String  | `"json"` or `"xml"` | Specifies the desired output format. |
  | `landmark_1`   | Integer | 1 to 24,000,000+    | ID of the starting landmark.         |
  | `landmark_2`   | Integer | 1 to 24,000,000+    | ID of the destination landmark.      |

- **Output Specification**  
   The API provides route information with the following structure:

  - **JSON Format Example:**
    ```json
    {
      "time": 66,
      "steps": [
        { "landmark": 322, "distance": 33 },
        { "landmark": 323, "distance": 33 }
      ]
    }
    ```
  - **XML Format Example:**
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

- **Error Handling**  
   The API must handle invalid or erroneous inputs:

  | Case                      | HTTP Code | Description                                             |
  | ------------------------- | --------- | ------------------------------------------------------- |
  | Missing parameters        | 400       | Invalid or incomplete query parameters.                 |
  | Unsupported output format | 406       | Format not supported (e.g., anything besides JSON/XML). |
  | Disconnected graph        | 404       | No route exists between the provided landmarks.         |
  | Nonexistent landmarks     | 404       | One or both landmarks are not present in the dataset.   |

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

### Validation Criteria

- **Data Format Validation:**

  - Each row in the CSV dataset must adhere to the specified format:  
    `Landmark_A_ID, Landmark_B_ID, Time`.
  - Fields must be non-empty, and `Time` must be a positive integer or float.

- **Duplicate Entries:**

  - Duplicate connections (identical pairs of `Landmark_A_ID` and `Landmark_B_ID`) are flagged and removed to prevent redundancy in path calculations.

- **Connectivity Verification:**

  - The dataset must form a connected graph to ensure that there is at least one path between any two landmarks.
  - Disconnected subgraphs or isolated nodes are identified and flagged for correction.

- **Graph Validation:**
  - The graph must not contain cycles in paths intended to be acyclic, ensuring logical consistency in route calculations.

### Error Detection and Reporting

- A data validation tool will log all identified errors, categorized as specify the format:

  - **Format Errors:** Rows that fail to conform to the required format.
  - **Duplicate Entries:** Repeated connections.
  - **Disconnected Nodes:** Landmarks without connections.
  - **Cycles Detected:** Any cyclic paths in an acyclic graph context.

- A summary report will indicate the number of issues detected and provide actionable recommendations for resolution.

### Correction Recommendations

- Tools will suggest data fixes, such as:
  - Removing duplicate rows.
  - Connecting isolated nodes to the graph, if possible.
  - Correcting improperly formatted rows.

### Integrity Assurance

- The verification process will be automated and must be completed before the API uses the dataset.
- Upon successful validation, the dataset is marked as ready for use, ensuring it meets the required integrity standards.

![diagram](/documents/images/dataValidation.png)


## 5. System Architecture

### 5.1 Technology Stack

### 5.2 REST API Design

### 5.3 Algorithm Design

## 6. Key Features and Functions

### 6.1 Path Calculation

### 6.2 Data Validation Tool

### 6.3 Performance Testing

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
