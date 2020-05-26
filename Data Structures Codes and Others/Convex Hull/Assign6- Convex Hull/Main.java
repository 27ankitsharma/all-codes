/* Name : Ankit Sharma
 * Roll No:cs1429
 *Submission date : 29/09/14
 *Due Date : 29/09/14
 *Program description : This program calculates the convex hull of given points and calculates its
 *area.It also checks whether a given point lies inside  or outside or on the convex hull.
 */

import java.util.ArrayList;



//import cs1429.dsutils.*;
import cs1429.geometry.*;
public class Main {

	public static void main(String[] args) {
		
		Point p0 = new Point( 3 , 1 );
		Point p1 = new Point( 5 , 1 );
		Point p2 = new Point( 6 , 2 );
		Point p3 = new Point( 7 , 4 );
		Point p4 = new Point( 9 , 4 );
		Point p5 = new Point( 10 , 7 );
		Point p6 = new Point( 6 , 8 );
		Point p7 = new Point( 5 , 7 );
		Point p8 = new Point( 3 , 10);
		Point p9= new Point ( 2 , 5 );
		Point p10 = new Point ( 4 , 4 );
		Point p11 = new Point ( 11 , 8 );
		
		ArrayList <Point> inputPoints = new ArrayList <Point>(); 
		/*******Adding points to arraylist**********/
		inputPoints.add(p0);
		inputPoints.add(p1);
		inputPoints.add(p2);
		inputPoints.add(p3);
		inputPoints.add(p4);
		inputPoints.add(p5);
		inputPoints.add(p6);
		inputPoints.add(p7);
		inputPoints.add(p8);
		inputPoints.add(p9);
		inputPoints.add(p10);
		inputPoints.add(p11);
		
		ConvexHull ch1 = new ConvexHull();
		ch1 = ConvexHull.computeConvexHull(inputPoints);
		System.out.println();
		
		
		
		int position;
		/********Test point for checking point inside or outside.*********/
		Point pIn = new Point(5.0, 4.0);     //This point should lie inside the convex Hull.
		position = ch1.findPositionOfPoint (pIn);
		if (position == 0) {
			System.out.println ("Point ("+pIn.getX()+", "+pIn.getY() +") is on the convex hull.");
		}
		if (position == 1) {
			System.out.println ("Point ("+pIn.getX()+", "+pIn.getY() +") is inside the convex hull.");
		}
		if (position == -1) {
			System.out.println ("Point ("+pIn.getX()+", "+pIn.getY() +") is outside the convex hull.");
		}
		
		Point pOn = new Point(11.0, 8.0);     //This point should lie on the convex Hull.
		position = ch1.findPositionOfPoint ( pOn);
		if (position == 0) {
			System.out.println ("Point ("+pOn.getX()+", "+pOn.getY() +") is on the convex hull.");
		}
		if (position == 1) {
			System.out.println ("Point ("+pOn.getX()+", "+pOn.getY() +") is inside the convex hull.");
		}
		if (position == -1) {
			System.out.println ("Point ("+pOn.getX()+", "+pOn.getY() +") is outside the convex hull.");
		}
		
		Point pOut = new Point(20 , 23); //This point should lie outside the convex hull.
		position = ch1.findPositionOfPoint ( pOut);
		if (position == 0) {
			System.out.println ("Point ("+pOut.getX()+", "+pOut.getY() +") is on the convex hull.");
		}
		if (position == 1) {
			System.out.println ("Point ("+pOut.getX()+", "+pOut.getY() +") is inside the convex hull.");
		}
		if (position == -1) {
			System.out.println ("Point ("+pOut.getX()+", "+pOut.getY() +") is outside the convex hull.");
		}
		
	}

}
