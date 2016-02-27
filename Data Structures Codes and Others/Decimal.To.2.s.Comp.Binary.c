    /*
    
    NAME- Ankit Sharma
    ROLL NO- CS1429
    STREAM- MTECH(CS)
    ASSIGNMENT NO- 01
    Problem Statement: Write a program to convert any decimal number into its 2's complement binary representation.
    
    */
    
    
    #include<stdio.h>
    #include<math.h>
    int main(void)
    {
    int num,bit;  //user input for number and number of bits.
    int largest;  //To find the largest number in the given #input bits.
    int i=0;     //loop counter.
    int number;  //To store the intermediate number after applying mod operation on the input number.
    int rangechk; //To check the range from the input #bits.
    printf("Enter the number\n");
    scanf("%d",&num);
    printf("Enter the number of bits\n");
    scanf("%d",&bit);
    rangechk=pow(2.0,bit-1);
    if(num<-rangechk||num>rangechk)
        {
            printf("Overflow.Try with higher number of bits\n");
            getch();
            return;
        }
    int a[bit];  //array to store the binary representation.
    for(i=0;i<bit;i++)
           {
                 a[i]=0;
           }
    largest=pow(2.0,bit);
    number=(largest+num)%largest;
    i=bit-1;
    while(number!=0)  //loop for binary conversion.
       {
            a[i--]=number%2;
            number=number/2;
       }
    printf("2's complement of %d is = ",num);
    for(i=0;i<bit;i++)
      {
         printf("%d",a[i]);
      }
      getch();
    return;
    }
    
