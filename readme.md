# C_Data_Structures

A small C library implementing common data structures.

---

## Getting started

Copy `libdata_structures.a` to your project, and import it with `#include <data_structures.h>`.

Link the library like `gcc main.c -Iinclude -L. -ldata_structures -o main` where `main.c` is your program.

---

## Project Structure

/build/     - compiled object files (.o) generated from /src  
/include/   - public headers (library API)  
/src/       - implementation files (.c)  
/tests/     - test programs  
libdata_structures.a - static library built from /build objects  

---

## Build & Tests

Build the library with `make`, build a test with `gcc src/x.c tests/test_x.c -Iinclude -o test`
