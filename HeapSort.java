import java.io.BufferedWriter;
import java.io.File;
//import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
//import java.io.InputStream;
//import java.nio.file.Files;
import java.util.Scanner;


public class HeapSort {

	int[] heapAry; 

	HeapSort(int value){
		heapAry = new int[value+1]; 
		heapAry[0] = 0; 
	}

	void buildHeap(Scanner inFile, File in, BufferedWriter outFile1) throws IOException{
		inFile = new Scanner(in); 
		outFile1.write("Building the heap: ");
		outFile1.newLine(); 
		while(inFile.hasNextInt()){
			insertOneDataItem(inFile.nextInt());
			bubbleUp(); 
			printHeap(outFile1);
			outFile1.write("End of iteration.");
			outFile1.newLine(); 
			outFile1.newLine(); 
		}
		inFile.close(); 
		
	}
	void deleteHeap(BufferedWriter outFile1, BufferedWriter outFile2) throws IOException{

		outFile1.write("Deleting the Root");
		outFile1.newLine(); 
		while(!isHeapEmpty()){
			int delRoot = deleteRoot(); 
			bubbleDown(); 
			printHeap(outFile1); 
			outFile1.write("End of iteration.");
			outFile1.newLine(); 
			outFile1.newLine(); 
			outFile2.write("Deleting root value: " + String.valueOf(delRoot));
			outFile2.newLine(); 
			System.out.println(delRoot); 
		}

	}
	void insertOneDataItem(int data){
		if(isHeapEmpty()){
			heapAry[0]++; 
			heapAry[1] = data; 
		}
		else{
			heapAry[0]++;
			heapAry[heapAry[0]] = data; 
		}
	}

	void bubbleUp(){
		int childIndex = heapAry[0]; 
		while(childIndex!= 1){
			int parent = childIndex/2; 
			if(heapAry[parent] > heapAry[childIndex]){
				int temp = heapAry[childIndex];
				heapAry[childIndex] = heapAry[parent]; 
				heapAry[parent] = temp; 
			}
			childIndex = parent; 
		}
	}
	int deleteRoot(){
		int temp = heapAry[1]; 
		heapAry[1] = heapAry[heapAry[0]];
		heapAry[heapAry[0]] = -1; 
		heapAry[0]--; 
		return temp; 
	}
	void bubbleDown(){
		int parent = 1; 
		while(parent < heapAry[0]){

			int lChild = parent*2; 
			int rChild = parent*2+1; 
			int min = 0; 
			if(rChild > heapAry[0] && lChild > heapAry[0]){
				break;
			}
			else if(rChild > heapAry[0] && lChild <=heapAry[0]){
				min = lChild;
			}
			else if(rChild <= heapAry[0] && lChild > heapAry[0]){
				min = rChild; 
			}
			else{
				min = Math.min(heapAry[rChild], heapAry[lChild]);
				
				if(min == heapAry[lChild]){
					min = lChild;
				}
				else{
					min = rChild; 
				}
			}
			if(heapAry[parent] > heapAry[min]){
				int temp = heapAry[parent]; 
				heapAry[parent] = heapAry[min];
				heapAry[min] = temp; 
			}
			parent = min; 
		}
	}
	boolean isHeapEmpty(){
		if(heapAry[0] == 0){
			return true; 
		}
		return false; 
	}
	boolean isHeapFull(){
		if(heapAry.length == heapAry[0]){
			return true;
		}
		return false; 
	}
	void printHeap(BufferedWriter outFile) throws IOException{
		int size = 0; 
		if(heapAry[0] <= 10)
		{
			size = heapAry[0];
		}
		else {
			size = 10; 
		}
		for(int i =0; i < size; i++){
			
			outFile.write("Value at index "+ String.valueOf(i) + ": "+ String.valueOf(heapAry[i])); 
			outFile.newLine(); 
		}

	}

	public static void main(String[] args) throws IOException{
		int count = 0; 
		System.out.println("Hello");
		File instream = new File(args[0]);
		FileWriter out1 = new FileWriter(args[1]);
		FileWriter out2 = new FileWriter(args[2]);
		BufferedWriter outFile1 = new BufferedWriter(out1);
		BufferedWriter  outFile2 = new BufferedWriter(out2);
		Scanner inputF = new Scanner(instream); 
		
		while(inputF.hasNextInt()){
			count++;  
		}
		inputF.close(); 
		HeapSort sortedArray = new HeapSort(count); 
		sortedArray.buildHeap(inputF, instream, outFile1);
		sortedArray.deleteHeap(outFile1,outFile2); 
		outFile1.close(); 
		outFile2.close(); 
		
	}

}
