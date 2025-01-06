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
    - [1.4. Project Plan](#14-project-plan)
      - [1.4.1. Planning](#141-planning)
      - [1.4.2. Milestones](#142-milestones)
      - [1.4.3. Dependencies](#143-dependencies)
      - [1.4.4. Assumptions/Constraints](#144-assumptionsconstraints)
      - [1.4.5. Risks/Mitigation](#145-risksmitigation)
  - [2. Personas and Use Cases](#2-personas-and-use-cases)
    - [2.1. Personas](#21-personas)
    - [2.2. Use Cases](#22-use-cases)
  - [3. Functional Requirements](#3-functional-requirements)
    - [3.X. User Workflow](#3x-user-workflow)
  - [4. Non-functional Requirements](#4-non-functional-requirements)

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

#### 1.3.5. Deliverables

| Deliverable               | Purpose                                                                                                                                                                     |
| ------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Functional Specifications | Detailed documentation of the features used and their non-technical aspects.                                                                                                |
| Technical Specifications  | Detailed documentation of the features used and their non-technical aspects.                                                                                                |
| Data Validation Tool      | A utility to verify the integrity of the provided CSV file                                                                                                                  |
| C++ Source Code           | The source code of the software program, including the shortest path algorithm and the HTTP server.                                                                         |
| Test Suite                | Tests to validate correctness, performance, and compliance with the 10%                                                                                 approximation rule. |
| Test Plan & Test Cases    | A set of scenarios validating the algorithm's performance and accuracy with a strategy to run test suite tests in the most accurate and efficient way.                      |

### 1.4. Project Plan

#### 1.4.1. Planning

Planning will follow an iterative approach, with each iteration focused on specific functionality, testing, and validation to ensure quality and performance.

#### 1.4.2. Milestones

<!-- | Date       | Milestone                                        |
| ---------- | ------------------------------------------------ |
| YYYY-MM-DD | Complete data validation.                        |
| YYYY-MM-DD | Develop REST API and connect with the algorithm. |
| YYYY-MM-DD | Conduct performance testing.                     |
| YYYY-MM-DD | Launch MVP.                                      | -->

#### 1.4.3. Dependencies

- MVP development cannot start before the data integrity of the provided dataset is verified.
- An iteration on the project cannot start before tests are run on the current version.
- A release of the project cannot occur before all tests of the current version are successful.

#### 1.4.4. Assumptions/Constraints

**Assumptions:**

<!-- | Assumption           | Description                                        |
| -------------------- | -------------------------------------------------- |
| Dataset availability | The required datasets are accessible and accurate. | -->

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

- **Logistics Manager:** Needs to find efficient routes to reduce delivery times and costs.
- **Navigation App Developer:** Requires reliable algorithms to integrate into an existing app.
- **Researcher:** Analyzes transportation networks for academic or policy-making purposes.

### 2.2. Use Cases

<!-- | Use Case                  | Description                                                             |
| ------------------------- | ----------------------------------------------------------------------- |
| UC01: Route Calculation   | User submits two landmarks, and the API returns the quickest path.      |
| UC02: API Integration     | Developer integrates the API into an application for real-time routing. |
| UC03: Performance Testing | System validates response times under heavy load conditions.            | -->

## 3. Functional Requirements

### 3.X. User Workflow

<!-- 1. User submits a GET request to the API with two landmarks as parameters.
2. The system calculates the quickest path based on the provided dataset.
3. The API returns the result within 1 second, including the path duration and waypoints. -->

## 4. Non-functional Requirements

<!-- ### 4.X. Performance

- The API must handle up to 100 concurrent requests while maintaining response times under 1 second.

### 4.X. Scalability

- The system should support future integration with additional datasets and geographic regions.

### 4.X. Security

- The API must implement rate limiting and authentication to prevent misuse.

### 4.X. Usability

- API documentation must be clear and easy to follow for developers. -->

