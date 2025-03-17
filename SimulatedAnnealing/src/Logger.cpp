#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <algorithm>

#include "LOP.hpp"
#include "Logger.hpp"

using namespace std;

bool Logger::loadConfig(){
    ifstream file(filename);
    if (!file){
        cerr << "Error: No se pudo abrir el archivo de configuración.\n";
        return false;
    }

    string line;
    unordered_map<string, string> param_map;

    while (getline(file, line)){
        size_t pos = line.find('=');
        if (pos != string::npos)
        {
            string key = line.substr(0, pos);
            string value = line.substr(pos + 1);

            // Eliminar espacios en blanco alrededor del key y value
            key.erase(remove_if(key.begin(), key.end(), ::isspace), key.end());
            value.erase(remove_if(value.begin(), value.end(), ::isspace), value.end());

            param_map[key] = value;
        }
    }
    file.close();

    // Convertir parámetros desde strings
    config.file_path = param_map["file_path"];
    config.max_chain = stoi(param_map["max_chain"]);
    config.max_iter = stoi(param_map["max_iter"]);
    config.max_stagnation = stoi(param_map["max_stagnation"]);
    config.T_0 = stod(param_map["T_0"]);
    config.beta = stod(param_map["beta"]);

    // Conversión segura de update
    string update_str = param_map["update"];
    if (update_str == "GEOMETRIC"){
        config.update = GEOMETRIC;
    }
    else if (update_str == "LINEAR"){
        config.update = LINEAR;
    }
    else if (update_str == "LOGARITHMIC"){
        config.update = LOGARITHMIC;
    }
    else{
        cerr << "Error: Valor inválido para 'update'. Se usará GEOMETRIC por defecto.\n";
        config.update = GEOMETRIC;
    }

    // Conversión segura de neigh_type
    string neigh_str = param_map["neigh_type"];
    if (neigh_str == "SWAP"){
        config.neigh_type = SWAP;
    }
    else if (neigh_str == "TWO_OPT"){
        config.neigh_type = TWO_OPT;
    }
    else{
        cerr << "Error: Valor inválido para 'neigh_type'. Se usará SWAP por defecto.\n";
        config.neigh_type = SWAP;
    }

    // Conversión de booleano
    config.use_random_walk = (param_map["use_random_walk"] == "true");

    config.N_random_walks = stoi(param_map["N_random_walks"]);
    config.N_random_walk_perturbations = stoi(param_map["N_random_walk_perturbations"]);
    config.acceptance_rate = stod(param_map["acceptance_rate"]);

    return true;
}

void Logger::log(const string &message){
    log_buffer << message << endl;
}

void Logger::logParameters(){

    // update to string
    string update_str;
    switch (config.update){
    case GEOMETRIC:
        update_str = "GEOMETRIC";
        break;
    case LINEAR:
        update_str = "LINEAR";
        break;
    case LOGARITHMIC:
        update_str = "LOGARITHMIC";
        break;
    }

    // neighborhood function type to string
    string neighborhood_str;
    switch (config.neigh_type){
    case SWAP:
        neighborhood_str = "SWAP";
        break;
    case TWO_OPT:
        neighborhood_str = "TWO_OPT";
        break;
    }

    // Log parameters
    *this << "Parameters for Simulated Annealing Algorithm:";
    *this << "file_path = " + config.file_path;
    *this << "max_chain = " + to_string(config.max_chain) + "     // Fixed neighborhood exploration size";
    *this << "max_iter = " + to_string(config.max_iter) + "     // Max iterations";
    *this << "max_stagnation = " + to_string(config.max_stagnation) + "     // -1 -> No limit";
    *this << "T_0 = " + to_string(config.T_0) + "     // Fixed initial temp";
    *this << "beta = " + to_string(config.beta) + "     // Cooling factor";
    *this << "update = " + update_str + "     // Cooling strategy";
    *this << "neigh_type = " + neighborhood_str + "     // Neighborhood type";
    *this << "use_random_walk = " + string(config.use_random_walk ? "true" : "false") + "     // Initial exploration?";
    *this << "N_random_walks = " + to_string(config.N_random_walks);
    *this << "N_random_walk_perturbations = " + to_string(config.N_random_walk_perturbations);
    *this << "acceptance_rate = " + to_string(config.acceptance_rate);
    *this << "\n" + EXECUTION_HEADER;
}

void Logger::saveExecutionLog(){
    ifstream file_in(filename);
    stringstream new_content;
    string line;
    bool execution_found = false;

    // Leer el archivo y eliminar la ejecución anterior
    while (getline(file_in, line)){
        if (line == EXECUTION_HEADER)
        {
            execution_found = true;
            break;
        }
        new_content << line << endl;
    }
    file_in.close();

    // Agregar nueva ejecución
    new_content << log_buffer.str();

    // Escribir el archivo actualizado
    ofstream file_out(filename);
    if (!file_out){
        cerr << "Error: No se pudo escribir el archivo de configuración.\n";
        return;
    }
    file_out << new_content.str();
    file_out.close();
}

Config Logger::getConfig() { return config; }