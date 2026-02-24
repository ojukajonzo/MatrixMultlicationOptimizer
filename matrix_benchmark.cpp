#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include "matrix_utils.h"

class MatrixGenerator {
public:
static std::vector<std::vector<double> > generate(size_t n) {
    std::vector<std::vector<double> > mat(n, std::vector<double>(n));
    std::mt19937 rng(42);     // Fixed seed for reproducibility
    std::uniform_real_distribution<double> dist(0.0, 10.0);
    for (size_t i = 0; i < n; ++i)
	for (size_t j = 0; j < n; ++j)
	    mat[i][j] = dist(rng);
    return mat;
}
};

class MatrixBenchmark {
public:
static void run() {
    std::vector<size_t> sizes = {2, 10, 50, 100, 200, 500, 1000};
    size_t num_threads = 4;     // Adjust as needed
    for (size_t n : sizes) {
	auto A = MatrixGenerator::generate(n);
	auto B = MatrixGenerator::generate(n);

	// Sequential
	auto start_seq = std::chrono::high_resolution_clock::now();
	auto C_seq = matrix_multiply(A, B);
	auto end_seq = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed_seq = end_seq - start_seq;

	// Parallel
	auto start_par = std::chrono::high_resolution_clock::now();
	auto C_par = matrix_multiply_parallel(A, B, num_threads);
	auto end_par = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed_par = end_par - start_par;

	std::cout << "Matrix size: " << n << "x" << n << std::endl;
	std::cout << "  Sequential time: " << elapsed_seq.count() << " s" << std::endl;
	std::cout << "  Parallel time:   " << elapsed_par.count() << " s" << std::endl;
	std::cout << "--------------------------------------" << std::endl;
    }
}
};

int main() {
    MatrixBenchmark::run();
    return 0;
}
