/*
 * Name : Ankit Sharma
 * Roll No : CS1429
 * Program description : This program is written in java.It takes two strings as input and outputs 
 * the edit distance between them.
 * Submission Deadline : 02/12/2014
 * */

package editDistance;

public class Test {

	public static void main(String[] args) {
		String s1 = "abcd";  //input string 1.
		String s2 = "adb";   //input string 2.
		editDistance ed = new editDistance(s1 ,s2); 
        System.out.println("The edit distance of Strings "+s1+" and "+s2+ " is = "+ed.editDP());
	}

}
