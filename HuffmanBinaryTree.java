//Sumaita Hussain 
//Huffman Coding Implementation in Java

import java.io.*; 
import java.util.Scanner;

class listBinTreeNode{
	String chStr; 
	int prob; 
	listBinTreeNode next; 
	listBinTreeNode left; 
	listBinTreeNode right; 
	
	listBinTreeNode(){}
	listBinTreeNode(String alpha, int probab){
		chStr = alpha; 
		prob = probab; 
	}
	void printNode(listBinTreeNode T, BufferedWriter outFile){
		try {
//			if(T.left == null && T.right == null && T.next == null){
//				outFile.write("char: " + T.chStr + " prob: " + T.prob + " next string: -- " + " left string: -- right string: -- ");
//				outFile.newLine(); 
//			}
			if(T.left == null && T.right == null){
				outFile.newLine();
				outFile.write("string: " + T.chStr + " prob: " + T.prob + " left string: -- right string: -- ");
				outFile.newLine(); 				
			}
//			else if(T.next == null){
//				outFile.write("char: " + T.chStr + " prob: " + T.prob + " next string: -- "
//						+ " left string: " + T.left.chStr + " right string: " + T.right.chStr);
//				outFile.newLine(); 
//			}
			else{
				outFile.newLine();
				outFile.write("string: " + T.chStr + " prob: " + T.prob + 
						" left string: " + T.left.chStr + " right string: " + T.right.chStr);
				outFile.newLine(); 				
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
class HuffmanLinkedList{
	listBinTreeNode listHead; 
	listBinTreeNode oldListHead; 
	
	HuffmanLinkedList(){
		listHead = new listBinTreeNode(); 
		listHead.chStr = "Dummy";
		oldListHead = new listBinTreeNode(); 
		oldListHead.chStr = "Dummy";
	}
	void listInsert(listBinTreeNode newNode, listBinTreeNode spot){ 
			newNode.next = spot.next; 
			spot.next = newNode; 	
	}
	listBinTreeNode findSpot(int data){
		listBinTreeNode spot = listHead;
		if(spot.next == null){
			if(spot.prob < data){				
			}
		}
		
		while(spot.next!=null && spot.next.prob < data){
			spot = spot.next;
		}
		return spot; 
	}
	boolean isEmpty(){
		if(listHead.next == null){
			return true; 
		}
		else
			return false; 
	}
	void printList(BufferedWriter outFile){
		try{
			listBinTreeNode temp = listHead; 
			outFile.write("listHead-->");
			while(temp.next!=null){
				//System.out.println("(" + temp.chStr + ", " + temp.prob + ", " + temp.next.chStr + ")--->");
				outFile.write("(" + temp.chStr + ", " + temp.prob + ", " + temp.next.chStr + ")--->");
				outFile.newLine(); 
				temp = temp.next;
			}
			//System.out.println("(" + temp.chStr + ", " + temp.prob + ", null)");
			outFile.write("(" + temp.chStr + ", " + temp.prob + ", null)");
			outFile.newLine(); 
		} catch(IOException e){
			e.printStackTrace();
		}
	}
}

public class HuffmanBinaryTree{
	String code; 
	listBinTreeNode root; 
	
	HuffmanBinaryTree(){
		root = new listBinTreeNode(); 
	}
	void preOrderTraversal(listBinTreeNode T, BufferedWriter outFile){
		if(T==null){
			
		}
		else{
			T.printNode(T,outFile);
			preOrderTraversal(T.left, outFile);
			preOrderTraversal(T.right, outFile);
		}
	}
	void constructCharCode(listBinTreeNode T, String code1, BufferedWriter outFile1, BufferedWriter outFile2){
		if(T == null){
			
		}
		else if (T.left==null && T.right==null){
			try {
				outFile1.write(T.chStr);
				outFile1.write(" "+ code1);
				outFile1.newLine(); 
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		else{
			constructCharCode(T.left, code1 + "0", outFile1, outFile2);
			constructCharCode(T.right, code1 + "1", outFile1, outFile2);
		}
	}
	public static void main(String[] args) {
		HuffmanLinkedList huffList = new HuffmanLinkedList();
		Scanner inFile;
		try {
			inFile = new Scanner(new FileReader(args[0]));
			while(inFile.hasNext()){
				listBinTreeNode newNode = new listBinTreeNode(); 
				newNode.chStr = inFile.next();
				newNode.prob = inFile.nextInt();
				listBinTreeNode spot = huffList.findSpot(newNode.prob);
				huffList.listInsert(newNode, spot);
			}
			inFile.close();
			File outPath1 = new File(args[1]);
			File outPath2 = new File(args[2]);
			File outPath3 = new File(args[3]);
			
			BufferedWriter out1 = new BufferedWriter(new FileWriter(outPath1));
			BufferedWriter out2 = new BufferedWriter(new FileWriter(outPath2));
			BufferedWriter out3 = new BufferedWriter(new FileWriter(outPath3));
			
			huffList.oldListHead.next = huffList.listHead.next; 
			huffList.listHead = huffList.listHead.next; 
			
			while(!huffList.isEmpty()){	
				listBinTreeNode newNode = new listBinTreeNode(); 
				newNode.chStr = huffList.listHead.chStr + huffList.listHead.next.chStr; 
				newNode.prob = huffList.listHead.prob + huffList.listHead.next.prob; 
				newNode.left = huffList.listHead; 
				newNode.right = huffList.listHead.next; 
				newNode.printNode(newNode, out3);
				listBinTreeNode spot = huffList.findSpot(newNode.prob);
				huffList.listInsert(newNode, spot);
				huffList.printList(out3);
				huffList.listHead = huffList.listHead.next.next;	
			}
			HuffmanBinaryTree huffTree = new HuffmanBinaryTree(); 
			huffTree.root = huffList.listHead; 
			String code = "";
			huffTree.constructCharCode(huffTree.root, code, out1, out2);
			huffTree.preOrderTraversal(huffTree.root, out2);
			
			out1.close();
			out2.close();
			out3.close(); 
 		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}

	}

}
