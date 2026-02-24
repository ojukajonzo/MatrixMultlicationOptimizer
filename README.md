# Matrix Multiplication Optimizer

This project demonstrates matrix multiplication in C++ with both sequential and parallel (multi-threaded) implementations. It includes code, pseudo-code, and detailed explanations for educational and performance comparison purposes.

## Folder Contents

- **matrix_multiplication.cpp**  
  Implements standard matrix multiplication using triple nested loops.  
  - Uses C++ vectors for matrix storage.
  - Checks for dimension compatibility.
  - Prints the result matrix.
  - Example matrices are provided for demonstration.

- **with_multithreads.cpp**  
  Implements matrix multiplication using C++11 threads for parallelism.  
  - Splits the computation of matrix rows across multiple threads.
  - Each thread computes a chunk of rows independently.
  - Uses static load balancing for fair work distribution.
  - No explicit synchronization needed (each thread writes to unique rows).
  - Demonstrates performance benefits for large matrices.

- **pseudo_code.txt**  
  Provides high-level pseudo-code for matrix multiplication.  
  - Describes the algorithm in plain language.
  - Useful for understanding the logic before diving into C++ code.

- **with_multiplication_explained.txt**  
  Explains the multi-threaded approach in detail.  
  - Covers parallelism strategy, work splitting, thread creation, execution model, and synchronization.
  - Discusses overhead, limitations, and scalability.
  - Offers insights into why and how multi-threading is used.

## How to Use

1. Compile and run `matrix_multiplication.cpp` for sequential multiplication.
2. Compile and run `with_multithreads.cpp` for parallel multiplication.
3. Refer to `pseudo_code.txt` for algorithm understanding.
4. Read `with_multiplication_explained.txt` for a deep dive into the parallel implementation.

## Educational Value

- Compare sequential vs parallel performance.
- Learn about matrix multiplication algorithms.
- Understand practical multi-threading in C++.
