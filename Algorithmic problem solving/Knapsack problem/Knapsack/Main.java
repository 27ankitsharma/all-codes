/*
 * Name : Ankit Sharma
 * Roll no : CS1429
 * Program description : This program is written in java and implements Knapsack problem
 * solution using dynamic programming technique.
 * It takes Capacity C andtwo input array as input: first Profit array and second weight array.
 * And outputs the maximum profit subject to the constraint C according to the problem statement. 
 * */
public class Main {

	public static void main(String[] args) {
		Knapsack kp = new Knapsack();
		int wt[] = {1 ,5 , 3 , 4};  //weight array
		int profit[] = {15 ,10 ,9 ,5}; //profit array.
		int C = 8;   //Knapsack capacity
		System.out.println("Result = " +kp.KnapsackSol(C, wt, profit));  //printing maximum profit
	}

}
