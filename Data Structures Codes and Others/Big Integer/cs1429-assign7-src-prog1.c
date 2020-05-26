#include<stdio.h>
#include<stdlib.h>
#include "cs1429-assign7-prog1.h"
/* *******Function to find maximum of size of two array****** */
int max(int* a,int sizea, int* b ,int sizeb) {

if ( sizea >= sizeb ) {  // if array a is bigger.
    return 0;
 }
 else {         //array b is bigger
   return 1;
 }
}

/* *******Function to perform addition of two input numbers stored in two arrays****** */
int *bigAddition ( int* a,int sizea ,int* b ,int sizeb) {  //performing a+b
int i, carry = 0  ,diff ,k;
int status=-1 ,*sum;
status = max (a ,sizea, b ,sizeb );  //knowing which array is bigger and accordingly alocating space.
  if (status == 0) {    //means array a is bigger or equal to array b.
    
      sum = (int*)calloc (sizeof(int), (sizea+1)); //if array a is bigger, then make sum array as big as array a plus 1.
      sumSize = sizea+1;   
      diff = sizea - sizeb;    
      for (i = sizea-1, k =sumSize-1; i >= (sizea-sizeb); i--,k-- ) {  //firstly adding corresponding digits
         sum [k] = (a[i] + b[i-diff] + carry) % 10;
         carry = ((a[i] + b[i-diff] + carry) / 10);
       }
       
     for (i = diff-1; i >= 0; i--,k--) {  //And now filing rest of the digits as they are including carry.
     sum[k] = (carry + a[i])%10;
     carry =  (carry + a[i])/10;
       } 
     sum [0] = carry;  
   }
  else {
      sum = (int*)calloc (sizeof(int), (sizeb+1));     //if array b is bigger, then make sum array as big as array b plus 1.
      sumSize = sizeb+1;
      diff = sizeb - sizea;
        for (i = sizeb-1,k =sumSize-1; i >= (sizeb-sizea); i--, k-- ) { //firstly adding corresponding digits
         sum [k] = (a[i-diff] + b[i] + carry) % 10;
         carry = ((a[i-diff] + b[i] + carry) / 10);   
      }
    
     for (i = diff-1; i >= 0; i--,k--) {  //And now filing rest of the digits as they are including carry.
         sum[k] = (carry + b[i])%10;
         carry = (carry + b[i])/10;
     } 
     sum [0] = carry; 
 }
  return sum;
}

/* *******Function to convert string to integer****** */
int* strToInt (char* str ,int* bigArray) {

   int i;
   for (i = 0; i < strlen(str); i++) {
      bigArray [i] = str [i]-48;     //converting each character to its corresponding integer.
    }

   return bigArray;
}
/* *******Function to find product of two arrays****** */
int* bigMultiplication (int *multiplicand , int sizea, int *multiplier, int sizeb ) {
     int i ,j, value;
     int *prodArray ,*tmp,*tmp1;

     tmp = (int*) mul (multiplicand , sizea ,multiplier [sizeb-1]);  //multiplying digit by digit of multiplier.
     prodArray  = (int*)sizeIncrease (tmp , sizea+1 ,(sizea + sizeb));  //increasing size of array  obtained above.
     prodSize = sizea + sizeb;  //product array will be as big as sum of input arrays

     for ( j = sizeb-2 ; j >= 0; j--) {  
         tmp1 = mul (multiplicand , sizea ,multiplier[j]);   //multiplying digit by digit of multiplier.
         tmp1 = sizeIncrease (tmp1 , sizea+1 ,sizea + sizeb); //increasing size of array  obtained above to perform partial sum addition.
         tmp1 = leftShiftByZero (tmp1 ,sizea+sizeb ,sizeb-j-1);  //left shifting to perform partial sum addition.

         prodArray = bigAddition2 (  prodArray, (sizea+sizeb) , tmp1 , (sizea + sizeb)); //adding partial sum.
         
     }
     return prodArray;          
}
/* *******Function to multiply by one digit to a multiplicand used in multiplication function above****** */
int *mul (int *array ,int size , int num) {
     int i  , carry =0;
     int *parray;
     parray = (int*) calloc (sizeof(int), size+1); //alocating space one more than the size of multplicand.
     for ( i = size-1 ; i >= 0 ; i--) {  //performing multiplication
         parray [i+1] = ((array[i] * num )+ carry )%10 ;
         carry = (array[i] * num + carry)/10 ;
     }
     parray [0] = carry;
     return parray;
}
/* *******Function to find sum of two arrays used in above multiplication function.****** */
int *bigAddition2 ( int* a, int sizea ,int* b ,int sizeb) {  
      int i, carry = 0;
      int *sum;
      sum = (int*) calloc (sizeof (int), sizea);  //allocating space equal to that of multiplicand array. 
      for (i = sizea-1; i >= 0; i-- ) {
         sum [i] = (a[i] + b[i] + carry) % 10;
         carry = ((a[i] + b[i] + carry) / 10);
      }
  return sum;
}

