/*
Name: ANKIT SHARMA
ROLL NO: CS1429
SUBJECT: COMPUTER ORGANIZATION
ASSIGNMENT NO-2
PROGRAM DESCRIPTION: This program implements the MacClusky algorithm for logic minimization using only decimal.Here 
binary conversion is used just for grouping them.Thereafter only decimal representation is used throughout 
the program.Here are some printf statement which are not part of the final program.These were used when I was writing
the program.I have not deleted them.because I think they may help in understanding the code and also in debugging.
This program finds the prime implicants only.It does not find essential prime implicents.
SUBMISSION DATE: 26/08/2014
*/


#include<stdio.h>

/************Function declaration*********************/
int binary_convertor(int);
void print_Group_Terms();
//void print_Group_Terms();
void pass1();
void pass2();

/*Global variable declaration*/
/*These are the counters used in various phases of computation.*/
int G0_counter=0,G1_counter=0,G2_counter=0,G3_counter=0,G4_counter=0; /*Counters for grouping phase.*/
int G01_counter=0,G12_counter=0,G23_counter=0,G34_counter=0; /*counters for pass 1*/
int G01_12_counter=0,G12_23_counter=0,G23_34_counter=0; /*Counters for pass 2*/


struct input         /*Structure for input minterms*/
{
       int min;    /*contains minterm*/
       int flag;   /*contains info whether this has been included in computation or not*/
};

/*Structure type array for storing binary conversions of input minterms.*/
struct input G0[16]; 
struct input G1[16];
struct input G2[16];
struct input G3[16];
struct input G4[16];

struct pass1       /*Structure for pass 1*/
{
       int min_pair[2];
       int diff;
       int flag;
};

/*Structure type array for pass 1*/
struct pass1 p1G0_1[8];
struct pass1 p1G1_2[8];
struct pass1 p1G2_3[8];
struct pass1 p1G3_4[8];

struct pass2        /*Structure for pass 2*/
{
       int min_quad[4];
       int diff[2];
       int flag;
};
/*Structure type array for  pass 2*/
struct pass2 p1G01_12[3];
struct pass2 p1G12_23[3];
struct pass2 p1G23_34[3];


struct pass3        /*Structure for pass 3*/
{
       int min_oct[8];
       int diff[2];
       int flag;
};
/*Structure type array for  pass 3*/
struct pass3 p1G01_12_12_23[2];
struct pass3 p1G012_23_23_34[2];


struct pass4        /*Structure  for  pass 4*/
{
       int min_oct[16];
       int diff[2];
       int flag;
};
struct pass4 p1G01_12_12_23_34  ;   /*Structure type array for  pass 4*/

       
int main(void)
{
    int i,j,num,min_count;
    printf("How many minterms do you want to enter.(maximum 16)\n");
    scanf("%d",&min_count);
    for(i=0;i<min_count;i++)
    {
       printf("Enter the minterms one by one.\n");
       scanf("%d",&num); 
       binary_convertor(num);   /*converting and storing each minterm in binary as it entered by the user.*/
    }
    printf("Minterms entered by you are grouped according to number of 1's in them.They are grouped as follows:\n");
    print_Group_Terms();    /*Printing input minterms after grouping.*/
    printf("\n\n*****************All pairs formed in Pass 1:**********************\n\n");
    printf("These are those minterms which are forming pairs.Later on some of these may form quads also,which are printed in next pass.\n");
    pass1();
    printf("\n\n*****************After that All quads formed:**********************\n\n");
    printf("These are those minterms which are forming quads.\n");
    pass2();
    
    getch();
    return 0;
           
}
/***************************Binary conversion function for input minterms*************************/
int binary_convertor(int num)
{
    int i=3,r,counter=0,minterm;
    minterm=num;
    while(i>=0)
    {
               r=num%2;
               if(r==1)
               {
               counter++;
               }
               num=num/2;
               i--;
    }
    /*Storing for number of 1's in each minterm in the structure one by one.*/
                if(counter==0){
                   G0[G0_counter].min=minterm;
                   G0_counter++;}
                else if(counter==1){
                   G1[G1_counter].min=minterm;
                   G1_counter++;}
                else if(counter==2){
                   G2[G2_counter].min=minterm;
                   G2_counter++;}
                else if(counter==3){
                   G3[G3_counter].min=minterm;
                   G3_counter++;}
                else if(counter==4){
                   G4[G4_counter].min=minterm;
                   G4_counter++;}
         return;
}
           
