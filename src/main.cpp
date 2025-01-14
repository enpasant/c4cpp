#include "../argparse/argparse.hpp"
#include <iostream>
#include <string>
#include <cctype>
#include <sstream>

using namespace std;

int evex(const string& expression) {
    int result = 0;
    int current_number = 0;
    char current_operator = '+';  // Fix: use single quotes for a char

    for (size_t i = 0; i < expression.size(); ++i) {
        char ch = expression[i];

        // If the character is a digit, form the current number
        if (isdigit(ch)) {
            current_number = current_number * 10 + (ch - '0');
        }

        // If the character is an operator or we reached the end of the string, process the current number
        if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || i == expression.size() - 1) {
            switch (current_operator) {
                case '+':
                    result += current_number;
                    break;
                case '-':
                    result -= current_number;
                    break;
                case '*':
                    result *= current_number;
                    break;
                case '/':
                    if (current_number != 0)
                        result /= current_number;
                    else
                        cerr << "Don't divide by zero, silly." << endl;
                    break;
            }

            // Reset for the next number
            current_number = 0;

            // Update the current operator
            current_operator = ch;
        }
    }

    return result;
}

int main(int argc, char* argv[]) {
    argparse::ArgumentParser program("c4cpp");

    // Expression argument
    program.add_argument("-e", "--expression")
        .help("Get expression with operations (e.g., 20*2-10).")
        .default_value("No expression!")
        .nargs(1);

    try {
        program.parse_args(argc, argv);

        string expression = program.get<string>("--expression");

        // Check if the expression is valid
        if (expression == "No expression!") {
            cout << "No expression provided." << endl;
        } else {
            // Run the expression evaluation
            int result = evex(expression);
            cout << "Result: " << result << "\n";
        }

    } catch (const std::exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
