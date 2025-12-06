import sys
lines = []
for line in sys.stdin:
    lines.append(line)
operators = [x for x in lines[-1] if x in ['+', '*']]
lines = lines[:-1]
#print(lines)
#print(operators)
result = 0
numbers = []
op_index = 0
for col in range(len(lines[0])):
    # Generate number.
    num = ""
    for row in range(len(lines)):
        num += lines[row][col]
    num = num.rstrip()
    # If no number is generated, then perform the operation.
    if len(num) > 0:
        numbers.append(num)
    else:
        #print(numbers)
        op = operators[op_index]
        col_result = 0 if op == '+' else 1
        op_index += 1
        for num in numbers:
            val = int(num)
            if op == '+':
                col_result += val
            else:
                col_result *= val
        numbers = []
        result += col_result
    #print("Number: ", num)
print(result)

        