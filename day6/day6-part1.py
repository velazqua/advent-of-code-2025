import sys
lines = []
for line in sys.stdin:
    line = [x for x in line.split()]
    lines.append(line)    
result = 0
for col in range(len(lines[0])):
    op = lines[4][col]
    col_result = 0 if op == '+' else 1
    for row in range(4):
        val = int(lines[row][col])
        if op == '+':
            col_result += val
        else:
            col_result *= val
    result += col_result
print(result)

        