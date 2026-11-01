# KMap Simplifier

A console-based C++ application that simplifies Boolean expressions using Karnaugh Maps (K-Maps) for 1, 2, 3, and 4 variables.

The program allows users to enter minterms and don't-care conditions, generates the corresponding Karnaugh Map, and finds a simplified Boolean expression using logical grouping.

---

## Features

- Supports 1-variable Karnaugh Maps.
- Supports 2-variable Karnaugh Maps.
- Supports 3-variable Karnaugh Maps.
- Supports 4-variable Karnaugh Maps.
- Accepts minterms as user input.
- Supports don't-care conditions.
- Displays the Karnaugh Map in the correct Gray Code order.
- Groups adjacent 1s to simplify Boolean expressions.
- Identifies essential prime implicants.
- Displays the final minimized Boolean expression.
- Provides a menu-driven console interface.

## Concepts Used

This project focuses on implementing fundamental programming and digital logic concepts using C++.

- **C++ Fundamentals:** Variables, data types, conditional statements, loops and functions.
- **Arrays and Vectors:** Storing and managing minterms and K-Map values.
- **Boolean Algebra:** Understanding Boolean expressions and simplification.
- **Karnaugh Maps:** Gray Code ordering and adjacent cell grouping.
- **Bitwise Operations:** Working with binary representations of minterms.
- **Algorithms:** Finding valid groups and generating simplified expressions.
- **Modular Programming:** Dividing the program into smaller reusable functions.

## Supported Variables

| Variables | K-Map Size | Number of Cells |
|---|---|---:|
| 1 Variable (A) | 1 × 2 | 2 |
| 2 Variables (A, B) | 2 × 2 | 4 |
| 3 Variables (A, B, C) | 2 × 4 | 8 |
| 4 Variables (A, B, C, D) | 4 × 4 | 16 |

## How It Works

1. The user selects the number of variables.
2. The program accepts the minterms where the Boolean function evaluates to 1.
3. The user can optionally enter don't-care conditions.
4. The program generates the corresponding Karnaugh Map.
5. Adjacent cells are grouped according to K-Map simplification rules.
6. The program identifies the simplified Boolean expression.
7. The result is displayed in the terminal.

## Example

**Input:**

```text
Enter number of variables: 3

Enter number of minterms: 4
Enter minterms:
1 3 5 7

Enter number of don't-care conditions: 0
```

**Expected Output:**

```text
Karnaugh Map:

       BC
       00  01  11  10
A = 0   0   1   1   0
A = 1   0   1   1   0

Simplified Boolean Expression:

F = C
```

## Requirements

- C++ compiler supporting C++11 or later.
- Terminal or command-line interface.
- macOS, Linux, or Windows.

## Compilation and Execution

Clone the repository:

```bash
git clone https://github.com/sarveshdevx/CPP-Projects.git
```

Navigate to the project directory:

```bash
cd CPP-Projects/03-kmap-simplifier
```

Compile:

```bash
g++ -std=c++11 kmap.cpp -o kmap
```

Run:

```bash
./kmap
```

## Project Structure

```text
03-kmap-simplifier/
│
├── kmap.cpp
└── README.md
```

## Learning Objectives

- Understand how Karnaugh Maps simplify Boolean expressions.
- Learn to represent binary combinations programmatically.
- Implement grouping logic using C++.
- Develop problem-solving and algorithmic thinking.
- Apply digital logic concepts through programming.

## Future Improvements

- Add a graphical representation of Karnaugh Maps.
- Support Product of Sums (POS) simplification.
- Display intermediate grouping steps.
- Improve input validation and error handling.
- Add automated test cases for different Boolean functions.

---

**Status:** In Development 🚧

**Language:** C++

**Project Category:** Digital Logic Design / Algorithmic Problem Solving
