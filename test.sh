#!/bin/bash

COMMANDS=(
    "./build/tests/swap_testing ./src/GA_testing/Mutation/test1_input ./src/GA_testing/Mutation/test1_output  ./src/GA_testing/Mutation/test1_output2"
    "./build/tests/order_crossover_testing 0 ./src/GA_testing/Crossover/test1_parent1 ./src/GA_testing/Crossover/test1_parent2 ./src/GA_testing/Crossover/test1_expected_child"
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