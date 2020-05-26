/*
NAME : Ankit Sharma
Roll No : CS1429
DATE OF SUBMISSION : 13-AUG-2014
DEADLINE DATE : 14-AUG-2014 
Program Description : This recursive C program takes as input a positive integer 'n' and generates
a matrix of size 2^n x 2^n using pointer to pointer.Fill the matrix with integers in the range [1,2^(2n)] and then print
the matrix in a spiral fashion.
ACKNOWLEDGEMENT:Lecture slide of day2 for using 2Dallocate function.
*/



#include<stdio.h>
#include "cs1429-assign2-prog1.h"


                        /*************Main starts here***********/

int main(void){

   int n;
   int i,j,k=1;     //Here i,j,k are simply loop variables for 'for' loop.
   int size_Of_Array=0;      //For storing 2^n.
   int **array;     //Declaring pointer to pointer to array.
  
   printf("\nEnter the values of n:\n");
   scanf("%d",&n);
   size_Of_Array=power(n);  /*calculating 2^n and storing in size variable*/

   array=allocate2D(size_Of_Array);  //Calling function for array allocation and storing the returned address in array pointer.

  /*Filling the matrix with numbers from 1 to 2^n*/
   for(i=0;i<size_Of_Array;i++){
     for(j=0;j<size_Of_Array;j++){
        array[i][j]=k;
        k++;
     }
   }

/*Printing the filled values by above for loop.*/
   printf("\n\nFilled array values are:\n");
   for(i=0;i<size_Of_Array;i++){ 
     printf("\n");
     for(j=0;j<size_Of_Array;j++){
       printf("%d  ",array[i][j]);
     }
   }

 printf("\n\n");
 printf("**************************************************************************\n\n");
 printf("Array values printed in spiral fashion are: \n\n");
 spiral(0,size_Of_Array-1,0,size_Of_Array-1,array);  //calling spiral function to print in spiral fashion.
 return 0;
}


