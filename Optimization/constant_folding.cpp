#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

string evaluateExpression(const string& expression) {
    char op;
    int val1, val2;

    istringstream iss(expression);
    if (iss >> val1 >> op >> val2) {
        switch (op) {
            case '+': return to_string(val1 + val2);
            case '-': return to_string(val1 - val2);
            case '*': return to_string(val1 * val2);
            case '/': return to_string(val1 / val2);
            default: return expression; 
        }
    }
    return expression;
}

void constantFolding(const string& inputFilename, const string& outputFilename) {
    ifstream inputFile(inputFilename); 
    ofstream outputFile(outputFilename); 

    string line;
    while (getline(inputFile, line)) {
        size_t assignPos = line.find('=');
        if (assignPos != string::npos) {
            string variable = line.substr(0, assignPos);
            string expression = line.substr(assignPos + 1);
            expression.erase(remove(expression.begin(), expression.end(), ' '), expression.end()); 

            if (expression.back() == ';') {
                expression.pop_back();
            }

            string evaluated = evaluateExpression(expression);
            outputFile << variable << " = " << evaluated << ";" << endl; 
        } else {
            outputFile << line << endl; 
        }
    }

    inputFile.close();
    outputFile.close();
    cout << "Constant folding completed. Optimized code written to '" << outputFilename << "'." << endl;
}

int main() {
    const string inputFilename = "input1.cpp"; 
    const string outputFilename = "optimized_output_folding.cpp"; 
    constantFolding(inputFilename, outputFilename); 
    return 0;
}
