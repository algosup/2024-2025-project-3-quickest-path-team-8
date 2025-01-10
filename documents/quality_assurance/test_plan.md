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

Testing will cover functional, performance, scalability, and data integrity aspects of the software. Key focus areas include:

- **Functional Testing**: Ensuring REST API, pathfinding algorithm, and data validation tool comply with requirements.
- **Performance Testing**: Validating the 1-second response time target under typical and high-load scenarios.
- **Scalability Testing**: Assessing the system's capacity to handle the large dataset (28M nodes) and concurrent requests.
- **Data Validation Testing**: Ensuring the dataset forms a valid, connected, and loop-free graph.

### Detailed Categories

| **Category**      | **Description**                                                                                      |
|-------------------|----------------------------------------------------------------------------------------------------|
| **API**           | Testing REST API input validation, response formats (JSON/XML), and error handling.                 |
| **Performance**   | Validating system response under varying load conditions and compliance with 1-second target.       |
| **Data Integrity**| Ensuring CSV data passes connectivity, graph validation, and cyclic dependency checks.              |
| **Algorithm**     | Testing pathfinding accuracy with a maximum deviation of 10% from the optimal path.                |

---

## Success Criteria

| **Category**          | **Success Criteria**                                                                                                                                         |
|------------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **API Functionality**  | Correct and consistent responses for valid inputs and proper error handling for invalid inputs.                                                              |
| **Performance**        | All queries return results within 1 second on a typical laptop.                                                                                            |
| **Scalability**        | System can handle the full dataset (28M nodes) and at least 100 concurrent requests without significant performance degradation.                              |
| **Data Validation**    | The dataset passes all integrity checks, ensuring a fully connected and loop-free graph.                                                                    |
| **Algorithm Accuracy** | Results are within 10% of the optimal path duration.                                                                                                       |

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

### Methodology

- **Proactive Testing**: Automated and manual test cases for regression and performance monitoring.
- **Corrective QA**: Efficient tracking and resolution of bugs.

### Tools

- **Unit Testing Framework**: Google Test (GTest) for C++.
- **Load Testing**: Apache JMeter or similar.
- **Issue Tracking**: Jira for logging and managing testing issues.

---

## Strategy

### Testing Approaches

1. **Unit Testing**:
   - Validate core components such as the pathfinding algorithm and data validation functions.
2. **Integration Testing**:
   - Ensure seamless operation between REST API, algorithms, and data validation tool.
3. **Performance Testing**:
   - Simulate high-load scenarios to validate system performance.
4. **Regression Testing**:
   - Verify previous fixes are not reintroduced with new updates.
5. **Data Validation Testing**:
   - Ensure datasets pass all checks before integration.
6. **End-to-End Testing**:
   - Validate the entire workflow from input request to API response.

### Test Environment and Continuous Integration

#### Linux-Based Test Server
The testing environment will leverage a dedicated server running Linux to ensure a stable and high-performance setup that mirrors production-like conditions. This environment is critical for:

- Running and benchmarking the software in a controlled and consistent setting.
- Validating performance metrics such as API response time (within 1 second) and concurrent request handling.
- Conducting extensive load and scalability tests using real-world datasets (e.g., 24 million nodes).

By using a Linux server, we can take advantage of its stability, resource efficiency, and compatibility with the C++ environment, ensuring optimal conditions for software validation.

#### Continuous Integration with GitHub Actions
To streamline testing and benchmarking, we have integrated **GitHub Actions** as a Continuous Integration (CI) tool. Key features of this CI pipeline include:

1. **Triggering Tests on Push**:
   - Every push to the `dev` branch triggers automated test suites, ensuring immediate feedback on code quality and functionality.
   - Pull requests to the `main` branch are gated by successful test execution and benchmarking results.

2. **Benchmark Execution**:
   - The CI pipeline runs performance benchmarks to validate compliance with the <1-second response time and the 10% approximation accuracy requirement.
   - Benchmarking results are logged for historical analysis and trend tracking.

3. **Automated Testing**:
   - Unit tests and integration tests are executed to verify the correctness and reliability of all code changes.

4. **Artifact Storage**:
   - Test and benchmark results are stored as artifacts in the CI system, ensuring transparency and traceability.

#### Test-Driven Development (TDD) Approach
The development process adheres to a **Test-Driven Development (TDD)** methodology using the **Google Test Framework**. This ensures robust and reliable software through rigorous testing practices:

1. **Unit Testing**:
   - Individual components, such as the pathfinding algorithm, REST API endpoints, and data validation functions, are tested in isolation.
   - Focuses on correctness, edge cases, and compliance with functional requirements.

2. **Integration Testing**:
   - Validates the interaction between the REST API, pathfinding algorithm, and data validation tool.
   - Ensures that integrated components function together as expected.

3. **TDD Workflow**:
   - Tests are written before the implementation of any feature, ensuring that all code changes meet the predefined acceptance criteria.
   - Any new functionality must pass the relevant test cases before merging into the main codebase.

This approach, combined with automated testing and benchmarking in the CI pipeline, fosters high code quality, performance optimization, and rapid feedback for developers. The synergy between a Linux-based test environment and GitHub Actions ensures consistent and thorough validation of the software at every stage of development.

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
