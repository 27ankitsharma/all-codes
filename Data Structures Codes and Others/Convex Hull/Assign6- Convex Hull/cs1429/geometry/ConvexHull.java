/* Name : Ankit Sharma
 * Roll No:cs1429
 *Submission date : 29/09/14
 *Due Date : 29/09/14
 *Program description : This program calculates the convex hull of given points and calculates its
 *area.It also checks whether a given point lies inside  or outside or on the convex hull.
 */

package cs1429.geometry;
import java.util.ArrayList;

import cs1429.dsutils.*;
public class ConvexHull {
	 static ArrayList<Point> arl = new ArrayList<Point>();
	 static public double areaOfConvexHull;
	public static  ConvexHull computeConvexHull (ArrayList<Point> points)
	{
	
		ConvexHull ch = new ConvexHull();
		points = ch.minY_Ordinate(points);   //Now arraylist have bottom-most point at its 1st index.
		ch.setAngle(ch, points);             //setting angle of each point with reference point.
		points = ch.sort(points); //Sorting points according to the angle with the bottommost point calculated above.
		Stack mystack = new Stack(); //creating instance of stack class.
		mystack.push(points.get(0)); //pushing initial first point into the stack.
		mystack.push(points.get(1)); //pushing initial second point into the stack.
		mystack.push(points.get(2)); //pushing initial third point into the stack.
		
	  	for (int index = 3; index < points.size(); index++) { 
			   while ( ch.orientation( mystack.nextToTop() , mystack.showTop(), points.get(index))!= 2 ) {  //while point does not non left turn,keep poping.
					 mystack.pop();
				}
				  mystack.push(points.get(index));   //on right left turn push.
			}
		System.out.println("Points of Convex Hull are : ");
		mystack.display();   //printing convex hull points stored in the stack.
	   
		Point item;
		while (mystack.top !=-1) {  //Store all elements of convex Hull stored in the stack in arraylist.
			item = mystack.returnPop();   
			arl.add(item);
		}
		
		areaOfConvexHull = ch.area(arl);   //calculating area of convex hull.
		System.out.println();
		System.out.println("Area of convex Hull is = :"+areaOfConvexHull);
		
		return ch;
	}
	
	
	/*********** Method for finding bottommost point or leftmost point in case of tie.***************/
	public ArrayList<Point> minY_Ordinate(ArrayList <Point> al) {
		Point min = al.get(0);  //setting first point to minimum.
		int minIndex = 0;
		for ( int index = 1; index < al.size() ; index++) {
		
			if ( (al.get(index).getY() < min.y) || (al.get(index).getY() == min.y) && (al.get(index).getX() < min.x)) { //comparing based on y-ordinate.
			
				min = al.get(index);
				minIndex = index;
			}
		}
		Point tmp ;
		tmp = al.get(0);
		al.set(0, min);  //setting angle of reference point to 0.
		al.set(minIndex, tmp); //swapping with the first element.
		return al;
	}
	
	
/********Method for calculating angle between reference point and every other point *********/ 
	public void calculateAngle (Point px, Point py) {
		double angle,angleInDegree;
		angle = (py.y - px.y) / (py.x - px.x);
		angleInDegree = Math.toDegrees(Math.atan(angle)); //converting angle in radian to degree.
		if (angleInDegree < 0) {
			angleInDegree = angleInDegree +180;
		}
		py.angle = angleInDegree;
	}
	
/********Method for setting angle of each point with the reference point.********/	
	public void setAngle (ConvexHull ch , ArrayList <Point> al) {
		for (int index = 1; index < al.size() ; index++) {
			ch.calculateAngle(al.get(0), al.get(index)); 
		}
	}
/* **method for finding orientation of three points as required in algorithm.**********/
	public int orientation (Point p , Point q, Point r) { 
		int val = (int)((q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y)); 
		 if (val == 0) return 0;  // collinear
	    return (val > 0)? 1: 2; // clock or counterclock wise.
	}
/* *******Method for finding distance between two points********/
	public double distanceTo(Point px, Point py) {
		
		double distance;
		double tmp1,tmp2;
		tmp1=(px.x-py.x)*(px.x-py.x);
		tmp2=(px.y-py.y)*(px.y-py.y);
		distance=(tmp1 + tmp2);  //No need of calculating square root of distance.since we need to compare only.
		return distance;
	}
/* ******method for printing points***************************************/	
	public void printPoints(ArrayList <Point> al) {
	for (int index = 0; index < al.size(); index++) {
		System.out.println(al.get(index).x +", "+al.get(index).y);
	  }
		
	}
	/* **************Method for sorting points according to angle with reference point****************************/
	 public ArrayList<Point> sort(ArrayList <Point> al) {
		//double tmp1;
		Point tmp2;
		Point array[] = new Point[al.size()];
		array = al.toArray(array);  //converting arraylist into array.
		int sizeOfArray = al.size();
		for ( int i = 1 ; i < sizeOfArray; i++) {
			for(int j = i+1 ; j < sizeOfArray; j++ ) {
				if (array[i].angle > array[j].angle) {
					tmp2= array [i];
					array [i] = array [j];
					array [j] = tmp2;
				}
			}
		}
		ArrayList<Point> al2 = new ArrayList<Point>(); 
		for(int k = 0 ; k < sizeOfArray; k++)
		{
			al2.add(array[k]);  //converting array again into arraylist.
		}
		
		return al2;
	}

   /* *******Method for calculating area of convex Hull**********/	
	public double area(ArrayList<Point> arl) {
		double area2=0;
		Point p1, p2, p3;
		p1 = arl.get(0);
		p2 = arl.get(1);
		for (int index =2; index < (arl.size()); index++) {
			p3 = arl.get(index);
			area2 = area2 + areaOfTriangle (p1 ,p2, p3); 
			p2 = p3;
			}
		return area2;
	}
	
/**** *****Method for checking whether a point lies inside ,ouside or on the convex Hull.*******/
	public int findPositionOfPoint (Point p) {
		double areaByPoint = areaWithPoint (p, arl); 
		if (areaByPoint == 0.0) {  //if point lies on the convex hull,at least one triangle's area wil be zero.
			return 0;
			
		}
		if(areaOfConvexHull == areaByPoint) {
			return 1;
			}
		return -1;
		
	}
	/* ***Method for finding area of all triangles taking external point.***/
	public double areaWithPoint(Point p, ArrayList<Point> arl) {
		double areaTmp =0, area2 =0;
		int tmpindex = arl.size()-1;  //starting with the last point.
		Point p2 = arl.get(tmpindex);
		Point p3 ;
		for (int index = 0; index < arl.size(); index++) {
			p3 = arl.get(index);
			areaTmp = areaOfTriangle (p , p2, p3);  //This method for calculating area of triangle is defined below this method
			p2 = p3 ;
			if( areaTmp == 0.0) {   //This happens because if point is on the hull,at least one triangle wil have area zero.
				return 0.0;
			}
			area2 = area2 + areaTmp;
		 
		}
		return area2;
	}
	
	/* *Method for calculating area of triangle as required in finding area of convex Hull**/
	public double areaOfTriangle(Point p1, Point p2, Point p3) {
		 double area1 = p1.x * ( p2.y-p3.y) + p2.x * (p3.y-p1.y) +p3.x * (p1.y-p2.y);
		 
		 if (area1 <0) {
			 area1 = (area1 * -1);  //if -ve make it +ve.
		 }
		 if (area1 == 0.0) {
			 return 0.0;
		 }
		 area1 = area1/2;
		 return area1;
	}
	
	
}
