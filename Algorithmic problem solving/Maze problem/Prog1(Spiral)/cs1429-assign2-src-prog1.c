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


#include<stdlib.h>
#include<stdio.h>



 int** allocate2D(int n) { 
  int k;    //'for' loop variable.
  int **S;  //Declaring pointer to pointer.

  S=(int **)calloc(n,sizeof(int *));  //Using calloc function to allocate rows first.
   if(S==NULL) { 
    printf("\n No space \n");
    exit(0); 
   }
   for(k=0; k<n; k++) {
    S[k]=(int *)calloc(n,sizeof(int)); //Using calloc function to allocate columns.
     if(S[k]==NULL) {
      printf("\n No space \n"); 
      exit(0); 
   }
  }
  return S;     //Returning the address of 2-D array.
}



 void spiral(int top_Of_Row, int bottom_Of_Row, int left_Of_Column, int right_Of_Column, int **arr) {

    if( top_Of_Row > bottom_Of_Row || left_Of_Column > right_Of_Column )            /*Recursion termination condition when all elements are printed and on next call starting indices becomes greater than end indices.*/
    return;
    else {
    int i,j;  //Just two variables for 'for' loop.i is used for row printing and j for column printing.
    for(i = left_Of_Column; i <= right_Of_Column; i++) //Prints the top row element of each call.
      printf("%d ",arr[top_Of_Row][i]);
      printf("\n");
 

    for(j = top_Of_Row + 1;j <= bottom_Of_Row;j++)     //Prints the right row element of each call.
      printf("%d ",arr[j][right_Of_Column]);
      printf("\n");


    for(i = right_Of_Column - 1;i >= left_Of_Column;i--) //Prints the bottom row element of each call.
      printf("%d ",arr[bottom_Of_Row][i]);
      printf("\n");
 

    for(j = bottom_Of_Row - 1;j > top_Of_Row;j--)      //Prints the left row element of each call.
      printf("%d ",arr[j][left_Of_Column]);
      printf("\n");



    return (spiral((top_Of_Row+1),(bottom_Of_Row-1),(left_Of_Column+1),(right_Of_Column-1),arr));  /*Recursive call after reducing each indices from all four sides by 1.*/

}
}

int power(int n)   //Power function to calculate 2^n.
{
 int i = 0,size = 1;
 for(i = 0;i < n;i++){
   size = size * 2;
 }
 return size;
}

