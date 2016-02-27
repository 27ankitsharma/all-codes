/*NAME : Ankit Sharma
Roll No : CS1429
DATE OF SUBMISSION : 14-AUG-2014
DEADLINE DATE : 14-AUG-2014 

Program Description : This is the solution to the Maze problem.Here n , m are inputs to be taken from the user. The array A is
treated as a maze in which a mouse is trying to find its way. A[i][j]=0 indicates that the mouse can step onto the location(i,j) and A[i][j]=1 indicates that the mouse can't step onto the location (i,j). A mouse starts from A[0][0] and has to reach A[n-1][m-1], by passing only through positions that are set to 0. A mouse can move in any of the 8 directions -- N, S, E, W, NE, NW, SE, SW provided that those locations have a 0 and they are valid array entries.

ACKNOWLEDGEMENT:Youtube programming interview lecture.
*/


#include<stdio.h>
#include<stdlib.h>
#include "cs1429-assign2-prog2.h"

int row, col;			//Global variables for row and column of input matrix.
int main (void){

  int i, j;			//Two variables simply for 'for' loop.
  int **matrix;			//Pointer to pointer to integer for input matrix.
  int **sol_Matrix;             //Pointer to pointer to integer forsolution matrix.

  printf ("\nEnter the values for row and column\n");
  scanf ("%d%d", &row, &col);

  matrix = allocate (row, col);      //Dynamically allocating space for input matrix using allocate2D function.
  sol_Matrix = allocate (row, col);  //Dynamically allocating space for input matrix.

  for (i = 0; i < row; i++) {       
      for (j = 0; j < col; j++){

	  sol_Matrix[i][j] = 1;      //Initializing solution matrix with 1.

	}
    }

  printf ("\n\nInitial solution matrix is:");
  print_Matrix (row, col, sol_Matrix);  //Using print_Matrix function for printing initial solution matrix.

  /*Filling the matrix entries with 0 and 1 randomly using random generator function. */
  matrix = fill_Randomly (row, col, matrix);
  matrix[0][0]=0;            

  /*Printing filled values. */
  printf ("\n\nRandomly filled matrix is:");
  print_Matrix (row, col, matrix);

  call_Solve_Maze (matrix, sol_Matrix);  //calling call_Solve_Maze to find the path.

  printf ("\n\nFinal path matrix is:(Here 1 indicate the cell not included in path and 0 indicate cell included in path\n");
  printf("Path matrix will show 0 in cells only when there exists a path otherwise it will display all 1's.)\n");
  print_Matrix (row, col, sol_Matrix);  //printing final path matrix.
  printf ("\n\n");
  return 0;
}
