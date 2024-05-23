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