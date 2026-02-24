#ifndef MATRIX_UTILS_H
#define MATRIX_UTILS_H

#include <vector>
#include <stdexcept>
#include <thread>

// Sequential matrix multiplication
std::vector<std::vector<double>> matrix_multiply(
    const std::vector<std::vector<double>>& A,
    const std::vector<std::vector<double>>& B) {
    size_t m = A.size();
    size_t n = A[0].size();
    size_t p = B[0].size();
    if (A[0].size() != B.size()) {
        throw std::invalid_argument("Matrices cannot be multiplied: Columns of A must equal rows of B");
    }
    std::vector<std::vector<double>> C(m, std::vector<double>(p, 0.0));
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < p; ++j) {
            double sum = 0.0;
            for (size_t k = 0; k < n; ++k) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
    return C;
}

// Parallel chunk computation
void compute_rows(
    const std::vector<std::vector<double>>& A,
    const std::vector<std::vector<double>>& B,
    std::vector<std::vector<double>>& C,
    size_t start_row, size_t end_row) {
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

// Parallel matrix multiplication
std::vector<std::vector<double>> matrix_multiply_parallel(
    const std::vector<std::vector<double>>& A,
    const std::vector<std::vector<double>>& B,
    size_t num_threads) {
    size_t m = A.size();
    size_t n = A[0].size();
    size_t p = B[0].size();
    if (A[0].size() != B.size()) {
        throw std::invalid_argument("Matrices cannot be multiplied: Columns of A must equal rows of B");
    }
    std::vector<std::vector<double>> C(m, std::vector<double>(p, 0.0));
    std::vector<std::thread> threads;
    size_t rows_per_thread = m / num_threads;
    size_t extra_rows = m % num_threads;
    size_t start_row = 0;
    for (size_t t = 0; t < num_threads; ++t) {
        size_t end_row = start_row + rows_per_thread + (t < extra_rows ? 1 : 0);
        threads.emplace_back(compute_rows, std::cref(A), std::cref(B), std::ref(C), start_row, end_row);
        start_row = end_row;
    }
    for (auto& thread : threads) {
        thread.join();
    }
    return C;
}

#endif // MATRIX_UTILS_H
