#include <iostream>
#include <cctype>
#include <cstring>
#include <unordered_set>

using namespace std;

bool isNonTerminal(char c) {
    return isupper(c);
}

void addToSet(char set[], char element) {
    if (strchr(set, element) == NULL) {
        int length = strlen(set);
        set[length] = element;
        set[length + 1] = '\0';
    }
}

void findFirst(char first[], char productions[][10], char nonTerminal) {
    for (int i = 0; i < 10; i++) {
        if (productions[i][0] == nonTerminal) {
            char* production = productions[i] + 2;  

            if (production[0] == '\0') continue; 

            char* option = strtok(production, "/");
            while (option) {
                if (!isNonTerminal(option[0])) {
                    addToSet(first, option[0]);
                } else {
                    findFirst(first, productions, option[0]);
                }
                option = strtok(NULL, "/");
            }
        }
    }
}

void findFollow(char follow[], char productions[][10], char nonTerminal) {
    if (nonTerminal == productions[0][0]) {
        addToSet(follow, '$');
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 2; productions[i][j] != '\0'; j++) {
            if (productions[i][j] == nonTerminal) {
                if (productions[i][j + 1] != '\0') {
                    char temp[10] = "";
                    findFirst(temp, productions, productions[i][j + 1]);
                    for (int k = 0; temp[k] != '\0'; k++) {
                        if (temp[k] != 'n') { 
                            addToSet(follow, temp[k]);
                        }
                    }
                } else if (productions[i][j + 1] == '\0' && productions[i][0] != nonTerminal) {
                    char temp[10] = "";
                    findFollow(temp, productions, productions[i][0]);
                    for (int k = 0; temp[k] != '\0'; k++) {
                        addToSet(follow, temp[k]);
                    }
                }
            }
        }
    }
}

int main() {
    int n;
    char productions[10][10], nonTerminal[10], first[10] = "", follow[10] = "";

    cout << "Enter the number of production rules: ";
    cin >> n;

    cout << "Enter the production rules (e.g., S=abAB/bB):\n";
    for (int i = 0; i < n; i++) {
        cin >> productions[i];
    }

    cout << "Enter the non-terminal to find the First and Follow sets: ";
    cin >> nonTerminal;

    findFirst(first, productions, nonTerminal[0]);
    findFollow(follow, productions, nonTerminal[0]);

    cout << "First(" << nonTerminal[0] << ") =  ";
    for (int i = 0; first[i] != '\0'; i++) {
        cout << first[i] << " ";
    }
    cout << "\n";

    cout << "Follow(" << nonTerminal[0] << ") =  ";
    for (int i = 0; follow[i] != '\0'; i++) {
        cout << follow[i] << " ";
    }
    cout << "\n";

    return 0;
}
