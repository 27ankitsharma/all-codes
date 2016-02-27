/* Name : Ankit Sharma
 * Roll No:cs1429
 *Submission date : 29/09/14
 *Due Date : 29/09/14
 *Program description : This program calculates the convex hull of given points and calculates its
 *area.It also checks whether a given point lies inside  or outside or on the convex hull.
 */

package cs1429.dsutils;
import cs1429.geometry.*;
import java.util.ArrayList;

public class Stack {

	ArrayList<Point> arrStack=new ArrayList<Point>() ;
	public int top;   //Top points to index of the last pushed element.
	public Stack() {
	
		top=-1;
	}
	/****Method for setting top*******/
	public void setTop(int setValue) {
		this.top = setValue;
	}
	/****Method for getting value of top*******/
	public Point showTop() {
		
		return arrStack.get(top);
	}
	/****Method for getting value of top*******/
	public Point nextToTop () {

		int topNext =top;
		if (top == 0)
			return null;
		topNext = top-1;
		return (arrStack.get(topNext));
		
	}
	/****Method for pushing element*******/
	public void push(Point p) {
		    top++;
			arrStack.add(p);
	}
	/****Method for pop element.This method just remove the top value.*******/	
  public void pop() {
	
		if( top !=-1){
			
			arrStack.remove(top);
			top--;
			
		}
	}
  /****Method for returning poped element *******/
  public Point returnPop() {
	  
	  if( top == -1 ){
			return null;
		}
		else {
			
			return(arrStack.remove(top--));
			
		}
  }
  /*******Method for checking stack is empty or not.********/
 public Boolean isEmpty() {
  
	  if (top == -1) {
	  
		 return true;
	  }
	  else {
	  
		  return false;
	  }
  }
 /********Method for printing stack element*****************/
  public void display () {
	  for (Point number : arrStack) {
		   System.out.println("( "+number.getX() + ", "+ number.getY()+" )");
	    }  
}
}
