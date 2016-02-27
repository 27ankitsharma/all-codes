/*
NAME : Ankit Sharma
Roll No : CS1429
DATE OF SUBMISSION : 18-SEP-2014
DEADLINE DATE : 18-SEP-2014 
Program Description : This program implements social network and various functionalities as given in assignment.
Acknowledgement:Java : The Complete Reference by Herbert Schildt
*/

package cs1429;
import java.security.KeyStore.Entry;
import java.util.*;  //importing java.util package to use ArrayList and HashMap
public class Test {   //Test class

	public static void main(String[] args) {  
		
		Network n1 = new Network(); //Creating object of Network class.
	/* ***********Defining and adding members to the network.*********** */
		
		Member m1 = new Member ( "Ankit", "ankit@abc.com"); //creating member m1
		n1.hm1.put(m1.Name, m1);  
		Member m2 = new Member ( "Rahul", "rahul@gmail.com"); //creating member m2
		n1.hm1.put(m2.Name, m2);
		Member m3 = new Member ( "vj", "vj@gmail.com");  //creating member m3
		n1.hm1.put(m3.Name, m3);
		Member m4 = new Member ( "abhi", "abhi@gmail.com");  //creating member m4
		n1.hm1.put(m4.Name, m4);
		Member m5 = new Member ( "Prateek", "Prateek@gmail.com");  //creating member m4
		n1.hm1.put(m5.Name, m5);
		Member m6 = new Member ( "Arpan", "Arpan@gmail.com");  //creating member m4
		n1.hm1.put(m6.Name, m6);
		Member m7 = new Member ( "KD", "KD@gmail.com");  //creating member m4
		n1.hm1.put(m7.Name, m7);
	/* ***********Adding members to the network ends here.*********** */
		
	/* ***********Adding friends to memeber m1.******************* */
		m1.add_Friend( m1,m2 );
		m1.add_Friend( m1,m4 );
		m1.add_Friend( m1,m6 );
	/* ***********Adding friends to memeber m2.******************* */
		m2.add_Friend( m2,m7 );
		m2.add_Friend( m2,m3 );
	/* ***********Adding friends to memeber m3.******************* */
		m3.add_Friend( m3,m4 );
		m3.add_Friend( m3,m5 );
	/* ***********Adding friends to memeber m5.******************* */
		m5.add_Friend( m5,m6 );
		
	/* **************Adding friends to memeber m1 ends here.******** */
		
	/* **********Printing friends of m1.************* */	
		System.out.print ( "Friends of "+m1.Name+" are :" ) ;
		m1.show_Friends ( m1 );
	/* **********Printing friends of m2.************* */
		System.out.println () ;
		System.out.print ( "Friends of "+m2.Name+" are :");
		m2.show_Friends ( m2 );
	/* **********Printing friends of m3.************* */	
		System.out.println ();
		System.out.print("Friends of "+m3.Name+" are :");
		m3.show_Friends ( m3 );
	/* **********Printing friends of m4.************* */
		System.out.println ();
		System.out.print("Friends of "+m4.Name+" are :");
		m4.show_Friends ( m4 );
	/* **********Printing friends of m5.************* */
		System.out.println ();
		System.out.print("Friends of "+m5.Name+" are :");
		m5.show_Friends ( m5 );
	/* **********Printing friends of m6.************* */
		System.out.println ();
		System.out.print("Friends of "+m6.Name+" are :");
		m6.show_Friends ( m6 );
	/* **********Printing friends of m7.************* */
		System.out.println ();
		System.out.print("Friends of "+m6.Name+" are :");
		m6.show_Friends ( m6 );
	/* ***********Printing friends of various members ends here.*********** */	
		
	/* **********Printing all members currently in the network************* */
		System.out.println ();
		System.out.println ("**************************************************************");
		System.out.println ();
		System.out.println ( "All memebers which are currently in the network are folowing :");
		Set<Map.Entry<String, Member>> set = n1.hm1.entrySet(); //Taking all keys of HashMap in variable set to playaround.
		Member tmp2;
		for ( Map.Entry<String, Member> tmp1 : set ) {
			tmp2 = tmp1.getValue ();  //storing ArrayList of reference in tmp2 variable.  
			System.out.print ( tmp2.Name ); //printing corresponding member name.
			System.out.print (" , ");
		}
		
	/* **********Printing all members currently in the network ends here.************* */
		
	/* *******************Printing Mutual friends*************************** */
		System.out.println ();
		System.out.println ("**************************************************************");
		
		System.out.println ();
		n1.mutual_Friend_List (m1, m3);   //between m1(ankit) and m3(vj)
		System.out.println ();
		n1.mutual_Friend_List (m1, m7);   //between m1(ankit) and m7(KD)
		System.out.println ();
		n1.mutual_Friend_List (m6, m3);   //between m6(Prateek) and m3(vj)
		System.out.println ();
		n1.mutual_Friend_List (m6, m7);   //between m6(Prateek) and m7(KD)
		
	/* ********************Printing Mutual friends ends here************* */
    /* ******Printing friend suggestions for all members****************** */
		
		System.out.println ("**************************************************************");
		System.out.println ();
		Set<Map.Entry<String, Member>> set2 = n1.hm1.entrySet(); //again storing all keys in set2 to playaround
		
		 for ( Map.Entry<String, Member> tmp3 : set2) { //For each member in the network.
		  Member tmp4 = tmp3.getValue();  //Storing arrayList reference in tmp4.
		  System.out.println ();
		  System.out.println ( "Friend suggestions for "+tmp4.Name+" are folowing :");
		  Set<Map.Entry<String, Member>> set1 = n1.hm1.entrySet();
		    for ( Map.Entry<String, Member> tmp1 : set1) { //With each other member of network. 
		        n1.friend_Suggestion_List(tmp3.getValue(), tmp1.getValue()); //calling method to print suggestion from Network class.
		}
	}
	}

}
