#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <vector>
#include <sstream>

#define MAX_MNEMONICS 29
#define MAX_CODE_LINES 100

using namespace std;

struct Mnemonic {
    string mnemonic;
    string class_;
    string machineCode;
    int length;
};

struct Literal {
    string literal;
    int address;
};

struct Symbol {
    string symbol;
    int address;
};

struct Pool {
    int startIndex;
};

int findMnemonic(const vector<Mnemonic>& mnemonics, const string& mnemonic) {
    for (int i = 0; i < mnemonics.size(); i++) {
        if (mnemonics[i].mnemonic == mnemonic) {
            return i;
        }
    }
    return -1;
}

int findSymbol(const vector<Symbol>& symbols, const string& symbol) {
    for (int i = 0; i < symbols.size(); i++) {
        if (symbols[i].symbol == symbol) {
            return i;
        }
    }
    return -1;
}

int addSymbol(vector<Symbol>& symbols, const string& symbol, int currentAddress) {
    symbols.push_back({symbol, currentAddress});
    return symbols.size() - 1;
}

bool isValidSymbol(const string& str) {
    return !isdigit(str[0]);
}

void printIntermediateCode(ofstream& outputFile, const vector<string>& ic, const vector<string>& assemblyCode, const vector<string>& machineCode, const vector<int>& lc) {
    outputFile << "\nSRC                 LC         IC                      Machine Code\n";
    outputFile << "\n";
    
    for (size_t i = 0; i < ic.size(); i++) {
        outputFile << assemblyCode[i] << "        " << lc[i] << "       " << ic[i] << "        " << machineCode[i] << "\n";
    }
}

void printLiteralTable(ofstream& outputFile, const vector<Literal>& literals) {
    outputFile << "\nLiteral Table:\n";
    outputFile << "Index    Literal     Address\n";
    for (size_t i = 0; i < literals.size(); i++) {
        outputFile << i << "        " << literals[i].literal << "        " << literals[i].address << "\n";
    }
}

void printSymbolTable(ofstream& outputFile, const vector<Symbol>& symbols) {
    outputFile << "\nSymbol Table:\n";
    outputFile << "Index    Symbol     Address\n";
    for (size_t i = 0; i < symbols.size(); i++) {
        outputFile << i << "        " << symbols[i].symbol << "        " << symbols[i].address << "\n";
    }
}

void printPoolTable(ofstream& outputFile, const vector<Pool>& pools) {
    outputFile << "\nPool Table:\n";
    outputFile << "Pool No.    Literal Start Index\n";
    for (size_t i = 0; i < pools.size(); i++) {
        outputFile << i << "            " << pools[i].startIndex << "\n";
    }
}

int main() {
    vector<Mnemonic> mnemonics = {
        {"STOP", "IS", "00", 1},{"ADD", "IS", "01", 1},{"SUB", "IS", "02", 1},{"MULTI", "IS", "03", 1},{"MOVER", "IS", "04", 1},
        {"MOVEM", "IS", "05", 1},{"COMP", "IS", "06", 1},{"BC", "IS", "07", 1},{"DIV", "IS", "08", 1},{"READ", "IS", "09", 1},
        {"PRINT", "IS", "10", 1},{"START", "AD", "01", 0},{"END", "AD", "02", 0},{"ORIGIN", "AD", "03", 0},{"EQU", "AD", "04", 0},
        {"LTORG", "AD", "05", 0},{"DS", "DL", "01", 0},{"DC", "DL", "02", 1},{"AREG", "RG", "01", 0},{"BREG", "RG", "02", 0},
        {"CREG", "RG", "03", 0},{"EQ", "CC", "03", 0},{"LT", "CC", "01", 0},{"GT", "CC", "04", 0},{"LE", "CC", "02", 0},
        {"GE", "CC", "05", 0},{"NE", "CC", "06", 0}
    };

    vector<Literal> literals;
    vector<Symbol> symbols;
    vector<Pool> pools;
    int currentAddress = 0, icCount = 0;
    vector<string> intermediateCode, assemblyCode, machineCode;
    vector<int> lc;
    string line, mnemonic, operand1, operand2;

    ifstream file("input.asm");
    ofstream outputFile("output.txt");

    if (!file || !outputFile) {
        cout << "Error opening files!" << endl;
        return 1;
    }

    pools.push_back({0});

    while (getline(file, line)) {
        operand1.clear();
        operand2.clear();
        stringstream ss(line);
        ss >> mnemonic >> operand1 >> operand2;

        int mIndex = findMnemonic(mnemonics, mnemonic);
        if (mIndex != -1) {
            lc.push_back(currentAddress);

            if (mnemonics[mIndex].mnemonic == "START") {
                currentAddress = stoi(operand1);
                assemblyCode.push_back(mnemonic + " " + operand1);
                intermediateCode.push_back("(AD, " + mnemonics[mIndex].machineCode + ") (C, " + to_string(currentAddress) + ")");
                machineCode.push_back("-");
            } else if (mnemonics[mIndex].mnemonic == "LTORG" || mnemonics[mIndex].mnemonic == "END") {
                for (size_t i = pools.back().startIndex; i < literals.size(); i++) {
                    literals[i].address = currentAddress++;
                }
                pools.push_back({(int)literals.size()});
                assemblyCode.push_back(mnemonic);
                intermediateCode.push_back("(AD, " + mnemonics[mIndex].machineCode + ")");
                machineCode.push_back("-");
            } else if (operand2[0] == '=') {
                literals.push_back({operand2, currentAddress++});
                assemblyCode.push_back(mnemonic + " " + operand1 + ", " + operand2);
                intermediateCode.push_back("(IS, " + mnemonics[mIndex].machineCode + ") (" + operand1 + ") (L, " + to_string(literals.size() - 1) + ")");
                machineCode.push_back(mnemonics[mIndex].machineCode + " " + operand1 + " " + to_string(literals.size() - 1));
            } else if (isValidSymbol(operand2)) {
                int symbolIndex = findSymbol(symbols, operand2);
                if (symbolIndex == -1) {
                    symbolIndex = addSymbol(symbols, operand2, currentAddress);
                }
                assemblyCode.push_back(mnemonic + " " + operand1 + ", " + operand2);
                intermediateCode.push_back("(IS, " + mnemonics[mIndex].machineCode + ") (" + operand1 + ") (S, " + to_string(symbolIndex) + ")");
                machineCode.push_back(mnemonics[mIndex].machineCode + " " + operand1 + " " + to_string(symbols[symbolIndex].address));
                currentAddress++;
            }
            icCount++;
        }
    }

    file.close();

    printIntermediateCode(outputFile, intermediateCode, assemblyCode, machineCode, lc);
    printSymbolTable(outputFile, symbols);
    printLiteralTable(outputFile, literals);
    printPoolTable(outputFile, pools);

    outputFile.close();

    cout << "Output written to output.txt" << endl;

    return 0;
}
