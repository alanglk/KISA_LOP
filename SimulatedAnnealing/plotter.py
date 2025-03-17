import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import math

import re
import os
import glob

class SimulatedAnnealingParser:
    def __init__(self, execution_name:str, file_path:str):
        self.execution_name = execution_name
        self.file_path = file_path
        self.parameters = {
            "max_iter": None,
            "max_chain": None,
            "max_stagnation": None,
            "T_0": None,
            "beta": None,
            "update": None,
            "neigh_type": None,
            "N_random_walks": None,
            "N_random_walk_perturbations": None,
            "acceptance_rate": None,
            "use_random_walk": False
        }
        self.iterations = []
        self.iteration_headers = set()

        self.execution_time_ns = float("nan")
        self.bounds_min = float("nan")
        self.bounds_max = float("nan")
    
    def params_to_str(self) -> str:
        string = ""
        for k, v in self.parameters.items():
            string += f"{k}:{v}\n"
        return string
    
    def set_benchmark_info(self, bounds_min:float, bounds_max:float):
        self.bounds_min = bounds_min
        self.bounds_max = bounds_max

    def parse_file(self):
        with open(self.file_path, 'r', encoding='utf-8') as file:
            lines = file.readlines()

        parsing_parameters = False
        parsing_iterations = False
        use_random_walk = False
        
        for line in lines:
            line = line.strip()
            if not line:
                continue

            if "Parameters for Simulated Annealing Algorithm" in line:
                parsing_parameters = True
                parsing_iterations = False
                continue
            elif "Simulated Annealing Algorithm Execution" in line:
                parsing_iterations = True
                parsing_parameters = False
                self.extract_execution_time(line)
                continue

            if parsing_parameters:
                if "[Random Walk]" in line:
                    use_random_walk = True
                self.parse_parameter(line, use_random_walk)
            elif parsing_iterations:
                iteration_data = self.parse_iteration(line)
                if iteration_data:
                    self.iterations.append(iteration_data)
                    self.iteration_headers.update(iteration_data.keys())
    def parse_parameter(self, line, use_random_walk):
        # Eliminar cualquier comentario dentro de [ ]
        line = re.sub(r'\[.*?\]', '', line).strip()

        # Expresión para capturar parámetros en el formato: "Nombre: Valor"
        match = re.match(r'^(?:Random Walk )?(.+?):\s*(.+)$', line)
        if match:
            key, value = match.groups()
            key = key.strip()
            value = value.strip()

            # Ajustar los nombres para coincidir con la estructura Config
            key_mapping = {
                "Number of iterations": "max_iter",
                "Maximum chain size": "max_chain",
                "Maximum Stagnation": "max_stagnation",
                "Initial temperature (T_0)": "T_0",
                "Beta": "beta",
                "Update type": "update",
                "Neigborhood": "neigh_type",
                "Number of random walks": "N_random_walks",
                "Number of perturbations per random walk": "N_random_walk_perturbations",
                "Acceptance rate": "acceptance_rate"
            }

            if key in key_mapping:
                param_key = key_mapping[key]
                if param_key in self.parameters:  # Solo guardar si está en los parámetros definidos
                    if self.is_number(value):  # Convertir números
                        self.parameters[param_key] = float(value) if "." in value else int(value)
                    else:
                        self.parameters[param_key] = value

            # Detectar si se usa random walk
            if "use_random_walk" in key.lower():
                self.parameters["use_random_walk"] = True

    def parse_iteration(self, line):
        # Expresión regular para capturar el número de iteración y los campos clave-valor
        match = re.match(r'Iteration:\s*(\d+)\s*(.*)', line)
        if match:
            iteration_num = int(match.group(1))  # Número de la iteración
            fields = match.group(2)  # Los campos después de "Iteration: <número>"
            
            # Diccionario para almacenar los datos de la iteración
            iteration_data = {'Iteration': iteration_num}
            
            # Encontrar todos los pares clave:valor en el resto de la línea
            key_value_pairs = re.findall(r'(\w+):\s*([\S]+)', fields)
            
            for key, value in key_value_pairs:
                # Manejar el caso de NaN (podría ser "NaN", "nan", "N/A", etc.)
                if value.lower() in ['nan', 'n/a', 'na']:
                    value = float('nan')
                else:
                    # Convertimos a float si el valor es un número
                    try:
                        value = float(value)
                    except ValueError:
                        pass  # Si no es un número, mantenemos el valor como string
                iteration_data[key] = value

            return iteration_data
        return None
    
    def extract_execution_time(self, line):
        # Print the line to debug
        match = re.search(r'Simulated Annealing Algorithm Execution took\s+(\d+)\s+nanoseconds', line, re.IGNORECASE)
        if match:
            self.execution_time_ns = int(match.group(1))
        
    @staticmethod
    def is_number(value):
        try:
            float(value)
            return True
        except ValueError:
            return False

    def to_dataframe(self):
        df = pd.DataFrame(self.iterations)
        columns = ['Iteration'] + sorted(self.iteration_headers - {'Iteration'})
        df = df[columns] if not df.empty else df
        return df

    def get_parameters(self):
        return self.parameters


def get_prob_name(string):
    return re.sub(r'^N-(r\d+a\d+)(_.*)?$', r'\1', string)

