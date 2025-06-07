# Tiny Project Report: Linear System Solver and Evaluator

## Introduction

The objective of this project is to design and implement an object-oriented C++ system that can solve linear systems using techniques from linear algebra. This includes handling regular square systems, symmetric positive definite systems, and non-square systems such as those encountered in data modeling.

The project is divided into two parts:

- **Part A:** Reusable C++ classes to represent vectors, matrices, and various types of linear systems.
- **Part B:** Application of these classes to solve a real-world linear regression problem using the UCI CPU Performance dataset.

This project demonstrates how object-oriented programming (OOP) principles and numerical linear algebra can be combined to build modular, testable, and extensible computational tools.

---

## Project Structure
tinyProjectFinal/
│
├── partA/
│ ├── LinearSystem.cpp/h
│ ├── Matrix.cpp/h
│ ├── Vector.cpp/h
│ ├── NonSquareSystem.cpp/h
│
├── partB/
│ ├── DataLoader.cpp/h
│ ├── Evaluator.cpp/h
│ ├── machine.data <-- UCI CPU Performance dataset
│
└── README.md

---

## Setup Instructions

To run and test this project, follow these steps:

### 1. Create a New C++ Project

You can use any IDE (such as Visual Studio, CLion, or Code::Blocks), or simply compile via terminal.

### 2. Clone or Download the Project

Download all the contents of the repository and place them in a **single project folder**. Ensure the folder structure is preserved as shown above.

### 3. Add Files to the Project

- Add all `.cpp` and `.h` files from both `partA/` and `partB/` into your project.
- Make sure to **include the necessary header files** in your main test file.

### 4. Compile and Run

- Build the project using your IDE or with a compiler like g++:
  ```bash
  g++ partA/*.cpp partB/*.cpp -o LinearSystemSolver
  ./LinearSystemSolver

Note: You may need to create a main.cpp file to test the functionality using the classes from both parts.
