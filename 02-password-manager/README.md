# CLI Password Manager

A simple command-line Password Manager built using C++ and File Handling.

This project allows users to store and manage their account credentials through a terminal-based interface. Users can create a master password to access the application and perform basic operations such as adding, viewing, updating, and deleting saved credentials.

All data, including the master password and account credentials, is stored in a local text file using C++ file handling.

---

## Features

- **Master Password:** Set and verify a master password before accessing the password manager.
- **Add Password:** Save credentials for different platforms and services.
- **View Passwords:** Display all saved account credentials.
- **Update Password:** Modify the username, email, or password of an existing account.
- **Delete Password:** Remove saved credentials from the text file.
- **File Handling:** Store and retrieve all credentials using a local `.txt` file.
- **Menu-Driven Interface:** Navigate through the application using a simple terminal menu.

## Technologies Used

- **Programming Language:** C++
- **File Handling:** `fstream`, `ifstream`, `ofstream`
- **Data Storage:** Local text file (`.txt`)
- **Interface:** Command-Line Interface (CLI)

## C++ Concepts Used

- Variables and Data Types
- Conditional Statements (`if-else`, `switch`)
- Loops (`for`, `while`)
- Functions
- Structures (`struct`), if used
- String Handling
- File Handling and File Streams
- Reading and Writing Data to Files
- Searching and Updating File Records
- Basic Input Validation

## Stored Information

Each saved account contains the following information:

| Field | Description |
|---|---|
| Company / Platform | Account service (e.g., Spotify, Amazon) |
| Account ID | Username, email, or phone number |
| Password | Account password |

The master password is also stored in the local text file.

## How It Works

1. The user launches the application.
2. The application asks for the master password.
3. If the master password is correct, the main menu is displayed.
4. The user selects an operation:
   - Add a new password.
   - View all saved passwords.
   - Update an existing password.
   - Delete a saved password.
   - Exit the application.
5. Changes are saved to the text file using C++ file handling.

## Project Structure

```text
02-password-manager/
│
├── password_manager.cpp
├── passwords.txt
└── README.md
```

## Requirements

- C++ compiler supporting C++11 or later.
- Terminal or command-line interface.
- macOS, Linux, or Windows.

## Compilation and Execution

Navigate to the project directory:

```bash
cd 02-password-manager
```

Compile the program:

```bash
g++ -std=c++11 password_manager.cpp -o password_manager
```

Run the application:

```bash
./password_manager
```

## Data Storage

All master password and account credential information is stored locally in `passwords.txt`.

The application uses file handling operations to:
- Create and write records.
- Read and display stored records.
- Search for specific accounts.
- Update existing records.
- Delete unwanted records.

## Security Note

**This is an educational project and does not provide secure password storage.**

The master password and account credentials are stored in plain text without encryption or hashing. Anyone who can access the text file can read the stored information.

Do not use this version to store real or sensitive passwords.

Encryption and secure storage may be considered in a future version.

## Learning Objectives

- Understand file handling in C++.
- Learn how to create, read, write, and modify text files.
- Implement CRUD operations (Create, Read, Update, Delete).
- Understand how to organize and manage records.
- Build a practical command-line application.

---

**Status:** In Development

**Language:** C++

**Project Category:** File Handling / Command-Line Application
