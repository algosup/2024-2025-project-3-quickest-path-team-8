# Test Plan

---

## Introduction

### Purpose

This document outlines the testing strategy and plan for ensuring the successful development and deployment of the high-performance pathfinding software. The primary focus is on verifying the correctness, efficiency, and reliability of the REST API, pathfinding algorithm, and data validation tool while adhering to the performance and functional requirements specified in the project tender document.

### Product Overview

The software solution aims to calculate the quickest path between two landmarks in the United States using a REST API. Key features include:

- **Programming Language**: C++ for optimal performance.
- **REST API**: Single GET endpoint supporting JSON and XML responses.
- **Performance**: Ensuring responses are within 1 second for queries with up to 10% approximation.
- **Data Validation**: A utility to ensure data integrity by checking connectivity, graph structure, and absence of loops.

---
## Testing Areas

### Overview

Testing encompasses the functional, performance, scalability, and data integrity aspects of the software while also evaluating the quality of project documentation, including functional specifications, technical specifications, and management artifacts. Key focus areas include:

#### Functional Testing

Verifying that the REST API, pathfinding algorithm, and data validation tool meet the specified requirements.

To address the questions regarding invalid input scenarios and error handling for the REST API, consider incorporating the following sections into the **Test Plan** document under the **Testing Areas** section:

**1. Invalid Input Scenarios and Edge Cases**

Add a subsection titled **"REST API Invalid Input Testing"** under **Functional Testing**.

In this subsection, detail the approach for identifying and testing invalid input scenarios.

Include a comprehensive list of edge cases, such as:

- **Missing Parameters**: Requests lacking required parameters.

- **Invalid Data Types**: Parameters with incorrect data types (e.g., string instead of integer).

- **Out-of-Range Values**: Parameters with values outside acceptable ranges.

- **Unsupported Formats**: Requests specifying unsupported response formats.

- **Malformed Requests**: Improperly structured requests that violate API specifications.

For each edge case, define the expected behavior and corresponding error response.

**2. Error Codes and Corresponding Messages**

Add a subsection titled **"API Error Codes and Messages"** under **Documentation Quality Testing**.

In this subsection, provide a detailed list of all possible error codes and their corresponding messages, ensuring they align with standard HTTP status codes and best practices.

For example:

- **400 Bad Request**: "The request could not be understood or was missing required parameters."

- **401 Unauthorized**: "Authentication failed or user does not have permissions for the desired action."

- **403 Forbidden**: "Authentication succeeded but authenticated user does not have access to the requested resource."

- **404 Not Found**: "The requested resource could not be found."

- **406 Not Acceptable**: "Requested format is not supported."

- **500 Internal Server Error**: "An error occurred on the server."


#### Performance Testing

To ensure the software meets the **1-second response time target** under both typical and high-load scenarios, it's essential to incorporate a comprehensive **Performance Testing** strategy into the **Test Plan**.

**1. Performance Testing Strategy**

Add a subsection titled **"Performance Testing"** under the **Testing Areas** section.

In this subsection, outline the approach for evaluating the system's performance, focusing on:

- **Load Testing**: Simulate typical and peak loads to assess the API's ability to handle expected traffic without performance degradation. This involves gradually increasing the number of concurrent requests to observe how the system responds under varying load conditions. 

- **Stress Testing**: Push the API beyond its normal operational capacity to determine its breaking point and observe how it behaves under extreme conditions. This helps identify the maximum load the system can handle before failing. 

- **Spike Testing**: Introduce sudden bursts of traffic to evaluate the API's ability to handle unexpected increases in load and its recovery time after the spike. 

- **Soak Testing**: Run the API under a sustained load for an extended period to detect performance degradation, memory leaks, or stability issues over time. 

**2. Performance Metrics**

Define the key performance indicators (KPIs) to be measured during testing, such as:

- **Response Time**: Time taken to receive a response for a request. The target is to maintain this under 1 second for all valid queries.

- **Throughput**: Number of requests handled per second, indicating the system's capacity to process concurrent requests.

- **Error Rate**: Percentage of failed requests, which should remain minimal even under high load.

- **Resource Utilization**: CPU and memory usage during different load conditions, ensuring efficient resource management.

**3. Testing Tools**

List the tools to be used for performance testing, such as:

- **Apache JMeter**: For simulating concurrent requests and load testing the REST API.

- **Postman**: For manual API testing to validate inputs, outputs, and error handling.

- **Google Benchmark**: For microbenchmarking performance-critical operations, such as shortest path calculations.

**4. Test Scenarios**

Develop specific test scenarios to evaluate performance, including:

- **Baseline Testing**: Measure performance under normal operating conditions to establish a reference point.

