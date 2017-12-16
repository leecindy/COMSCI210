// Programmer: Pui Lee
// Programmer's ID: 1147451

#include <iostream>
#include <sstream>
using namespace std;

#include "Stack.h"

void calculate(string myStr, Stack<double> &myStack){
    stringstream ss;
    char symbol;
    double b = myStack.peek();
    myStack.pop();
    double a = myStack.peek();
    myStack.pop();
    double c;
    ss << myStr;
    ss >> symbol;
    switch(symbol){
        case '+':
            c = a + b;
            break;
        case '-':
            c = a - b;
            break;
        case '*':
            c = a * b;
            break;
        case '/':
            c = a / b;
            break;
    }
    myStack.push(c);
}

int main( ) {
    // programmer's identification
    cout << "Programmer: Pui Lee\n";
    cout << "Programmer's ID: 1147451\n";
    cout << "File: " << __FILE__ << endl;
    
    Stack<double> myStack;
    Stack<double> copyStack;
    string myStr;

    bool again = true;
    
    while(again){
        cout << "Enter: ";
        while(!copyStack.empty()){
            cout << copyStack.peek() << " ";
            copyStack.pop();
        }
        cin >> myStr;
        
        if(myStr == "Q" || myStr == "q"){
            again = false;
            break;
        }
        else if(myStr == "+" || myStr == "-" || myStr == "*" || myStr == "/"){
            calculate(myStr, myStack);
        }
        else{
            myStack.push(atof(myStr.c_str()));
        }
        copyStack = myStack;
    }
    
}
