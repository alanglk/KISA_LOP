#!/bin/bash

COMMANDS=(
    "./build/GA_main ../instances/N-r100a2 100 99999999 33 0.7 0.4 ./results/N-r100a2_pob100.txt 2 50000"
    "./build/GA_main ../instances/N-r100a2 150 99999999 50 0.7 0.4 ./results/N-r100a2_pob150.txt 2 50000"
    "./build/GA_main ../instances/N-r100a2 200 99999999 73 0.7 0.4 ./results/N-r100a2_pob200.txt 2 50000"
    "./build/GA_main ../instances/N-r100b2 100 99999999 33 0.7 0.4 ./results/N-r100b2_pob100.txt 2 50000"
    "./build/GA_main ../instances/N-r100b2 150 99999999 50 0.7 0.4 ./results/N-r100b2_pob150.txt 2 50000"
    "./build/GA_main ../instances/N-r100b2 200 99999999 73 0.7 0.4 ./results/N-r100b2_pob200.txt 2 50000"
    "./build/GA_main ../instances/N-r150a0 150 99999999 50 0.7 0.4 ./results/N-r150a0_pob150.txt 2 50000"
    "./build/GA_main ../instances/N-r150a0 200 99999999 73 0.7 0.4 ./results/N-r150a0_pob200.txt 2 50000"
    "./build/GA_main ../instances/N-r150a0 300 99999999 100 0.7 0.4 ./results/N-r150a0_pob300.txt 2 50000"
    "./build/GA_main ../instances/N-r150c0 150 99999999 50 0.7 0.4 ./results/N-r150c0_pob150.txt 2 50000"
    "./build/GA_main ../instances/N-r150c0 200 99999999 73 0.7 0.4 ./results/N-r150c0_pob200.txt 2 50000"
    "./build/GA_main ../instances/N-r150c0 300 99999999 100 0.7 0.4 ./results/N-r150c0_pob300.txt 2 50000"
    "./build/GA_main ../instances/N-r200a0 200 99999999 73 0.7 0.4 ./results/N-r200a0_pob200.txt 2 50000"
    "./build/GA_main ../instances/N-r200a0 300 99999999 100 0.7 0.4 ./results/N-r200a0_pob300.txt 2 50000"
    "./build/GA_main ../instances/N-r200a0 400 99999999 133 0.7 0.4 ./results/N-r200a0_pob400.txt 2 50000"
    "./build/GA_main ../instances/N-r200c0 200 99999999 73 0.7 0.4 ./results/N-r200c0_pob200.txt 2 50000"
    "./build/GA_main ../instances/N-r200c0 300 99999999 100 0.7 0.4 ./results/N-r200c0_pob300.txt 2 50000"
    "./build/GA_main ../instances/N-r200c0 400 99999999 133 0.7 0.4 ./results/N-r200c0_pob400.txt 2 50000"
    "./build/GA_main ../instances/N-r250a0 250 99999999 83 0.7 0.4 ./results/N-r250a0_pob250.txt 2 50000"
    "./build/GA_main ../instances/N-r250a0 376 99999999 125 0.7 0.4 ./results/N-r250a0_pob375.txt 2 50000"
    "./build/GA_main ../instances/N-r250a0 500 99999999 166 0.7 0.4 ./results/N-r250a0_pob500.txt 2 50000"
    "./build/GA_main ../instances/N-r250c0 250 99999999 83 0.7 0.4 ./results/N-r250c0_pob250.txt 2 50000"
    "./build/GA_main ../instances/N-r250c0 376 99999999 125 0.7 0.4 ./results/N-r250c0_pob375.txt 2 50000"
    "./build/GA_main ../instances/N-r250c0 500 99999999 166 0.7 0.4 ./results/N-r250c0_pob500.txt 2 50000"
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