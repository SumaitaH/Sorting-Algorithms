import java.io.*; 
import java.util.*;

public class bucketSort {

	int minData; 
	int maxData;
	int offset; 
	int[] bucketAry; 
	
	bucketSort(){
		minData = 0; 
		maxData = 0; 
		offset = 0; 
	}
	void findMinMax(int data){
		if(data > maxData){
			maxData = data; 
		}
		if(data < minData){
			minData = data; 
		}
	}
	int getIndex(int data){
		return data - offset; 
	}
	void printBucketAry(BufferedWriter outFile2){
		try {
			outFile2.write("Index: ");
			for(int i = 0; i <=18; i++){
				if(i < 10){
					outFile2.write("0"+i+" "); 
				}
				else
					outFile2.write(i + " ");
			}
			outFile2.newLine();
			
			outFile2.write("Value:  ");
			for(int i = 0; i <=18; i++){
				outFile2.write(bucketAry[i]+"  "); 
			}
			outFile2.newLine();
			outFile2.close(); 
			
		} catch (IOException e) {
			e.printStackTrace();
		}
		
	}
	void printSortedData(BufferedWriter outFile1) {
		try {
			int kVal = 1;
			outFile1.write("Sorted Values using BucketSort Implementation:");
			outFile1.newLine();
			for (int i = 0; i < bucketAry.length; i++) {
				while (bucketAry[i] != 0) {
					int val = i + offset; 
					outFile1.write("Output #" + kVal + ": " + val);
					outFile1.newLine();

					bucketAry[i]--;
					kVal++;
				}
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public static void main(String[] args){

		try {
			bucketSort SortedAry = new bucketSort(); 
			int num = 0; 
			Scanner inFile = new Scanner(new FileReader(args[0]));
			num= inFile.nextInt();
			SortedAry.minData = num; 
			SortedAry.maxData = num; 
			while(inFile.hasNextInt()){
				num = inFile.nextInt(); 
				SortedAry.findMinMax(num);
			}
			inFile.close(); 
			
			int minSize = SortedAry.maxData - SortedAry.minData +1; 
			SortedAry.bucketAry = new int[minSize];

			SortedAry.offset = SortedAry.minData;
			
			inFile = new Scanner(new FileReader(args[0]));
			
			File outPath1 = new File(args[2]);
			File outPath2 = new File(args[1]);
			BufferedWriter outFile1 = new BufferedWriter(new FileWriter(outPath1));
			BufferedWriter outFile2 = new BufferedWriter(new FileWriter(outPath2));
			outFile2.write("Updating values in bucketSort array...");
			outFile2.newLine(); 
			while(inFile.hasNextInt()){
				num = inFile.nextInt(); 
				int index = SortedAry.getIndex(num); 
				SortedAry.bucketAry[index]++; 
				outFile2.write("BucketAry[" + index + "] = " + SortedAry.bucketAry[index]);
				outFile2.newLine();  
			}
			outFile2.write("Values updated.");
			outFile2.newLine(); 
			outFile2.newLine();
			inFile.close(); 
			
			SortedAry.printBucketAry(outFile2);
			SortedAry.printSortedData(outFile1);
			
			outFile1.close();
			outFile2.close(); 
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	
	}
}

