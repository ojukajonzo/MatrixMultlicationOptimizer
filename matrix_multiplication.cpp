#include <iostream>
#include <vector>

// Function to multiply two matrices A (m x n) and B (n x p)
// Returns C (m x p)
std::vector<std::vector<double>> matrix_multiply(
    const std::vector<std::vector<double>>& A,
    const std::vector<std::vector<double>>& B) {
    
    size_t m = A.size();    // Rows in A
    size_t n = A[0].size(); // Columns in A (must equal rows in B)
    size_t p = B[0].size(); // Columns in B
    
    // Check compatibility
    if (A[0].size() != B.size()) {
        throw std::invalid_argument("Matrices cannot be multiplied: Columns of A must equal rows of B");
    }
    
    // Initialize result matrix C with zeros
    std::vector<std::vector<double>> C(m, std::vector<double>(p, 0.0));
    
    // Triple-loop multiplication
    for (size_t i = 0; i < m; ++i) {      // Loop over rows of C (from A)
        for (size_t j = 0; j < p; ++j) {  // Loop over columns of C (from B)
            double sum = 0.0;
            for (size_t k = 0; k < n; ++k) {  // Inner loop: dot product
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
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
    
    try {
        auto C = matrix_multiply(A, B);
        std::cout << "Result matrix C:" << std::endl;
        print_matrix(C);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    return 0;
}