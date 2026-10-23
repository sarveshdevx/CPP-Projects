# DOB & Weekday Calculator

A console-based C++ program that determines the day of the week on which a person was born and calculates the total number of days elapsed between their birth date and the current date.

The project demonstrates fundamental algorithmic thinking, arithmetic-based date parsing, and Gregorian calendar math without relying on external third-party date libraries.

---

## Overview

The program takes a birth date input in integer format (`ddmmyyyy`), queries the system clock for the current date, validates basic chronological bounds, and performs calendar arithmetic to calculate:
1. The total days elapsed from birth to today.
2. The specific weekday (Sunday through Saturday) of the birth date using a baseline anchor date (Dec 31, 1899).

---

## Features

- **Weekday Calculation:** Calculates the birth weekday by determining total accumulated days since an anchor date and applying modulo-7 arithmetic.
- **Elapsed Days Calculation:** Calculates the exact number of elapsed days across three distinct segments:
  - Remaining days in the birth year (`dy()`).
  - Days in intermediate full years between birth year and current year (`by()`).
  - Elapsed days in the current year (`ty()`).
  - Special handling when birth year matches the current year (`dty - ty(...)`).
- **Gregorian Leap Year Handling:** Correctly applies the standard 4-year, 100-year, and 400-year leap rules:
  ```cpp
  (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)
  ```
- **Live System Time Retrieval:** Uses C++ `<chrono>` and `<ctime>` (`localtime`, `std::tm`) to automatically fetch today's date from the operating system.
- **Input Validation:** Rejects inputs with years earlier than 1900, invalid months (`< 1` or `> 12`), invalid days (`< 1` or `> 31`), and any dates occurring in the future relative to system time.

---

## C++ Concepts Used

- **Input and Output Streams:** Standard I/O (`std::cin`, `std::cout`) from `<iostream>`.
- **Modular Functions:** Decomposition of logic into distinct calculation functions (`ty`, `dy`, `by`, `pday`).
- **Control Flow & Fall-Through:** `switch` statements utilizing intentional fall-through to compute cumulative day offsets across calendar months.
- **Conditional Logic:** Complex multi-condition `if-else` expressions for boundary validation and leap adjustments.
- **Loops:** Iterative `for` loops across year spans with leap checking.
- **Time Utilities:** System clock integration using `<chrono>` and POSIX calendar conversion with `<ctime>`.
- **Arithmetic Parsing:** Modulo (`%`) and integer division (`/`) to extract day, month, and year components from a single numerical integer.

---

## Prerequisites

- **C++ Compiler:** `g++` (GCC) or `clang++` (Apple Clang / LLVM) supporting C++11 or newer.
- **Operating System:** macOS, Linux, or Windows.

---

## Compilation and Execution

### Using Clang++ or G++

From the `01-dob-weekday-calculator` directory:

```bash
# Compile
g++ -std=c++11 dob.cpp -o dob_calculator

# Run on macOS / Linux
./dob_calculator

# Run on Windows
dob_calculator.exe
```

---

## Example Input and Output

### Sample Run

```text
Enter Your DOB (ddmmyyyy): 
15082000
No Of Days :9565
Tuesday
```

### Invalid Date Example

```text
Enter Your DOB (ddmmyyyy): 
15142024
Invalid DOB
```

---

## Current Limitations

- **Integer Input Limitation:** Because input is read into a standard `int`, dates with leading zeros (e.g., `05082001` or `01012000`) lose their leading digits upon extraction, leading to invalid date errors or incorrect calculations.
- **Month Length Validation:** The program verifies days between 1 and 31 generally, but does not yet validate specific days per individual month (e.g., February 30 or April 31 are not rejected upfront).
- **Minimum Year Bound:** Input is constrained to years from 1900 onward due to the anchor date baseline calculation.

---

## Possible Future Improvements

- [ ] Transition input parsing to `std::string` with delimiter support (e.g., `DD/MM/YYYY`) to preserve leading zeros.
- [ ] Implement an exact month-length validator for February and 30-day months.
- [ ] Refactor function and variable names (`ty`, `dy`, `by`, `nof`, `fnof`) to improve readability and maintainability.
- [ ] Add automated unit tests to verify known reference dates and leap year edge cases.
