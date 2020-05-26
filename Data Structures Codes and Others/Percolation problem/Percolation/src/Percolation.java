/*
* Name : Ankit Sharma
* Roll No : CS1429
* Program Description : This program implements solution of percolation problem as given in assignment no 10.
* Submission date : 05-NOV-2014
*/


public class Percolation {

	int[][] grid ;  //array will be craeted of size N*N. with starting indices to 1 not zero.
	  //that is indices involving 0 wil not be used at all.
	int N;
	WeightedQuickUnionUF uf;  //creating object of WeightedQuickUnionUF class.
	
	public Percolation(int N) {   // create N-by-N grid, with all sites blocked
		this.N = N;
		uf = new WeightedQuickUnionUF (N*N); //creating array of size equals to square of N.
		grid = new int[N+1][N+1];
		for (int rowIndex = 1; rowIndex < N+1 ;rowIndex++)
			for (int colIndex = 1; colIndex < N+1 ;colIndex++)
				grid[rowIndex][colIndex] = 0;   //initializing each index of grid array by zero.
	}
	
	   //creating object of WeightedQuickUnionFind class.
	
	/*This method converts 2D array into 1D array.*/
	public  int xyTo1D( int i , int j) {
		if( i < 1 || i > N || j < 1 || j > N)  //if index is out of bound then return 0
		{
			return 0;
		}
		else 
			return ((i-1)*N +j-1);  //mapping 2D array into 1-D array
	}

	public void open(int i, int j) { // open site (row i, column j) if it is not open.
			grid[i][j] = 1;
			int pos1 ,pos2;
			pos1 = xyTo1D(i , j);  //converting (i , j) to 1D array.
			if ((j-1) >= 1 && grid[i][j-1] ==1) {  //if left cell of input cell is open
				pos2 = xyTo1D(i , j-1);
				  uf.union(pos1, pos2);  //union both input and left cell.
			}
			if ((i-1) >= 1 && grid[i-1][j] ==1) { //upper cell
				pos2 = xyTo1D(i-1 , j);
				 uf.union(pos1, pos2);  //union both input and upper cell.
			}
			if ((j+1) <= N && grid[i][j+1] ==1) { //right cell
				pos2 = xyTo1D(i , j+1);
				uf.union(pos1, pos2);   //union both input and right cell.
			}
			if ((i+1) <= N && grid[i+1][j] ==1) { //bottom cell
				pos2 = xyTo1D(i+1 , j);
				 uf.union(pos1, pos2);  //union both input and bottom cell.
			}
	}
	public boolean isOpen(int i, int j) {// is site (row i, column j) open? {

	return (grid[i][j] == 1);  //if site open then return 1 otherwise 0.
}

public boolean isFull(int i, int j) { // is site (row i, column j) full?
   int index;
	for ( index = 0; index < N; index++) {
	    if( uf.connected( index ,xyTo1D(i ,j))) { //if both site are in same component
	    	return true;
	    }
	}
	return false;
}

/*This method detects percolation by comparing each cell in upper row to lowest row of grid array*/
//if at least one cell are found to be in same component then system percolates.
public boolean percolates() {// does the system percolate?
      int index1 ,index2;
      for ( index1 = 0; index1 < N-1; index1++) {
  	    for (index2 = N*(N-1); index2 < N*N-1; index2++) {
  	    	if(uf.connected(index1, index2))
  	    		return true;
  	      }
     }
      return false;
  	}  
}