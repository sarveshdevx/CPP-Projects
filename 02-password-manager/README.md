# Encrypted CLI Password Manager

A secure, terminal-based C++17 password manager that stores encrypted account credentials in an authenticated local vault using modern cryptographic primitives.

---

## Overview

The Password Manager allows users to securely store, retrieve, update, and manage sensitive credentials from their command-line interface. It implements industry-standard cryptography via **libsodium** to protect the credential vault against unauthorized inspection or tampering. The master password never touches disk, sensitive buffers are scrubbed from memory after use, and terminal echo is suppressed during password entry.

---

## Features

- **Authenticated Encryption:** Encrypts vault contents using **XChaCha20-Poly1305** (`crypto_aead_xchacha20poly1305_ietf`) authenticated encryption with associated data (AEAD).
- **Strong Key Derivation:** Derives a 256-bit encryption key from the user's master password using **Argon2id** (`crypto_pwhash_argon2id`) with random cryptographic salt.
- **Terminal Masking:** Temporarily disables terminal echo using POSIX `<termios.h>` so master passwords are not visible on screen while typing.
- **Memory Sanitization:** Clears plaintext passwords, encryption keys, and sensitive buffers from RAM using `sodium_memzero()` before program exit or upon locking the vault.
- **Atomic File Writing:** Writes updates to a temporary file (`vault.txt.tmp`) before renaming it to `vault.txt` to prevent vault corruption in case of unexpected termination.
- **Full Credential Lifecycle (CRUD):**
  - Add new password records (Company, Account Type, Username/ID, Password).
  - Update existing entries by ID.
  - Delete entries with ID realignment.
  - Display all stored records.
  - Explicitly save changes or prompt before discarding unsaved modifications.
  - Lock vault without exiting the session.

---

## C++ Concepts Used

- **Modern C++17 Standards:** Structured data models and `std::filesystem` for file existence and atomic renaming operations.
- **Structures & Data Models:** `PasswordEntry` and `Vault` struct records.
- **STL Containers & Algorithms:** `std::vector<unsigned char>` for binary buffer manipulation, `std::vector<PasswordEntry>`, `std::string`, and `<algorithm>`.
- **Low-Level Binary Serialization:** Custom byte-level serialization using bitwise shifts (`>>`, `& 0xff`, `|`) to encode and decode numeric field lengths and string payloads.
- **File I/O:** Stream reading and writing with `std::ifstream` and `std::ofstream`.
- **Error Handling:** Robust exception management using `try-catch` blocks and `std::runtime_error`.
- **POSIX System APIs:** Low-level terminal manipulation via `tcgetattr()` and `tcsetattr()`.
- **Third-Party C Library Integration:** Direct interoperability with `libsodium` for hashing, random generation, and AEAD encryption.

---

## Prerequisites

- **C++ Compiler:** `clang++` or `g++` supporting C++17.
- **libsodium:** Cryptographic library installed on the system.
  - macOS: `brew install libsodium pkg-config`
  - Ubuntu/Debian: `sudo apt-get install libsodium-dev pkg-config`
  - Fedora: `sudo dnf install libsodium-devel pkgconf`
- **Build Tools (Optional):** CMake (3.20 or newer).

---

## Compilation and Execution

### Method 1: Direct Compilation with `pkg-config`

```bash
# Compile using g++ or clang++
g++ -std=c++17 password_manager.cpp $(pkg-config --cflags --libs libsodium) -o password_manager

# Run the program
./password_manager
```

### Method 2: Using CMake

```bash
# Generate build configuration
cmake -B build -S .

# Build the executable
cmake --build build

# Run
./build/password_manager
```

---

## Example Usage

### First Launch: Creating Master Password
```text
Create your master password.
New master password (at least 12 characters): [hidden]
Confirm master password: [hidden]
Encrypted vault created.

===== PASSWORD MANAGER =====
1. Save new password
2. Update password
3. Delete password
4. Show all passwords
5. Save changes
6. Lock vault
7. Exit
Choose an option: 
```

### Storing a New Password
```text
Choose an option: 1
Company: GitHub
Account type: Personal
Account ID / Username: sarveshdevx
Password: [hidden]
Entry added successfully.
```

---

## Current Limitations

- **Terminal Portability:** Terminal echo suppression uses POSIX `termios`, which targets Unix-like environments (macOS, Linux, WSL). On native Windows CMD/PowerShell, password masking requires Windows Console APIs (`SetConsoleMode`).
- **Single Vault File:** Operates on a single `vault.txt` file located in the working directory.
- **Sequential Search:** Viewing entries prints all stored records; there is no keyword search or categorization filter yet.

---

## Possible Future Improvements

- [ ] Add cross-platform abstraction for Windows terminal echo suppression.
- [ ] Add search and filter capability by service name or username.
- [ ] Implement an integrated cryptographically secure password generator.
- [ ] Support password strength analysis and duplicate password warnings.
- [ ] Add export/import functionality for encrypted backups.
