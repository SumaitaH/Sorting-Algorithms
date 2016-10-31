//Sumaita Hussain
//Implementation of Stack using 1D Array in C++ 

#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

class Stack {
public:
    int top;
    int* StackArray;
    
    Stack(int size);
    ~Stack(); 
    int pop(); 
    void push(int newNum);
    bool isEmpty(); 
};
//Constructor
    Stack::Stack(int size) {
        top = -1;
        StackArray = new int[size];
    }
//Destructor
    Stack::~Stack() {
        cout << "Stack has been deleted." << endl;
    }
//Pop Method
    int Stack::pop() {
        if (!isEmpty()) {
            int a = StackArray[top - 1];
            top--;
            return a;
        } else
            return -1;
    }
//Push Method
    void Stack::push(int newNum) {
        top++;
        StackArray[top] = newNum;
    }
//isEmpty Method
    bool Stack::isEmpty() {
        if (top < 1) {
            return true;
        }
        return false;
    }


int main(int argc, char** argv) {

    int count = 0;
    int num;
//Open file    
    ifstream myfile;
    myfile.open(argv[1]);
    if (!myfile) {
        cout << "ERROR: WRONG FILE" << endl;
    }
//Increment count 
    while (!myfile.eof()) {
        myfile >> num;
        count++;
    }
    myfile.close();
    
//Create new stack with size count and push values from file 
    
    Stack newStack(count);
    myfile.open(argv[1]);
    cout << "Adding values to stack " << endl; 
    while (!myfile.eof()) {
        myfile >> num;
        newStack.push(num);
        cout << "Pushing: " << num << endl;  
    }

    myfile.close();
//Pop values from file 
    cout << "Removing values from stack " << endl;
    while (!(newStack.isEmpty())) {

        cout << "Popping: " << newStack.pop() << endl;
    }
    return 0;
}