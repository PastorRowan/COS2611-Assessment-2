# COS2611 Assessment 2 - Phase 1 (Sorting Algorithms)

## Student Information
- Student Number: 25939831  
- Name: Rowan Van Zyl  
- Module: COS2611  
- Assessment: Assessment 2 - Phase 1  

---

## Project Overview

This project implements and compares 2 sorting algorithms in C++:

- Bubble Sort
- Merge Sort

The program generates random integer arrays of different sizes and measures the execution time of each sorting algorithm. It also reports the theoretical time complexity of each algorithm.

---

## Features

### 1. Sorting Algorithms Implemented
- **Bubble Sort**
  - Optimised with early exit if no swaps occur.
- **Merge Sort**
  - Recursive divide-and-conquer implementation.
  - Uses vector splitting and merging.

---

### 2. Random Data Generation
The program generates random integer arrays of the following sizes:
- 100 elements
- 1000 elements
- 5000 elements

Each run uses fresh random values.

---

### 3. Performance Measurement
The program measures execution time using:
- `std::chrono::high_resolution_clock`

Execution time is displayed in seconds for both algorithms across all input sizes.

---

### 4. Time Complexity Analysis

Theoretical time complexities included in output:

- **Bubble Sort:**  
  O(n²)

- **Merge Sort:**  
  O(n log₂ n)

---

## Program Output Example
```
Input Size: 100

Bubble Sort:
Execution Time: 0.0020000s

MergeSort:
Execution Time: 0.0010000s

Input Size: 1000

Bubble Sort:
Execution Time: 0.0500000s

MergeSort:
Execution Time: 0.0100000s

Input Size: 5000

Bubble Sort:
Execution Time: 2.5000000s

MergeSort:
Execution Time: 0.1000000s


The time complexity formula for Bubble Sort: O(n^2)
The time complexity formula for Merge Sort: O( nlog_2(n) )

```

---

## How to Compile and Run

#### Using mingw64 toolchain with g++ on Windows 11
```
g++ 25939831A2P1.cpp -o main.exe
```
```
main.exe
```

---

## Note
Project was compiled using the mingw64 toolchain with the g++ compiler on a laptop with the Windows 11 operating system installed.
Results using different toolchains with different compilers with different operating systems may vary.
