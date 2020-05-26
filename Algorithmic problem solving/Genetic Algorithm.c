/*
Name : Ankit Sharma
Course : M.Tech(CS)
Roll NO : CS1429
email: 27ankitsharma@gmail.com
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<malloc.h>
#define PI 3.14159

int M = 10, L = 15;   //M = Population size, L = Length of bit strings.
float fitnessArray[10]; // Array to store fitness values of each binary string.
float MaxFitValue, MaxFitValue1;    // To store best fitness value.
int MaxIndex, MaxIndex1;         // To store corresponding string index.
int TotalIterations;

float g( int * );
float f (float );
int* selection ( int **  , int * );
int ** crossover( int ** );
int ** mutation( int ** , int );
float mutProbability( int  );
int * calculateFitness( int ** );
int maximum( float* );
int findIndex(float * , float );
int ** Allocate2D (int , int );
int ** initPop();

int main()
{
    int i ,j;
    float *fitnessArray;
    int **Q0 , **Q1 = NULL, **Q2 = NULL, **Q3 = NULL;
    printf(" How many iterations do you want ?\n ");
    scanf("%d",&TotalIterations);

    Q0 = initPop();     // Initializing population.
    fitnessArray = calculateFitness( Q0) ;
    MaxIndex = maximum( fitnessArray);     // Calculating the index of the best fit string in old population.
    MaxFitValue = fitnessArray[MaxIndex];  // Getting the fitness value of the best fit string in old population.

    int N = 1;
    while (N<=TotalIterations) {   // Iteration
        Q1 = selection(Q0, fitnessArray);
        Q2 = crossover( Q1 );
        Q3 = mutation(Q0, N);
        fitnessArray = calculateFitness( Q3) ;

        MaxIndex1 = maximum( fitnessArray );     // Calculating the index of the best fit string in fitnessArray obtained by new population Q3.
        MaxFitValue1 = fitnessArray[MaxIndex1];  // Calculating the fitness value of the best fit string for new population.
        if (MaxFitValue1 >= MaxFitValue )  {      // Got a better or equivalent fit string.
            MaxIndex = MaxIndex1;
            MaxFitValue = MaxFitValue1;
            Q0 = Q3;
        }
        else {    // MaxFitValue1 < MaxFitValue ...Did not get better fit string.
            for ( j = 0; j < L; j++) { //replace a string in Q3 by original best string from Q0.
                Q3[0][j] = Q0[MaxIndex][j];
            }
            Q0 = Q3;
        }
        N = N + 1;
     }

     fitnessArray = calculateFitness( Q3) ;
     MaxIndex = maximum( fitnessArray);     // Calculating the index of the best fit string in old population.
     MaxFitValue = fitnessArray[MaxIndex];  // Getting the fitness value of the best fit string in old population.
     printf(" Final Population is : \n");
     for ( i = 0; i < M; i++){
        printf("\n");
        for ( j= 0; j < L; j++)
            printf(" %d,",Q3[i][j]);
     }
     printf("\n\n And Fitness value of each string is :\n");
     for ( i = 0; i < M; i++)
        printf("%f,",fitnessArray[i]);
     printf("\n\n Maxima point x = %f\n",g(Q3[MaxIndex]));
     printf(" Maximum value f(x) = %f\n",MaxFitValue);
}

// Function to implement selection step of genetic algorithm
int* selection ( int ** Q0 , int * fitnessArray) {
    int i, j;
    float randNumber;
    float cumulativeFitness[M];
    float cumSum = 0;
    int ** Q1;
    cumulativeFitness[0] = fitnessArray[0];

    for ( i = 1; i < M; i++){   // Calculating cumulative sum.
         cumulativeFitness[i] = cumulativeFitness[i-1] + fitnessArray[i];
    }
    cumSum = cumulativeFitness[M-1];
    for ( i = 0; i < M; i++){   // dividing by cumSum
         cumulativeFitness[i] /= cumSum ;
    }

    Q1 = Allocate2D(M, L);
    int tmpIndex;
    for ( i = 0; i < M; i++) {
         randNumber = (float) rand()/RAND_MAX;
         tmpIndex = findIndex(cumulativeFitness, randNumber);  //Finding index of the string which is chosen by using SRSWR.
         for ( j = 0; j < L; j++)
            Q1[i][j] = Q0[tmpIndex][j];

    }
    return Q1;
}


// Function to implement crossover operation of genetic algorithm.
int ** crossover(int **Q1 ) {
    int i,j ;
    int **Q2;
    Q2 = Allocate2D(M, L);

    for ( i = 0; i <= M-2; i = i+2){  // Performing crossover pairwise for adjacent locations.
      float randNumber = (float) rand()/RAND_MAX;
      if (randNumber <= 0.9) {   // Crossover probability p = 0.9
        int k = rand()% 15; // Choosing random number between 0 and L-1.Crossover will be performed at kth positions of both strings
        for ( j = 0; j <= k; j++){    // Swapping the left hand sides of both strings.
           Q2[i][j]   = Q1[i+1][j] ;
           Q2[i+1][j] = Q1[i][j];
        }
        for ( j = k+1; j < L; j++){  // copying rest of the string as it is.
           Q2[i][j]   = Q1[i][j] ;
           Q2[i+1][j] = Q1[i+1][j];
        }
      }
      else { // Crossover doesn't happen so copy them as it is.
        for ( j = 0; j < L; j++){
           Q2[i][j] = Q1[i][j];
           Q2[i+1][j] = Q1[i+1][j];
        }
      }
    }
    return Q2;
}

// Function to implement mutation.
int ** mutation( int ** Q2, int N) {
    int i, j ;
    int **Q3 ;
    Q3 = Allocate2D(M, L);
    float q = mutProbability( N ); // Obtaining mutation probability as a function of iteration number N.

    for ( i = 0; i < M; i++){
        for (j = 0; j < L; j++) {
            float randNumber = (float) rand()/RAND_MAX;
            if ( randNumber <= q )
               Q3[i][j] = 1 - Q2[i][j];  //Mutating each binary string with probability q
            else
               Q3[i][j] = Q2[i][j];
        }
    }
    return Q3;
}

// Function to calculate mutation probability based on number of iterations.
float mutProbability( int N ) {
    float q = (17.0/60 + (13.0/60) * cos((3*PI * N)/TotalIterations));
//    if ( N== 2000)
//      printf("q = %f,",q);
//    //q = 0.1;
    return q;
}
// Function to calculate fitness of a population.
int * calculateFitness( int ** Q ) {
    int i;
    float * fitnessArray;
    fitnessArray = (int*) malloc( M * sizeof(float));
    for(i = 0; i < M; i++){   // Calculating the fitness values of each binary string.
        fitnessArray[i] = f (g( Q[i] ) );
    }
    return fitnessArray;
}

// Function to find best fit string.
int maximum(float* binArray){

    float max = binArray[0];
    int i ;
    int MaxIndex = 0;
    for ( i = 1; i < M; i++){
        if (binArray[i] > max ){
            max = binArray[i];
            MaxIndex = i;
        }
    }
    return MaxIndex;
}


// Function to implement g function
float g(int *binArray ){
    int i ;
    float gValue = 0.0;

    for ( i = 0; i < L; i++){
        gValue += binArray[i]* pow(2.0,4-i);   // 4-i = 5-i-1

    }
    return gValue;
}

//Function to implement f function
float f (float x) {

    if (0 <= x && x <= (2 * PI) )     // 0<=x<= 2PI
        return ( sin(x) + 6 );

    else if ( (2 * PI) <= x && x <= (4 * PI) )     // 0<=x<= 2PI
        return ( 2 * sin(x) + 6 );

    else if ( (4 * PI) <= x && x <= (6 * PI) )     // 4PI<=x<= 6PI
        return ( 3 * sin(x) + 6 );

    else if ( (6 * PI) <= x && x <= (8 * PI) )     // 6PI<=x<= 8PI
        return ( 4 * sin(x) + 6 );

    else if ( (8 * PI) <= x && x <= (10 * PI) )     // 8PI<=x<= 10PI
        return ( 5 * sin(x) + 6 );

    else if ( (10 * PI) <= x && x <= 32 )     // 10PI<=x<= 32
        return ( sin(x) + 6 );

    else
        printf("\nError !! Function is not defined for x = %f",x);
}


// Function to allocate 2-d array.
int ** Allocate2D (int M, int L) {
    int i;
    int ** array;
    array = ( int ** )malloc( M * sizeof(int *));

    if (array == NULL) {
        printf ("\n Memory allocation failed.\n");
        exit (0);
    }
    for ( i = 0; i < M; i++) {
        array[i] = ( int* ) malloc(L * sizeof(int));
        if (array[i] == NULL) {
	        printf ("\n Memory allocation failed.\n");
	        exit (0);
	}
    }
     return array;
}
// Function to generate initial population randomly.
int ** initPop(){
    int ** Q0 = Allocate2D( M, L );
    int i, j;
    float randNumber;
    for (i = 0; i < M; i++){
        for ( j = 0; j < L; j++){
            randNumber = (float) rand()/RAND_MAX;
            if (randNumber <= .5)    // Crossover probability p = 0.9
               Q0[i][j] = 0;
            else
              Q0[i][j] = 1;
        }
    }
    return Q0;
}

// Function to select population corresponding to randValue. (cumulative fitness size).
int findIndex(float * cumulativeFitness, float randValue) {

    int i ;
    if (randValue <= cumulativeFitness[0])
        return 0;
    else if (randValue > cumulativeFitness[M-2])
        return M-1;

    else {
       for ( i = 1; i < M-1; i++){
           if ( randValue > cumulativeFitness[i-1] &&  randValue <= cumulativeFitness[i])
               return i;
      }
    }
}
