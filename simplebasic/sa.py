import sys
import os
from utils.io import *
from utils.compiler import *

def read_file_into_array(file_path):

    lines = []
    try:
        with open(file_path, 'r') as file:
            for line in file:
                lines.append(line)
    except FileNotFoundError:
        print(f"The file {file_path} does not exist.")
    except PermissionError:
        print(f"Permission denied to open the file {file_path}.")
    except Exception as e:
        print(f"An unexpected error occurred: {e}")
    return lines

def main():
    # Ввод из файла 
    if not (sys.argv[1] and sys.argv[2]):
        raise ValueError("Пропущены аргументы.")
    if (not os.path.isfile(sys.argv[1])):
        raise FileNotFoundError("Указан несуществующий входной файл.")
    lines = read_file_into_array(sys.argv[1])
    
     # utils/compiler.py
    compiler = SimpleCompiler(lines)
    compiler.assemble()
    strs = compiler.output()
    with open(sys.argv[2], 'w') as f:
        f.writelines(line + '\n' for line in strs)

if __name__ == '__main__':
    # execute only if run as the entry point into the program
    main()