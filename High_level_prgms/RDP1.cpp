#include<iostream>
#include<string>

using namespace std;


const char* pointer;

int E(),F(),Tdash(),Edash(),T();

int F(){
    if(*pointer == 'i'){
        cout << "i parsed"<<endl;
        pointer++;
        return 0;
    }else if(*pointer == '('){
        cout << "( parsed" << endl;
        pointer++;
        if(E()==0){
            cout << "E parsed"<<endl;
            if(*pointer == ')'){
                cout << ") parsed" << endl;
                pointer++;
                return 0;
            }else{
                return 1;
            }
        }else{
            return 1;
        }
    }else{
        return 1;
    }
}

int Tdash(){
    if(*pointer == '*' or *pointer =='/'){
        cout << "* or / parsed"<<endl;
        pointer++;
        if(F()==0){
            cout << "F parsed"<<endl;
            if(Tdash()==0){
                cout << "Tdash parsed"<<endl;
                return 0;
            }else{
                return 1;
            }
        }else{
            return 1;
        }
    }else if(*pointer == '\0'){
        pointer++;
        return 0;
    }else{
        return 0;
    }
}

int T(){
    if(F()==0){
        cout << "F parsed"<<endl;
        if(Tdash()==0){
            cout << "Tdash parsed"<<endl;
            return 0;
        }else{
            return 1;
        }
    }else{
        return 1;
    }
}

int Edash(){
    if(*pointer == '+' or *pointer == '-'){
        cout << "+ or - parsed"<<endl;
        pointer++;
        if(T()==0){
            cout << "T parsed"<<endl;
            if(Edash()==0){
                cout << "Edash parsed"<<endl;
                return 0;
            }else{
                return 1;
            }
        }else{
            return 1;
        }
    }else if(*pointer == '\0'){
        pointer++;
        return 0;
    }else{
        return 0;
    }
}

int E(){
    if(T() == 0){
        cout << "T parsed"<<endl;
        if(Edash() == 0){
            cout << "Edash parsed"<<endl;
            return 0;
        }else{
            return 1;
        }
    }else{
        return 1;
    }
}

int main(){
    string str;
    cout<<"Enter a string: ";
    cin >> str;
    pointer = str.c_str();
    if(E()==0 && *pointer == '\0'){
        cout << "String is successfully parsed";
        return 0;
    }else{
        cout << "String is not successfully parsed";
        return 1;
    }
    
}
