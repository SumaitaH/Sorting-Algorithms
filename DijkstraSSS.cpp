/**Sumaita Hussain
 Implementation of the Minimum Spanning Tree using C++
 April 27, 2016 **/

#include <fstream>
#include <cstdlib>

using namespace std;

class DijkstraSSS {
public:
    //variables
    int numNodes;
    int sourceNode;
    int minNode;
    int currentNode;
    int newCost;
    int** costMatrix;
    int* fatherAry;
    int* markedAry;
    int* bestCostAry;

    //methods
    DijkstraSSS();
    DijkstraSSS(int numN);
    ~DijkstraSSS();
    //read from input file and fill the costMatrix
    void loadCostMatrix(ifstream &inFile);
    //copy the row of source nodes from costMatrix
    void loadBestCostAry();
    //set all to source
    void loadFatherAry();
    //set all to 0
    void loadMarkedAry();
    //it computes the currentNode’s cost ( bestCostArray[minNode] +  cost from minNode to currentNode, in costMatrix)
    int computeCost();
    //mark the minNode in markedAry
    void markMinNode(int minNode);
    //set node's father to be minNode in fatherAry
    void changeFather();
    //set node's best cost to newCost in bestCostAry
    void changeCost();
    //print sourceNode, fatherAry, bestCostAry, markedAry
    void debugPrint(ofstream &outFile);
    // trace from currentNode back to sourceNode (via fatherAry),
    // and print the shortest path from sourceNode to currentNode
    // with the cost to output-1 (with proper heading)
    void printShortestPaths(ofstream &outFile);
    //checks if all are marked
    bool isMarked();
};

DijkstraSSS::DijkstraSSS() {}

DijkstraSSS::DijkstraSSS(int numN) {
    numNodes = numN;
    costMatrix = new int*[numNodes];
    fatherAry = new int[numNodes];
    markedAry = new int[numNodes];
    bestCostAry = new int[numNodes];

    for (int i = 0; i < numNodes; i++) {
        costMatrix[i] = new int[numNodes];
    }
    for (int i = 0; i < numNodes; i++) {
        fatherAry[i] = i;
        bestCostAry[i] = 99999;
        for (int j = 0; j < numNodes; j++) {
            costMatrix[i][j] = 99999;
        }
        costMatrix[i][i] = 0;
    }
}

DijkstraSSS::~DijkstraSSS() {}

void DijkstraSSS::loadCostMatrix(ifstream &inFile) {
    int x;
    int y;
    int cost;
    while (inFile >> x) {
        inFile >> y;
        inFile >> cost;
        costMatrix[x - 1][y - 1] = cost;
    }
}

void DijkstraSSS::loadFatherAry() {
    for (int i = 0; i < numNodes; i++) {
        fatherAry[i] = sourceNode - 1;
    }
}

void DijkstraSSS::loadBestCostAry() {
    for (int i = 0; i < numNodes; i++) {
        bestCostAry[i] = costMatrix[sourceNode - 1][i];
    }
}

void DijkstraSSS::loadMarkedAry() {
    for (int i = 0; i < numNodes; i++) {
        markedAry[i] = 0;
    }
}

void DijkstraSSS::markMinNode(int minNode) {
    markedAry[minNode] = 1;
}

void DijkstraSSS::debugPrint(ofstream &outFile) {
    outFile << "The sourceNode is " << sourceNode << endl;
    outFile << "fatherAry: [";
    for (int i = 0; i < numNodes; i++) {
        if (i == numNodes - 1) {
            outFile << fatherAry[i] << " ]" << endl;
        } else {
            outFile << fatherAry[i] << ", ";
        }
    }
    outFile << "bestCostAry: [";
    for (int i = 0; i < numNodes; i++) {
        if (i == numNodes - 1) {
            outFile << bestCostAry[i] << " ]" << endl;
        } else {
            outFile << bestCostAry[i] << ", ";
        }
    }
    outFile << "markedAry: [";
    for (int i = 0; i < numNodes; i++) {
        if (i == numNodes - 1) {
            outFile << markedAry[i] << " ]" << endl;
        } else {
            outFile << markedAry[i] << ", ";
        }
    }
    outFile << endl << endl;
}
//it computes the currentNode’s cost ( bestCostArray[minNode] +  cost from minNode to currentNode, in costMatrix)
int DijkstraSSS::computeCost() {
    return bestCostAry[minNode] + costMatrix[minNode][currentNode];
}
//set node's father to be minNode in fatherAry
void DijkstraSSS::changeFather() {
    fatherAry[currentNode] = minNode;
}
//set node's best cost to newCost in bestCostAry
void DijkstraSSS::changeCost() {
    bestCostAry[currentNode] = newCost;
}

