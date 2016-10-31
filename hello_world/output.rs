fn main(){
//input output
	let input = "Hello"; 
	let entry = "Hello"; 
	if entry == input{
		println!("Hey, what's up?"); 
	}
//using arrays
	let input_ary = ["Hey", "Hello", "Howdy", "Hi there", "Bonjour"];
	let output_ary = ["What's up?", "Hi!", "How do you do?", "Hello from 
				here", "Bonjourno!"];
	
	for i in 0..input_ary.len(){
		if entry == input_ary[i]{
			println!("{}" , output_ary[i]); 
		}
	}
}
