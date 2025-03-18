#!/bin/bash

COMMANDS=(
    "./build/tests/swap_testing ./src/GA_testing/Mutation/test1_input ./src/GA_testing/Mutation/test1_output  ./src/GA_testing/Mutation/test1_output2"
    "./build/tests/order_crossover_testing 0 ./src/GA_testing/Crossover/test1_parent1 ./src/GA_testing/Crossover/test1_parent2 ./src/GA_testing/Crossover/test1_expected_child"
    "./build/tests/tournament_selection_testing 0 ./src/GA_testing/Parent_selector/tournament/test1 ./src/GA_testing/Parent_selector/tournament/test2 ./src/GA_testing/Parent_selector/tournament/test3"
    "./build/tests/elitist_selector_testing 0 ./src/GA_testing/Population_selector/elitist_selector/test1_s1 ./src/GA_testing/Population_selector/elitist_selector/test1_s2 ./src/GA_testing/Population_selector/elitist_selector/test1_s3 ./src/GA_testing/Population_selector/elitist_selector/test1_s4"
)

echo "== Ejecutando tests =="

# ejecutar cada comando
for CMD in "${COMMANDS[@]}"; do
    echo ""
    # ejecutar el comando
    eval $CMD
done

echo ""
echo "== Todos los tests han finalizado =="