
#include <iostream>
#include <vector>
#include <memory> // For smart pointers

#include "LOP.hpp"
#include "SimulatedAnnealing.hpp"

using namespace std;
namespace fs = std::filesystem;

int main(int argc, char *argv[])
{
    std::cout << "Goku, esta vaina e seria." << std::endl;

    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return EXIT_FAILURE;
    }

    int n;
    auto initial_solution = std::make_unique<solution_t>();

    read_from_file(argv[1], initial_solution);
    std::cout << "\nInitial Solution:\n"
              << *initial_solution << std::endl
              << std::endl;

    int N_iterations = 100;
    int N_chain = 100;    // max chain
    double T_0 = 74933.4; // Fixed initial temp
    double beta = T_0 / N_iterations;

    // Heuristic initial temp
    int N_random_walks = 10000;
    int N_random_walk_perturbations = 100;
    double acceptance_rate = 0.75;
    // T_0 = SimulatedAnnealing::get_initial_temperature(initial_solution, N_random_walks, N_random_walk_perturbations, acceptance_rate);

    std::cout << "Parameters for Simulated Annealing Algorithm:" << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "Number of iterations: " << N_iterations << std::endl;
    std::cout << "Maximum chain size: " << N_chain << std::endl;
    std::cout << "Initial temperature (T_0): " << T_0 << std::endl;
    std::cout << "Beta (T_0 / N_iterations): " << beta << std::endl;
    std::cout << "Number of random walks: " << N_random_walks << std::endl;
    std::cout << "Number of perturbations per random walk: " << N_random_walk_perturbations << std::endl;
    std::cout << "Acceptance rate: " << acceptance_rate << std::endl;

    SimulatedAnnealing SA(T_0, beta, N_chain, N_iterations, LINEAR);
    SA.run(initial_solution);

    std::cout << "\nFinal solution:\n"
              << *SA.final_x << std::endl
              << std::endl;

    return 0;
}