
#include <iostream>
#include <vector>
#include <memory> // For smart pointers

#include <limits.h>

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

    // Parameters
    int max_chain               = 1000;         // Fixed neighborhood exploration size
    int max_iter                = 100000;       // Max number of iterations
    int max_stagnation          = 100;          // -1 -> Dont use stagnation stopping
    double T_0                  = 122142;       // Fixed initial temp
    double beta                 = 0.8;          // Cooling factor
    TUpdateType update          = GEOMETRIC;    // Cooling strategy
    TNeighborhood neigh_type    = SWAP;         // Neighborhood
    bool use_random_walk        = false;        // Initial exploration?

    // Heuristic initial temp
    int N_random_walks = 10000;
    int N_random_walk_perturbations = 100;
    double acceptance_rate = 0.75;
    if (use_random_walk){
        T_0 = SimulatedAnnealing::get_initial_temperature(initial_solution, N_random_walks, N_random_walk_perturbations, acceptance_rate, neigh_type);
        // N-r100a2: Heuristic T_0: 122142 -> [max_func_value: 101376 | min_func_value: 66238]
    }

    std::cout << "Parameters for Simulated Annealing Algorithm:" << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "Number of iterations: " << max_iter << std::endl;
    std::cout << "Maximum chain size: " << max_chain << std::endl;
    std::cout << "Maximum Stagnation: " << max_stagnation << std::endl;
    std::cout << "Initial temperature (T_0): " << T_0 << std::endl;
    std::cout << "Beta: " << beta << std::endl;
    std::cout << "Update type: " << update << " [0: LINEAR | 1: GEOMETRIC | 2: LOGARITMIC]" << std::endl;
    std::cout << "Neigborhood: " << neigh_type << " [0: SWAP | 1: 2-OPT]" << std::endl;
    std::cout << std::endl;
    if (use_random_walk) {
    std::cout << "[Random Walk] Number of random walks: " << N_random_walks << std::endl;
    std::cout << "[Random Walk] Number of perturbations per random walk: " << N_random_walk_perturbations << std::endl;
    std::cout << "[Random Walk] Acceptance rate: " << acceptance_rate << std::endl;
    std::cout << std::endl;
    }

    SimulatedAnnealing SA(T_0, beta, max_chain, max_iter, max_stagnation, update, neigh_type);
    SA.run(initial_solution);

    std::cout << "\nFinal solution:\n"
              << *SA.final_x << std::endl
              << std::endl;

    return 0;
}