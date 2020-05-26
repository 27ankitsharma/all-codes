#include<stdio.h>
#include<stdlib.h>
#include "cs1429-assign7-prog1.h"

int main (void) {

  int choice = 0 ;
  printf ("Enter your choice : \n");  //giving user choices of various operations.
  printf ("1.Addition\n2.Multiplication.\n3.Factorial\nAny other key to exit.");
  scanf ("%d" , &choice );
  while ( choice == 1 || choice == 2 || choice == 3 ) {
        
  if (choice == 1) {
  int i = 0 , sizea , sizeb ;
  char stra [1000], strb [1000];  //strings just to take number and storing them to strings
  int *bigArraya ,*bigArrayb, *sum;

  printf ("Enter your 1st number:\n");
  scanf ( "%s" , stra );
  bigArraya = (int*) calloc (sizeof(int),strlen(stra));
  bigArraya = (int*) strToInt (stra , bigArraya) ;  //converting input number string into integer array.
  
  printf ("\nEnter your 2nd number:\n");
  scanf ( "%s", strb );
  bigArrayb = (int*) calloc ( sizeof(int) , strlen (strb));
  bigArrayb = (int*) strToInt (strb , bigArrayb) ; //converting input number string into integer array.
  
  sizea = (int) strlen (stra);  //getting the size of input string
  sizeb = (int) strlen (strb);  //getting the size of input string

  sum = (int*) bigAddition ( bigArraya, sizea, bigArrayb ,sizeb);  //performing addition operation.
  printf ("\nSum is = ");

  while ( sum[i] == 0){  //skipping leading zeros to print
    i++ ;
   }
   while (i < sumSize ) {
      printf("%d" , sum [i] );
      i++ ;
    }
   free (bigArraya);  //freeing memory
   free (bigArrayb);  //freeing memory
   free (sum);         //freeing memory
  }
 
  else if ( choice == 2 ) {

  int i = 0 ,sizea, sizeb ;
  char stra [1000], strb [1000];  //strings just to take number and storing them to strings
  int *bigArraya ,*bigArrayb, *sum;

  printf ( "Enter your 1st number:\n");
  scanf ("%s",stra );
  bigArraya = (int*) calloc ( sizeof (int), strlen (stra));
  bigArraya = (int*) strToInt ( stra , bigArraya) ; //converting input number string into integer array.
  
  printf ("\nEnter your 2nd number:\n");
  scanf ("%s",strb);
  bigArrayb = (int*) calloc (sizeof(int),strlen(strb));
  bigArrayb = (int*) strToInt (strb , bigArrayb) ; //converting input number string into integer array.
  
  sizea = (int) strlen ( stra );  //getting the size of input string
  sizeb = (int) strlen ( strb );  //getting the size of input string
  int *prodArray ;
  prodArray = (int*) bigMultiplication ( bigArraya , sizea ,bigArrayb ,sizeb );  // calling multiplication function
  printf ("\n\nProduct is = ");

  while ( prodArray[i] == 0){  //skipping leading zeros from printing
                 i++;
         }
   while ( i < sizea+sizeb ) {
   printf ("%d" , prodArray[i] );
   i++;
    }
   free (bigArraya);  //freeing memory
   free (bigArrayb);  //freeing memory
   free (prodArray);         //freeing memory
  }
  else if (choice == 3) {
  int i =0 ,sizea ;
  char stra[1000];
  int *bigArraya,  *sum;
  printf ("Enter your number:\n");
  scanf ("%s",stra) ;

  bigArraya = (int*) calloc ( sizeof(int), strlen (stra) );
  bigArraya = (int*) strToInt ( stra , bigArraya ) ; //converting input number string into integer array.
  sizea = (int) strlen(stra);  //getting the size of input string
  int *fact;
   prodSize = 1;  //global variable to know the size of  'fact' array while in calculation.
   sumSize = 1;   //same as above, except this is used to keep size of 'tmp' tracking array which keeps track of where we have reached.
   printf ("\nFactorial of number is = ");
   fact = factorial ( bigArraya , sizea );
   while ( fact [i] == 0) {  //skipping leading zeros from printing
                 i++;
         }
   while ( i < prodSize ) {
   printf ( "%d" , fact[i] );
   i++;
   } 
   free (bigArraya);  //freeing memory
   free (fact);  //freeing memory
  }
 else {
    exit ( 0 );     //exit on wrong choice
 }
   printf ( "\n\n1.Addition\n2.Multiplication.\n3.Factorial\nAny other key to exit." );
   scanf ( "%d" , &choice );
}      
   
   return 0;
}