/* *******Function to find maximum of size of two array****** */
/*int *padder (int *array, int size, int digit) {
    if(digit == 0) {
             return array;
    }
    int *paddedArray ;
    int total ,i;
    total = size + digit;
    paddedArray = (int*) calloc(sizeof(int) , total);
    if (array == NULL) {
              exit (0);
    }
    for ( i = 0; i < total ; i++ ) {
        if ( i < size) {
        paddedArray [i] = array [i] ;
        }
        else {
             paddedArray [i] = 0;
        }
    }
   
    return paddedArray; 
} */
/* *******Function to left shift array by required digits as needed in adding partial sums.****** */
int* leftShiftByZero (int* array ,int size, int digit) {
       
     int i ,j;
     while (digit !=0) {     
       for ( i = 0; i < size-1; i++) {
          array [i] = array [i+1];  //shifting digit by digit
       }
       array [size-1] = 0;
       digit--;
     }
     return array;
}
/* *******Function to increase the size of array****** */
int* sizeIncrease ( int* array , int size , int newSize) {
     if (size == newSize) {
      return array;
     } 
     int* newArray;
     int i;
     newArray = (int*) calloc (sizeof(int), newSize);
     for ( i = size-1; i >= 0 ; i--) {
         newArray [newSize-size+i] = array [i];  //copying content of previous array into new array.
         
     }
     return newArray;
}
/* *******Function to find factorial of number****** */
int* factorial (int* num ,int numSize) {
     int *tmp ,*fact ,a [1] = {1};  //a is small array.it just keep 1 and acts as the loop counter.
     tmp = (int*) calloc ( sizeof (int), 1);  //tmp array contains the number upto where factorial has been calculated in the loop.
     fact = (int*) calloc ( sizeof (int), 1);  //fact array contains actual factorial of the number
     tmp [0] = 1;
     fact[0] = 1;   
       
     while ( isNotEqual ( num, numSize, tmp, sumSize)) {
       tmp = bigAddition (tmp ,sumSize ,a ,1);  //incrementing number
       fact = bigMultiplication ( fact , prodSize ,tmp , sumSize); //multiplying intermediate factorial values.
       }
       return fact;
       
}
/* *******Function to check whether number reached to the input number.It is used in factorial function above****** */
int isNotEqual (int* num , int numSize ,int *tmp ,int tmpSize) {
    int flag = 0,i =0 ,j = 0 ; //flag = 0 means equal.
    while ( tmp[j] == 0 ) {  //skipping zeros. 
          j++ ;     
      }
    if ((tmpSize - j) != numSize) { //if even size are not equal, they can never be equal.
      flag = 1;
      return flag;
      }
       for ( i = 0; i < numSize ; i++) {
           if (tmp[j] != num[i]) {
             flag = 1;  // 1 means not equal.
          
          }
          j++;
       }
       return flag;
}
        