void print_Group_Terms()
{
                   int i;
                   printf("\nGroup 0 : ");
                   for(i=0;i<G0_counter;i++)
                   {
                       printf("%d  ",G0[i].min); 
                   } 
                   printf("\nGroup 1 : ");
                   for(i=0;i<G1_counter;i++)
                   {
                       printf("%d  ",G1[i].min); 
                   }
                   printf("\nGroup 2 : ");
                   for(i=0;i<G2_counter;i++)
                   {
                       printf("%d  ",G2[i].min); 
                   }
                   printf("\nGroup 3 : ");
                   for(i=0;i<G3_counter;i++)
                   {
                       printf("%d  ",G3[i].min); 
                   }
                   printf("\nGroup 4 : ");
                   for(i=0;i<G4_counter;i++)
                   {
                       printf("%d  ",G4[i].min); 
                   }
         return;
}  
 
/*******************************function for pass 1 in which pairs are formed.*********************************/ 
void pass1()
{
        
         int difference=0,i,j;
        // printf("\n\n0 - 1\n\n");
        /***************Loop for comparison of group 0 and group 1 elements***************************/
        for(i=0;i<G0_counter;i++)
         {
               for(j=0;j<G1_counter;j++)
                   {              
                                   difference=(G1[j].min-G0[i].min);  
                                   //printf("i=%d and j=%d then difference = %d",i,j,difference);
                                   if(difference==1||difference==2||difference==4||difference==8||difference==16)
                                       {
                                       
                                        p1G0_1[j].min_pair[0]=G0[i].min; //storing them in paas 1 structure.
                                        p1G0_1[j].min_pair[1]=G1[j].min;
                                        p1G0_1[j].diff=difference;
                                        G0[i].flag=1;   //setting flag to 1.
                                        G1[j].flag=1;
                                        G01_counter++;
                                        
                                   printf("\n%d,",j,p1G0_1[j].min_pair[0]);
                                   printf("%d\n",p1G0_1[j].min_pair[1]);
                                   //printf("p1G0_1[%d].diff=%d\n",j,p1G0_1[j].diff);
                                   //printf("p1G0_1[%d].flag=%d\n",j,p1G0_1[j].flag);
                                   //printf("p1G0_1[%d].diff= %d\n",j,p1G0_1[j].diff);
                                   //printf("G0[%d].flag= %d\n",i,G0[i].flag);
                                   //printf("G1[%d].flag= %d\n",j,G1[j].flag);
                                   
                                        }
                                   else
                                   {
                                       if(G0[0].flag!=1)
                                       G0[0].flag=0;
                                       if(G1[0].flag!=1)
                                       G1[0].flag=0;
                                   }
                                   
                                   
                   }
                  
         }
          //printf("Number of pairs added in 0-1 phase= %d\n\n",G01_counter);
         difference=0;
         
         // printf("\n\n1 - 2\n\n");
         /***************Loop for comparison of group 1 and group 2 elements***************************/
         for(i=0;i<G1_counter;i++)
         {
               for(j=0;j<G2_counter;j++)
                   {               
                                   //printf("\nG1[%d].min=%d,G2[%d].min=%d\n",i,j,G1[i].min,G2[j].min);
                                   difference=(G2[j].min-G1[i].min);
                                   //if(difference<0){
                                   //difference=(difference * -1);}
                                   //printf("i=%d and j=%d then difference = %d",i,j,difference);
                   if((difference==1||difference==2||difference==4||difference==8||difference==16))
                                       {
                                       
                                        p1G1_2[j].min_pair[0]=G1[i].min; //storing them in pass 2 structure.
                                        p1G1_2[j].min_pair[1]=G2[j].min;
                                        p1G1_2[j].diff=difference;
                                        G1[i].flag=1;
                                        G2[j].flag=1;
                                        G12_counter++;
                                        
                                        printf("\n%d,",j,p1G1_2[j].min_pair[0]);
                                        printf("%d\n",p1G1_2[j].min_pair[1]);
                                        //printf("p1G0_1[%d].diff=%d\n",j,p1G0_1[j].diff);
                                        //printf("p1G0_1[%d].flag=%d\n",j,p1G0_1[j].flag);
                                       
                                        //printf("p1G1_2[%d].diff= %d\n",i,p1G1_2[j].diff);
                                        //printf("G1[%d].flag= %d\n",i,G1[i].flag);
                                       // printf("G2[%d].flag= %d\n\n",j,G2[j].flag);
                                        
                                        }
                                   else
                                   {
                                       if(G1[0].flag!=1)
                                       G1[0].flag=0;
                                       if(G2[0].flag!=1)
                                       G2[0].flag=0;
                                   }
                                   
                                   
                   }
                   
         }
         //printf("Number of pairs added in 1-2 phase= %d\n\n",G12_counter);
         difference=0;
         
          //printf("\n\n2 - 3\n\n");
          /***************Loop for comparison of group 2 and group 3 elements***************************/
         for(i=0;i<G2_counter;i++)
         {
               for(j=0;j<G3_counter;j++)
                   {               
                                  // printf("\nG1[%d].min=%d,G2[%d].min=%d\n",i,j,G1[i].min,G2[j].min);
                                   difference=(G3[j].min-G2[i].min);
                                   //if(difference<0){
                                   //difference=(difference * -1);}
                                   //printf("i=%d and j=%d then difference = %d",i,j,difference);
                                   if(difference==1||difference==2||difference==4||difference==8||difference==16)
                                       {
                                        
                                        p1G2_3[j].min_pair[0]=G2[i].min;
                                        p1G2_3[j].min_pair[1]=G3[j].min;
                                        p1G2_3[j].diff=difference;
                                        G1[i].flag=1;
                                        G2[j].flag=1;
                                        G23_counter++;
                                        
                                        printf("\n%d,",j,p1G2_3[j].min_pair[0]);
                                        printf("%d\n",p1G2_3[j].min_pair[1]);
                                        //printf("p1G0_1[%d].diff=%d\n",j,p1G0_1[j].diff);
                                        //printf("p1G0_1[%d].flag=%d\n",j,p1G0_1[j].flag);
                                        //printf("p1G2_3[%d].diff= %d\n",i,p1G2_3[j].diff);
                                        //printf("G2[%d].flag= %d\n",i,G2[i].flag);
                                       // printf("G3[%d].flag= %d\n\n",j,G3[j].flag);
                                         
                                        }
                                   else
                                   {
                                       if(G2[0].flag!=1)
                                       G2[0].flag=0;
                                       if(G3[0].flag!=1)
                                       G3[0].flag=0;
                                   }
                                   
                                   
                   }
                   
         }
         //printf("Number of pairs added in 2-3 phase= %d\n\n",G23_counter);
         difference=0;
         //printf("\n\n3 - 4\n\n");
         /***************Loop for comparison of group 3 and group 4 elements***************************/
         for(i=0;i<G3_counter;i++)
         {
               for(j=0;j<G4_counter;j++)
                   {               
                                  
                                  // printf("\nG1[%d].min=%d,G2[%d].min=%d\n",i,j,G1[i].min,G2[j].min);
                                   difference=(G3[i].min-G4[j].min);
                                   if(difference<0){
                                   difference=(difference * -1);}
                                   //printf("i=%d and j=%d then difference = %d",i,j,difference);
                                   if(difference==1||difference==2||difference==4||difference==8||difference==16)
                                       {
                                      
                                        p1G3_4[j].min_pair[0]=G3[i].min;
                                        p1G3_4[j].min_pair[1]=G4[j].min;
                                        p1G3_4[j].diff=difference;
                                        G1[i].flag=1;
                                        G2[j].flag=1;
                                        G34_counter++;
                                        
                                        printf("\n %d,",j,p1G3_4[j].min_pair[0]);
                                        printf("%d\n",p1G3_4[j].min_pair[1]);
                                        //printf("%d\n",j,p1G0_1[j].diff);
                                        //printf("p1G0_1[%d].flag=%d\n",j,p1G0_1[j].flag);
                                        //printf("p1G3_4[%d].diff= %d\n",i,p1G3_4[j].diff);
                                        //printf("G3[%d].flag= %d\n",i,G3[i].flag);
                                        //printf("G4[%d].flag= %d\n\n",j,G4[j].flag);
                                         
                                        }
                                   else
                                   {
                                       if(G3[0].flag!=1)
                                       G3[0].flag=0;
                                       if(G4[0].flag!=1)
                                       G4[0].flag=0;
                                   }
                                   
                                   
                   }
                  
         }
          //printf("Number of pairs added in 3-4 phase= %d\n\n",G34_counter);
         //Pass 1 is upto here.
         
}

