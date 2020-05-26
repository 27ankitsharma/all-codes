/*NAME : Ankit Sharma
Roll No : CS1429
DATE OF SUBMISSION : 14-AUG-2014
DEADLINE DATE : 14-AUG-2014 

Program Description : This is the solution to the Maze problem.Here n , m are inputs to be taken from the user. The array A is
treated as a maze in which a mouse is trying to find its way. A[i][j]=0 indicates that the mouse can step onto the location(i,j) and A[i][j]=1 indicates that the mouse can't step onto the location (i,j). A mouse starts from A[0][0] and has to reach A[n-1][m-1], by passing only through positions that are set to 0. A mouse can move in any of the 8 directions -- N, S, E, W, NE, NW, SE, SW provided that those locations have a 0 and they are valid array entries.

ACKNOWLEDGEMENT:Youtube programming interview lecture.
*/

extern int** allocate(int ,int);  
extern int** fill_Randomly(int ,int ,int**);
extern void print_Matrix(int ,int ,int**);
extern int is_Possible(int, int,int**);
extern int row; //This is global variable for row.
extern int col; //This is global variable for column.
extern int call_Solve_Maze(int**,int**);
extern int solve_Maze(int ,int, int**,int**); 

