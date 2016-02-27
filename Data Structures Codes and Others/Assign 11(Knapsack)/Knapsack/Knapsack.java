/*
 * Name : Ankit Sharma
 * Roll no : CS1429
 * Program description : This program is written in java and implements Knapsack problem
 * solution using dynamic programming technique.
 * It takes Capacity C andtwo input array as input: first Profit array and second weight array.
 * And outputs the maximum profit subject to the constraint C according to the problem statement. 
 * */
public class Knapsack {
   //Method for calculating maximum of two values.
	public int maximum(int a, int b) {
		if (a > b)
		return a;
		else 
		return b;
		
	}
	
	public int KnapsackSol(int C ,int wt[] ,int profit[]) {
		int lenp = profit.length;  //calculating length of profit array.
		int[][] table = new int[lenp+1][C+1]; //creating table for memoization.
		for (int i = 0 ; i <= lenp; i++) {  
			for (int j = 0 ; j <= C ; j++) {
				if (i == 0 || j == 0) 
					table[i][j] = 0; 
				else if(wt[i-1] <= j) {  //item i can be part of the solution
					int tmp = j-wt[i-1]; 
				    table[i][j] = maximum(profit[i-1] + table[i-1][tmp],  table[i-1][j]); //best subset either contains ith item or not.	
				}
				    else
					table[i][j] = table[i-1][j]; //weight of ith element is > C
			}
		}
	   return table[lenp][C];	
	}
}
