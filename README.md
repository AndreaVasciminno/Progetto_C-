# Custom C++ Stack Implementation

A robust, custom implementation of a **Stack** data structure in C++. This project provides a header-only class (`Stack.hpp`) designed to mimic the standard `std::stack` behavior with a focus on educational clarity and easy integration.

It includes a configured `Doxyfile` to automatically generate HTML and LaTeX documentation for the code.

---

## 📋 Features

This Stack implementation follows the **LIFO** (Last-In, First-Out) principle and includes the following core operations:

* **Push:** Add an element to the top of the stack.
* **Pop:** Remove the top element.
* **Top/Peek:** Access the top element without removing it.
* **Size:** Check the current number of elements.
* **IsEmpty:** Check if the stack is empty.
* **Clear:** Empty the stack efficiently.

---

## 📂 Project Structure

'''text
.
├── Stack.hpp        # The core stack class implementation
├── main.cpp         # Example usage / Test file
├── Doxyfile         # Doxygen configuration file
└── README.md        # This file


---

## 🚀 Getting Started

**Prerequisites:**

* A C++ Compiler (GCC, Clang, MSVC) supporting C++11 or later.
* Doxygen (Optional, for generating documentation).

**Installation**

Since this is a header-only implementation, you do not need to compile a library. Simply copy the Stack.hpp file into your project directory and include it.

**Usage example**

'''cpp
#include <iostream>
#include "Stack.hpp"

int main() {
    // Initialize the stack (assuming template class)
    Stack<int> myStack;

    // Push elements
    myStack.push(10);
    myStack.push(20);
    myStack.push(30);

    // Check top element
    std::cout << "Top element: " << myStack.top() << std::endl; // Output: 30

    // Pop element
    myStack.pop();
    std::cout << "New top after pop: " << myStack.top() << std::endl; // Output: 20

    // Check size
    std::cout << "Stack size: " << myStack.size() << std::endl; // Output: 2

    return 0;
}
'''

---

## 📚 Documentation
This project uses Doxygen to document the code structure and API. To generate the documentation locally:

Ensure Doxygen is installed on your machine.

Open a terminal in the project root directory.

Run the following command:

'''doxygen Doxyfile'''

---
*Project developed for the C++ Development Course at the University of Milan-Bicocca.*

