//Sumaita Hussain 
//Quad Tree Implementation

#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;

class image {
public:
    int numRows;
    int numCols;
    int minVal;
    int maxVal;
    int** imgAry;
    image();
    image(int nRows, int nCols, int minV, int maxV);
    ~image();
    void makeImgAry();
    void loadImage(ifstream &inFile);

};

image::image(){}
image::~image() {
}
image::image(int nRows, int nCols, int minV, int maxV) {

    numRows = nRows;
    numCols = nCols;
    minVal = minV;
    maxVal = maxV;
}
void image::makeImgAry(){
    imgAry = new int*[numRows];
    for (int i = 0; i < numRows; i++) {
        imgAry[i] = new int[numCols];
    }
}
void image::loadImage(ifstream &inFile) {
    int data;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            inFile >> imgAry[i][j];
        }
    }
}

class QuadTreeNode {
public:
    friend class QuadTree;
    friend class image;
    int numRows;
    int numCols;
    int minVal;
    int maxVal;
    int color;
    int rowOffset;
    int colOffset;
    QuadTreeNode* NW_Kid;
    QuadTreeNode* SW_Kid;
    QuadTreeNode* SE_Kid;
    QuadTreeNode* NE_Kid;

    QuadTreeNode(int** img, int nRows, int nCols, int rOff, int cOff, int typeNode, ofstream &outFile2);
    ~QuadTreeNode();
    void computeOffsets(int rOff, int cOff, int typeNode);
    void computeNumRowsCols(int nRows, int nCols, int typeNode);
    void computeMinMaxValue();
    void computeColor(int** img);
    void printNode(QuadTreeNode* T, ofstream &outFile1);

};

QuadTreeNode::QuadTreeNode(int** img, int nRows, int nCols, int rOff, int cOff, int typeNode, ofstream &outFile2) {
    
    rowOffset = 0;
    colOffset = 0;
    computeNumRowsCols(nRows, nCols, typeNode);
    computeOffsets(rOff, cOff, typeNode);
    computeColor(img);
    computeMinMaxValue();
    
    outFile2 << "(" << rowOffset << " , " << colOffset << ") --> " ;
    outFile2 << "(" << rowOffset+numRows << " , " << colOffset+numCols << ")" << endl; 
    outFile2 << "Color: " << color << endl; 
    outFile2 << "minVal: " << minVal << endl; 
    outFile2 << "maxVal: " << maxVal << endl; 
    outFile2 << "numRows/numCols: " << numRows << endl <<endl; 

    NW_Kid = NULL;
    SW_Kid = NULL;
    SE_Kid = NULL;
    NE_Kid = NULL;

}
void QuadTreeNode::computeNumRowsCols(int nRows, int nCols, int typeNode) {
    switch (typeNode) {
        case 0:
            numRows = nRows;
            numCols = nCols;
            break;
        case 1:
        case 2:
        case 3:
        case 4:
            numRows = nRows / 2;
            numCols = nCols / 2;
            break;
    }
}
void QuadTreeNode::computeOffsets(int rOff, int cOff, int typeNode) {
    switch (typeNode) {
        case 1:
            rowOffset = rOff;
            colOffset = cOff;
            break;
        case 2:
            rowOffset = rOff + numRows;
            colOffset = cOff; 
            break;
        case 3:
            rowOffset = rOff + numRows;
            colOffset = cOff + numCols;
            break;
        case 4:
            rowOffset = rOff;
            colOffset = cOff + numCols;
            break;
        case 0:
            break;
        default:
            cout << "Wrong input";
            break;
    }
}
void QuadTreeNode::computeColor(int** img) {
    bool black = false;
    bool white = false;
 
    for (int i = rowOffset; i < rowOffset + numRows; i++) {
        for (int j = colOffset; j < colOffset + numCols; j++) {
            if (img[i][j] == 0) {
                white = true;
            } else {
                black = true;
            }
        }
    }
    if (black && white) {
        color = 2;
    } else if (black) {
        color = 1;
    } else {
        color = 0;
    }
}

void QuadTreeNode::computeMinMaxValue() {
    if (color == 0) {
        minVal = 0;
        maxVal = 0;
    }
    if (color == 1) {
        minVal = 1;
        maxVal = 1;
    } else {
        minVal = 0;
        maxVal = 1;
    }
}

