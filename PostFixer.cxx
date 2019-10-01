/* 
 * File: PostFixer.cxx
 * Author: Jeff Flanegan
 * Date: 2019-10-1
 */
#include <cstdlib> //provides size_t
#include <fstream> //provides ifstream
#include <cstring> //provides string class (for my compiler)
#include "string" //provides string class (for other compilers)
#include <iostream> //provides cout
#include "stack2.h" //provides stack and node templates

using namespace std;
using namespace main_savitch_7B;

/* Description:
 * This program uses a linked list to simulate a stack which
 * makes calculations on expressions written in post-fix notation.
 * The expression is printed to the console followed by the result.
 * The expressions in question are read from a file named HomeworkSixInput.txt,
 * and the file is not altered while the program is running.
 */
//Calculates expressions written in post-fix notation
void calculate(stack<double>& numStack, stack<char>& operStack){
    //get top 2 numbers and remove from stack
    double num1, num2;   
    num2 = numStack.top();
    numStack.pop();
    num1 = numStack.top();
    numStack.pop();
    //get operator and push result to stack
    switch(operStack.top()){
        case '+': numStack.push(num1 + num2); break;
        case '-': numStack.push(num1 - num2); break;
        case '*': numStack.push(num1 * num2); break;
        case '/': numStack.push(num1 / num2);        
    }
    //remove operator from stack
    operStack.pop();   
}
//scan file line-by-line and parse data-types from string
void fileOps(stack<double>& numStack, stack<char>& operStack, string& line){
    
    string temp;
    cout << line << endl;
    for (size_t i = 0; i < line.length(); i++){
        //find numbers
        if(isdigit(line[i])){
           temp = line[i];
           //find multiple digits
            while(isdigit(line[i+1])){
                i++;
                temp+=line[i];                    
            }
        //convert to double and push
        numStack.push(stod(temp));               
        }
        //operator pushes to stack
        else if(strchr("+-*/", line[i])){
            operStack.push(char(line[i]));
            //make calculation on top 2 numbers in numStack
            calculate(numStack, operStack);               
        }
    }
    //number on top of the stack is the result
    cout << " = " << numStack.top() << '\n' <<endl;
    //clear stack for next line in file
    numStack.pop();             
}

int main(int argc, char** argv) {
    //make number and operator stacks
    stack<double> numStack;
    stack<char> operStack;
    //open file
    ifstream file("HomeworkSixInput.txt");
    if(!file){
        cout << "file not found" << endl;
        return -1;
    }
    //read line-by-line
    string line;
    while(getline(file,line)){
        fileOps(numStack, operStack, line);
    }
    file.close();
    return 0;
}

