import sys
import os
import struct

CMDS = {
    "NOP": 0,
    "CPUINFO": 1,
    "READ": 10,
    "WRITE": 11,
    "LOAD": 20,
    "STORE": 21,
    "ADD": 30,
    "SUB": 31,
    "DIVIDE": 32,
    "MUL": 33,
    "JUMP" : 40,
    "JNEG": 41,
    "JZ": 42,
    "HALT": 43,
    "NOT": 51,
    "AND": 52,
    "OR": 53,
    "XOR": 54,
    "JNS": 55,
    "JC": 56,
    "JNC": 57,
    "JP": 58,
    "JNP": 59,
    "CHL": 60,
    "SHR": 61,
    "RCL": 62,
    "RCR": 63,
    "NEG": 64,
    "ADDC": 65,
    "SUBC": 66,
    "LOGLC": 67,
    "LOGRC": 68,
    "RCCL": 69,
    "RCCR": 70,
    "MOVA": 71,
    "MOVR": 72,
    "MOVCA": 73,
    "MOVCR": 74,
    "ADDC": 75,
    "SUBC": 76
}

 
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

def serialize_string_to_array(input_string):
    words = input_string.split()
    words.extend([''] * (5 - len(words)))
    return words


def encode_string(input_string):
    if len(input_string) != 5:
        raise ValueError("Input string must be 5 characters long")

    sign, hex_byte1, hex_byte2 = input_string[0], input_string[1:3], input_string[3:5]

    if int(hex_byte1, 16) > 0x7F or int(hex_byte2, 16) > 0x7F:
        raise ValueError("Hex bytes cannot be larger than 0x7F")

    # Initialize the output value
    output_value = 0

    # If the sign is negative, set bit 15 high
    if sign == '-':
        output_value |= 1 << 14

    # Map hex_byte1 to bits 14-7
    output_value |= int(hex_byte1, 16) << 7

    # Map hex_byte2 to bits 6-0
    output_value |= int(hex_byte2, 16)

    return output_value

def modify_number_in_array(index_str, operation_str, operand_str, array_handle):
    # Convert arguments to integers
    index = int(index_str)
    

    if index < 0 or index >= 128:
        raise ValueError("Index out of bounds. Must be between 0 and 127.")
    
    # Get the current value at the specified index
    current_value = array_handle[index]
    
    # Perform the operation
    if operation_str == "=":
        current_value = encode_string(operand_str)
        array_handle[index] = current_value
        return
    
    operand = int(operand_str)
    # Check if operand is larger than 7 bits
    if operand & (1 << 7):
        raise ValueError("Operand is larger than 7 bits.")
    # Set bit 15 high
    
    
    # Shift operation to uppercase and look it up in CMDS
    operation_upper = operation_str.upper()
    cmd = CMDS.get(operation_upper, None)
    if cmd is None:
        raise ValueError(f"Unknown operation: {operation_upper}")
    
    current_value |= 0 << 14
    current_value |= cmd << 7
    current_value |= operand
    
    # Update the value in the array
    array_handle[index] = current_value

def main():
    if not (sys.argv[1] and sys.argv[2]):
        print("Не указаны входной/выходной файлы.\n")
        return

    input_file_name = sys.argv[1]
    output_file_name = sys.argv[2]
    in_pre, in_ext = os.path.splitext(input_file_name)
    out_pre, out_ext = os.path.splitext(output_file_name)

    if (in_ext != '.sa'):
        print("Некорректное расширение входного файла.")
        return

    if (out_ext != '.o'):
        print("Некорректное расширение выходного файла.")
        return

    # Example usage
    lines = read_file_into_array(input_file_name)

    array = [0] * 128  # Initialize an array of 128 zeros

    for line in lines:
        cmd = serialize_string_to_array(line)
        modify_number_in_array(cmd[0], cmd[1], cmd[2], array)
   
    with open(output_file_name, 'wb') as f:
        for num in array:
            f.write(struct.pack('i', num))


if __name__ == '__main__':
    # execute only if run as the entry point into the program
    main()
    