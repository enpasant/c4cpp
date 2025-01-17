#include "lib/argparse/argparse.hpp"
#include <iostream>
#include <string>
#include <cctype>
#include <cmath>  // for pow(), sqrt(), M_PI, and other math functions
using namespace std;

double evex(const string& expression) {
    double result = 0.0;
    double current_number = 0.0;
    char current_operator = '+';  // fix: use single quotes for a char

    for (size_t i = 0; i < expression.size(); ++i) {
        char ch = expression[i];

        // if the character is a digit, form the current number
        if (isdigit(ch)) {
            current_number = current_number * 10 + (ch - '0');
        }

        // if the character is an operator or we reached the end of the string, process the current number
        if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == 'r' || i == expression.size() - 1) {
            // switch for checking operators
            switch (current_operator) {
                case '+': result += current_number; break;
                case '-': result -= current_number; break;
                case '*': result *= current_number; break;
                case '/': 
                    if (current_number != 0) 
                        result /= current_number; 
                    else 
                        cerr << "Don't divide by zero, silly!" << endl; 
                    break;
                case '^': result = pow(result, current_number); break;  // power
            }

            // Square root operation (represented by "r")
            if (ch == 'r') {
                result = sqrt(current_number);  // square root of a number
            }

            current_number = 0;  // reset for the next number
            current_operator = ch;  // update the current operator
        }

        // Support for Pi constant
        if (expression[i] == 'p' && i + 1 < expression.size() && expression[i + 1] == 'i') {
            current_number = M_PI;  // assign the value of Pi
            i++;  // skip the 'i' in "pi"
        }
    }

    return result;
}

int main(int argc, char* argv[]) {
    argparse::ArgumentParser program("c4cpp");

    // expression argument
    program.add_argument("-e", "--expression")
        .help("Provide an expression with operations (e.g., 20*2-10, 3^2, sqrt(9), pi+2).")
        .default_value("No expression!");  // default value 

    try {
        program.parse_args(argc, argv);

        string expression = program.get<string>("--expression");

        // check if the expression is valid
        if (expression == "No expression!") {
            cout << "Provide expression with -e (--expression)." << endl;
        } else {
            // run the expression evaluation
            cout << evex(expression) << "\n";
        }

    } catch (const std::exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
