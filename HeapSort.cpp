/* Sumaita Hussain
 Project 4: HeapSort based on Implementation of POBT/ Priority Q
 Language: C++ */

#include <cstdlib>
#include <fstream> 
#include <iostream>

using namespace std;

class HeapSort {
public:
    int* heapAry;

    HeapSort(int count);
    ~HeapSort();
    void buildHeap(ifstream &inFile, string file, ofstream &outFile);
    void deleteHeap(ofstream &outFile1, ofstream &outFile2);
    void insertOneDataItem(int data);
    int deleteRoot();
    void bubbleUp();
    void bubbleDown();
    bool isHeapEmpty();
    bool isHeapFull();
    void printHeap(ofstream &outFile);
};
//Constructor initialized array with size count and ary[0] = count  

HeapSort::HeapSort(int count) {
    heapAry = new int[count++];
    heapAry[0] = 0;
}
//Destructor

HeapSort::~HeapSort() {
    cout << "~HeapSort" << endl;
}

/* 1. Add data from file to the heap 
   2. insert item and bubble up
   3. Print to out file
   4. Repeat 1-3 until there is no more data*/

void HeapSort::buildHeap(ifstream &inFile, string file, ofstream &outFile) {
    int num;
    inFile.open(file);
    outFile << "Bulding the HeapSort Array:" << endl; 
    outFile << "(Up to first 10 values)" << endl << endl;
    while (!inFile.eof()) {
        inFile >> num;
        outFile << "Array data after inserting " << num << ":" << endl << endl; 
        insertOneDataItem(num);
        bubbleUp();
        
        printHeap(outFile);
        outFile << "End of iteration." << endl << endl;
    }
   // outFile.close();
    inFile.close();
}

/* 1. Delete root 
   2. Bubble down 
   3. Print contents of array to out1 file
   4. Print root to out2 file
   5. Repeat steps 1-4 until heap is empty */

void HeapSort::deleteHeap(ofstream &outFile1, ofstream &outFile2) {
    int num;
    outFile1 << "Deleting the HeapSort Array Values: " << endl;
    outFile1 << "(Up to first 10 values)" << endl << endl;
    while (!isHeapEmpty()) {
        num = deleteRoot();
        outFile1 << "Array data after removing " << num << ":" << endl <<endl; 
        bubbleDown();
        outFile2 << "Deleting root value:" << num << endl; 
        printHeap(outFile1);
        outFile1 << "End of iteration." << endl << endl;

    }
    outFile1.close();
    outFile2.close(); 
    delete heapAry;
}

// Insert data at last index 

void HeapSort::insertOneDataItem(int data) {
    if (isHeapEmpty()) {
        heapAry[1] = data;
        heapAry[0]++;
    } else {
        int lastInd = heapAry[0] + 1;
        heapAry[lastInd] = data;
        heapAry[0]++;
    }
}
//Delete data from the root. Replace with value from last index

int HeapSort::deleteRoot() {
    int lastInd = heapAry[0];
    int temp = heapAry[1];
    heapAry[1] = heapAry[lastInd];
    heapAry[lastInd] = 0;
    heapAry[0]--;
    return temp;
}
//Sort data by swapping parent/child values until parent < child 

void HeapSort::bubbleUp() {
    int lastInd = heapAry[0];
    int childIndex = lastInd;
    int parentIndex;
    while (childIndex > 1) {
        parentIndex = childIndex / 2;
        if (heapAry[parentIndex] > heapAry[childIndex]) {
            int temp = heapAry[parentIndex];
            heapAry[parentIndex] = heapAry[childIndex];
            heapAry[childIndex] = temp;
        }
        childIndex = parentIndex;
    }

}
//Sort root by swapping parent/child until parent < child. This is for 
//when the root is deleted. 

void HeapSort::bubbleDown() {
    int parent = 1;
    int rChild;
    int lChild;

    while (parent <= heapAry[0]) {
        rChild = parent * 2;
        lChild = parent * 2 + 1;
        int min;

        //Checks whether child index is out of bounds 
        if (rChild > heapAry[0] || lChild > heapAry[0]) {
            break;
        }
        if (rChild > heapAry[0] && lChild <= heapAry[0]) {
            min = heapAry[lChild];
        }
        if (rChild <= heapAry[0] && lChild > heapAry[0]) {
            min = heapAry[rChild];
        } else {
            min = std::min(heapAry[rChild], heapAry[lChild]);
            heapAry[rChild] == min ? min = rChild : min = lChild;
        }
        if (heapAry[parent] > min) {
            int temp = heapAry[min];
            heapAry[min] = heapAry[parent];
            heapAry[parent] = temp;
        }
        parent = min;
    }
}

bool HeapSort::isHeapEmpty() {
    if (heapAry[0] == 0) {
        return true;
    }
    return false;
}

bool HeapSort::isHeapFull() {
    if (heapAry[0] == sizeof (heapAry)) {
        return true;
    }
    return false;
}

void HeapSort::printHeap(ofstream &outFile) {
    int iteration;
    if (heapAry[0] <=9) {
        iteration = heapAry[0];
    } else {
        iteration = 9;
    }

    for (int i = 0; i <= iteration; i++) {
        outFile << "Index [" << i << "]" << ": " << heapAry[i] << endl;
    } 
}

int main(int argc, char** argv) {

    int count = 0;
    int val;
    string inFilePath = argv[1];
    ifstream inFile(argv[1]);
    ofstream outFile1(argv[2]);
    ofstream outFile2(argv[3]);

    if (!inFile) {
        cout << "ERROR: WRONG INPUT FILE PATH" << endl;
    }
    if (!outFile1) {
        cout << "ERROR: WRONG OUTPUT FILE 1 PATH" << endl;
    }
    if (!outFile2) {
        cout << "ERROR: WRONG OUTPUT FILE 2 PATH" << endl;
    }
    while (!inFile.eof()) {
        inFile >> val;
        count++;
    }
    inFile.close();

    HeapSort sortedArrayH(count);
    sortedArrayH.buildHeap(inFile, inFilePath, outFile1);
    sortedArrayH.deleteHeap(outFile1, outFile2);

    return 0;
}