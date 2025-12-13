import sys
from scipy.optimize import linprog

total = 0
for line in sys.stdin:
    tokens = [x for x in line.split()]
    lights = tokens[0]
    str_buttons = tokens[1:-1]
    buttons = []
    for btn in str_buttons:
        btn_lights = []
        sep_buttons = [int(x) for x in btn[1:-1].split(',')]
        for i in range(len(sep_buttons)):
            btn_lights.append(sep_buttons[i])
        buttons.append(btn_lights)
    joltage = tokens[-1]
    num_variables = len(buttons)
    num_equations = len(lights) - 2
    obj_coeffs = [1] * num_variables
    lhs_eq = []
    for num in range(num_equations):
        coeffs = [0] * num_variables
        for i in range(num_variables):
            if num in buttons[i]:
                coeffs[i] = 1
        lhs_eq.append(coeffs)
    rhs_eq = [int(x) for x in joltage[1:-1].split(',')]

    bounds = [(0, sum(rhs_eq)) for _ in range(num_variables)]
    print("Solving linear program...")
    print("buttons:", buttons)
    print("joltage:", rhs_eq)
    print("lhs_eq:", lhs_eq)
    print("rhs_eq:", rhs_eq)
    print("bounds:", bounds)
    opt = linprog(c=obj_coeffs, A_eq=lhs_eq, b_eq=rhs_eq, bounds=bounds, method='highs', integrality=obj_coeffs)
    print(f"Minimum presses: {int(round(opt.fun))}")
    print("Button presses:", opt.x)
    total += int(round(opt.fun))

    # Verify that the solution found works.
    test_lights = [0] * num_equations
    for i in range(num_variables):
        presses = int(round(opt.x[i]))
        for light_idx in buttons[i]:
            test_lights[light_idx] += presses
    assert test_lights == rhs_eq, f"Verification failed: expected {rhs_eq}, got {test_lights}"
print(f"Total presses: {total}")

        