- **Scalability Testing**: Assess how performance scales with increased load, such as expanding the dataset or increasing the number of concurrent users.

- **Failure Recovery Testing**: Evaluate the system's ability to recover gracefully from failures under high load.

**5. Success Criteria**

Define clear success criteria for performance testing, such as:

- **Response Time**: Maintaining sub-1-second response times under specified load conditions.

- **Stability**: No crashes or unhandled exceptions during load tests.

- **Resource Usage**: CPU and memory usage within acceptable limits, ensuring no resource exhaustion.


#### Scalability Testing

**1. Scalability Testing Strategies**

Add a subsection titled **"Scalability Testing Strategies"** under **Performance Testing**.

In this subsection, outline the methodologies to assess the system's scalability:

- **Vertical Scaling (Scaling Up)**: Evaluate the system's performance by increasing resources on a single machine, such as adding more CPU, memory, or storage. This approach tests the application's ability to utilize enhanced resources efficiently. 

- **Horizontal Scaling (Scaling Out)**: Assess the system's capability to handle increased load by adding more machines or nodes to the network. This method examines how well the application distributes workloads across multiple servers. 

- **Elastic Scaling**: Test the system's ability to dynamically adjust resources based on real-time demand, ensuring optimal performance during varying load conditions. 

**2. Scalability Testing Best Practices**

Add a subsection titled **"Scalability Testing Best Practices"** under **Performance Testing**.

In this subsection, detail best practices to ensure comprehensive scalability testing:

- **Define Clear Objectives**: Establish specific goals for scalability testing, such as maximum user load, data volume, and acceptable response times. 

- **Incremental Load Testing**: Gradually increase the load to identify the system's breaking point and monitor performance metrics at each level. 

- **Automate Testing Processes**: Utilize tools like Apache JMeter or Gatling to automate scalability tests, ensuring consistent and repeatable results. 

- **Monitor Resource Utilization**: Track CPU, memory, disk I/O, and network usage during tests to identify potential bottlenecks. 

- **Plan for Failures**: Develop a disaster recovery plan and conduct routine checks to ensure the system can recover gracefully from failures during high-load scenarios. 

**3. Scalability Testing Tools**

Add a subsection titled **"Scalability Testing Tools"** under **Performance Testing**.

In this subsection, list and describe tools that can facilitate scalability testing:

- **Apache JMeter**: An open-source tool designed to load test functional behavior and measure performance. 

- **Gatling**: A powerful open-source load testing solution capable of simulating large numbers of users and analyzing the system's performance. 

- **Neoload**: A performance testing tool for web and mobile applications, offering a user-friendly interface and robust reporting features. 



#### Data Validation Testing

**Graph Data Validation Testing**

Ensuring the integrity of the dataset is crucial for the reliability of the pathfinding algorithm. The following validation steps are recommended:

1. **Schema Validation**: Verify that the dataset adheres to the predefined schema, ensuring all required fields are present and correctly formatted.

2. **Connectivity Check**: Confirm that the graph is fully connected, meaning there is a path between any two landmarks. This ensures the algorithm can function correctly across the entire dataset.

3. **Cycle Detection**: Identify and handle any cycles within the graph, especially if the application requires a Directed Acyclic Graph (DAG). Detecting cycles is essential to prevent infinite loops and ensure accurate pathfinding.

4. **Data Quality Assurance**: Implement checks for data consistency, such as detecting duplicate entries, missing values, and anomalies that could affect the algorithm's performance.

**Tools and Techniques**

Several tools and techniques can facilitate these validation processes:

- **SHACL (Shapes Constraint Language)**: A W3C standard for validating RDF graphs against a set of conditions. SHACL allows for the definition of constraints to ensure data integrity and can be used to validate the structure and content of graph data. 

- **Graph Validation Algorithms**: Implement algorithms to check for connectivity and detect cycles within the graph. These algorithms can be custom-built or adapted from existing libraries to suit specific dataset requirements.

- **Data Validation Frameworks**: Utilize data validation frameworks that support complex data structures. For instance, tools like Great Expectations provide a way to define and execute validation tests on datasets, ensuring they meet the required quality standards. 

**Implementation Steps**

1. **Define Validation Rules**: Clearly specify the validation rules based on the dataset's schema and the application's requirements.

2. **Automate Validation Processes**: Develop scripts or use existing tools to automate the validation checks, ensuring efficiency and repeatability.

3. **Integrate Validation into Data Pipeline**: Incorporate the validation steps into the data ingestion pipeline to catch and address issues early in the process.

4. **Continuous Monitoring**: Establish monitoring mechanisms to detect and resolve data integrity issues that may arise over time, maintaining the dataset's reliability. 