void pass2()
{
    int difference=0,i,j;
        // printf("\n\n0 - 1:1_2\n\n");
        /***************Loop for comparison of group (0-1) and group (1-2) elements***************************/
        for(i=0;i<G01_counter;i++)
         {
               for(j=0;j<G12_counter;j++)
                   {              
                                    //printf("i = %d,j = %d\n",i,j);
                                    //printf("p1G1_2[%d].min_pair[0] =%d\n",i,p1G1_2[i].min_pair[0]);
                                    // printf("p1G0_1[%d].min_pair[0] =%d\n",j,p1G0_1[j].min_pair[0]);
                                   difference=(p1G1_2[j].min_pair[0]-p1G0_1[i].min_pair[0]);
                                  //printf("i=%d and j=%d then difference = %d\n",i,j,difference);
                                   if((difference==1||difference==2||difference==4||difference==8||difference==16)&&(p1G0_1[i].diff==p1G1_2[j].diff))
                                       {
                                          if(difference > p1G0_1[i].diff)                                                                                                  
                                        //printf("Hi\n");
                                        //printf("p1G0_1[%d].min_pair[0]= %d,\n",i,p1G0_1[i].min_pair[0]);
                                        //printf("p1G0_1[%d].min_pair[1]= %d,\n",i,p1G0_1[i].min_pair[1]);
                                        //printf("p1G1_2[%d].min_pair[0]= %d,\n",i,p1G1_2[i].min_pair[0]);
                                        //printf("p1G1_2[%d].min_pair[1]= %d,\n",i,p1G1_2[i].min_pair[1]);
                                        
                                        p1G01_12[j].min_quad[0]=p1G0_1[i].min_pair[0];
                                        p1G01_12[j].min_quad[1]=p1G0_1[i].min_pair[1];
                                        p1G01_12[j].min_quad[2]=p1G1_2[j].min_pair[0];
                                        p1G01_12[j].min_quad[3]=p1G1_2[j].min_pair[1];
                                        //printf("p1G01_12[%d].min_quad[0]=%d\n",j,p1G01_12[j].min_quad[0]);
                                        //printf("p1G01_12[%d].min_quad[1]=%d\n",j,p1G01_12[j].min_quad[1]);
                                        //printf("p1G01_12[%d].min_quad[2]=%d\n",j,p1G01_12[j].min_quad[2]);
                                        //printf("p1G01_12[%d].min_quad[3]=%d\n",j,p1G01_12[j].min_quad[3]);
                                        
                                        p1G01_12[j].diff[0]=p1G0_1[0].diff;
                                        p1G01_12[j].diff[1]=difference;
                                        //printf("This = %d",p1G01_12[j].diff[1]);
                                        
                                        p1G0_1[i].flag=1;
                                        p1G1_2[j].flag=1;
                                        
                                        printf("\n(%d,",j,p1G01_12[j].min_quad[0]);
                                        printf("%d),",p1G01_12[j].min_quad[1]);
                                        printf("(%d,",p1G01_12[j].min_quad[2]);
                                        printf("%d)",p1G01_12[j].min_quad[3]);
                                        
                                        //printf("p1G0_1[%d].diff=%d\n",j,p1G0_1[j].diff);
                                        //printf("p1G0_1[%d].flag=%d\n",j,p1G0_1[j].flag);
                                        //printf("\np1G01_12[%d].diff[0]= %d",j,p1G01_12[j].diff[0]);
                                        //printf(",%d\n",p1G01_12[j].diff[1]);
                                         //printf("Difference = %d\n",difference);
                                        //printf("p1G0_1[%d].flag= %d\n",i,p1G0_1[i].flag);
                                        //printf("G1_2[%d].flag= %d\n\n",j,p1G1_2[j].flag);
                                        G01_12_counter++;
                                        }
                                   else
                                   {
                                       if(p1G0_1[i].flag!=1)
                                       p1G0_1[i].flag=0;
                                       if(p1G1_2[j].flag!=1)
                                       p1G1_2[j].flag=0;
                                   }
                                   
                                   
                   }
         }
         //printf("Number of quads added in 01-12 phase = %d",G01_12_counter);
         
         difference=0; 
        //printf("\n\n1-2_2-3\n\n");
        /***************Loop for comparison of group (1-2) and group (2-3) elements***************************/
        for(i=0;i<G12_counter;i++)
         {
               for(j=0;j<G23_counter;j++)
                   {              
                                    //printf("i = %d,j = %d\n",i,j);
                                    //printf("p1G1_2[%d].min_pair[0] =%d\n",i,p1G1_2[i].min_pair[0]);
                                    // printf("p1G0_1[%d].min_pair[0] =%d\n",j,p1G0_1[j].min_pair[0]);
                                   difference=(p1G2_3[j].min_pair[0]-p1G1_2[i].min_pair[0]);
                                  //printf("i=%d and j=%d then difference = %d\n",i,j,difference);
                                   if((difference==1||difference==2||difference==4||difference==8||difference==16)&&(p1G1_2[i].diff==p1G2_3[j].diff))
                                       {
                                          if(difference > p1G1_2[i].diff)                                                                                                  
                                        
                                        //printf("p1G0_1[%d].min_pair[0]= %d,\n",i,p1G0_1[i].min_pair[0]);
                                        //printf("p1G0_1[%d].min_pair[1]= %d,\n",i,p1G0_1[i].min_pair[1]);
                                        //printf("p1G1_2[%d].min_pair[0]= %d,\n",i,p1G1_2[i].min_pair[0]);
                                        //printf("p1G1_2[%d].min_pair[1]= %d,\n",i,p1G1_2[i].min_pair[1]);
                                        
                                        p1G12_23[j].min_quad[0]=p1G1_2[i].min_pair[0];
                                        p1G12_23[j].min_quad[1]=p1G1_2[i].min_pair[1];
                                        p1G12_23[j].min_quad[2]=p1G2_3[j].min_pair[0];
                                        p1G12_23[j].min_quad[3]=p1G2_3[j].min_pair[1];
                                        //printf("p1G01_12[%d].min_quad[0]=%d\n",j,p1G01_12[j].min_quad[0]);
                                        //printf("p1G01_12[%d].min_quad[1]=%d\n",j,p1G01_12[j].min_quad[1]);
                                        //printf("p1G01_12[%d].min_quad[2]=%d\n",j,p1G01_12[j].min_quad[2]);
                                        //printf("p1G01_12[%d].min_quad[3]=%d\n",j,p1G01_12[j].min_quad[3]);
                                        
                                        p1G12_23[j].diff[0]=p1G1_2[0].diff;
                                        p1G12_23[j].diff[1]=difference;
                                        //printf("This = %d",p1G01_12[j].diff[1]);
                                        
                                        p1G1_2[i].flag=1;
                                        p1G2_3[j].flag=1;
                                        
                                        printf("\n(%d,",j,p1G12_23[j].min_quad[0]);
                                        printf("%d),",p1G12_23[j].min_quad[1]);
                                        printf("(%d,",p1G12_23[j].min_quad[2]);
                                        printf("%d)",p1G12_23[j].min_quad[3]);
                                        
                                        //printf("p1G0_1[%d].diff=%d\n",j,p1G0_1[j].diff);
                                        //printf("p1G0_1[%d].flag=%d\n",j,p1G0_1[j].flag);
                                        //printf("\np1G12_23[%d].diff[0]= %d",j,p1G12_23[j].diff[0]);
                                        //printf(",%d\n",p1G12_23[j].diff[1]);
                                         //printf("Difference = %d\n",difference);
                                        //printf("p1G1_2[%d].flag= %d\n",i,p1G1_2[i].flag);
                                        //printf("G2_3[%d].flag= %d\n\n",j,p1G2_3[j].flag);
                                        G12_23_counter++;
                                        }
                                   else
                                   {
                                       if(p1G1_2[i].flag!=1)
                                       p1G1_2[i].flag=0;
                                       if(p1G2_3[j].flag!=1)
                                       p1G2_3[j].flag=0;
                                   }
                                   
                                   
                   }
         }
         
        // printf("\n\n2-3_3-4\n\n");
        /***************Loop for comparison of group (2-3) and group (3-4) elements***************************/
        for(i=0;i<G23_counter;i++)
         {
               for(j=0;j<G34_counter;j++)
                   {              
                                    //printf("i = %d,j = %d\n",i,j);
                                    //printf("p1G2_3[%d].min_pair[0] =%d\n",i,p1G2_3[i].min_pair[0]);
                                     //printf("p1G3_4[%d].min_pair[0] =%d\n",j,p1G3_4[j].min_pair[0]);
                                   difference=(p1G3_4[j].min_pair[0]-p1G2_3[i].min_pair[0]);
                                  //printf("i=%d and j=%d then difference = %d\n",i,j,difference);
                                   if((difference==1||difference==2||difference==4||difference==8||difference==16)&&(p1G2_3[i].diff==p1G3_4[j].diff))
                                       {
                                          if(difference > p1G2_3[i].diff)                                                                                                  
                                        //printf("Hi\n");
                                        //printf("p1G0_1[%d].min_pair[0]= %d,\n",i,p1G0_1[i].min_pair[0]);
                                        //printf("p1G0_1[%d].min_pair[1]= %d,\n",i,p1G0_1[i].min_pair[1]);
                                        //printf("p1G1_2[%d].min_pair[0]= %d,\n",i,p1G1_2[i].min_pair[0]);
                                        //printf("p1G1_2[%d].min_pair[1]= %d,\n",i,p1G1_2[i].min_pair[1]);
                                        
                                        p1G23_34[j].min_quad[0]=p1G2_3[i].min_pair[0];
                                        p1G23_34[j].min_quad[1]=p1G2_3[i].min_pair[1];
                                        p1G23_34[j].min_quad[2]=p1G3_4[j].min_pair[0];
                                        p1G23_34[j].min_quad[3]=p1G3_4[j].min_pair[1];
                                        //printf("p1G01_12[%d].min_quad[0]=%d\n",j,p1G01_12[j].min_quad[0]);
                                        //printf("p1G01_12[%d].min_quad[1]=%d\n",j,p1G01_12[j].min_quad[1]);
                                        //printf("p1G01_12[%d].min_quad[2]=%d\n",j,p1G01_12[j].min_quad[2]);
                                        //printf("p1G01_12[%d].min_quad[3]=%d\n",j,p1G01_12[j].min_quad[3]);
                                        
                                        p1G23_34[j].diff[0]=p1G2_3[0].diff;
                                        p1G23_34[j].diff[1]=difference;
                                        //printf("This = %d",p1G01_12[j].diff[1]);
                                        
                                        p1G2_3[i].flag=1;
                                        p1G3_4[j].flag=1;
                                        
                                        printf("\n(%d,",j,p1G23_34[j].min_quad[0]);
                                        printf("%d),",p1G23_34[j].min_quad[1]);
                                        printf("(%d,",p1G23_34[j].min_quad[2]);
                                        printf("%d)",p1G23_34[j].min_quad[3]);
                                        
                                        //printf("p1G0_1[%d].diff=%d\n",j,p1G0_1[j].diff);
                                        //printf("p1G0_1[%d].flag=%d\n",j,p1G0_1[j].flag);
                                        //printf("\np1G23_34[%d].diff[0]= %d",j,p1G23_34[j].diff[0]);
                                        //printf(",%d\n",p1G23_34[j].diff[1]);
                                         //printf("Difference = %d\n",difference);
                                        //printf("p1G2_3[%d].flag= %d\n",i,p1G2_3[i].flag);
                                        //printf("p1G2_3[%d].flag= %d\n\n",j,p1G2_3[j].flag);
                                        G23_34_counter++;
                                        }
                                   else
                                   {
                                       if(p1G2_3[i].flag!=1)
                                       p1G2_3[i].flag=0;
                                       if(p1G3_4[j].flag!=1)
                                       p1G3_4[j].flag=0;
                                   }
                                   
                                   
                   }
         }
        
    }
    /**********************************End of porgram************************************/
     

                                        
                           
                    

                                     
