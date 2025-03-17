
#include <iostream>
#include <vector>
#include <memory> // For smart pointers

#include <limits.h>

#include "LOP.hpp"
#include "SimulatedAnnealing.hpp"
#include "Logger.hpp"

using namespace std;
namespace fs = std::filesystem;

int main(int argc, char *argv[])
{
    std::cout << "Goku, esta vaina e seria." << std::endl;

    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <config_file>" << std::endl;
        return EXIT_FAILURE;
    }

    // Read config file: set algorithm params and init the logger
    Logger logger(argv[1]);
    if (!logger.loadConfig()){
        std::cerr << "Error reading config file: " << argv[1] << std::endl;
        return EXIT_FAILURE;
    }
    Config config = logger.getConfig();    

    auto initial_solution = std::make_unique<solution_t>();
    read_from_file(config.file_path, initial_solution);
    std::cout   << "\nInitial Solution:\n" << *initial_solution << std::endl << std::endl;

    if (config.use_random_walk){
        config.T_0 = SimulatedAnnealing::get_initial_temperature(initial_solution, config.N_random_walks, config.N_random_walk_perturbations, config.acceptance_rate, config.neigh_type);
        // N-r100a2: Heuristic T_0: 122142 -> [max_func_value: 101376 | min_func_value: 66238]
    }
    
    std::cout << "Parameters for Simulated Annealing Algorithm:" << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "Number of iterations: " << config.max_iter << std::endl;
    std::cout << "Maximum chain size: " << config.max_chain << std::endl;
    std::cout << "Maximum Stagnation: " << config.max_stagnation << std::endl;
    std::cout << "Initial temperature (T_0): " << config.T_0 << std::endl;
    std::cout << "Beta: " << config.beta << std::endl;
    std::cout << "Update type: " << config.update << " [0: LINEAR | 1: GEOMETRIC | 2: LOGARITMIC]" << std::endl;
    std::cout << "Neigborhood: " << config.neigh_type << " [0: SWAP | 1: 2-OPT]" << std::endl;
    std::cout << std::endl;
    if (config.use_random_walk) {
        std::cout << "[Random Walk] Number of random walks: " << config.N_random_walks << std::endl;
        std::cout << "[Random Walk] Number of perturbations per random walk: " << config.N_random_walk_perturbations << std::endl;
        std::cout << "[Random Walk] Acceptance rate: " << config.acceptance_rate << std::endl;
        std::cout << std::endl;
    }

    std::cout << "Simulated Annealing Algorithm Execution:" << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
    SimulatedAnnealing SA(config, logger);
    SA.run(initial_solution);

    std::cout << "\nFinal solution:\n" << *SA.final_x << std::endl << std::endl;

    return 0;
}