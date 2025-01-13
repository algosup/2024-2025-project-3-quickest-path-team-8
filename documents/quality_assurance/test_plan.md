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

- **Functional Testing**: Verifying that the REST API, pathfinding algorithm, and data validation tool meet the specified requirements.
- **Performance Testing**: Ensuring the software achieves the 1-second response time target under both typical and high-load scenarios.
- **Scalability Testing**: Assessing the system's capability to handle a large dataset (28M nodes) and concurrent requests effectively.
- **Data Validation Testing**: Ensuring the dataset forms a valid, connected, and loop-free graph.
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

### Alignment with Overall Objectives

Each component of the project must support the overarching goal of delivering a high-performance, reliable, and user-friendly software solution. These criteria ensure that the software not only meets its functional and technical requirements but also provides a foundation for future scalability and usability.


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
