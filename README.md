# Simple Blockchain in C++

This is a basic blockchain implementation in C++ as part of the internship assignment.

## Features:
- SHA-256 hashing (implemented manually using `sha256.cpp`)
- Tamper detection (blockchain validity check before and after data modification)
- Basic Proof-of-Work simulation

## Files:
- `main.cpp` – Contains the core blockchain implementation and demonstration
- `sha256.cpp` – SHA-256 hashing logic
- `sha256.h` – Header file for hashing

## Sample Data Used:
- A sends 10 BTC to B
- B sends 5 BTC to C
- C sends 2 BTC to D

## How to Run:
1. Compile all `.cpp` files using any C++ compiler (e.g., g++, CodeBlocks, or online GDB)
2. Run the executable to see blockchain validation and tampering detection.
