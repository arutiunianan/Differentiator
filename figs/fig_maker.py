import numpy as np
import matplotlib.pyplot as plt
from pathlib import Path
import sympy as sp
import sys
 
if __name__ == '__main__':

    f1 = open(sys.argv[1], 'r') #'in.txt'
    f2 = open(sys.argv[2], 'r') #'out.txt'

    x = sp.symbols('x')

    expr_str = f1.read()
    expr = sp.sympify(expr_str)

    expr_str1 = f2.read()
    expr1 = sp.sympify(expr_str1)

    my_function = sp.lambdify(x, expr, 'numpy')
    x_values = np.linspace(-10, 10, 100)
    y_values = my_function(x_values)
    plt.plot(x_values, y_values, label=expr_str)

    my_function = sp.lambdify(x, expr1, 'numpy')
    y_values1 = my_function(x_values)
    plt.plot(x_values, y_values1, label=expr_str1)

    plt.title('Ani Graph<3')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.legend()
    plt.grid(True)
    plt.savefig('figs/fig' + sys.argv[3] + '.png',)

    #plt.show()