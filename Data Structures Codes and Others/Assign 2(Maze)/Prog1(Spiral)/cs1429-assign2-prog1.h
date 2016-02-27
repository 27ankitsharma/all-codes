/*
NAME : Ankit Sharma
Roll No : CS1429
DATE OF SUBMISSION : 14-AUG-2014
DEADLINE DATE : 14-AUG-2014 
Program Description : This recursive C program takes as input a positive integer 'n' and generates
a matrix of size 2^n x 2^n using pointer to pointer.Fill the matrix with integers in the range [1,2^(2n)] and then print
the matrix in a spiral fashion.
ACKNOWLEDGEMENT:Lecture slide of day2 for using 2Dallocate function.
*/


extern void spiral(int,int,int,int,int**);
extern int** allocate2D(int);
int power(int);
