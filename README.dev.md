# C to C++ Conversion Plan

This document outlines the plan to convert the `pgvector` extension from C to C++. The conversion will be done in a series of small, independent steps to minimize disruption and allow for easier testing and verification.

## Phase 1: Core Infrastructure and Build System

1.  **Setup C++ Compiler:** Modify the `Makefile` to use a C++ compiler (`g++`) for `.cpp` files. Ensure that C files are still compiled with `gcc`. The build system should be able to handle both C and C++ source files.
2.  **Introduce `extern "C"`:** Create a common header file (e.g., `pgvector.h`) that includes all other headers and wraps them in `extern "C" { ... }` when compiled with a C++ compiler. This will ensure that the C functions are still callable from PostgreSQL.
3.  **Convert `vector.c` to `vector.cpp`:** Convert the main `vector.c` file to C++. This will be the first file to be converted and will serve as a template for the other files. This involves renaming the file, updating the `Makefile`, and fixing any compilation errors.
4.  **Convert `utils.c` files:** Convert the utility files like `bitutils.c`, `halfutils.c`, `ivfutils.c`, and `hnswutils.c` to C++. These files are likely to have fewer dependencies and should be straightforward to convert.

## Phase 2: Data Types and Structures

5.  **Convert `vector.h`:** Convert the `vector.h` header file to be C++ compatible. This may involve using C++ features like namespaces, classes, and structs with methods.
6.  **Convert `sparsevec.c` and `halfvec.c`:** Convert the `sparsevec.c` and `halfvec.c` files to C++. These files define the sparse and half-precision vector types.
7.  **Convert `bitvec.c`:** Convert the `bitvec.c` file to C++. This file defines the binary vector type.

## Phase 3: IVF ADC

8.  **Convert `ivfflat.c` and `ivfflat.h`:** Convert the `ivfflat.c` and `ivfflat.h` files to C++. This is the implementation of the IVFFlat index.
9.  **Convert `ivfbuild.c`:** Convert the `ivfbuild.c` file to C++. This file contains the logic for building the IVFFlat index.
10. **Convert `ivfscan.c`:** Convert the `ivfscan.c` file to C++. This file contains the logic for scanning the IVFFlat index.
11. **Convert `ivfinsert.c`:** Convert the `ivfinsert.c` file to C++. This file contains the logic for inserting into the IVFFlat index.
12. **Convert `ivfvacuum.c`:** Convert the `ivfvacuum.c` file to C++. This file contains the logic for vacuuming the IVFFlat index.
13. **Convert `ivfkmeans.c`:** Convert the `ivfkmeans.c` file to C++. This file contains the k-means clustering implementation for the IVFFlat index.

## Phase 4: HNSW

14. **Convert `hnsw.c` and `hnsw.h`:** Convert the `hnsw.c` and `hnsw.h` files to C++. This is the implementation of the HNSW index.
15. **Convert `hnswbuild.c`:** Convert the `hnswbuild.c` file to C++. This file contains the logic for building the HNSW index.
16. **Convert `hnswscan.c`:** Convert the `hnswscan.c` file to C++. This file contains the logic for scanning the HNSW index.
17. **Convert `hnswinsert.c`:** Convert the `hnswinsert.c` file to C++. This file contains the logic for inserting into the HNSW index.
18. **Convert `hnswvacuum.c`:** Convert the `hnswvacuum.c` file to C++. This file contains the logic for vacuuming the HNSW index.

## Phase 5: Refactoring and Cleanup

19. **Refactor to C++ classes:** Once all files are converted to C++, refactor the code to use C++ classes and objects where appropriate. For example, the `Vector`, `SparseVector`, and `HalfVector` types could be represented as classes.
20. **Code Cleanup:** Perform a final code cleanup to remove any remaining C-style code and ensure that the codebase is consistent with modern C++ practices.