def main(data_path, benchmark_path, select_names=[], ignore_names=[], show_benchmark = True):
    # 1. Leer todos los archivos de benchmark_path y generar un pandas dataset común
    benchmark_files = glob.glob(os.path.join(benchmark_path, "*.csv"))
    benchmark_df_list = []
    for benchmark_file in benchmark_files:
        benchmark_df = pd.read_csv(benchmark_file)
        benchmark_df_list.append(benchmark_df)
    benchmarks_df = pd.concat(benchmark_df_list, ignore_index=True)

    # 2. Listar todos los archivos de data_path y actualizar select_names 
    data_files = glob.glob(os.path.join(data_path, "*.out"))
    data_names = [os.path.basename(f).replace(".out", "") for f in data_files]    
    if not select_names:
        select_names = data_names
    else:
        select_names = [name for name in select_names if name in data_names]

    
    # 3. Parsear las ejecuciones seleccionadas con 
    executions = {}
    for exec_name in select_names:
        file_path = os.path.join(data_path, f"{exec_name}.out")
        execution = SimulatedAnnealingParser(exec_name, file_path)
        execution.parse_file()
        
        # 4. Relacionar cada ejecución parseada con su benchmark
        benchmark_name = get_prob_name(exec_name) 
        benchmark_row = benchmarks_df[benchmarks_df["Problem"] == benchmark_name]
        if not benchmark_row.empty:
            benchmark = benchmark_row.iloc[0]
            bounds = benchmark[['Bounds_min', 'Bounds_max']].to_dict()
            execution.set_benchmark_info(bounds['Bounds_min'], bounds['Bounds_max'])
        else:
            print(f"No se encontró benchmark para la ejecución {exec_name}.")
        executions.update({exec_name: execution})
    print('\n')

    # 5. Graficar
    print(f"Showing executions: {executions.keys()}\n")
    for exec_name, execution in executions.items():
        df = execution.to_dataframe()
        exec_time_ns    = execution.execution_time_ns
        exec_time_s     = exec_time_ns * 1e-9
        exec_mean_dt_ns = np.mean(df['dt'])
        exec_mean_dt_s  = exec_mean_dt_ns * 1e-9
        exec_params_str = execution.params_to_str()
        exec_bounds_min = execution.bounds_min
        exec_bounds_max = execution.bounds_max
        exec_ofv        = df['OFV'].iloc[-1]
        exec_iters      = df['Iteration'].iloc[-1]

        exec_prob       = get_prob_name(exec_name)
        exec_t0         = execution.parameters['T_0']
        exec_update     = execution.parameters['update'] +1 # +1 because in the document it starts from 1
        exec_beta       = execution.parameters['beta']
        exec_ch         = execution.parameters['max_chain']
        exec_st         = execution.parameters['max_stagnation']
        # Show execution
        print(f"Simulated Annealing Algorithm Execution: {exec_name}")
        print(f"------------------------------------------------")
        print(exec_params_str)
        print(f"Benchmark bounds: [{exec_bounds_min}, {exec_bounds_max}]")
        print(f"Execution time: {exec_time_ns}ns or {exec_time_s}s")
        print(f"Execution mean delta time per iteration: {exec_mean_dt_ns:.5f}ns or {exec_mean_dt_s:.5f}s")
        print(f"Execution iterations: {exec_iters}")
        print(f"Execution Objective Function Value (OFV): {exec_ofv}")
        print(f"Latex table entry:\t N-{exec_prob} & {exec_bounds_min} & {exec_ofv} & {exec_t0} & {exec_update} & {exec_beta} & {exec_ch} & {exec_st} & {exec_iters} & {exec_time_s}")

        fig, axes = plt.subplots(1, 2, figsize=(12, 6))
        fig.tight_layout()
        axes[0].plot(df['Iteration'], df['OFV'], c = "blue", label = f"{exec_name}")

        if show_benchmark:
            if not math.isnan(exec_bounds_min):
                axes[0].axhline(y = exec_bounds_min, c = "red", label="benchmark bound")
            if not math.isnan(exec_bounds_max):
                axes[0].axhline(y = exec_bounds_max, c = "red")
        
        axes[0].set_title(f"Objective Function Value Evolution of {exec_name}")
        axes[0].set_xlabel("Iteration")
        axes[0].set_ylabel("OFV")
        axes[0].legend()

        axes[1].plot(df['Iteration'], df['T_k'], c = "red", label="Temperature")
        axes[1].set_title(f"Temperature Evolution of {exec_name}")
        axes[1].set_xlabel("Iteration")
        axes[1].set_ylabel("Temperature")

        plt.show()
        print()

if __name__ == "__main__":
    # Carpeta que guarda las ejecuciones -> nombre_problema.out
    data_path = "./data/output"
    
    benchmark_path = "../Best_LOP-Like" 
    # carpeta con varios archivos .csv que tienen los mejores resultados de cada ejecución
    # Se utiliza como benchmark.
    # Cada .csv tiene esta estructura: Problem,Bounds_min,Bounds_max
    # Lo que nos interesa es relacionar cada archivo de data_path con su benchmark. Para 
    # relacionar el benchmark con la ejecución, hay que buscar el nombre de la ejecución en
    # cada csv
    
    
    select_names = []
    ignore_names = []
    show_benchmark = True
    
    # parse_names indica qué problemas se van a utilizar. si es [] se utilizan todos por defecto.
    # ignore_names indica qué problemas se van a ignorar. Si es [] no se ignora ninguno

    main(data_path, benchmark_path, select_names=select_names, ignore_names=ignore_names, show_benchmark=show_benchmark)

