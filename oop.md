# Plan for Refactoring to Object-Oriented C++

This document outlines a step-by-step methodology for converting a procedural C++ codebase into a modern, Object-Oriented, and optimized application. The process is divided into phases, with each step designed as a manageable task.

## Prerequisites

Before starting the refactoring process, ensure you have the following in place:

- **Version Control**: Ensure your codebase is managed by a system like Git. Commit your changes after completing each step.

- **Build System**: Have a functioning build system (e.g., CMake, Make) that you can use to compile and test your code incrementally.

- **Testing Strategy**: If possible, create a suite of high-level tests to verify the application's functionality. These tests will be invaluable for ensuring that your refactoring does not introduce regressions.

## Phase 1: Analysis and Foundational Setup

The goal of this phase is to analyze the existing code to identify potential classes and to set up a clean project structure.

### Step 1: Identify Candidate Classes

**Focus**: The entire codebase.

**Plan**:

- **Analyze Data Structures**: Look for structs and global data structures. These are often the blueprint for your classes' data members.

- **Map Functions to Data**: Identify all the global functions that create, modify, or use these data structures. These functions are candidates for class methods.

- **Identify Nouns and Verbs**: Think about the problem your application solves. The "nouns" often correspond to classes (e.g., User, Report, Connection), and the "verbs" correspond to methods (e.g., user.save(), report.generate()).

**Outcome**: A document listing potential classes, their responsibilities, the data they will manage, and the actions they will perform.

### Step 2: Establish a C++ Project Structure

**Focus**: The project's directory layout.

**Plan**:

- Create `src` and `include` directories.
- Move all source files (`.cpp`) to the `src` directory.
- Move all header files (`.h`) to the `include` directory.
- Update your build system to reflect this new structure.

**Benefit**: This separation of interface and implementation is a standard practice in C++ and improves code organization.

## Phase 2: Initial Class Implementation (Bottom-Up)

Start by converting the most straightforward and least dependent parts of your code into classes.

### Step 3: Convert a Simple struct to a Class

**Focus**: A simple data structure (e.g., `user_data.h`, `config_settings.h`) and the source files that use it.

**Plan**:

- In the header file, change the `struct` keyword to `class`.
- Use the `public:` and `private:` keywords to declare the class's public interface and hide its data members. Data members should be private by default.
- Create a constructor to initialize the data members.
- Move the functions that operate on this data into the class as public methods.
- Update the code that used the old struct to instantiate the new class and use its public methods.

**OOP Concept**: _Encapsulation_. This binds the data and the functions that operate on it together, hiding the internal complexity.

### Step 4: Replace Macros with C++ Constructs

**Focus**: Files that heavily use `#define` for constants or macros.

**Plan**:

- Replace constant-defining macros (`#define PI 3.14`) with `const` or `constexpr` variables (`constexpr double PI = 3.14;`).
- Convert function-like macros to inline functions or regular functions.

**Benefit**: Improves type safety and avoids the pitfalls of preprocessor text replacement.

## Phase 3: Building the OOP Structure

Now, create more complex classes that manage the application's core logic and data.

### Step 5: Create "Manager" or "Service" Classes

**Focus**: Core logic files, often where multiple data structures are manipulated together (e.g., `main.cpp`, `processing.cpp`).

**Plan**:

- Create a new class (e.g., `UserManager`, `ReportGenerator`).
- This class will hold instances of the simpler classes you created earlier as private member variables.
- Move the high-level business logic from global functions in your `.cpp` files into public methods of this manager class.
- Your main function should now primarily create instances of these manager classes and call their methods to run the application.

**OOP Concepts**: _Composition_, _Abstraction_. You are building complex objects from simpler ones and providing a simplified interface to the application's core functionalities.

### Step 6: Introduce Inheritance for Common Behavior

**Focus**: Two or more classes that share similar data or functionality.

**Plan**:

- Identify the common elements between the classes.
- Create a new base class that contains these common data members and functions.
- Declare functions that will have different implementations in the child classes as `virtual`.
- Ensure the base class has a virtual destructor to handle proper cleanup.
- Modify the existing classes to inherit from this new base class and use the `override` keyword on the specialized virtual functions.

**OOP Concepts**: _Inheritance_, _Polymorphism_. This allows you to treat different but related objects in a uniform way, reducing code duplication.

## Phase 4: Modernization and Optimization

With the OOP structure in place, the final phase is to refactor the code to leverage modern C++ features for safety, performance, and readability.

### Step 7: Modernize Memory Management

**Focus**: Any code that uses raw pointers (`*`) with `new` and `delete`.

**Plan**:

- Replace owning raw pointers with smart pointers: `std::unique_ptr` for exclusive ownership and `std::shared_ptr` for shared ownership.
- Use `std::make_unique` and `std::make_shared` for their creation.

**Benefit**: Automates memory management, significantly reducing the risk of memory leaks and dangling pointers.

### Step 8: Utilize the Standard Template Library (STL)

**Focus**: Code using C-style arrays, `char*` for strings, and manual implementations of data structures.

**Plan**:

- Replace C-style arrays with `std::vector` or `std::array`.
- Replace C-style strings (`char*`) with `std::string`.
- Replace manual loops with STL algorithms from the `<algorithm>` header where appropriate (e.g., `std::find`, `std::for_each`, `std::sort`).

**Benefit**: Results in more robust, expressive, and often more performant code.

### Step 9: Refine Class Interfaces and const-correctness

**Focus**: All newly created class header files.

**Plan**:

- Mark any member function that does not modify the object's state as `const`.
- Pass complex objects by reference (`&`) or const reference (`const&`) to functions to avoid unnecessary and costly copies.
- Adopt and enforce a consistent coding style (like the Google C++ Style Guide) for better readability and maintainability.

**Benefit**: Enhances code safety by clearly defining what can and cannot be modified, and can lead to performance improvements.

---

## Summary

This systematic approach to refactoring will transform your procedural C++ code into a well-structured, object-oriented application. Each phase builds upon the previous one, ensuring that you maintain functionality while improving code quality, maintainability, and modern C++ best practices.
