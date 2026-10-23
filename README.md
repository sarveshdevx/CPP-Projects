# C++ Projects Portfolio

Welcome to my central repository for C++ projects. This repository serves as a portfolio of my practical journey with C++, spanning fundamental syntax and algorithmic problem-solving to modern systems programming and cryptography.

As I build new applications and explore advanced C++ concepts, each project is added here as an independent, self-contained module with its own source code, documentation, and build instructions.

---

## Repository Structure

```text
DOBC/
├── README.md                          # Portfolio index and documentation
├── .gitignore                         # Build and temporary artifacts ignore rules
├── 01-dob-weekday-calculator/         # Project 1: Date of birth & weekday calculator
│   ├── dob.cpp                        # Calculator source code
│   └── README.md                      # Project-specific documentation
└── 02-password-manager/               # Project 2: CLI encrypted password manager
    ├── password_manager.cpp           # Vault & encryption implementation
    ├── CMakeLists.txt                 # CMake build configuration
    └── README.md                      # Project-specific documentation
```

---

## Project Index

| # | Project | Description | Primary Concepts | Status |
|---|---|---|---|---|
| **01** | [DOB & Weekday Calculator](./01-dob-weekday-calculator/) | Calculates elapsed days and birth weekday from a date of birth using manual calendar arithmetic. | Functions, `switch` fall-through, `if-else`, loops, `<chrono>`, `<ctime>`. | Completed |
| **02** | [CLI Encrypted Password Manager](./02-password-manager/) | Terminal-based password manager securing credentials with Argon2id and XChaCha20-Poly1305 AEAD. | Modern C++17, structs, `std::vector`, POSIX `termios`, byte serialization, `libsodium`. | Completed |

---

## Project Details

### 01. [DOB & Weekday Calculator](./01-dob-weekday-calculator/)

- **Folder:** [`01-dob-weekday-calculator/`](./01-dob-weekday-calculator/)
- **Description:** A console application that reads a user's date of birth in numeric format (`ddmmyyyy`), queries the system clock for the current date, validates chronological validity, and calculates both total days lived and the specific weekday on which they were born.
- **Key Concepts:**
  - Date decomposition using integer arithmetic (`%` and `/`).
  - Gregorian calendar leap year logic (`(y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)`).
  - Cumulative day calculation using `switch-case` fall-through.
  - Integration with `<chrono>` and `<ctime>` for live date querying.
- **Quick Compilation & Run:**
  ```bash
  cd 01-dob-weekday-calculator
  g++ -std=c++11 dob.cpp -o dob_calculator
  ./dob_calculator
  ```

---

### 02. [CLI Encrypted Password Manager](./02-password-manager/)

- **Folder:** [`02-password-manager/`](./02-password-manager/)
- **Description:** An authenticated command-line credential manager. Master passwords are used with Argon2id to derive 256-bit keys that encrypt a local credential vault using XChaCha20-Poly1305. The terminal suppresses echo during password entry, and sensitive memory is sanitized using `sodium_memzero`.
- **Key Concepts:**
  - C++17 standard filesystem and memory operations.
  - Low-level binary serialization and deserialization with bitwise operations.
  - Secure credential lifecycle management (Add, Update, Delete, List, Lock).
  - Masking password input in terminal sessions via POSIX `<termios.h>`.
  - Cryptographic integration with `libsodium` (Argon2id, XChaCha20-Poly1305, Base64/Hex encoding).
- **Quick Compilation & Run:**
  ```bash
  cd 02-password-manager
  # Method A: Direct compilation with pkg-config
  g++ -std=c++17 password_manager.cpp $(pkg-config --cflags --libs libsodium) -o password_manager
  ./password_manager

  # Method B: Using CMake
  cmake -B build -S .
  cmake --build build
  ./build/password_manager
  ```

---

## Adding Future Projects

Whenever a new C++ project is developed, it is added following this repeatable workflow:

1. **Create a numbered folder:** Use the standard naming convention (e.g., `03-network-packet-sniffer/`, `04-mini-database/`).
2. **Add C++ source files:** Place all source code (`.cpp`, `.hpp`, `.h`), build files, and assets inside that dedicated project folder.
3. **Write a project `README.md`:** Document the project using the standard template:
   - Project title & overview
   - Features
   - C++ concepts used
   - Prerequisites & dependencies
   - Compilation and execution commands
   - Example inputs/outputs
   - Current limitations & planned improvements
4. **Update the root README.md:** Add the project entry into the repository structure, the Project Index table, and the Project Details section.
5. **Test the build:** Compile and verify the project cleanly before committing.
6. **Commit and push:** Stage the changes, commit with a descriptive message, and push to GitHub.

---

## Roadmap

This portfolio is an active workspace. Future additions will continue to explore:
- Object-Oriented Design (OOP) and modern design patterns.
- Data structures and algorithms implemented from scratch.
- Memory management, smart pointers, and RAII.
- Multi-threading, concurrency, and asynchronous programming.
- Socket programming and networked systems.
