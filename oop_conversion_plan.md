# Plan for Converting to Object-Oriented Programming

This document outlines the plan to refactor the codebase from a procedural C-style to a more robust and maintainable Object-Oriented C++ structure. The conversion will be done in several small, focused steps.

## Step 1: Create the `Vector` Class

The `Vector` struct is a fundamental data structure used throughout the codebase. This step will focus on converting it into a proper C++ class.

**Files:** `src/vector.h`, `src/vector.cpp`

**Plan:**

1.  **Create a `Vector` class:** The existing `Vector` struct will be converted into a class.
2.  **Encapsulate data:** The `dim` and `x` members will be made private to encapsulate the vector's internal representation.
3.  **Convert functions to methods:** The C-style functions `Init`, `Print`, and `Cmp` will be converted into public member functions of the `Vector` class.
4.  **Add constructor and destructor:** A constructor will be added to handle the initialization of a `Vector` object, and a destructor will be added to manage memory.
5.  **Overload operators:** To make the `Vector` class more intuitive to use, operators for common vector operations (e.g., `+`, `-`, `*` for dot product) will be overloaded.

## Step 2: Create an Abstract `Index` Base Class

To create a common interface for different index types (HNSW, IVF-Flat), an abstract base class `Index` will be created.

**File:** `src/index.h` (new file)

**Plan:**

1.  **Create an abstract `Index` class:** This class will serve as the base for all index implementations.
2.  **Define a common interface:** Pure virtual functions for common index operations will be defined:
    *   `build()`: To build the index.
    *   `insert()`: To insert a new vector into the index.
    *   `search()`: To search for the nearest neighbors of a vector.
    *   `vacuum()`: To clean up the index.

## Step 3: Refactor HNSW into an `HnswIndex` Class

This step will focus on encapsulating the HNSW implementation within a new `HnswIndex` class.

**Files:** `src/hnsw.h`, `src/hnsw.cpp`

**Plan:**

1.  **Create an `HnswIndex` class:** This class will inherit from the `Index` base class.
2.  **Encapsulate HNSW data structures:** The numerous structs in `hnsw.h` (e.g., `HnswGraph`, `HnswBuildState`) will be analyzed and encapsulated as private member variables or nested classes within the `HnswIndex` class.
3.  **Convert HNSW functions to methods:** The global functions in `hnsw.cpp` will be converted into private or public member functions of the `HnswIndex` class.
4.  **Implement the `Index` interface:** The public interface of the `HnswIndex` class will implement the pure virtual functions defined in the `Index` base class (`build`, `insert`, `search`, `vacuum`).

## Step 4: Refactor IVF-Flat into an `IvfflatIndex` Class

Similar to the HNSW refactoring, this step will encapsulate the IVF-Flat implementation within an `IvfflatIndex` class.

**Files:** `src/ivfflat.h`, `src/ivfflat.cpp`

**Plan:**

1.  **Create an `IvfflatIndex` class:** This class will inherit from the `Index` base class.
2.  **Encapsulate IVF-Flat data structures:** The structs in `ivfflat.h` (e.g., `IvfflatBuildState`, `IvfflatMetaPageData`) will be encapsulated within the `IvfflatIndex` class.
3.  **Convert IVF-Flat functions to methods:** The global functions in `ivfflat.cpp` will be converted into member functions of the `IvfflatIndex` class.
4.  **Implement the `Index` interface:** The public interface of the `IvfflatIndex` class will implement the pure virtual functions defined in the `Index` base class.

## Step 5: Refactor Helper Utilities

The codebase contains several utility functions that can be better organized.

**Files:** `src/bitutils.*`, `src/halfutils.*`, etc.

**Plan:**

1.  **Create a `utils` namespace:** A namespace `utils` will be created to house all utility functions.
2.  **Group related functions:** Related utility functions will be grouped into static classes or within the `utils` namespace (e.g., `BitUtils`, `HalfUtils`). This will improve code organization and prevent naming conflicts.

## Step 6: Update the Top-Level API

The top-level C functions that are exposed to PostgreSQL will be updated to use the new C++ classes.

**Files:** `src/vector.cpp`, `src/hnsw.cpp`, `src/ivfflat.cpp`

**Plan:**

1.  **Create wrapper functions:** The C-style functions that are part of the public API (e.g., `hnswbuild`, `ivfflatinsert`) will be updated to act as wrappers around the new C++ classes.
2.  **Instantiate and use C++ classes:** These wrapper functions will create instances of the `HnswIndex` or `IvfflatIndex` classes and call their member functions to perform the required operations.
