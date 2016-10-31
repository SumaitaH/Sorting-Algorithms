/* Sumaita Hussain
 * Algorithms (323-23) 
 * 
 * Project 10.1: Graph Coloring Problem: Given an undirected graph G = <N,E>, 
 * find the minimum number of colors to color all nodes in N, 
 * such that two adjacent nodes <ni, nj> are not colored the same.
 */
#include <cstdlib>
#include <fstream>

using namespace std;

class graphColoring{
public: 
    int** adjacencyMatrix;
    int uncoloredNode; 
    int newColor;
    int numNodes; 
    
    graphColoring(int size);
    ~graphColoring(); 
    void loadAdjMatrix(ifstream &inFile, ofstream &outFile);
    void printAdjMatrix(ofstream &outFile);
};

graphColoring::graphColoring(int size){
    numNodes = size;  
    adjacencyMatrix = new int*[size];
    for(int i = 0; i < size; i++){
        adjacencyMatrix[i] = new int[size];
    }
    for(int i =0; i < size; i++){
        for(int j = 0; j < size; j++){
            adjacencyMatrix[i][j] = 0;
        }
    }
}
graphColoring::~graphColoring(){}

void graphColoring::loadAdjMatrix(ifstream &inFile, ofstream &outFile){
    int Ni; 
    int Nj; 
    
    while(inFile >> Ni){
        inFile >> Nj;      
        outFile << "<" << Ni << ", " << Nj << ">, "; 
        adjacencyMatrix[Ni-1][Nj-1] = 1;
        adjacencyMatrix[Nj-1][Ni-1] = 1;   
    }
    outFile << endl << endl; 
}
void graphColoring::printAdjMatrix(ofstream &outFile){
        outFile << "The adjacencyMatrix values: " << endl << endl
                << "   "; 
        
    for(int i = 0; i < numNodes; i++){
        if(i >= 9){
            outFile << i+1 << " "; 
        } else
        {
            outFile << " " << i+1 << " ";
        }
    }
        outFile << endl << endl;
    for(int i = 0; i < numNodes; i++){
        if(i >= 9){
            outFile << i+1 << " ";
        } else{
            outFile << i+1 << "  ";
        }
        
        for(int j = 0; j < numNodes; j++){
            outFile << "[" << adjacencyMatrix[i][j]<< "]";
        } 
        outFile << endl;
    }
        outFile << endl << endl;
}


int main(int argc, char** argv) {
    
    ifstream inFile(argv[1]);
    ofstream outFile1(argv[2]);
    //Step 0: numNode <-- get from input file 
    
    int numNodes; 
    inFile >> numNodes; 
    
    //dynamically allocate adjacencyMatrix 
    graphColoring gColProb(numNodes);
    outFile1 << "Bidirectional Edges: " << endl; 
    //load adjacencyMatrix from the input pairs
    gColProb.loadAdjMatrix(inFile, outFile1);
    //print adjacencyMatrix
    gColProb.printAdjMatrix(outFile1);
    
    int allNodesColored = 0; 
    int iteration = 0; 
    
    //Step 5: Repeat steps 1-3 until all nodes are colored  
    while(allNodesColored != numNodes){
        
        iteration++; 
        outFile1 << "Iteration # " << iteration << endl <<endl ; 
        
        //Step 1:
        gColProb.newColor++; 
        
        //Step 3: Repeat step 2 until all uncolored nodes are checked
        for(int i =0; i < numNodes; i++){
            if(gColProb.adjacencyMatrix[i][i]==0){
                
                //Step 2: unColoredNode <--get an uncolored node 
                gColProb.uncoloredNode = i;               
                 
                //check if uncoloredNode does not have any adjacent node that
                //is colored with newColor
	        //adjacentMatrix[uncolorNode][uncolorNode] <-- newColor
                bool checkAdj = false;
                for(int j= 0; j < numNodes; j++){
             
                    if(gColProb.adjacencyMatrix[gColProb.uncoloredNode][j]==1 
                        &&gColProb.adjacencyMatrix[j][j]== gColProb.newColor){
                        checkAdj = true; 
                    }
                }
                //adjacentMatrix[uncolorNode][uncolorNode] <-- newColor
                if(!checkAdj){
                    gColProb.adjacencyMatrix[gColProb.uncoloredNode][gColProb.uncoloredNode] = gColProb.newColor;
                    allNodesColored++;         
                    gColProb.printAdjMatrix(outFile1);
                }                
            }
        }    
    }

    outFile1 << "All nodes have been colored." << endl << endl  
             << "# of colors used: " << gColProb.newColor << endl; 
    
    outFile1 << "Final adjacencyMatrix: " << endl << endl; 
    gColProb.printAdjMatrix(outFile1);
    
    outFile1.close();
    inFile.close(); 
    
    return 0;
}