- **Documentation Quality Testing**: Evaluating the accuracy, completeness, and consistency of functional specifications, technical documents, and management artifacts to ensure clarity and alignment with the project goals.

### Detailed Categories

| **Category**            | **Description**                                                                                                      |
|-------------------------|----------------------------------------------------------------------------------------------------------------------|
| **API**                 | Testing REST API input validation, response formats (JSON/XML), and error handling.                                   |
| **Performance**         | Validating system response under varying load conditions and compliance with the 1-second target.                     |
| **Data Integrity**      | Ensuring CSV data passes connectivity, graph validation, and cyclic dependency checks.                                |
| **Algorithm**           | Testing pathfinding accuracy with a maximum deviation of 10% from the optimal path.                                  |
| **Documentation**       | Reviewing the functional, technical, and management documentation for completeness, coherence, and adherence to standards.|

---

## Success Criteria

The success of this project is determined through clearly defined goals and testing metrics. The criteria are categorized into technical, functional, performance, and documentation quality, ensuring comprehensive validation of the software and its accompanying materials.

### API Functionality

The REST API is a core component of the software. Success in this area is defined by:

- **Input Validation**: The API must reject invalid inputs gracefully, returning appropriate error messages to the user.
- **Consistent Responses**: All valid queries must produce correct and reliable outputs in both JSON and XML formats.
- **Error Handling**: Errors such as incorrect parameters or system issues should result in well-documented and predictable error codes or messages, ensuring clarity for users and developers.

### Performance

Achieving high-performance benchmarks is a fundamental requirement:

- **Response Time**: The API must handle typical queries within 1 second on standard hardware, meeting the specified performance requirements.
- **Efficient Algorithms**: The underlying pathfinding and data validation algorithms must be optimized for time and space complexity, enabling rapid processing of requests.

### Scalability

Scalability ensures the software can handle increasing demand without degrading performance:

- **Dataset Handling**: The system must efficiently process datasets containing up to 28 million nodes, ensuring compatibility with large-scale applications.
- **Concurrent Requests**: At least 100 simultaneous requests must be processed without noticeable performance degradation, validating the robustness of the software architecture.

### Data Validation

The integrity of the dataset is paramount for accurate and reliable operation:

- **Graph Structure**: The dataset must form a valid, connected, and loop-free graph. This ensures the pathfinding algorithm operates correctly.
- **Data Quality Checks**: The data validation tool must identify and resolve issues such as missing nodes, duplicate entries, or disconnected subgraphs.

### Algorithm Accuracy

The pathfinding algorithm must maintain a balance between speed and precision:

- **Approximation Threshold**: Results should be accurate within a 10% deviation from the optimal path, validating the effectiveness of the heuristic approach.
- **Edge Case Handling**: Special cases, such as disconnected nodes or ambiguous paths, must be managed appropriately to ensure robustness.

### Documentation Quality

High-quality documentation supports development, deployment, and maintenance:

- **Functional Specifications**: Clearly outline the purpose, scope, and user requirements. Ensure objectives are measurable and align with project goals&#8203;:contentReference[oaicite:0]{index=0}.
- **Technical Specifications**: Provide detailed guidance for implementation, including data structures, REST API details, and performance heuristics&#8203;:contentReference[oaicite:1]{index=1}.
- **Management Artifacts**: Include comprehensive project plans, timelines, and roles to facilitate efficient tracking and execution&#8203;:contentReference[oaicite:2]{index=2}.
- **Accessibility and Clarity**: Ensure all documents are structured logically, easily navigable, and accessible to both technical and non-technical stakeholders.



---

## Identified Risks and Mitigations

| **Risk**                | **Description**                                      | **Mitigation**                                                                                 |
|-------------------------|------------------------------------------------------|-----------------------------------------------------------------------------------------------|
| API input errors        | Invalid inputs causing failures.                     | Thorough input validation and unit tests for all API parameters.                              |
| Performance bottlenecks | Slower response times under high load.               | Algorithm profiling and optimization, with load tests to identify and address bottlenecks.    |
| Dataset inconsistencies | Errors in CSV affecting results.                     | Comprehensive data validation before API integration.                                         |
| Algorithm inaccuracies  | Pathfinding exceeds 10% error threshold.             | Regularly compare algorithm outputs with known results during development.                   |

---

## Tooling

### Unit Testing Framework

We utilize **Google Test (GTest)**, a robust and widely adopted C++ testing framework. GTest offers a comprehensive set of assertions and supports the creation of both unit and integration tests, facilitating thorough verification of code functionality. 

### Build System

Our project employs **CMake** as the build system. CMake simplifies the management of build configurations and seamlessly integrates with GTest, streamlining the compilation and execution of test suites.

