# Technical Specifications: 2024-2025 Project 3: Call for Tender

- [Technical Specifications: 2024-2025 Project 3: Call for Tender](#technical-specifications-2024-2025-project-3-call-for-tender)
  - [1. Audience](#1-audience)
  - [2. Project Overview](#2-project-overview)
  - [3. Glossary](#3-glossary)
  - [4. Requirements](#4-requirements)
    - [4.1 Core Requirements](#41-core-requirements)
    - [4.2 Performance Goals](#42-performance-goals)
    - [4.3 Data Integrity Verification](#43-data-integrity-verification)
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

## 1. Audience

This document is primarily intended for:

- Software developer - to understand the user and technical requirements, and to guide decision-making and planning. Help them understand risks and challenges, customer requirements, and additional technical requirements and choices made

Secondary audiences

- Program manager - to validate against the functional specification, and the client expectations
- QA - to aid in preparing the test plan and to use it for validating issues.
- Project manager - to help identify risks and dependencies

## 2. Project Overview

This project involves developing a high-performance C++ software solution to calculate the quickest path between two landmarks in the United States. The solution will be accessible via a REST API, supporting both XML and JSON responses. It will use a dataset with 24 million connections between landmarks, with travel times. The software must handle large-scale data efficiently, return results within 1 second, and ensure the path is within 10% of the shortest possible duration. Data integrity checks are also required for the dataset to ensure correctness and connectivity. 

## 3. Glossary

| Term | Definition |
| ---- | ---------- |
| Landmark | A point in the graph representing a location in the U.S. |
| Graph | A network of nodes (landmarks) connected by edges (paths) with associated travel times. |
| DAG (Directed Acyclic Graph) | A graph that doesn’t contain cycles, used to model the landmark connections. |
| REST API | A web service that exposes functionality via HTTP endpoints, in this case, to query the shortest path. |

## 4. Requirements

### 4.1 Core Requirements

### 4.2 Performance Goals

### 4.3 Data Integrity Verification

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