void QuadTreeNode::printNode(QuadTreeNode* T, ofstream &outFile1) {
    if (T->color != 2) {
        outFile1 << T->color << " " << T->numRows << " " << T->numCols << " " << T->minVal << " " << T->maxVal << " " << T->rowOffset
                << " " << T->colOffset << " " << 0 << " " << 0 << " " << 0 << " " << 0 << endl;
    } else {
        outFile1 << T->color << " " << T->numRows << " " << T->numCols << " " << T->minVal << " " << T->maxVal << " " << T->rowOffset
                << " " << T->colOffset << " " << T->NW_Kid->color << " " << T->SW_Kid->color << " " << T->SE_Kid->color << " " << T->NE_Kid->color << endl;
    }
}

QuadTreeNode::~QuadTreeNode() {
}


class QuadTree {
public:
    QuadTreeNode* rootNode;
    int** inputImg;

    QuadTree(int** img, QuadTreeNode* T);
    QuadTree(int** img);
    ~QuadTree();
    void buildQuadTree(QuadTreeNode* T, ofstream &outFile2);
    void printQuadTree(QuadTreeNode* T, ofstream &outFile1);

};

QuadTree::QuadTree(int** img) {
    inputImg = img;
}
QuadTree::QuadTree(int** img, QuadTreeNode* T) {
    inputImg = img;
    rootNode = T;
}
QuadTree::~QuadTree() {
}

void QuadTree::printQuadTree(QuadTreeNode* T, ofstream &outFile1) {
    if (T == NULL) {
    }
    else {
        T->printNode(T, outFile1);
        printQuadTree(T->NW_Kid, outFile1);
        printQuadTree(T->SW_Kid, outFile1);
        printQuadTree(T->SE_Kid, outFile1);
        printQuadTree(T->NE_Kid, outFile1);
    }
}

void QuadTree::buildQuadTree(QuadTreeNode* T, ofstream &outFile2) {

    if (T == NULL || T->color != 2) {

    } else {

        T->NW_Kid = new QuadTreeNode(inputImg, T->numRows, T->numCols, T->rowOffset, T->colOffset, 1, outFile2);
        outFile2 << "Creating NW_Kid" << endl <<endl; 

        buildQuadTree(T->NW_Kid, outFile2);
        T->SW_Kid = new QuadTreeNode(inputImg, T->numRows, T->numCols, T->rowOffset, T->colOffset, 2, outFile2);
        outFile2 << "Creating SW_Kid" << endl <<endl; 

        buildQuadTree(T->SW_Kid, outFile2);
        T->SE_Kid = new QuadTreeNode(inputImg, T->numRows, T->numCols, T->rowOffset, T->colOffset, 3, outFile2);
        outFile2 << "Creating SE_Kid" << endl <<endl; 

        buildQuadTree(T->SE_Kid, outFile2);
        T->NE_Kid = new QuadTreeNode(inputImg, T->numRows, T->numCols, T->rowOffset, T->colOffset, 4, outFile2);
        outFile2 << "Creating NE_Kid" << endl <<endl; 

        buildQuadTree(T->NE_Kid, outFile2);
    }
}


int main(int argc, char** argv) {

    ifstream infile(argv[1]);
    ofstream outfile1(argv[2]);
    ofstream outfile2(argv[3]);

    //Step 1: Read the image header and obtain values

    int nRows;
    int nCols;
    int minV;
    int maxV;

    infile >> nRows;
    infile >> nCols;
    infile >> minV;
    infile >> maxV;

    //Initialize object of class image
    image img(nRows, nCols, minV, maxV);
    //Step 2: makeImgAry()
    img.makeImgAry();
    //Step 3: loadImage()
    img.loadImage(infile);
    infile.close();

    //Step 4: rootNode <- Create the quadtree root

    QuadTree T(img.imgAry);
    
    outfile2 << "Quadtree created." << endl;

    T.rootNode = new QuadTreeNode(img.imgAry, nRows, nCols, 0, 0, 0, outfile2);
    
    outfile2 << "Root Created" << endl << endl;
    outfile2 << "Building Quad Tree..." << endl <<endl;
    
    //Step 5 <-- BuildQuadTree
    T.buildQuadTree(T.rootNode, outfile2);
    outfile2 << "Finished building." << endl << endl; 
    outfile2 << "Printing Quad Tree..." << endl;
    
    //Step 6 <-- PrintQuadTree
    outfile1 << "QuadTree Encoding" << endl; 
    T.printQuadTree(T.rootNode, outfile1);
    
    outfile1.close();
    //cout << "c: " << count << endl; 

}
