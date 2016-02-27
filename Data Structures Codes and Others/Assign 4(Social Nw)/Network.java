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
public class Network {
public HashMap<String, Member> hm1= new HashMap<String, Member>();

/* *********************Method for printing mutual friends of two members********** */
public void mutual_Friend_List ( Member i, Member j ) {
	   System.out.println ("Mutual friends of "+i.Name+ " and " +j.Name +" are folowing :");
	   Member tmp1, tmp2;
	   int friend_Count = 0; //to count mutual friends 
       for( int index1 = 0; index1 < i.al.size(); index1++ ) {
    	   tmp1 = i.al.get(index1);
    	   for( int index2 = 0; index2 < j.al.size(); index2++ )
    	   { 
    		   tmp2 = j.al.get(index2);
    		   if( tmp1.id == tmp2.id && i.id!=j.id) //if member in each other's list and ensuring that this is not the same member
    		   {
    			   System.out.println ( tmp1.Name );
    			   friend_Count ++;
    		   }
    	   }
       }
       if(friend_Count == 0) {  //if no mutual friend.
         System.out.println ("There is no mutual friend of "+i.Name+ " and " +j.Name );
       }
   }


/***********Method for printing suggestions to members who are not friends so far*****/
public int friend_Suggestion_List ( Member i, Member j ) {
	   
	   if(i.id == j.id){  //if the same member is being compared with itself.
		   return 0;
	   }
	   Member tmp;  //variable of type member class
	   int friend_Count=0; //keeping count of mutual friends to print suggestion for a member. 
	    for ( int index = 0; index<j.al.size(); index ++ ) {
		   tmp = j.al.get (index) ;  //
		   if (i.id == tmp.id) {  //if first member is already a friend of second member. 
			   return 0;
		   }
	   }
	   Member tmp1,tmp2; //Again both variables of type member class.
      for ( int index1 = 0; index1 < i.al.size(); index1 ++) {  //for loop upto size of 1st member's friend list
 	      tmp1 = i.al.get( index1 ); //storing reference of 1st member into tmp1.
 	      for ( int index2 = 0; index2 < j.al.size(); index2++ ) {  //for loop upto size of 2nd member's friend list
 	   
 		   tmp2 = j.al.get(index2) ; //storing reference of 2nd member into tmp2
 		   if ( tmp1.id == tmp2.id )  //if member exists in both member's friend list then count it.
 		   { 
 			  friend_Count ++;
 		   }
 	   }
    }
      
    if ( friend_Count >= 2) {  //if 2nd member appears more than two times in the friend list of 1st member's friend's list then suggest it.
      System.out.println ( j.Name ) ;
     }
    
    return 0;
}

}
