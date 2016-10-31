
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

class listBinTreeNode{
public:
    friend class HuffmanLinkedList;
    friend class HuffmanBinaryTree;
    string chStr;
    int prob;
    listBinTreeNode* next;
    listBinTreeNode* right;
    listBinTreeNode* left;

    listBinTreeNode();
//    listBinTreeNode(string ch, int data);
    ~listBinTreeNode();
    void printNode(ofstream &outFile, listBinTreeNode* T);
};
listBinTreeNode::listBinTreeNode(){}

listBinTreeNode::~listBinTreeNode(){}
void listBinTreeNode::printNode(ofstream &outFile, listBinTreeNode* T){
    outFile << "String: " << T->chStr << " Prob: " << T->prob << " Next: " << T->next << " Right " << T->right << " Left: " << T->left << endl;
}

class HuffmanLinkedList{
public:
    listBinTreeNode* listHead;
    listBinTreeNode* oldListHead;

    //create a dummy listNode and let listHead point to it
    HuffmanLinkedList();
    ~HuffmanLinkedList();
    //insert newNode into the list using insertion-sort
    void listInsert(listBinTreeNode* newNode, listBinTreeNode* spot);
    listBinTreeNode* findSpot(int data);
    bool isEmpty();
    //print the list from listHead to the end of the outFile3 in this format:
    //listhead-->("dummy", 0, nextString)-->(nextString, prob, next) -->
    //(nextString, prob, nextString) --> ....(nextString, prob, NULL)-->NULL
    void printList(listBinTreeNode* T, ofstream &outFile);
};

HuffmanLinkedList::HuffmanLinkedList(){
    listHead = new listBinTreeNode;
    oldListHead = new listBinTreeNode;
}
HuffmanLinkedList::~HuffmanLinkedList(){}
bool HuffmanLinkedList::isEmpty(){
    if(listHead->next == NULL){
        return true;
    }
    return false;
}
void HuffmanLinkedList::listInsert(listBinTreeNode* newNode, listBinTreeNode* spot){
    cout << "inserting " << newNode->prob << endl;
    cout << "spot: " << spot->prob << endl <<endl; ;
        listBinTreeNode* temp = spot;
        newNode->next = temp->next;
        spot->next = newNode;

}
listBinTreeNode* HuffmanLinkedList::findSpot(int data){
    listBinTreeNode* spot = listHead;

    while (spot->next!= NULL && spot->next->prob < data){
        if(spot->next->prob == 0){
            return spot;
        }
        //cout << "testb" << endl;
        spot= spot->next;
    }
    //cout << "testc" << endl;

    return spot;
    //}
    }

void HuffmanLinkedList::printList(listBinTreeNode* T, ofstream &outFile){
   
    listBinTreeNode* temp = T;
    while(temp->next!=NULL){
        outFile << "(" << temp->chStr << ", " << temp->prob << ", " << temp->next->chStr << ") -->"<<endl;
        temp = temp ->next;
    }
    outFile << "(" << temp->chStr << ", " << temp->prob << ", " << "null)"<<endl;
}

class HuffmanBinaryTree{
public:
    //string chStr;
    //int prob;
    string code;
    listBinTreeNode* root;

    HuffmanBinaryTree();
    ~HuffmanBinaryTree();
    void preOrderTraversal(listBinTreeNode* T, ofstream &outFile);
    void constructCharCode(listBinTreeNode* T, string code, ofstream &outFile1, ofstream &outFile2);

};
HuffmanBinaryTree::HuffmanBinaryTree(){
    root = new listBinTreeNode;
}
HuffmanBinaryTree::~HuffmanBinaryTree(){}
void HuffmanBinaryTree::preOrderTraversal(listBinTreeNode* T, ofstream &outFile){
    if(T == NULL){

    }
    else{
        T->printNode(outFile, T);
        preOrderTraversal(T->left, outFile);
        preOrderTraversal(T->right, outFile);
    }
}
void HuffmanBinaryTree::constructCharCode(listBinTreeNode* T, string code, ofstream &outFile1, ofstream &outFile2){
    if(T == NULL){

    }
    else if (T->left == NULL && T->right == NULL){
        outFile1 << T->chStr << endl;
        outFile2 << code << endl;
    }
    else {
        constructCharCode(T->left, code + "0", outFile1, outFile2);
        constructCharCode(T->right, code + "1", outFile1, outFile2);
    }

}
int main(int argc, char** argv){

    ifstream infile(argv[1]);
    ofstream out1(argv[2]);
    ofstream out2(argv[3]);
    ofstream out3(argv[4]);

    //Step 2: Construct Huffman Ordered Linked List
    HuffmanLinkedList huffList;
    huffList.listHead->next = NULL;
    huffList.listHead->chStr = "dummy";
    huffList.listHead->prob  = 0;

    string alpha;
    int data;

    while (infile >> alpha){
        //cout << "error?" <<endl;
        infile >> data;
        //cout << "alpha: " << alpha << endl;
        //cout << "data:  " << data << endl;
        listBinTreeNode* spot = huffList.findSpot(data);
        listBinTreeNode* newNode = new listBinTreeNode;
        newNode->chStr = alpha;
        newNode->prob = data;
        //cout << "hello1" << endl<<endl<<endl;
        huffList.listInsert(newNode, spot);
    }
    infile.close();
    
    huffList.oldListHead->chStr = "dummy";
    huffList.oldListHead->prob  = 0;
    huffList.oldListHead->next = huffList.listHead->next;
    huffList.listHead = huffList.listHead->next;
    //cout << "hello3" << endl;
           

    while(huffList.listHead->next!=NULL){
        if(huffList.listHead->prob == 100){
            break; 
        }
        listBinTreeNode* newNode = new listBinTreeNode;
        newNode->chStr = huffList.listHead->chStr + huffList.listHead->next->chStr;
        newNode->prob = huffList.listHead->prob + huffList.listHead->next->prob;
        newNode->left = huffList.listHead;
        newNode->right = huffList.listHead->next;
        out3 << "New Node: " << endl; 
        newNode->printNode(out3, newNode);
        listBinTreeNode* spot = huffList.findSpot(newNode->prob);
        huffList.listInsert(newNode, spot);
        huffList.listHead = huffList.listHead->next->next;
        out3 << "Printed List" << endl;
        huffList.printList(huffList.oldListHead,out3);
    }
    cout << huffList.listHead->chStr << endl;
    listBinTreeNode* newNode = huffList.listHead; 
    

    HuffmanBinaryTree huffTree;
   // cout << "l" << huffList.listHead->prob<<endl;
    huffTree.root = huffList.listHead;
    string code = ""; 
    huffTree.constructCharCode(huffTree.root, code, out1, out2);
    huffTree.preOrderTraversal(huffTree.root, out2);
   // cout << "hello5" << endl;

  //  huffList->listHead->chStr = "hello" ;
  //  huffList->listHead->prob = 0;

    out1.close();
    out2.close();
    out3.close();
}
