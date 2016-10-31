/**Sumaita Hussain
 Implementation of the Minimum Spanning Tree using C++
 April 27, 2016 **/

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class DijkstraSSS {

	// variables
	int numNodes;
	int sourceNode;
	int minNode;
	int currentNode;
	int newCost;
	int[][] costMatrix;
	int[] fatherAry;
	int[] markedAry;
	int[] bestCostAry;

	DijkstraSSS() {
	}

	DijkstraSSS(int numN) {
		numNodes = numN;
		costMatrix = new int[numNodes][numNodes];
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

	void loadCostMatrix(Scanner inFile) {
		int x;
		int y;
		int cost;
		while (inFile.hasNext()) {
			x = inFile.nextInt();
			y = inFile.nextInt();
			cost = inFile.nextInt();
			costMatrix[x - 1][y - 1] = cost;
		}
	}

	void loadFatherAry() {
		for (int i = 0; i < numNodes; i++) {
			fatherAry[i] = sourceNode - 1;
		}
	}

	void loadBestCostAry() {
		for (int i = 0; i < numNodes; i++) {
			bestCostAry[i] = costMatrix[sourceNode - 1][i];
		}
	}

	void loadMarkedAry() {
		for (int i = 0; i < numNodes; i++) {
			markedAry[i] = 0;
		}
	}

	void markMinNode(int minNode) {
		markedAry[minNode] = 1;
	}

	void debugPrint(BufferedWriter outFile) {
		try {
			// outFile << "The sourceNode is " << sourceNode << endl;
			outFile.write("The Source Node is " + sourceNode + ".");
			outFile.newLine();
			outFile.write("fatherAry: [");
			// outFile << "fatherAry: [";
			for (int i = 0; i < numNodes; i++) {
				if (i == numNodes - 1) {
					outFile.write(fatherAry[i] + " ]");
					outFile.newLine();
				} else {
					outFile.write(fatherAry[i] + ", ");
				}
			}
			outFile.write("bestCostAry: [");
			for (int i = 0; i < numNodes; i++) {
				if (i == numNodes - 1) {
					outFile.write(bestCostAry[i] + " ]");
					outFile.newLine();
				} else {
					outFile.write(bestCostAry[i] + ", ");
				}
			}
			outFile.write("markedAry: [");
			for (int i = 0; i < numNodes; i++) {
				if (i == numNodes - 1) {
					outFile.write(markedAry[i] + " ]");
					outFile.newLine();
				} else {
					outFile.write(markedAry[i] + ", ");
				}
			}
			outFile.newLine();
			outFile.newLine();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	// it computes the currentNode’s cost ( bestCostArray[minNode] + cost from
	// minNode to currentNode, in costMatrix)
	int computeCost() {
		return bestCostAry[minNode] + costMatrix[minNode][currentNode];
	}

	// set node's father to be minNode in fatherAry
	void changeFather() {
		fatherAry[currentNode] = minNode;
	}

	// set node's best cost to newCost in bestCostAry
	void changeCost() {
		bestCostAry[currentNode] = newCost;
	}

	boolean isMarked() {
		for (int i = 0; i < numNodes; i++) {
			if (markedAry[i] == 0) {
				return false;
			}
		}
		return true;
	} // trace from currentNode back to sourceNode (via fatherAry),
		// and print the shortest path from sourceNode to currentNode
		// with the cost to output-1 (with proper heading)

	void printShortestPaths(BufferedWriter outFile) {
		try {
			outFile.write("The path from " + sourceNode + " to " + currentNode
					+ ": " + sourceNode);

			if (sourceNode != currentNode) {
				int[] backwardsPath = new int[numNodes];
				int currentIndex = currentNode - 1;
				for (int i = 0; i < numNodes; i++) {
					if (fatherAry[currentIndex] != (sourceNode - 1)) {
						// outFile << "->" << fatherAry[currentIndex]+1;
						backwardsPath[i] = fatherAry[currentIndex];
						currentIndex = fatherAry[currentIndex];
					} else if (fatherAry[currentIndex] == (sourceNode - 1)) {
						backwardsPath[i] = -1;
					}
				}
				for (int i = numNodes - 1; i >= 0; i--) {
					if (backwardsPath[i] != -1) {
						int total = backwardsPath[i] + 1;
						outFile.write("->" + total);
					}
				}
			}
			outFile.write("->" + currentNode + " : cost = "
					+ bestCostAry[currentNode - 1]);
			outFile.newLine();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public static void main(String[] args) {
		try {

			// Step 0
			Scanner infile = new Scanner(new FileReader(args[0]));
			File outPath1 = new File(args[1]);
			File outPath2 = new File(args[2]);

			BufferedWriter outFile1 = new BufferedWriter(new FileWriter(
					outPath1));
			BufferedWriter outFile2 = new BufferedWriter(new FileWriter(
					outPath2));

			int numN = infile.nextInt();

			outFile1.write("There are " + numN + " nodes in the input graph.");
			outFile1.newLine();
			outFile1.write("===========================================================");
			outFile1.newLine();

			DijkstraSSS dAlg = new DijkstraSSS(numN);

			// Step 1
			dAlg.loadCostMatrix(infile);
			dAlg.sourceNode = 1;
			dAlg.markMinNode(dAlg.sourceNode - 1);

			// Step 11: repeat Step 2 - Step 10 until sourceNode > numNodes
			while (dAlg.sourceNode <= dAlg.numNodes) {
				outFile2.write("Iteration #" + dAlg.sourceNode);
				outFile2.newLine();
				outFile2.write("===========================================================");
				outFile2.newLine();

				// Step 2
				dAlg.loadBestCostAry();
				dAlg.loadFatherAry();
				dAlg.loadMarkedAry();

				// Step 6: Repeat Step 3 - 5 until all nodes are marked
				while (!(dAlg.isMarked())) {
					// Step 3: find an *unmarked node* with minimum cost from
					// bestCostAry

					int minNodeCost = 99999;
					for (int i = 0; i < dAlg.numNodes; i++) {
						if (dAlg.markedAry[i] == 0
								&& (dAlg.bestCostAry[i] < minNodeCost)) {
							minNodeCost = dAlg.bestCostAry[i];
							dAlg.minNode = i;
						}
					}

					dAlg.markMinNode(dAlg.minNode);
					// dAlg.markMinNode();
					dAlg.debugPrint(outFile2);

					// Step 5 : repeat step 4 until all unmarked nodes are
					// evaluated

					for (int i = 0; i < dAlg.numNodes; i++) {
						// Step 4: expanding the minNode
						// if unmarked and currentNode != minNode
						if (dAlg.markedAry[i] == 0) {

							dAlg.currentNode = i;
							// dAlg.newCost =
							// dAlg.computeCost(dAlg.minNode,dAlg.currentNode);
							dAlg.newCost = dAlg.computeCost();
							if (dAlg.newCost < dAlg.bestCostAry[dAlg.currentNode]) {
								// dAlg.changeFather(dAlg.currentNode,
								// dAlg.minNode);
								dAlg.changeFather();
								// dAlg.changeCost(dAlg.currentNode,
								// dAlg.newCost);
								dAlg.changeCost();
								dAlg.debugPrint(outFile2);
							}
						}

					}// end of step 5
				}// end of step 6

				// Step 7: currentNode<-1
				dAlg.currentNode = 1;
				outFile1.write("Source Node = " + dAlg.sourceNode);
				outFile1.newLine();
				outFile1.write("The shortest paths from node "
						+ dAlg.sourceNode + " are: ");
				outFile1.newLine();
				outFile1.newLine();

				// Step 10: repeat step 8 and 9 until currentNode >= numNodes
				while (dAlg.currentNode <= dAlg.numNodes) {
					// Step 8
					dAlg.printShortestPaths(outFile1);
					// Step 9
					dAlg.currentNode++;
				}// end of step 10
				outFile1.newLine();
				outFile1.write("===========================================================");
				outFile1.newLine();

				dAlg.sourceNode++;

			}// end of step 11
			infile.close();
			outFile1.close();
			outFile2.close();

		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}

	}
}