import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

//Sumaita Hussain
//Linked List Stack Implementation in Java 

class listNode {

	int data;
	listNode next;

	// Default Constructor
	listNode() {
		data = -1;
	}

	// Constructor that takes in int value
	listNode(int value) {
		data = value;
	}

	// Getters + Setters for listNode Next and int Data
	listNode getNext() {
		return next;
	}

	void setNext(listNode newPtr) {
		next = newPtr;
	}

	int getData() {
		return data;
	}

	void setData(int newVal) {
		data = newVal;
	}
}

public class LinkedListStack extends listNode {

	listNode top;

	// Constructor

	LinkedListStack() {
		top = null;
	}

	// Pop method
	int pop() {
		if (!isEmpty()) {
			listNode temp = top;
			top = top.getNext();
			return temp.getData();
		} else
			return 0;
	}

	// Push method returns listNode and accepts listNode as parameter
	listNode push(listNode value) {
		if (isEmpty()) {
			top = value;
		} else {
			value.setNext(top);
			top = value;
		}
		return value;
	}

	// Checks to see whether stack is empty
	boolean isEmpty() {
		if (top == null) {
			return true;
		}
		return false;
	}

	public static void main(String[] args) throws FileNotFoundException {

		LinkedListStack stackLinked = new LinkedListStack(); 		// Create new stack
		File instream = new File(args[0]); 							// Open file using command line
		Scanner myfile = new Scanner(instream);
		System.out.println("Input: ");
		while (myfile.hasNextInt()) { 								// Step 4
			
			// Create new listNode with value from infile
			listNode num = new listNode(myfile.nextInt()); 			

			// Push listNode into stack and output a) data and b) next address
			System.out.println("Pushing value: " + num.getData()
					+ "  Next Address:  " + stackLinked.push(num).getNext());
		}
		myfile.close();
		System.out.println("Ouput");
		while (!stackLinked.isEmpty()) {
			//Pop and output data from the stack 
			System.out.println("Popping: " + stackLinked.pop()); 
		}
	}
}
