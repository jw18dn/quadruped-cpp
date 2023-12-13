#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include <memory>

// ideally use this concept to preallocate the matrix space then modify them as we loop through

// Define the type of matrix (you can change the type and size as needed)
using MatrixType = Eigen::MatrixXd;

int main() {
    // Define the list of smart pointers to matrices
    std::vector<std::unique_ptr<MatrixType>> matrixSmartPtrList;

    // Create matrices and add their smart pointers to the list
    matrixSmartPtrList.push_back(std::make_unique<MatrixType>(MatrixType::Random(3, 3)));
    matrixSmartPtrList.push_back(std::make_unique<MatrixType>(MatrixType::Ones(4, 4)));
    matrixSmartPtrList.push_back(std::make_unique<MatrixType>(MatrixType::Identity(2, 2)));

    // Display the matrices using smart pointers in the list
    for (const auto& matrixSmartPtr : matrixSmartPtrList) {
        std::cout << "Matrix:\n" << *matrixSmartPtr << "\n\n";
    }

    // No need to manually free memory; smart pointers handle it automatically

    return 0;
}