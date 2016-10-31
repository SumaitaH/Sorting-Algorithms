//March 7, 2016 
//Algorithms 
//Implementation of bucket sort using the minimum # of buckets

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std; 

class bucketSort {
private:
    int minData; 
    int maxData; 
    int bucketSize; 
    int offset; 
    int* bucketAry;
public: 
    bucketSort(); 
    ~bucketSort(); 
    void findMinMax(int data); 
    int getIndex(int value); 
    void printBucketArray(ofstream &outFile2);
    void printSortedData(ofstream &outFile1);
    //Getters and setters 
    int getMin();
    int getMax();
    void setMin(int initMin); 
    void setMax(int initMax); 
    int* getBucket();
    void setBucketSize(int size);
    void setOffset(int val);   
};

bucketSort::bucketSort(){}
bucketSort::~bucketSort(){}
void bucketSort::findMinMax(int data){
    if(data > maxData){
        maxData = data; 
    }
    if(data < minData){
        minData = data;
    } 
}
int bucketSort::getIndex(int value){
    return value - offset;   
}
void bucketSort::setBucketSize(int size){
    bucketAry = new int[size+1]; 
    //initialize all values to 0
    for(int i = 0; i<=size; i++){
        bucketAry[i] = 0;  
    }
}
void bucketSort::printBucketArray(ofstream &outFile2){
    outFile2 << "Index: "; 
    for(int i =0; i < 19; i++){
        if(i < 10){
            outFile2 << "0" << i << " ";
        }
        else{
            outFile2 << i << " " ; 
        }    
    }
    outFile2 << endl; 
    outFile2 << "Value:  "; 
    for(int i =0; i < 19; i++){
        outFile2 << bucketAry[i] << "  "; 
    }
    outFile2 << endl; 
}
void bucketSort::printSortedData(ofstream &outFile1){
    int length = maxData - minData +1;
    int kVal = 1;
    outFile1 << "Sorted list using bucketSort Implementation: " << endl; 
    for(int i =0; i < length; i++){
        while(bucketAry[i]!=0){
            outFile1 << "Output #" << kVal << ": " << i + offset << endl; 
            kVal++;
            bucketAry[i]--; 
        }
    }
}
int bucketSort::getMin(){return minData;}
int bucketSort::getMax(){return maxData;}
void bucketSort::setMin(int initMin){minData = initMin;}
void bucketSort::setMax(int initMax){maxData = initMax;}
void bucketSort::setOffset(int val){offset = val;}
int* bucketSort::getBucket(){return bucketAry;}


int main(int argc, char** argv) {
    
    int data; 
    
    string filePath = argv[1];
    ifstream inFile(filePath);
    ofstream outFile1(argv[2]);
    ofstream outFile2(argv[3]);
 
    bucketSort bucketSorted;
    
    //go through infile and find min/max data
    inFile >> data; 
    bucketSorted.setMin(data); 
    bucketSorted.setMax(data);
    while(inFile >> data){
       // inFile >> data; 
        bucketSorted.findMinMax(data);
    }
    inFile.close(); 
    
    //Compute the minimum bucket size 
    int bucketSize = bucketSorted.getMax() - bucketSorted.getMin();
    
    //Compute the offset
    bucketSorted.setOffset(bucketSorted.getMin()); 
    
    //Dynamically allocate the bucketAry array to bucketSize
    bucketSorted.setBucketSize(bucketSize);
    
    //re-open the input file
    inFile.open(filePath); 
    outFile2 << "Updating values in array with bucketSort implementation..." << endl; 
    while(inFile >> data){
       // inFile >> data; 
        
        //Compute the index
        int index = bucketSorted.getIndex(data);
        
        //Update the array 
        bucketSorted.getBucket()[index]++;
        
        outFile2 << "BucketAry[" << index <<"]= " << bucketSorted.getBucket()[index] << endl;
    }
    outFile2 << endl << "Updating array complete." << endl << endl; 
    
    //Call printBucketArray
    bucketSorted.printBucketArray(outFile2);
    
    //Call printSortedData 
    bucketSorted.printSortedData(outFile1); 

    inFile.close();
    outFile1.close(); 
    outFile2.close(); 
}