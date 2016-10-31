

#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

class ListNode {
public:
    friend class LinkedListStack;
    int data;
    ListNode* next;

    ListNode(int value) {
        data = value;
    }

    ListNode() {
        data = -1; 
    }
    
    ~ListNode(){  }
    
};

class LinkedListStack {
public:

    ListNode* top;

    LinkedListStack() {
        top = NULL;
    }
    ~LinkedListStack(){
        cout << "The stack has been cleared." << endl;
    }

    void push(ListNode* ptr) {
        if (top == NULL) {
            top = ptr;
            top->next = NULL; 
        }
        else {
            ptr -> next = top;
            top = ptr;
        }
    }

    int pop() {
        
        if(!isEmpty()){
            ListNode* temp = top;
            top = top -> next; 
            return temp -> data; 
        }
        else
            return 0; 
    }

    bool isEmpty() {
        if (top == NULL) {
            return true;
        } else
            return false;
    }

};

int main(int argc, char** argv) {

    int num;
    int finish = 1; 
    LinkedListStack myStackLinked;
    ifstream myfile;

    myfile.open(argv[1]);
    cout << "Pushing values into the stack: " << endl;
    while (!myfile.eof()) {

        myfile >> num;
        ListNode* newNode = new ListNode(num);

        myStackLinked.push(newNode);
        cout << "Pushing: " << newNode->data << " Next Address: " << newNode->next << endl; 
    }
    myfile.close();
    cout << "Popping the stack: " << endl;
    
    while(finish!=0){
        
        finish = myStackLinked.pop();
        cout << "Popping:" << finish << endl;     
    }

    return 0;
            
}

