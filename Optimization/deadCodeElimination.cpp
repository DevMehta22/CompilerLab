#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");

    if (!inputFile.is_open()) {
        cout << "Error opening input file!" << endl;
        return 1;
    }

    string line;
    vector<string> lines;

    while (getline(inputFile, line)) {
        lines.push_back(line);
    }

    vector<vector<string> > instructions;

    for (const string& line : lines) {
        stringstream ss(line);
        string word;
        vector<string> instruction;
        while (ss >> word) {
            instruction.push_back(word);
        }
        instructions.push_back(instruction);
    }

    for (int i = 0; i < instructions.size(); i++) {
        vector<string>& currentInstruction = instructions[i];
        string var1 = currentInstruction[0];
        if (var1.substr(0, 1) == "t") {
            bool used = false;

            for (int j = i + 1; j < instructions.size(); j++) {
                const vector<string>& nextInstruction = instructions[j];
                for (const string& word : nextInstruction) {
                    if (word == var1) {
                        used = true;
                        break;
                    }
                }
                if (used) {
                    break;
                }
            }

            if (!used) {
                instructions.erase(instructions.begin() + i);
                i = -1;
            }
        }
    }

    for (const vector<string>& instruction : instructions) {
        for (size_t i = 0; i < instruction.size(); ++i) {
            outputFile << instruction[i];
            if (i != instruction.size() - 1) {
                outputFile << " ";
            }
        }
        outputFile << endl;
    }

    inputFile.close();
    outputFile.close();

    cout << "Optimized code has been written to output.txt" << endl;

    return 0;
}