### Continuous Integration

We have implemented **GitHub Actions** for continuous integration (CI). This setup automates the building and testing processes for each commit, ensuring immediate detection of issues and maintaining code quality throughout the development lifecycle.

### Code Coverage

To monitor test coverage, we use **gcov** in conjunction with **lcov**. These tools provide detailed insights into which parts of the codebase are exercised by tests, highlighting areas that may require additional testing to achieve comprehensive coverage.

### Static Code Analysis

Incorporating static code analysis enhances code quality by identifying potential issues early. We use **Clang-Tidy**, a versatile linting tool for C++, to detect common programming errors, enforce coding standards, and improve code reliability.

By integrating these tools into our development workflow, we establish a robust QA process that ensures the delivery of high-quality software while maintaining efficiency appropriate for the project's scope. 
---

## Strategy

### Testing Approaches

The testing strategy is designed to ensure reliability, performance, and functionality while maintaining simplicity suitable for the project's scale. The primary testing approaches include:

1. **Unit Testing**:
   - Focused on core components, such as the pathfinding algorithm and data validation functions.
   - Ensures each component behaves as expected in isolation.

2. **Integration Testing**:
   - Verifies seamless collaboration between the REST API, algorithms, and data validation tool.
   - Confirms that all interconnected parts function together properly.

3. **Performance Testing**:
   - Simulates high-load conditions to validate compliance with performance benchmarks.
   - Ensures responses are delivered within the targeted time under realistic use cases.

4. **Regression Testing**:
   - Confirms that previously fixed issues remain resolved as new updates are implemented.
   - Maintains software stability over the development lifecycle.

5. **Data Validation Testing**:
   - Evaluates the datasets to ensure integrity, connectedness, and the absence of loops before integration.
   - Guarantees the foundational accuracy of the system.

6. **End-to-End Testing**:
   - Tests the entire workflow, from input request through the REST API to the final output response.
   - Confirms full system functionality in production-like conditions.

### Test Environment and Continuous Integration

#### Linux-Based Test Environment

The testing process is conducted on a dedicated Linux-based server to ensure consistent, stable, and high-performance conditions that mirror a production environment. This setup provides the following advantages:

- Controlled and repeatable conditions for benchmarking.
- Validation of critical metrics, such as API response times and concurrent request handling.
- Scalability testing with real-world datasets, including graphs with up to 24 million nodes.

This configuration optimally supports C++ development, offering resource efficiency and compatibility for testing.

#### Continuous Integration with GitHub Actions

A continuous integration (CI) pipeline is implemented using **GitHub Actions**, ensuring automated, efficient testing at every stage of development. Key aspects include:

1. **Automated Testing on Push**:
   - All commits to the `dev` branch trigger a full suite of automated tests, providing rapid feedback on code quality.
   - Pull requests to the `main` branch are only merged after successful execution of tests.

2. **Performance Benchmarks**:
   - Performance metrics, such as response time and algorithm accuracy, are benchmarked during the CI process.
   - Results are logged for historical comparison and improvement tracking.

3. **Test Artifacts**:
   - All test outputs and benchmark data are archived as CI artifacts, ensuring transparency and traceability of testing efforts.

4. **Comprehensive Reporting**:
   - Detailed reports from test executions provide insights into failures, enabling timely resolution of issues.

#### Test-Driven Development (TDD) Workflow

The project follows a **Test-Driven Development (TDD)** approach, emphasizing the creation of tests before implementing new features. This ensures that:

- Every feature meets predefined acceptance criteria.
- Code changes are rigorously verified for correctness and reliability.
- The software adheres to functional requirements and handles edge cases effectively.


---

## Testing Schedule

| **Week** | **Activity**                                                                                                  |
|----------|--------------------------------------------------------------------------------------------------------------|
| Week 1   | Develop test cases for API functionality, data validation, and core algorithms.                              |
| Week 2   | Perform unit and integration testing of the REST API and data validation tool.                               |
| Week 3   | Conduct performance and scalability tests with datasets up to 24M nodes and 100 concurrent requests.         |
| Week 4   | Conduct end-to-end testing and validate all success criteria.                                                |

---

## Deliverables

| **Deliverable**       | **Description**                                                                                       |
|-----------------------|-------------------------------------------------------------------------------------------------------|
| Test Cases            | Detailed test cases covering all functional and performance requirements.                             |
| Test Reports          | Summaries of testing outcomes, highlighting pass/fail results and recommendations.                   |
| QA Checklist          | A comprehensive checklist of testing activities completed.                                           |
| Final QA Summary      | A report summarizing the software's quality, with risk assessments and recommendations.              |
