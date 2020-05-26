/*NAME : Ankit Sharma
Roll No : CS1429
DATE OF SUBMISSION : 14-AUG-2014
DEADLINE DATE : 14-AUG-2014 

Program Description : This is the solution to the Maze problem.Here n , m are inputs to be taken from the user. The array A is
treated as a maze in which a mouse is trying to find its way. A[i][j]=0 indicates that the mouse can step onto the location(i,j) and A[i][j]=1 indicates that the mouse can't step onto the location (i,j). A mouse starts from A[0][0] and has to reach A[n-1][m-1], by passing only through positions that are set to 0. A mouse can move in any of the 8 directions -- N, S, E, W, NE, NW, SE, SW provided that those locations have a 0 and they are valid array entries.

ACKNOWLEDGEMENT:Youtube programming interview lecture.
*/


#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include"cs1429-assign2-prog2.h"


int **allocate (int m, int n){

  int k = 0;			//'for' loop variable.
  int **S;			//Declaring pointer to pointer.

  S = (int **) malloc (m * sizeof (int *));	//Using calloc function to allocate rows first.

  if (S == NULL){
     
      printf ("\n No space \n");
      exit (0);
    }
  for (k = 0; k < m; k++){
      
      S[k] = (int *) malloc (n * sizeof (int));	//Using calloc function to allocate columns.
      if (S[k] == NULL)
	{
	  printf ("\n No space \n");
	  exit (0);
	}
    }
  return S;			//Returning the address of 2-D array.
}



/*Function to fill the input matrix randomly*/
int **fill_Randomly (int row_Size, int col_Size, int **matrix){

  int i, j, bit; 
  time_t t;
  
  /*Intializes random number generator */
  srand ((unsigned) time (&t));

  for (i = 0; i < row_Size; i++){
    
        for (j = 0; j < col_Size; j++){
	  bit = (rand ()) % 2;  //taking mod 2 to limit rrandomly generated number to 0 and 1.
	  matrix[i][j] = bit;   //filling each cell of input matrix with 0 or 1 randomly.
	}
    }
  return matrix;
}



/*Function to print any matrix needed in the program*/
void print_Matrix (int row_index, int col_index, int **matrix){

  int i, j;

  for (i = 0; i < row_index; i++){
      printf ("\n");
      for (j = 0; j < col_index; j++){
	  printf ("%d", matrix[i][j]);
	}
    }
  return;
}


/*Function to check whether path is possible from the current cell.if yes then filling that cell by 0.*/
int is_Possible (int i, int j, int **matrix){

  if (i >= 0 && i < row && j >= 0 && j < col && matrix[i][j] == 0)
    return 1;

  else
    return 0;
}


/*Routine function for finding path in all 8 directions from the current cell.*/
int solve_Maze (int i, int j, int **matrix, int **sol_Matrix){

   

  if (i == row - 1 && j == col - 1 && matrix[i][j] == 0){//To check if the final last cell is reached.

      sol_Matrix[i][j] = 0;                          //If yes making that 0 to be included in the path matrix.
      return 1;
    }
  else if (i == row - 1 && j == col - 1 && matrix[i][j] == 1) {//To chek if last cell contains 1.

      sol_Matrix[i][j] = 1;
      return 0;
    }
  else if (is_Possible (i, j, matrix) == 1){

       sol_Matrix[i][j] = 0;
       matrix[i][j]=1;

      if (solve_Maze (i + 1, j, matrix, sol_Matrix)){ //To check if there is 0 in below the current cell.			

	  return 1;
	}

      if (solve_Maze (i, j + 1, matrix, sol_Matrix)){  //To check if there is 0 in right of the current cell.
				

	  return 1;
	}

      if (solve_Maze (i - 1, j, matrix, sol_Matrix)){ //To check if there is 0 in above cell of the current cell.
				

	  return 1;
	}

      if (solve_Maze (i, j - 1, matrix, sol_Matrix)){  //To check if there is 0 in left cell of the current cell.
				

	  return 1;
	}

      if (solve_Maze (i - 1, j + 1, matrix, sol_Matrix)){ //To check if there is 0 in above-right cell of the current cell.
				

	  return 1;
	}

      if (solve_Maze (i + 1, j + 1, matrix, sol_Matrix)){  //To check if there is 0 in right-below cell of the current cell.
				
	  return 1;
	}

      if (solve_Maze (i + 1, j - 1, matrix, sol_Matrix)){  //To check if there is 0 in left-below cell of the current cell.
			

	  return 1;
	}

      if (solve_Maze (i + 1, j, matrix, sol_Matrix)){  //To check if there is 0 in above-left cell of the current cell.
			

	  return 1;
	}


      sol_Matrix[i][j] = 1;      //if there is no path,making the current cell filled by 1.
      return 0;
    }
  return 0;
}


//This is the main function to solve Maze problem.
int call_Solve_Maze (int **matrix, int **sol_Matrix){

    if (!solve_Maze (0, 0, matrix, sol_Matrix))
      return 0;
    else
    return 1;
}
