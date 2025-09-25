# Guide to Converting to Modern C++

This document outlines the steps to convert the existing C-style C++ code in this repository to a more modern and idiomatic C++ style. While this is a PostgreSQL extension and must interface with the PostgreSQL C API, we can still improve the codebase by adopting C++ features where appropriate.

The following is a list of tasks that need to be completed to fully convert the C code to C++ code.

## 1. Use C++ Headers

The first step is to replace C headers with their C++ counterparts. This improves namespacing and consistency.

**Example:**

In `src/vector.cpp`, change:

```c
#include <math.h>
```

to:

```cpp
#include <cmath>
```

A non-exhaustive list of headers to change:
- `<math.h>` -> `<cmath>`
- `<string.h>` -> `<cstring>`
- `<stdio.h>` -> `<cstdio>`
- `<stdlib.h>` -> `<cstdlib>`

## 2. Use `nullptr` instead of `NULL`

The `nullptr` keyword should be used for null pointers. It is type-safe and less error-prone than the `NULL` macro.

## 3. Convert C-style Casts to C++ Casts

C-style casts are not type-safe and can hide errors. They should be replaced with the appropriate C++ cast:
- `static_cast`: For safe and predictable conversions.
- `reinterpret_cast`: For low-level reinterpreting of bit patterns.
- `const_cast`: To add or remove `const`.
- `dynamic_cast`: For converting pointers/references within an inheritance hierarchy.

**Example:**

In `src/vector.cpp`:

```c
result = (Vector *) palloc0(size);
```

should be changed to:

```cpp
result = static_cast<Vector *>(palloc0(size));
```

## 4. Convert `struct`s to `class`es

Structs that have associated functions should be converted to classes with member functions. This improves encapsulation and data hiding. The `Vector` struct is a prime candidate.

**Example:**

The `Vector` struct in `src/vector.h` could be converted to a class:

```cpp
class Vector {
private:
    int32   vl_len_;    /* varlena header (do not touch directly!) */
    int16   dim;        /* number of dimensions */
    int16   unused;     /* reserved for future use, always zero */
    float   x[FLEXIBLE_ARRAY_MEMBER];

public:
    static Vector* Init(int dim);
    void Print(const char* msg) const;
    int Cmp(const Vector* b) const;

    // Accessors
    int Dim() const { return dim; }
    const float* Values() const { return x; }
    float* Values() { return x; }
};
```

## 5. Use `const` correctness

Use `const` to indicate that a function does not modify the state of an object or that a variable should not be modified. This helps the compiler enforce correctness and can lead to optimizations.

**Example:**

In `Vector::Cmp`, the parameter `b` should be a pointer to a `const Vector`, and the method itself should be `const` if it doesn't modify the `Vector` object.

```cpp
int Cmp(const Vector* b) const;
```

## 6. Use C++ Standard Library where appropriate

While we must use PostgreSQL's memory management (`palloc`, `pfree`), we can use other parts of the C++ standard library, such as algorithms (`std::sort`, etc.) and containers (`std::vector` for temporary storage).

## 7. Use namespaces

To avoid polluting the global namespace, the code for this extension could be wrapped in a namespace.

```cpp
namespace pgvector {
    // ... code ...
}
```

This will help prevent name clashes with other extensions or with PostgreSQL itself.

