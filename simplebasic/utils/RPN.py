is_accum_clear = False

def toRPN(infix_expression):
    precedence = {'+':1, '-':1, '*':2, '/':2, '^':3}
    output = []
    stack = []

    for token in infix_expression:
        if token in precedence:
            while stack and stack[-1] in precedence and precedence[token] <= precedence[stack[-1]]:
                output.append(stack.pop())
            stack.append(token)
        elif token == '(':
            stack.append(token)
        elif token == ')':
            while stack and stack[-1]!= '(':
                output.append(stack.pop())
            stack.pop()  # Remove the opening parenthesis
        else:
            output.append((token))

    while stack:
        output.append(stack.pop())

    return map(str, output)