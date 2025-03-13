#include <iostream>
#include <fstream>
// #include <algorithm>

#include "LOP.hpp"

std::ostream& operator<<(std::ostream& os, const solution_t& sol) {
    // Print the permutation vector
    os << "Permutation: ";
    for (int i = 0; i < sol.n; ++i) {
        os << sol.permutation[i] << " ";
    }
    os << "\n";

    // Print the matrix in a matrix-like form
    os << "Matrix: \n";
    for (int i = 0; i < sol.n; ++i) {
        for (int j = 0; j < sol.n; ++j) {
            os << sol.matrix[i * sol.n + j] << " ";
        }
        os << "\n";
    }

    // Print the objective function value
    os << "Objective Function Value: " << sol.obj_func_value << "\n";

    return os;
}

void LOP_objective_function(const std::unique_ptr<solution_t>& sol){
    sol->obj_func_value = 0;
    for(int i = 0; i< ( sol->n ); i++)
        for(int j = i+1; j< sol->n; j++)
            sol->obj_func_value += sol->matrix[i*sol->n+j];
}


/// @brief  Read LOP initial solution
/// @return 0 if all OK; 1 if not
int read_from_file(std::filesystem::path file_path, const std::unique_ptr<solution_t>& sol){
    std::ifstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << file_path << std::endl;
        return 1;
    }

    file >> sol->n;
    sol->permutation.resize(sol->n);
    sol->matrix.resize(sol->n * sol->n);

    // Initialize permutation
    for (int i = 0; i < sol->n; i++) {
        sol->permutation[i] = i;
    }

    // Read matrix values
    for (int i = 0; i < sol->n; i++) {
        for (int j = 0; j < sol->n; j++) {
            file >> sol->matrix[i * sol->n + j];
        }
    }

    file.close();
    
    LOP_objective_function(sol);
    return 0;
}


std::unique_ptr<solution_t> copy_solution(const std::unique_ptr<solution_t>& original) {
    // Create a new solution instance
    auto new_solution = std::make_unique<solution_t>();
    new_solution->n = original->n;
    new_solution->obj_func_value = original->obj_func_value;
    new_solution->permutation = original->permutation;
    new_solution->matrix = original->matrix;
    return new_solution;  
}

/// @brief Swap operation between two elements. Swaps permutation and matrix.
/// @param solution Structure with permutation and matrix to swap
/// @param s1 First index to swap with
/// @param s2 Second index to swap with
void swap_op(const std::unique_ptr<solution_t>& solution, int s1, int s2) {
    if (s1 == s2) return;  // No need to swap if indices are the same

    // Swap permutation
    std::swap(solution->permutation[s1], solution->permutation[s2]);

    // Swap corresponding rows in the matrix
    for (int j = 0; j < solution->n; j++) {
        std::swap(solution->matrix[s1 * solution->n + j], solution->matrix[s2 * solution->n + j]);
    }

    // Swap corresponding columns in the matrix
    for (int i = 0; i < solution->n; i++) {
        std::swap(solution->matrix[i * solution->n + s1], solution->matrix[i * solution->n + s2]);
    }
}

/// @brief 2-Opt operation between two segments of the permutation.
/// @param solution Structure with permutation and matrix to apply 2-opt
/// @param i First index of the first segment to reverse
/// @param j Second index of the second segment to reverse
void two_opt_op(const std::unique_ptr<solution_t>& solution, int s1, int s2) {
    if (s1 >= s2 || s1 < 0 || s2 >= solution->n) return;  // Valid indices check

    // Reverse the permutation between i and j
    // std::reverse(solution->permutation.begin() + s1, solution->permutation.begin() + s2 + 1);

    // Update the matrix by swapping rows and columns corresponding to the reversed segment
    for (int k = 0; k < solution->n; ++k) {
        // Swap rows
        std::swap(solution->matrix[s1 * solution->n + k], solution->matrix[s2 * solution->n + k]);
        // Swap columns
        std::swap(solution->matrix[k * solution->n + s1], solution->matrix[k * solution->n + s2]);
    }
}