bool DijkstraSSS::isMarked() {
    for (int i = 0; i < numNodes; i++) {
        if (markedAry[i] == 0) {
            return false;
        }
    }
    return true;
} // trace from currentNode back to sourceNode (via fatherAry),
// and print the shortest path from sourceNode to currentNode
// with the cost to output-1 (with proper heading)

void DijkstraSSS::printShortestPaths(ofstream& outFile) {

    outFile << "The path from " << sourceNode << " to " << currentNode << ": "
            << sourceNode;
    if (sourceNode != currentNode) {
        int backwardsPath[numNodes];
        int currentIndex = currentNode - 1;
        for (int i = 0; i < numNodes; i++) {
            if (fatherAry[currentIndex] != (sourceNode - 1)) {
                //outFile << "->" << fatherAry[currentIndex]+1;
                backwardsPath[i] = fatherAry[currentIndex];
                currentIndex = fatherAry[currentIndex];
            } else if (fatherAry[currentIndex] == (sourceNode - 1)) {
                backwardsPath[i] = -1;
            }
        }
        for (int i = numNodes - 1; i >= 0; i--) {
            if (backwardsPath[i] != -1) {
                outFile << "->" << backwardsPath[i] + 1;
            }
        }
    }
    outFile << "->" << currentNode << " : cost = " << bestCostAry[currentNode - 1] << endl;
}

int main(int argc, char** argv) {
    //Step 0
    ifstream infile(argv[1]);
    ofstream outFile1(argv[2]);
    ofstream outFile2(argv[3]);

    int numN;
    infile >> numN;
    outFile1 << endl << "There are " << numN << " nodes in the input graph." << endl;
    outFile1 << "==========================================================="
             << endl;

    DijkstraSSS dAlg(numN);

    //Step 1
    dAlg.loadCostMatrix(infile);
    dAlg.sourceNode = 1;
    dAlg.markMinNode(dAlg.sourceNode - 1);

    //Step 11: repeat Step 2 - Step 10 until sourceNode > numNodes
    while (dAlg.sourceNode <= dAlg.numNodes) {
        outFile2 << "Iteration # " << dAlg.sourceNode << endl 
                << "===========================================================" 
                << endl;
         //Step 2
        dAlg.loadBestCostAry();
        dAlg.loadFatherAry();
        dAlg.loadMarkedAry();

        //Step 6: Repeat Step 3 - 5 until all nodes are marked
        while (!(dAlg.isMarked())) {
            //Step 3: find an *unmarked node* with minimum cost from bestCostAry

            int minNodeCost = 99999;
            for (int i = 0; i < dAlg.numNodes; i++) {
                if (dAlg.markedAry[i] == 0 && (dAlg.bestCostAry[i] < minNodeCost)) {
                    minNodeCost = dAlg.bestCostAry[i];
                    dAlg.minNode = i;
                }
            }

            dAlg.markMinNode(dAlg.minNode);
            //dAlg.markMinNode();
            dAlg.debugPrint(outFile2);

            //Step 5 : repeat step 4 until all unmarked nodes are evaluated

            for (int i = 0; i < dAlg.numNodes; i++) {
                //Step 4: expanding the minNode
                //if unmarked and currentNode != minNode
                if (dAlg.markedAry[i] == 0) {

                    dAlg.currentNode = i;
                    //dAlg.newCost = dAlg.computeCost(dAlg.minNode,dAlg.currentNode);
                    dAlg.newCost = dAlg.computeCost();
                    if (dAlg.newCost < dAlg.bestCostAry[dAlg.currentNode]) {
                        //dAlg.changeFather(dAlg.currentNode, dAlg.minNode);
                        dAlg.changeFather();
                        //dAlg.changeCost(dAlg.currentNode, dAlg.newCost);
                        dAlg.changeCost();
                        dAlg.debugPrint(outFile2);
                    }
                }

            }//end of step 5
        }//end of step 6
        
        //Step 7: currentNode<-1
        dAlg.currentNode = 1;

        outFile1 << "Source node = " << dAlg.sourceNode << endl;
        outFile1 << "The shortest paths from node " << dAlg.sourceNode << " are: " << endl << endl;

        //Step 10: repeat step 8 and 9  until currentNode >= numNodes
        while (dAlg.currentNode <= dAlg.numNodes) {
            //Step 8
            dAlg.printShortestPaths(outFile1);
            //Step 9
            dAlg.currentNode++;
        }//end of step 10
        outFile1 << endl
                 << "===========================================================" 
                 << endl;
        dAlg.sourceNode++;
    }//end of step 11
    infile.close();
    outFile1.close();
    outFile2.close();
}