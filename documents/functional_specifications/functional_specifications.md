# Functional Specifications

<details>
<summary>Table of Contents</summary>

- [Functional Specifications](#functional-specifications)
  - [1. Introduction](#1-introduction)
    - [1.1. Glossary](#11-glossary)
    - [1.2. Project Overview](#12-project-overview)
    - [1.3. Project Definition](#13-project-definition)
      - [1.3.1. Vision](#131-vision)
      - [1.3.2. Objectives](#132-objectives)
      - [1.3.3. Scope](#133-scope)
      - [1.3.4. Target Audience](#134-target-audience)
      - [1.3.5. Deliverables](#135-deliverables)
    - [1.4. Project Organization](#14-project-organization)
      - [1.4.1. Project Representatives](#141-project-representatives)
      - [1.4.2. Stakeholders](#142-stakeholders)
      - [1.4.3. Project Roles](#143-project-roles)
      - [1.4.4. Project Reviewers](#144-project-reviewers)
    - [1.4. Project Plan](#14-project-plan)
      - [1.4.1. Planning](#141-planning)
      - [1.4.2. Milestones](#142-milestones)
      - [1.4.3. Dependencies](#143-dependencies)
      - [1.4.4. Assumptions/Constraints](#144-assumptionsconstraints)
      - [1.4.5. Risks/Mitigation](#145-risksmitigation)
  - [2. Personas and Use Cases](#2-personas-and-use-cases)
    - [2.1. Personas](#21-personas)
      - [2.1.1. Alex](#211-alex)
      - [2.1.2. Emily](#212-emily)
      - [2.1.3. Dr. Nair](#213-dr-nair)
    - [2.2. Use Cases](#22-use-cases)
  - [3. Functional Requirements](#3-functional-requirements)
    - [3.1. REST API Implementation](#31-rest-api-implementation)
      - [3.1.1. Route Description](#311-route-description)
      - [3.1.2. Reponse codes](#312-reponse-codes)
      - [3.1.3. Request Examples](#313-request-examples)
      - [3.1.4. Response examples](#314-response-examples)
    - [3.2. Data Verification Tool](#32-data-verification-tool)
      - [3.2.1. Features](#321-features)
      - [3.2.3. Error Reporting](#323-error-reporting)
      - [3.2.4. Output](#324-output)
    - [3.3. User Workflow](#33-user-workflow)
  - [4. Non-functional Requirements](#4-non-functional-requirements)
    - [4.1. Performance](#41-performance)
    - [4.2. Scalability](#42-scalability)
    - [4.3. Usability](#43-usability)
    - [4.4. Data Integrity](#44-data-integrity)
    - [4.5. Reliability](#45-reliability)
    - [4.6. Security](#46-security)
    - [4.7. Maintainability](#47-maintainability)
    - [4.8. Compliance](#48-compliance)
    - [4.9. Energy Efficiency](#49-energy-efficiency)

</details>

## 1. Introduction

### 1.1. Glossary

| Term       | Definition                                                                                              |
| ---------- | ------------------------------------------------------------------------------------------------------- |
| REST API   | A web service architecture that uses HTTP requests to provide access to resources or perform actions.   |
| Heuristics | Techniques that find approximate solutions to complex problems more quickly than traditional methods.   |
| MVP        | Minimum Viable Product, the simplest version of a product that can be released to gather user feedback. |

### 1.2. Project Overview

This project aims to create a software solution that calculates the quickest path between two landmarks in the United States.

### 1.3. Project Definition

#### 1.3.1. Vision

The vision of our algorithm is to provide a fast, reliable approximation of the shortest path duration between two points in the United States, with the potential to expand globally and integrate with mapping services.

#### 1.3.2. Objectives

- **REST API with single endpoint:** The software exposes its functionality through a XML and JSON REST API running on an HTTP server with a unique GET endpoint for requests.
- **Response Time:** All queries to the API should be handled in less than 1 second on a typical laptop.
- **Approximation Heuristics:** The returned path should not exceed the shortest path duration by more than 10% when prioritizing speed over precision.

#### 1.3.3. Scope

This software will be developed using C++, a high-performance language that allows fast processing of data. The program will also include an HTTP server running a REST API in XML and JSON format with a single GET endpoint.

#### 1.3.4. Target Audience

The target audience includes:
- Logistics companies seeking efficient routing solutions.
- Developers of navigation applications.
- Researchers in transportation optimization looking for new algorithms.

#### 1.3.5. Deliverables

| Deliverable               | Purpose                                                                                                                                                |
| ------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------ |
| Functional Specifications | Detailled documentation of the features used and their non-technical aspects.                                                                          |
| Technical Specifications  | Detailled  documentation about the technical implementation of software                                                                                |
| Data Validation Tool      | A utility to verify the integrity of the provided CSV file.                                                                                            |
| C++ Source Code           | The source code of the software program, including the shortest path algorithm and the HTTP server.                                                    |
| Test Suite                | Tests to validate correctness, performance, and compliance with the 10% approximation rule.                                                            |
| Test Plan & Test Cases    | A set of scenarios validating the algorithm's performance and accuracy with a strategy to run test suite tests in the most accurate and efficient way. |
| User Manual               | The end-user documentation for the software.                                                                                                           |

### 1.4. Project Organization

#### 1.4.1. Project Representatives

| Full Name             | Occupation        | Links                                                                   |
| --------------------- | ----------------- | ----------------------------------------------------------------------- |
| Victor LEROY          | Project manager   | [LinkedIn](https://www.linkedin.com/in/victor-leroy-64baa3229/)         |
| Antoine PREVOST       | Program manager   | [LinkedIn](https://www.linkedin.com/in/antoine-prevost-dev/)            |
| David CUAHONTE CUEVAS | Tech lead         | [LinkedIn](https://www.linkedin.com/in/david-cuahonte-527781221/)       |
| Thomas PLANCHARD      | Software engineer | [LinkedIn](https://www.linkedin.com/in/thomas-planchard-461782221/)     |
| Mathis KAKAL          | Software engineer | [LinkedIn](https://www.linkedin.com/in/mathis-k-a239ba10a/)             |
| Max BERNARD           | Quality assurance | [LinkedIn](https://www.linkedin.com/in/max-bernard-b77680210/)          |
| Quentin CLEMENT       | Technical writer  | [LinkedIn](https://www.linkedin.com/in/quentin-cl%C3%A9ment-939110221/) |

#### 1.4.2. Stakeholders

| Role            | Representative | Expectations                                                           |
| --------------- | -------------- | ---------------------------------------------------------------------- |
| Client          | Franck JEANNIN | Finished project meeting requirements                                  |
| School director | Franck JEANNIN | Clear documentation and management based on the skills learnt in class |

#### 1.4.3. Project Roles

| Role              | Description                                                                                                                                                          | Name                             |
| ----------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------- | -------------------------------- |
| Project Manager   | Responsible for the overall planning, execution, and success of the project.                                                                                         | Victor LEROY                     |
| Program Manager   | Makes sure the project meets expectation. <br> Is in charge of design. Is responsible for writing the Functional Specifications                                      | Antoine PREVOST                  |
| Tech Lead         | Makes the technical decision in the project. <br> Translates the Functional Specification into Technical Specifications. <br> Does code review.                      | David CUAHONTE CUEVAS            |
| Software Engineer | Writes the code. <br> Writes documentation. <br> Participate in the technical design.                                                                                | Thomas PLANCHARD<br>Mathis KAKAL |
| Quality Assurance | Tests all the functionalities of a product to find bugs and issues. <br> Document bugs and issues. <br> Write the test plan. <br> Check that issues have been fixed. | Max BERNARD                      |
| Technical Writer  | Responsible for creating and maintaining the project's documentation.                                                                                                | Quentin CLEMENT                  |

#### 1.4.4. Project Reviewers

External project reviewers have been appointed by the project owner to review our specifications and provide us with feedback.

### 1.4. Project Plan

#### 1.4.1. Planning

Planning will follow an iterative approach, with each iteration focused on specific functionality, testing, and validation to ensure quality and performance.

#### 1.4.2. Milestones

| Date | Milestone |
| ---- | --------- |
|      |           |

#### 1.4.3. Dependencies

- MVP development cannot start before the data integrity of the provided dataset is verified.
- An iteration on the project cannot start before tests are run on the current version.
- A release of the project cannot occur before all tests of the current version are successful.

#### 1.4.4. Assumptions/Constraints

**Assumptions:**

| Assumption           | Description                                        |
| -------------------- | -------------------------------------------------- |
| Dataset availability | The required datasets are accessible and accurate. |

**Constraints:**

| Constraint           | Description                                               |
| -------------------- | --------------------------------------------------------- |
| Performance          | Response time must be under 1 second.                     |
| Resource Utilization | The program must operate efficiently on a typical laptop. |

#### 1.4.5. Risks/Mitigation

| ID  | Description            | Consequence                 | Impact | Likelihood | Mitigation          |
| --- | ---------------------- | --------------------------- | ------ | ---------- | ------------------- |
| R01 | Dataset errors or gaps | Incorrect route calculation | High   | Medium     | Validate datasets.  |
| R02 | API performance issues | Delayed response times      | High   | High       | Optimize algorithm. |

## 2. Personas and Use Cases

### 2.1. Personas

#### 2.1.1. Alex

![Alex](./images/alex.png)

#### 2.1.2. Emily

![Emily](./images/emily.png)

#### 2.1.3. Dr. Nair

![Dr. Nair](./images/doctor_nair.png)

### 2.2. Use Cases

| Use Case            | Description                                                                                                      |
| ------------------- | ---------------------------------------------------------------------------------------------------------------- |
| Route Calculation   | User submits two landmarks, and the API returns the quickest path between them in order to transport themselves. |
| API Integration     | Developer integrates the API into an application for real-time routing between two landmarks via their ID.       |
| Performance Testing | System validates response times under heavy load conditions.                                                     |

## 3. Functional Requirements

### 3.1. REST API Implementation

#### 3.1.1. Route Description

- **URL:** `http://127.0.0.1:8080/quickest_path`
- **Method:** `GET`
- **Headers:**
  - `Content-Type`: `application/json`
  - `Accept`: `application/json` or `application/xml`

- **Query Parameters:**

| Parameter Name | Type    | Expected value               |
| -------------- | ------- | ---------------------------- |
| landmark_1     | integer | Value between 1 and 23947347 |
| landmark_2     | integer | Value between 1 and 23947347 |

#### 3.1.2. Reponse codes

| Case                      | HTTP Code | Description                                                                        | Example Response                                                                                                                  |
| ------------------------- | --------- | ---------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------- |
| Valid request             | 200       | Successfully returns the quickest path.                                            | `{ "time": 66, "steps": [ { "landmark": 322, "distance": 33 }, { "landmark": 323, "distance": 33 } ] }`                           |
| Identical landmarks       | 200       | Returns response with `time` as `0` and empty steps.                               | `{ "time": 0, "steps": [] }`                                                                                                      |
| Non-existent landmarks    | 404       | One or both landmarks are not found in the dataset.                                | `{ "error": { "code": 404, "message": "No path found between the specified landmarks." } }`                                       |
| Disconnected graph        | 404       | No path exists between the specified landmarks.                                    | `{ "error": { "code": 404, "message": "No path found between the specified landmarks." } }`                                       |
| Missing or invalid inputs | 400       | Request does not include valid `format`, `landmark_1` and `landmark_2` parameters. | `{ "error": { "code": 400, "message": "Missing or invalid parameters: 'format', 'landmark_1' and 'landmark_2' are required." } }` |

#### 3.1.3. Request Examples

```http
GET /quickest_path?landmark_1=322&landmark_2=333 HTTP/1.1
Host: 127.0.0.1:8080
Accept: application/json
```

```http
GET /quickest_path?landmark_1=3455&landmark_2=745647 HTTP/1.1
Host: 127.0.0.1:8080
Accept: application/xml
```

#### 3.1.4. Response examples

**JSON Example Response:**

```json
{
  "time": 66,
  "steps": [
    { "landmark": 322, "distance": 33 },
    { "landmark": 323, "distance": 33 }
  ]
}
```

**XML Example Response:**

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

### 3.2. Data Verification Tool

The data verification tool ensures the integrity and usability of the `USA-roads.csv` dataset. It performs the following checks and validations:

#### 3.2.1. Features

| Feature                    | Description                                                                                               | Example error                                                                                    |
| -------------------------- | --------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------ |
| Duplicate Connection Check | Identifies and flags any duplicate entries in the dataset to ensure unique connections between landmarks. | `Duplicate connection found: Landmark_A_ID=322, Landmark_B_ID=333.`                              |
| Graph Validation           | Ensures the dataset forms a valid graph structure without any cycles (Directed Acyclic Graph - DAG).      | `Cycle detected: Landmark_A_ID=100 -> Landmark_B_ID=200 -> Landmark_A_ID=100.`                   |
| Connectivity Check         | Verifies that the graph is fully connected, ensuring there are paths between all pairs of landmarks.      | `Disconnected subgraph found: Node group starting from Landmark_A_ID=500.`                       |
| Data format Validation     | Checks for malformed or invalid rows in the dataset.                                                      | `Invalid row format: Expected format 'Landmark_A_ID,Landmark_B_ID,Time'. Row: '322,invalid,33'.` |

#### 3.2.3. Error Reporting

- Generates a detailed log file summarizing all detected issues for developer review.
- Categorizes errors by type (e.g., duplicate connections, graph validation errors) for quick identification.

#### 3.2.4. Output

- A summary report indicating whether the dataset passed or failed validation.
- Suggestions for corrective actions, such as removing duplicates or fixing disconnected subgraphs.

### 3.3. User Workflow

```mermaid
graph TD
A[User submits GET request] --> B[API validates parameters]
B --> C[System calculates quickest path]
C --> D[Returns result in JSON/XML]
```

## 4. Non-functional Requirements

### 4.1. Performance

   - The API must handle all queries within **1 second** on a typical laptop.

### 4.2. Scalability

   - The system must be designed to accommodate future expansion to larger datasets or additional geographic regions.
   - Modular architecture to allow integration with third-party systems or additional functionality (e.g., live traffic data).

### 4.3. Usability

   - API responses must support both **JSON** and **XML** formats to meet diverse client requirements.
   - Clear API documentation to facilitate easy integration by developers.

### 4.4. Data Integrity

   - Include utilities for **graph validation** and **connectivity checks** to ensure dataset consistency before use.

### 4.5. Reliability

   - High availability of the service with proper error handling for invalid input or unexpected conditions.
   - Ensure fault tolerance in the presence of incomplete or incorrect dataset entries.

### 4.6. Security

   - Implement basic security measures like **rate limiting**, **input validation**, and **HTTPS support** to prevent misuse and ensure data safety.
   - Avoid exposing sensitive internal errors in the API response.

### 4.7. Maintainability

   - The codebase must follow best practices for readability and maintainability, with sufficient inline comments and comprehensive documentation.
   - Support for future updates to algorithms or dataset formats.

### 4.8. Compliance

   - Adherence to RESTful API standards for consistency in design and implementation.

### 4.9. Energy Efficiency

   - Optimized computational resources to reduce power consumption during large-scale calculations, especially on personal devices like laptops.
