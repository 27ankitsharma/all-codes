/*
Name: Ankit Sharma
Roll Number:mtc1429
Date of Submission:07-Aug-2014
Deadline date:08-Aug-2014
Program description:This program prints the sizes and ranges of various primitive data types of C.
Acknowledgements:1.GCC header files like limits.h and float.h
2.Wikipedia article on printf function.
 source:http://en.wikipedia.org/wiki/Printf_format_string
*/
 #include<stdio.h>
 #include<limits.h>
 #include<float.h>


  void char_Data_Type(void){
    printf("\n\n\t Data Type:Character\n\n");
    printf("size of char          = %lu,  minimum = %d   maximum = %d\n",sizeof(char),CHAR_MIN,CHAR_MAX);
    printf("size of signed char   = %lu,  minimum = %d  maximum = %d\n",sizeof(signed char),SCHAR_MIN,SCHAR_MAX);
    printf("size of unsigned char = %lu,  minimum = 0,  maximum = %d\n\n\n",sizeof(unsigned char),UCHAR_MAX);
   return;
}

  void int_Data_Type(void){ 
    printf("\tData Type:Integer\n\n");
    printf("size of signed short int    = %lu,  minimum = %d  maximum = %d\n",sizeof(signed short int),SHRT_MIN,SHRT_MAX);
    printf("size of unsigned short int  = %lu,  minimum =0   maximum = %d\n\n",sizeof(unsigned short int),UINT_MAX);

    printf("size of signed int          = %lu,  minimum = %d  maximum = %d\n",sizeof(signed int),INT_MIN,INT_MAX);
    printf("size of unsigned int        = %lu,  minimum = 0  maximum = %d\n\n",sizeof(unsigned int),INT_MAX);

    printf("size of signed long int     = %lu,  minimum = %ld  maximum = %ld\n",sizeof(signed long int),LONG_MIN,LONG_MAX);
    printf("size of unsigned long int   = %lu,  minimum = 0,  maximum = %ld\n\n",sizeof(unsigned long int),ULONG_MAX);

    printf("size of signed long long int= %lu,  minimum = %lld  maximum = %lld\n",sizeof(signed long long int),LLONG_MIN,LLONG_MAX);
    printf("size of unsigned long int   = %lu,  minimum = 0,  maximum = %llu\n\n\n",sizeof(unsigned long long int),ULLONG_MAX);
   return;
}
 
    void float_Data_Type(void){
    printf("\tData Type:Float and Double\n\n");
    printf("size of float       = %lu,  minimum = %e   maximum = %e\n",sizeof(float),FLT_MIN,FLT_MAX);
    printf("size of double      = %lu,  minimum = %e  maximum = %e\n",sizeof(double),DBL_MIN,DBL_MAX);
    printf("size of long double = %lu,  minimum = %Le  maximum = %Le\n\n",sizeof(long double),LDBL_MIN,LDBL_MAX);
   return;
}

