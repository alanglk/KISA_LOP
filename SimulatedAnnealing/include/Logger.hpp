#ifndef LOGGER_H
#define LOGGER_H

#include "LOP.hpp"

using namespace std;

// Loggear ejecución y cargar parámetros de Simulated Annealing
class Logger {
private:
    string filename;
    stringstream log_buffer;
    const string EXECUTION_HEADER = "========================== Simulated Annealing Execution ==========================";
    Config config;

public:
    explicit Logger(const string& filename) : filename(filename) {}

    bool loadConfig();
    void log(const string& message);
    void logParameters();
    void saveExecutionLog();
    Config getConfig();

    // Sobrecarga del operador << para loguear mensajes
    template <typename T>
    Logger& operator<<(const T &msg) {
        log_buffer << msg;
        return *this;
    }

    // Sobrecarga especial para manipuladores de flujo (ej. std::endl)
    Logger& operator<<(std::ostream& (*manip)(std::ostream&)) {
        log_buffer << manip;
        return *this;
    }  
    
};



#endif