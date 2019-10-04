/* 
 * File: PostFixer.cxx
 * Author: Jeff Flanegan
 * Date: 2019-10-1
 */
#include <cstdlib> //provides size_t
#include <fstream> //provides ifstream
#include <cstring> //provides string class (for my compiler)
#include <string> //provides string class (for other compilers)
#include <iostream> //provides cout
#include "stack2.h" //provides stack and node templates

using namespace std;
using namespace main_savitch_7B;

/* Description:
 * This program uses a linked list as a Stack which
 * makes calculations on expressions written in post-fix notation.
 * The expression is printed to the console followed by the result.
 * The expressions are read from a file named HomeworkSixInput.txt,
 * and is not altered by the program.
 */
//Calculates expressions written in post-fix notation
void calculate(stack<double>& numStack, char op){
    //get top 2 numbers and remove from stack
    double num1, num2;   
    num2 = numStack.top();
    numStack.pop();
    num1 = numStack.top();
    numStack.pop();
    //get operator and push result to stack
    switch(op){
        case '+': numStack.push(num1 + num2); break;
        case '-': numStack.push(num1 - num2); break;
        case '*': numStack.push(num1 * num2); break;
        case '/': numStack.push(num1 / num2);        
    }  
}
//scan file line-by-line and parse data-types from string
void fileOps(stack<double>& numStack, string& line){
    
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
        else if(strchr("+-*/", line[i])){
            //make calculation on top 2 numbers in numStack
            calculate(numStack, char(line[i]));               
        }
    }
    //number on top of the stack is the result
    cout << " = " << numStack.top() << '\n' <<endl;
    //clear stack for next line in file
    numStack.pop();             
}

int main(int argc, char** argv) {
    //declare stack
    stack<double> numStack;
    //open file
    ifstream file("HomeworkSixInput.txt");
    if(!file){
        cout << "file not found" << endl;
        return -1;
    }
    //read line-by-line
    string line;
    while(getline(file,line)){
        fileOps(numStack, line);
    }
    file.close();
    return 0;
}

