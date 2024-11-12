#include<iostream>
#include<vector>
#include<stack>

using namespace std;

int getIndex(char op, const vector<char>& operators) {
    for (int i = 0; i < operators.size(); i++) {
        if (operators[i] == op) {
            return i;
        }
    }
    return -1;
}

int main(){
    vector<char> operators = {'+', '-', '*', '/', '(', ')', 'i', '$'};
    vector<vector<char>> matrix(8, vector<char>(8, '_'));
    stack<char> stk;  
    stk.push('$'); 
    string inputExpr;

    matrix[0] = vector<char>({'g', 'g', 'l', 'l', 'l', 'g', 'l', 'g'});  
    matrix[1] = vector<char>({'g', 'g', 'l', 'l', 'l', 'g', 'l', 'g'});  
    matrix[2] = vector<char>({'g', 'g', 'g', 'g', 'l', 'g', 'l', 'g'}); 
    matrix[3] = vector<char>({'g', 'g', 'g', 'g', 'l', 'g', 'l', 'g'});  
    matrix[4] = vector<char>({'l', 'l', 'l', 'l', 'l', 'e', 'l', '_'});  
    matrix[5] = vector<char>({'g', 'g', 'g', 'g', '_', 'g', '_', 'g'});  
    matrix[6] = vector<char>({'g', 'g', 'g', 'g', '_', 'g', '_', 'g'});  
    matrix[7] = vector<char>({'l', 'l', 'l', 'l', 'l', '_', 'l', 'e'});  

    cout << "Operator Precedence Matrix:" << endl;
    for (int i = 0; i < operators.size(); i++) {
        for (int j = 0; j < operators.size(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Enter the expression (with 'i' representing identifiers): ";
    cin >> inputExpr;

    int i = 0;

    while (i < inputExpr.size()) {
        char currentChar = inputExpr[i];
        int currentIndex = getIndex(currentChar, operators);  

        if (currentChar == 'i') {
            cout << "Encountered identifier: " << currentChar << endl;
            stk.push(currentChar);
            i++;
            continue;
        }

        char topOperator = stk.top();
        int topIndex = getIndex(topOperator, operators);

        char precedence = matrix[topIndex][currentIndex];

        if (precedence == 'l' || precedence == 'e') {
            cout << "Pushing operator: " << currentChar << endl;
            stk.push(currentChar);
            i++;
        }
        else if (precedence == 'g') {
            cout << "Popping and evaluating operator: " << topOperator << endl;
            stk.pop();
        }
        else {
            cout << "Invalid operation or precedence!" << endl;
            break;
        }
    }

    while (stk.top() != '$') {
        char topOperator = stk.top();
        cout << "Popping and evaluating remaining operator: " << topOperator << endl;
        stk.pop();
    }

    return 0;
}
