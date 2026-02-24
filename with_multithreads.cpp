#include <iostream>
#include <vector>
#include <thread>
#include <mutex>  // For potential synchronization, but not strictly needed here

// Function to compute a chunk of rows in C
void compute_rows(
    const std::vector<std::vector<double>>& A,
    const std::vector<std::vector<double>>& B,
    std::vector<std::vector<double>>& C,
    size_t start_row, size_t end_row) {
    
    size_t m = A.size();
    size_t n = A[0].size();
    size_t p = B[0].size();
    
    for (size_t i = start_row; i < end_row; ++i) {
        for (size_t j = 0; j < p; ++j) {
            double sum = 0.0;
            for (size_t k = 0; k < n; ++k) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
}

// Function to multiply two matrices A (m x n) and B (n x p) in parallel
// Returns C (m x p)
std::vector<std::vector<double>> matrix_multiply_parallel(
    const std::vector<std::vector<double>>& A,
    const std::vector<std::vector<double>>& B,
    size_t num_threads) {
    
    size_t m = A.size();    // Rows in A
    size_t n = A[0].size(); // Columns in A (must equal rows in B)
    size_t p = B[0].size(); // Columns in B
    
    // Check compatibility
    if (A[0].size() != B.size()) {
        throw std::invalid_argument("Matrices cannot be multiplied: Columns of A must equal rows of B");
    }
    
    // Initialize result matrix C with zeros
    std::vector<std::vector<double>> C(m, std::vector<double>(p, 0.0));
    
    // Create threads
    std::vector<std::thread> threads;
    size_t rows_per_thread = m / num_threads;
    size_t extra_rows = m % num_threads;
    
    size_t start_row = 0;
    for (size_t t = 0; t < num_threads; ++t) {
        size_t end_row = start_row + rows_per_thread + (t < extra_rows ? 1 : 0);
        threads.emplace_back(compute_rows, std::cref(A), std::cref(B), std::ref(C), start_row, end_row);
        start_row = end_row;
    }
    
    // Join all threads
    for (auto& th : threads) {
        th.join();
    }
    
    return C;
}

// Helper function to print a matrix
void print_matrix(const std::vector<std::vector<double>>& mat) {
    for (const auto& row : mat) {
        for (double val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    // Example usage: 2x2 matrices
    std::vector<std::vector<double>> A = {{2, 3}, {4, 5}};
    std::vector<std::vector<double>> B = {{1, 6}, {7, 8}};
    
    size_t num_threads = 2;  // Adjust based on your CPU cores
    
    try {
        auto C = matrix_multiply_parallel(A, B, num_threads);
        std::cout << "Result matrix C (parallel):" << std::endl;
        print_matrix(C);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    return 0;
}