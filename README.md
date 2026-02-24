# Matrix Multiplication Optimizer


This project demonstrates and benchmarks matrix multiplication in C++ using both sequential and parallel (multi-threaded) approaches. The code is organized for clarity, modularity, and performance comparison.

## Folder Contents

- **matrix_utils.h**  
  Contains all core matrix multiplication logic:
  - `matrix_multiply`: Standard triple-loop sequential multiplication.
  - `matrix_multiply_parallel`: Multi-threaded multiplication using C++11 threads.
  - Helper: `compute_rows` for parallel chunk computation.
  - All functions are reusable and header-only for easy inclusion.

- **matrix_benchmark.cpp**  
  The main entry point for benchmarking and comparing performance:
  - Generates random square matrices of various sizes.
  - Runs both sequential and parallel multiplication for each size.
  - Measures and prints execution time for both methods.
  - Uses OOP for matrix generation and benchmarking.

- **pseudo_code.txt**  
  Provides high-level pseudo-code for matrix multiplication.  
  - Describes the algorithm in plain language.
  - Useful for understanding the logic before diving into C++ code.

- **with_multiplication_explained.txt**  
  Explains the multi-threaded approach in detail.  
  - Covers parallelism strategy, work splitting, thread creation, execution model, and synchronization.
  - Discusses overhead, limitations, and scalability.
  - Offers insights into why and how multi-threading is used.

### Files No Longer Used

- `matrix_multiplication.cpp` and `with_multithreads.cpp` are now just stubs including `matrix_utils.h` for backward compatibility. All logic has been moved to the header and benchmark files.

## How to Use

1. **Compile:**
   ```bash
   g++ -std=c++11 matrix_benchmark.cpp -o benchmark -pthread
   ```
2. **Run:**
   ```bash
   ./benchmark
   ```
3. **Output:**
   - For each matrix size, you will see the time taken by both sequential and parallel multiplication, making it easy to visualize time complexity and performance gains.

## Educational Value
- Compare sequential vs parallel performance.
- Learn about matrix multiplication algorithms and multi-threading in C++.
- Modular, OOP-based design for easy extension and experimentation.
