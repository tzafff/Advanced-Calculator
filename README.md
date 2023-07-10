# Advanced Calculator - Mini C

This repository contains the source code for an advanced calculator implemented in Mini C. The calculator provides a set of mathematical operations and expressions, as well as basic C programming functions.

## Repository Structure

The repository has the following structure:

- `Mini C/MiniC`: This directory contains the main source code for the calculator.

  - `Grammar.flex.cpp`: This file is generated from the `Grammar.l` file and contains the lexer implementation for the Mini C calculator.

  - `Grammar.l`: This file defines the lexical rules for the Mini C calculator using the Flex tool.

  - `Grammar.tab.cpp`: This file is generated from the `Grammar.y` file and contains the parser implementation for the Mini C calculator.

  - `Grammar.tab.h`: This file is generated from the `Grammar.y` file and contains the parser's header definitions for the Mini C calculator.

  - `Grammar.y`: This file defines the grammar rules and syntax for the Mini C calculator using the Bison tool.

## Building and Running

To build and run the Mini C calculator, follow these steps:

1. Clone or download the repository to your local machine.

2. Navigate to the `Mini C/MiniC` directory.

3. Ensure that Flex and Bison are installed on your system.

4. Compile the lexer and parser files by running the following commands:

   ```bash
   flex Grammar.l
   bison -d Grammar.y
   g++ Grammar.tab.cpp lex.yy.c -o calculator
   ```

5. Execute the `calculator` binary to run the Mini C calculator:

   ```bash
   ./calculator
   ```

## Usage

Once the Mini C calculator is running, you can enter expressions to be evaluated. The calculator supports basic arithmetic operations, such as addition, subtraction, multiplication, and division, as well as parentheses for grouping expressions. It also supports C programming functions, including conditional statements using "if" and logical operations like "and" and "or".

Example expressions:

- `2 + 3 * 4`: Calculates the result of multiplying 3 by 4 and adding 2, yielding 14.

- `(6 - 2) / (3 + 1)`: Evaluates the expression inside the parentheses first and then performs the division, resulting in 1.

- `3 * (4 + 2) - 8`: Computes the result of adding 4 and 2, multiplying the sum by 3, and subtracting 8, giving 10.

The Mini C calculator allows you to write more complex expressions, including conditional statements and logical operations. For example:

- `if (x > 0 and y < 10) then z = x + y else z = x - y`: This expression checks if both `x` is greater than 0 and `y` is less than 10. If the condition is true, it assigns the sum of `x` and `y` to `z`; otherwise, it assigns the difference between `x` and `y` to `z`.

Note: The Mini C calculator may have limitations compared to a full-fledged C programming environment. It is intended as a simplified tool for evaluating mathematical and basic programming expressions.

## Contributions

Contributions to this project are welcome. If you find any issues or have suggestions for improvements, feel free to open an issue or submit a pull request.

Please follow the guidelines outlined in the repository for contributing.

## License

The source code in this repository is available under the [MIT License](https://github.com/tzafff/Advanced-Calculator/blob/main/LICENSE). Make sure to review the license terms before using or modifying the code.
