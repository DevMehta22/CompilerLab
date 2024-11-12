#include<iostream>
#include<string>

using namespace std;

int S(),A(),B();

const char* pointer;

int S(){
    if(*pointer == 'a'){
        pointer++;
        if(A() or B()){
            if(*pointer == 'b'){
                pointer++;
                return 1;
            }else{
                return 0;
            }
        }else{
            return 0;
        }
    }else{
        return 0;
    }
}

int A(){
    if(*pointer == 'c' or *pointer == 'd'){
        pointer++;
        if(*pointer == 'x'){
            pointer++;
            return 1;
        }else{
            return 0;
        }
    }else{
        return 0;
    }
}

int B(){
    if(*pointer == 'x'){
        pointer++;
        if(*pointer == 'e'){
            pointer++;
            return 1;
        }else{
            return 0;
        }
    }else{
        return 0;
    }
}

int main(){
    string s;
    cout << "Enter the string:"<<endl;
    cin >> s;
    pointer =s.c_str();
    if(S() &&  *pointer == '\0'){
        cout << "String successfully parsed!" << endl;
    }else{
        cout << "Error parsing string!" << endl;
    }
}