# Assembly and C Projects Collection

This repository contains multiple small projects written in both Assembly (NASM syntax for Linux x86_64) and C. Each project demonstrates different low-level and systems programming concepts.

---

## 📁 Project: homework2

### Description
This project prints a list of signed integers in exactly 9-digit format (padded with leading zeros if necessary). Negative numbers are prefixed with a minus sign.

### Files
- `homework2.asm`: Assembly implementation using syscalls to print formatted integers.
- `homework2_asmReady.c`: Equivalent logic implemented in C using standard I/O.

### Concepts
- Integer formatting
- Conditional branching
- Stack manipulation in Assembly
- Goto-based loops in C

---

## 📁 Project: homework3

### Description
This project prints a square-shaped visual pattern based on Manhattan distance from a central radius. Values above a minimum distance are printed as characters using an offset; otherwise, spaces are used.

### Files
- `homework3.asm`: Assembly implementation with logic for character buffer creation and printing.
- `homework3_asmReady.c`: Equivalent C version using `putchar()`.

### Concepts
- Manhattan distance computation
- Pattern generation using nested loops
- Custom `abs()` function in Assembly
- Buffer-based printing

---

## 📁 Project: FloatValue Structure (Unnamed C++ file)

### Description
This C++ code defines a custom `FloatValue` structure that dissects a floating-point number into its IEEE-754 components: sign bit, exponent, and mantissa. It includes methods to interpret the number and check special cases (denormalized, infinity, NaN).

### File
- `İsimsiz1.cpp`: Contains full implementation and test examples.

### Concepts
- Bit-level floating point decomposition
- IEEE-754 standard interpretation
- Bit masking and shifting
- Handling special float values (NaN, Inf, Denormalized)

---

## ✅ How to Compile

### Assembly (NASM)
```bash
nasm -f elf64 -o homework2.o homework2.asm
ld -o homework2 homework2.o
./homework2
##C
gcc -o homework2_c homework2_asmReady.c
./homework2_c
###C++g++ -o float_value İsimsiz1.cpp
./float_value

## Note
All code is written and tested on Linux. Some syscalls or behavior may differ on Windows.

The assembly code is written for educational purposes and does not use high-level runtime features.
---

