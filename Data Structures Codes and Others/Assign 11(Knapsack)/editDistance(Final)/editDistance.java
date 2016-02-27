/*
 * Name : Ankit Sharma
 * Roll No : CS1429
 * Program description : This program is written in java.It takes two strings as input and outputs 
 * the edit distance between them.
 * Submission Deadline : 02/12/2014
 * */

package editDistance;

public class editDistance {
	String s1 , s2;
	int len1 ,len2;
	int table[][];  //creating table for memoization.

	public editDistance(String s1 , String s2) {
		this.s1 = s1;
		this.s2 = s2;
		len1 = s1.length();  //calculating length of string 1.
		len2 = s2.length();  //calculating length of string 2.
		table = new int[len1+1][len2+1];  //creating table by 2-D matrix 	

		for ( int j = 0; j <= len2 ; j++) { //intializing whole 0th row by all 0's.
			table [0][j] = j;

		}
		for (int i = 0; i <= len1; i++) {  //intializing whole 0th column by all 0's.
			table [i][0] = i; 
		}
	}


	public int minimum(int a , int b , int c) {  //method to find minimum of three numbers.
		int min = a < b ? a : b;
		min = c < min ? c : min;
		return min;

	}

	public int editDP() {  //method for calculating edit distance of two strings.

		for (int i = 0 ; i < len1; i++) {
			char c1 = s1.charAt(i);
			for ( int j = 0; j < len2; j++) {
				char c2 = s2.charAt(j);

				if (c1 == c2) 
					table[i+1][j+1] = table[i][j]; 

				else {
					int delete = table[i+1][j] + 1;  //cost by deleting a letter.
					int replace = table[i][j] + 1;   //cost by replacing a letter.
					int insert = table[i][j+1] + 1;  //cost by inserting a letter.
					int min = minimum(delete ,replace ,insert);  //finding minimum cost out of these three operations
					table[i+1][j+1] = min;  //incrementing cost by 1.
				}
			}
		}

		return table[len1][len2];  //returning the last cell's content.
	}
}




