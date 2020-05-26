/* Name : Ankit Sharma
 * Roll No:cs1429
 *Submission date : 29/09/14
 *Due Date : 29/09/14
 *Program description : This program calculates the convex hull of given points and calculates its
 *area.It also checks whether a given point lies inside  or outside or on the convex hull.
 */

package cs1429.geometry;

public class Point {
	double x,y;
	public double angle;
	public Point(double x, double y)  //constructor for this point class.
	{
		this.x=x;
		this.y=y;
		angle = 0;
	}
	
	public double getX()
	{
		return x;
	}
	public double getY()
	{
		return y;
	}
	/*****Method for calculating distance bw two points**********/
	public double distanceTo(double x1 , double y1 , double x2 , double y2 )
	{
		double distance;
		double tmp1,tmp2;
		tmp1=(x1-x2)*(x1-x2);
		tmp2=(y1-y2)*(y1-y2);
		distance=Math.sqrt((tmp1 + tmp2));
		return distance;
	}

}
