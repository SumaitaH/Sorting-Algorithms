#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

class graphNode
{
public:
    int nodeID;
    graphNode* next;

    graphNode(int nID);
    ~graphNode();
    void nodeInsert();
    void nodeDelete();
};

graphNode::graphNode(int nID)
{
    nodeID = nID;
    next = NULL;
}

graphNode::~graphNode(){}

void graphNode::nodeInsert(){}

void graphNode::nodeDelete(){}

class undirectedEdge
{
public:
    int Ni;
    int Nj;
    int edgeCost;
    undirectedEdge* next;

    undirectedEdge(int Nx, int Ny, int cost);
    ~undirectedEdge();
    void printEdge(ofstream &outFile);
    void edgeInsert();
    void edgeDelete();
};

undirectedEdge::undirectedEdge(int Nx, int Ny, int cost){
    Ni = Nx;
    Nj = Ny;
    edgeCost = cost;

    next = NULL;
}

undirectedEdge::~undirectedEdge(){}

void undirectedEdge::printEdge(ofstream &outFile){
    outFile << "(" << Ni << ", " << Nj << ", " << edgeCost << ")";
}

void undirectedEdge::edgeInsert(){}

void undirectedEdge::edgeDelete(){}

class KruskalMST
{
public:
    int numNodes; //number of nodes in G
    int* inWhichSet; //an int array of size = numNodes + 1
    //to indicate which set each node belongs; dynamically alloc.
    //and set to itself, initially.
    int numSets;
    int totalCost;
    undirectedEdge* edgeListHead;
    undirectedEdge* MSTofG;

    KruskalMST(int numN);
    ~KruskalMST();

    void insertEdge(undirectedEdge* newEdge);
    void printList(undirectedEdge* L, ofstream &outFile);
    void printMST(undirectedEdge* L, ofstream &outFile);
    void printSet(ofstream &outFile);
    void mergeTwoSets(int Nx, int Ny);
};

KruskalMST::KruskalMST(int numN)
{
    numNodes = numN;
    inWhichSet = new int[numNodes + 1]; //set to itself
    for (int i = 0; i <= numNodes; i++)
    {
        inWhichSet[i] = i;
    }
    numSets = numN; // initially set to number of nodes
    totalCost = 0; // initially equal to 0
    edgeListHead = new undirectedEdge(9999, 9999, 9999); //dummy node
    MSTofG = new undirectedEdge(9999, 9999, 9999);
}
KruskalMST::~KruskalMST(){}

void KruskalMST::insertEdge(undirectedEdge* newEdge)
{
    undirectedEdge* temp = edgeListHead;
    while (temp->next != NULL && temp->next->edgeCost < newEdge->edgeCost)
    {
        temp = temp->next;
    }
    newEdge->next = temp->next;
    temp->next = newEdge;
}

void KruskalMST::printList(undirectedEdge* L, ofstream &outFile)
{
    undirectedEdge* temp = L->next;
    outFile << "ListHead";
    for (int i = 0; i < 11; i++){
        if (temp == NULL){
            break;
        } else {
            outFile << "-->";
            temp->printEdge(outFile);
            temp = temp->next;
        }
    }
    outFile << endl;
}

void KruskalMST::mergeTwoSets(int Nx, int Ny)
{
    int min, max;
    if (Nx <= Ny){
        min = Nx;
        max = Ny;
    } else{
        min = Ny;
        max = Nx;
    }
    int index = min;
    while (index <= numNodes){
        if (inWhichSet[index] == max){
            inWhichSet[index] = min;
        }
        index++;
    }
}

void KruskalMST::printMST(undirectedEdge* E, ofstream &outFile)
{
    outFile << "A MST of the input graph"
            << endl
            << "==============================================================="
            << endl << endl << numNodes << endl;
    undirectedEdge* temp = MSTofG->next;
    while (temp != NULL)
    {
        outFile << temp->Ni << " " << temp->Nj << " " << temp->edgeCost << endl;
        temp = temp ->next;
    }
    outFile << "Total cost: " << totalCost << endl;
}
void KruskalMST::printSet(ofstream &outFile){
    outFile<< endl; 
    outFile<< "Value of inWhichSet : [" << inWhichSet[0];
    for(int i = 1; i <= numNodes; i++){
        outFile << "," << inWhichSet[i];
    }
    outFile << "]" << endl; 
}

int main(int argc, char** argv)
{

    //Step 0: determine numNodes value and allocate data accordingly
    ifstream inFile(argv[1]);
    ofstream outFile1(argv[2]);
    ofstream outFile2(argv[3]);

    int numNodes;
    inFile >> numNodes;

    KruskalMST T(numNodes);
    int cost;
    int Nx;
    int Ny;
    //Step 2:: Repeat Step 1 until infile is empty

    while (inFile >> Nx)
    {
        inFile>> Ny;
        inFile>> cost;
        //Step 1: Create linked list of input edges
        undirectedEdge* newEdge = new undirectedEdge(Nx, Ny, cost);

        T.insertEdge(newEdge);

    }
    inFile.close();
    outFile2 << "LinkedList of Sorted, Undirected Edges <ni, nj, edgeCost> : "
            << endl
            << "==============================================================="
            << endl;

    T.printList(T.edgeListHead, outFile2);

    outFile2 << endl << endl;

    //Step 7: Repeat 4-6 until there is one remaining set
    while (T.numSets > 1)
    {
        //Step 4: minEdge
        undirectedEdge* minEdge = new undirectedEdge(T.edgeListHead->next->Ni, T.edgeListHead->next->Nj, T.edgeListHead->next->edgeCost);
        if (T.inWhichSet[minEdge->Ni] != T.inWhichSet[minEdge->Nj])
        {

            //Step 5
            //insert minEdge in the front of MSTofG
            minEdge->next = T.MSTofG->next;

            T.MSTofG->next = minEdge;

            //add the cost of minEdge to totalCost
            T.totalCost += minEdge->edgeCost;

            //merge the two nodes in minEdge
            T.mergeTwoSets(minEdge->Ni, minEdge->Nj);

            //Decrement the number of sets
            T.numSets--;
            
            //Step 6: Print
            outFile2 << "Current nodes in the Minimum Spanning Tree <ni, nj, edgeCost> : "
                    << endl
                    << "==============================================================="
                    << endl;

            T.printList(T.MSTofG, outFile2);
            
            //print inWhichSet array to argv3
            T.printSet(outFile2);
            
            outFile2 << endl << "End of iteration. " << endl << endl;
        }
        undirectedEdge* temp = T.edgeListHead->next;

        T.edgeListHead->next = temp->next;
    }
    //Step 8: 
    T.printMST(T.MSTofG, outFile1);
    outFile1.close();
    outFile2.close();

}
