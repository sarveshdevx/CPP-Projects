# KMap Simplifier

A console-based C++ application that simplifies Boolean expressions using Karnaugh Maps (K-Maps).

The project currently supports **2-variable K-Map simplification**. Support for 3-variable and 4-variable K-Maps will be developed in future stages.

---

## Features

### Completed
- Supports 2-variable Karnaugh Maps.
- Accepts K-Map values (0 and 1) as user input.
- Generates binary representations of minterms.
- Identifies pairs of adjacent 1s.
- Generates simplified Boolean expressions.
- Removes duplicate combinations.
- Displays the minimized Boolean expression in the terminal.

### Planned
- Support for 3-variable Karnaugh Maps.
- Support for 4-variable Karnaugh Maps.
- Improved grouping and simplification.
- Identification of essential prime implicants.

## Supported Variables

| Variables | K-Map Size | Number of Cells | Status |
|---|---|---:|---|
| 2 Variables (A, B) | 2 × 2 | 4 | Completed |
| 3 Variables (A, B, C) | 2 × 4 | 8 | Planned |
| 4 Variables (A, B, C, D) | 4 × 4 | 16 | Planned |

## How It Works

1. The user selects the number of variables.
2. The program accepts the K-Map values (0 and 1).
3. The program generates binary representations of the minterms.
4. Adjacent combinations are compared.
5. Matching pairs are grouped using `X` as a placeholder.
6. Duplicate combinations are filtered.
7. The simplified Boolean expression is displayed in the terminal.

## Example

**Input:**

```text
Enter The Number Of Variable:
2

Please Enter K map values(0 & 1):
1 1 0 0
```

**Expected Output:**

```text
Kmap Evaluation : Ā
```

## Concepts Used

This project focuses on implementing fundamental programming and digital logic concepts using C++.

- **C++ Fundamentals:** Variables, data types, conditional statements and loops.
- **Arrays and Vectors:** Storing and managing K-Map values.
- **Strings:** Representing binary combinations and manipulating Boolean terms.
- **Boolean Algebra:** Understanding Boolean expressions and simplification.
- **Karnaugh Maps:** Understanding adjacent cell grouping.
- **Modular Programming:** Dividing the program into smaller reusable functions.

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
- Practise string manipulation in C++.
- Implement grouping logic using functions and loops.
- Develop problem-solving and algorithmic thinking.
- Apply digital logic concepts through programming.

## Future Improvements

- Implement 3-variable K-Map simplification.
- Implement 4-variable K-Map simplification.
- Add support for don't-care conditions.
- Identify essential prime implicants.
- Support Product of Sums (POS) simplification.
- Display intermediate grouping steps.
- Add a graphical representation of Karnaugh Maps.
- Improve input validation and error handling.
- Add automated test cases for different Boolean functions.

---

**Status:** 2-Variable K-Map Completed | 3-Variable and 4-Variable Development Pending

**Language:** C++

**Project Category:** Digital Logic Design / Algorithmic Problem Solving
