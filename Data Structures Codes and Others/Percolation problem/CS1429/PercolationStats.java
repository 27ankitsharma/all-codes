/*
* Name : Ankit Sharma
* Roll No : CS1429
* Program Description : This program implements solution of percolation problem as given in assignment no 10.
* Submission date : 05-NOV-2014
*/

public class PercolationStats {

	int N ,T;
	double th[];  //this array is used to calculate threshold.
	
	public PercolationStats(int N, int T) { // perform T independent experiments on an N-by-N grid
		this.T = T;
		this.N = N;
		Percolation p;
		th = new double[T];
		double num;
		int x, y;
		for(int i=0; i < T; i++){
                        System.out.print("Calculating for T = "+i+"\n");
			p = new Percolation(N);  //creating object of Percolation class.
			num = 0;
			while(!p.percolates()){  //untill system percolates.
				x = StdRandom.uniform(1, N+1);//generating random number in range 1 to N.
				y = StdRandom.uniform(1, N+1);
				if(!p.isOpen(x, y)){  //if site is not open then open it and count points.
					num++;
					p.open(x, y);
				}
				//System.out.println(" i = " + x +" j = " + y);
			}
			th[i] = num/(N*N);
		}
	}
	public double mean() {// sample mean of percolation threshold
	   return StdStats.mean(th);
	}
	public double stddev() { // sample standard deviation of percolation threshold
		return StdStats.stddev(th);
	}
	public double confidenceLo() { // low endpoint of 95% confidence interval
		double mean =mean();
		double stddev = stddev();
		double tmp = 1.96 * stddev;
		tmp = tmp / Math.sqrt(T);
		return (mean-stddev);
	}
	public double confidenceHi() { // high endpoint of 95% confidence interval
		double mean =mean();
		double stddev = stddev();
		double tmp = 1.96 * stddev;
		tmp = tmp / Math.sqrt(T);
		return (mean+stddev);
	}
	
	public static void main(String[] args)  {// test client (described below) 
		PercolationStats ps;
		ps = new PercolationStats(200,10);
		System.out.println("Mean = "+ps.mean());
		System.out.println("Standard deviation = "+ps.stddev());
		System.out.println("ConfidenceLo = "+ps.confidenceLo());
		System.out.println("confidenceHi = "+ps.confidenceHi());
		System.out.println();
	}
}
