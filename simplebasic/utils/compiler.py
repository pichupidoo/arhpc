from utils.RPN import toRPN

class SimpleCompiler:

    tokenized_lines = []    # Массив токенизированных значащих строк.
    variables = dict()      # Словрарь динамических переменных и начальных значения
    constants = []          # Массив констант
    assembly = []           # Массив комманд Simple Assembler (номер строки:команда)
    jump_address = dict() # номер строки : индекс в assembly
    is_accum_clear = True  # для rpn_asm 

    def __init__(self, lines) -> None:
        prev_line_number = -1
        for line in lines: 
             # Разбить строку на токены
            tokenized_line = line.split() 
            # Проверить возрастание номера строки
            if prev_line_number < int(tokenized_line[0]):
                prev_line_number = int(tokenized_line[0])
            else: raise Exception(f"Номер строки {int(tokenized_line[0])} меньше предествующего.")
            # Не добавлять в массив обрабатываемых строк комментарии
            if tokenized_line[1] != "REM":
                self.tokenized_lines.append(tokenized_line)

    # Проверить, является ли токен переменной (единичной заглавной буквой)
    def is_variable(self, token):
        return (len(token) == 1 and token.isupper())
    
    goto_skip = False
    # Обнаружить все переменные и константы.
    def get_all_vars(self, tokenized_lines):
        for tokenized_line in tokenized_lines:
            for token in tokenized_line[1:]: # отбросить номер строки

                # Костыль: номера строк для джампа не должны попадать в массив констант
                if token == "GOTO":
                    self.goto_skip = True
                    continue
                if self.goto_skip:
                    self.goto_skip = False
                    continue

                if (self.is_variable(token)):
                    self.variables.update({token:None})
                elif token.isnumeric() and token not in self.constants:
                    self.constants.append(token)

    # Адрес переменной: 1 + индекс переменной в массиве variables 
    # Адрес константы 1 + длина массива переменных + индекс в константах
    # (первая ячейка память программы всегда JUMP в область кода)
    def address_of(self, var):
        if self.is_variable(var):
            # Грязный хак: получить массив ключей и найти индекс в нем
            return 1 + list(self.variables.keys()).index(var)
        if var.isnumeric():
            return 1 + len(self.variables) + self.constants.index(var)

    # Транслировать математические операции в команды SA.
    def rpn_asm(self, operands, sign):
        codebuf = []  # временный буфер команд
        if not operands:
            raise ValueError("Invalid expression")
        operand1 = operands.pop()
        operand2 = None

        if self.is_accum_clear:
            if not operands:
                raise ValueError("Invalid expression")
            operand2 = operands.pop()
            self.is_accum_clear = False
            codebuf.append(["LOAD", self.address_of(operand2)])

        addr = self.address_of(operand1)
        if   sign == '+':
            codebuf.append(["ADD", addr])
        elif sign == '-':
            codebuf.append(["SUB", addr])
        elif sign == '*':
            codebuf.append(["MUL", addr])
        elif sign == '/':
            codebuf.append(["DIVIDE", addr])
        else:
            raise ValueError(f"Invalid operator {sign}")
        return codebuf
        
    def if_eval(self, expr, conditional):
        cbuf=[] # буфер для ассемблированного условия
        op1 = expr[0] # операнд 1
        op2 = expr[2] # =|= 2
        # знак
        # прыжки через подусловное выражение
        #   осуществляются на (1+длину переменных+длину констант+длину assembly+длина тела) + len(cbuf)
        #   (а cbuf всегда 2 на момент вызова прыжка)
        jump_len = 1 + len(self.variables) + len(self.constants) + len(self.assembly) + len(conditional) + 2
        if expr[1] == ">":  
            cbuf.append(["LOAD", self.address_of(op1)])
            cbuf.append(["SUB", self.address_of(op2)])    
            cbuf.append(["JNEG", jump_len+2])
        elif expr[1] == "<":
            cbuf.append(["LOAD", self.address_of(op2)])
            cbuf.append(["SUB", self.address_of(op1)])    
            cbuf.append(["JNEG", jump_len+2])
        elif expr[1] == "=":
            cbuf.append(["LOAD", self.address_of(op2)])
            cbuf.append(["SUB", self.address_of(op1)])    
            cbuf.append(["JNEG", jump_len+2])
            cbuf.append(["JNS", jump_len+2])
        for ops in conditional:
            cbuf.append(ops)
        return cbuf
    
    def assemble_command(self, tokens):
        cbuf = []
        if (tokens[0] == "LET"):
                assert self.is_variable(tokens[1])  
                assert tokens[2] == "="
                assert len(tokens[3:]) >= 0
                
                self.is_accum_clear = True
                # Выражение после знака '=' - только один токен
                if (len(tokens[3:]) == 1):
                    assert self.is_variable(tokens[3]) or tokens[3].isnumeric()
                    # Если переменная ничем не инициализирована, присвоение константы изменяет начальное значение
                    if self.variables.get(tokens[1]) == None and tokens[3].isnumeric():
                        self.variables[tokens[1]] = int(tokens[3])
                    # Переменной присваивают значение другой
                    elif self.is_variable(tokens[3]):
                        cbuf.append("LOAD", self.address_of(tokens[4]))
                else:
                    # Превратить всё по правую сторону от '=' в RPN-выражение
                    operand_stack = []  # Стек для чисел, над которыми проводится действие
                    rpn_tokens = toRPN(tokens[3:])
                    
                    # Посимвольно преобразовать RPN-выражение выражение в команды
                    for rpn_token in rpn_tokens:
                        
                        if (rpn_token.isupper() or rpn_token.isnumeric()): 
                            # Если число/переменная - добавить в стек операндов
                            operand_stack.append(rpn_token)
                        else:
                            # Если знак - произвести операцию
                            ops = self.rpn_asm(operand_stack, rpn_token)
                            for op in ops:
                                cbuf.append(op)
                    cbuf.append(["STORE", self.address_of(tokens[1])])

        elif (tokens[0] == "INPUT"):   
            assert self.is_variable(tokens[1])
            cbuf.append(["READ", self.address_of(tokens[1])])

        elif (tokens[0] == "IF"):
            assert len(tokens[1:4]) == 3
            assert len(tokens[4:]) >= 1
            
            # Ассемблиролвать выражение, выполняемое условно
            conditional = self.assemble_command(tokens[4:])

            for op in self.if_eval(tokens[1:4], conditional):
                cbuf.append(op)
            
                                  
        elif (tokens[0] == "GOTO"): 
            cbuf.append(["GOTO", tokens[1]])

        elif (tokens[0] in ["OUTPUT", "PRINT"]):
            assert self.is_variable(tokens[1])
            cbuf.append(["WRITE", self.address_of(tokens[1])])

        elif (tokens[0] == "END"):
            cbuf.append(["HALT", "00"])
        else:
            raise SyntaxError(" ".join(tokens) + f" -- Invalid token: {tokens[0]}")
        return cbuf
    
    # Выполнить построчное ассемблирование
    def assemble(self):
        self.get_all_vars(self.tokenized_lines)
        for tokens in self.tokenized_lines:
            self.jump_address[tokens[0]] = len(self.assembly)
            ops = self.assemble_command(tokens[1:])
            for op in ops:
                self.assembly.append(op)

        # Соотнести номера строк с командами goto 
        for asm in self.assembly:
            if asm[0] == "GOTO":
                asm[0] = "JUMP"
                asm[1] = 1+len(self.variables)+len(self.constants)+self.jump_address.get(asm[1])

    def int_to_custom_string(self, value):
    # Step 1: Determine the sign
        sign = '-' if value < 0 else '+'
        
        # Step 2 & 3: Convert bits 14-7 and 6-0 to hexadecimal
        # First, ensure the value is treated as a positive number for bit manipulation
        unsigned_value = abs(value)
        
        # Extract bits 14-7 and convert to hex
        bits_147 = (unsigned_value >> 7) & 0x3F  # Shift right by 7 and mask to get bits 14-7
        
        # Extract bits 6-0 and convert to hex
        bits_60 = unsigned_value & 0x3F  # Mask to get bits 6-0
        
        # Convert to hexadecimal and pad with zeros if necessary
        hex_147 = format(bits_147, '02X')
        hex_60 = format(bits_60, '02X')
        
        # Step 4: Combine components into a single string
        result = f"{sign}{hex_147}{hex_60}"
        
        return result


    def output(self):
        print(self.variables)
        print(self.constants)
        strs = []
        strs.append(f'0 JUMP {1+len(self.variables) + len(self.constants)}')
        for i in range(len(self.variables)):
            value = self.variables.get(list(self.variables.keys())[i])
            if value != None:
                strs.append(f'{i+1} = {self.int_to_custom_string(value)}')
            else:
                strs.append(f'{i+1} = +0000')
        for i in range(len(self.constants)):
            value = int(self.constants[i])
            strs.append(f'{i+1+len(self.variables)} = +{value:04}')
        for i in range(len(self.assembly)):
            value = self.assembly[i]

            strs.append(f'{i+1+len(self.variables)+len(self.constants)}'+ f' {" ".join(map(str, value))}')
        return strs