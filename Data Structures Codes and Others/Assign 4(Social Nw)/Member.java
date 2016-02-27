/*
NAME : Ankit Sharma
Roll No : CS1429
DATE OF SUBMISSION : 18-SEP-2014
DEADLINE DATE : 18-SEP-2014 
Program Description : This program implements social network and various functionalities as given in assignment.
Acknowledgement:Java : The Complete Reference by Herbert Schildt
*/
package cs1429;
import java.util.*;

//Member class stores all information required by the members like name,e-mail_ID and friend list.
public class Member {
   public String  Name;  //member's name
   public String id;     //member's email-id
   public ArrayList<Member> al = new ArrayList<Member>() ; //stores friend list of member.
   Member (String Name, String mail_ID ) {  //constructor for member class
   
	   this.Name = Name;  
	   this.id = mail_ID;
   }
   public void add_Friend ( Member first, Member second ) {  //method to add incoming member into each other's friend list.
   
	   al.add ( second ) ;
	   second.al.add ( first );
   }
   public void show_Friends ( Member m ) {  //Method for printing friends of member
	   Member temp;
       for(int i = 0; i < m.al.size (); i ++) {  //for loop upto size of its friend list
    	    temp = al.get (i);
	    System.out.print ( temp.Name+"," );
		
       }
   }
}
