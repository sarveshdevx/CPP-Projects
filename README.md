# C++ DOB & Weekday Calculator

A beginner-friendly C++ project that calculates the **day of the week on which a person was born** and the **number of days elapsed since their date of birth**.

The project uses basic C++ concepts and manual date calculations to understand how dates, leap years, and weekdays work.

## Features

- **Day of the Week:** Finds whether the birth date falls on a Monday, Tuesday, Wednesday, etc.
- **Days Elapsed:** Calculates the number of days between the birth date and the current date.
- **Leap Year Handling:** Accounts for leap years using the Gregorian calendar rules.
- **Current Date Detection:** Uses C++ `<chrono>` and `<ctime>` to obtain the current system date.
- **Date Validation:** Checks basic date ranges and prevents future dates.

## Concepts Used

- C++ functions
- `switch` statements and fall-through
- `if-else` conditions
- `for` loops
- Arithmetic and modulo operations
- Leap year calculations
- `<chrono>` and `<ctime>` libraries

## How It Works

The program divides the calculation into three main functions:

| Function | Purpose |
|---|---|
| `ty()` | Calculates the day number within a year. |
| `dy()` | Calculates the days remaining after the birth date in its year. |
| `by()` | Calculates the number of days in the complete years between the birth year and current year. |

The program combines these calculations to determine the elapsed days. It also calculates the birth date's weekday using a reference date and the modulo operator (`% 7`).

## How to Run

### 1. Clone the repository

```bash
git clone https://github.com/YOUR_USERNAME/cpp-dob-weekday-calculator.git
```

Replace `YOUR_USERNAME` with your GitHub username.

### 2. Open the project folder

```bash
cd cpp-dob-weekday-calculator
```

### 3. Compile the program

If you have GCC installed, run:

```bash
g++ main.cpp -o dob_calculator
```

### 4. Run the program

On macOS or Linux:

```bash
./dob_calculator
```

On Windows:

```bash
dob_calculator.exe
```

## Input Format

Enter your date of birth in the following format:

```text
ddmmyyyy
```

For example:

```text
Enter Your DOB (ddmmyyyy):
15082000
```

The program displays the number of elapsed days and the weekday on which you were born.

## Current Limitations

- The program does not yet validate the exact number of days in each month. For example, `31022000` may be accepted even though it is not a valid date.
- Input is read as an integer, so dates with a leading zero, such as `01012000`, are not handled correctly.
- The calculation uses the Gregorian calendar and restricts birth years to 1900 or later.

These limitations can be addressed in future improvements.

## Future Improvements

- Add complete calendar-date validation.
- Accept dates using string input to preserve leading zeros.
- Improve the output formatting.
- Add automated test cases for leap years and known weekdays.
- Refactor the date calculations for improved readability.

## Learning Goal

This project was created to practise C++ fundamentals by building a date calculator without relying on a dedicated date-calculation library.

---

**Built with C++**  
*Learning, experimenting, and improving one project at a time.*
