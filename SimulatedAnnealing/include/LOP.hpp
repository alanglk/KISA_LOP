
#ifndef LOP_HPP
#define LOP_HPP

#include <vector>
#include <memory>  // For smart pointers
#include <filesystem>

struct solution_t {
    std::vector<int> permutation;
    std::vector<int> matrix;
    int n;
    int obj_func_value;
};


std::ostream& operator<<(std::ostream& os, const solution_t& sol);

void LOP_objective_function(const std::unique_ptr<solution_t>& sol);

/// @brief  Read LOP initial solution
/// @return 0 if all OK; 1 if not
int read_from_file(std::filesystem::path file_path, const std::unique_ptr<solution_t>& sol);

/// @brief Swap operation between two elements. Swaps permutation and matrix.
/// @param solution Structure with permutation and matrix to swap
/// @param s1 First index to swap with
/// @param s2 Second index to swap with
void swap_op(const std::unique_ptr<solution_t>& solution, int s1, int s2);


std::unique_ptr<solution_t> copy_solution(const std::unique_ptr<solution_t>& original);

#endif
