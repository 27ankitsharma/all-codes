/*
Name: ANKIT SHARMA
Roll Number: CS1429
Date of Submission: 06/09/14
Deadline date: 08/09/14
Program description: This C program creates a singly linked list using self referential structures with the following
functionalities:
a.add a node at the beginning of the link list
b.add a node at the end of the link list.
c.add a node at the end of the link list; [15]
(c) ask from the user at which position the node is to be added, and if possible, add the node at the requisite
location.
d.delete a node from the beginning of the link list.
e.delete a node from the end of the link list;
f.(f) ask from the user the position of the node to be deleted, and if possible, 
delete the node from the requisite location.
g.prints the linked list
h.Once the linked list is created, simulate the to and fro walk on the linked list using link reversal techniques
*/


#include<stdlib.h>
#include<malloc.h>
#include"cs1429-assign5-prog1.h"


struct node *head=NULL; //declaring structure type variable for linked list and intializing to NULL
int counter=0;     //This keeps track of current number of nods in the linked list.

int main( void ){

  int i,node_Count , choice, value;  /*i is loop variable,node_Count gets the value of number of nodes
  input by the user,choice is switch variable.*/
   
  
  do {
  
           printf("\n\n*******************************************\n");
           printf("   Enter your choice\n");
           printf("\t1.Create linked list(For inserting some initial node at once)\n");
           printf("\t2.Insert at begining\n");
           printf("\t3.Insert at end\n");
           printf("\t4.Insert at particular position\n");
           printf("\t5.Print Linked list\n");
           printf("\t6.Delete a node at particular position.\n");
           printf("\t7.Delete a node at beginning\n");
           printf("\t8.Delete a node at the end\n");
           printf("\t9.Linked list Reversal(Reversing whole list at once.)\n");
           printf("\t10.Back and Forth traversal of linked list\n");
           printf("\tPress any other key for Exit\n");
           scanf("%d",&choice);
           
           switch(choice)
           {
                    /*Creating linked list at once if user wishes to insert some node at once.*/
                         case 1:
                              counter=0; //intialiasing to zero.
                              printf("How many nodes you want to insert\n");
                              scanf("%d",&node_Count);
                              printf("please enter the %d values :\n",node_Count);
                              for(i=0; i < node_Count; i++){
                                  scanf("%d",&value);
                                  insert(head,value);
                              }
                              printf("Your list has been created successfully.Your list is folowing:\n");
                              display(head);  //printing inserted nodes.
                              break;
                              
                    /*Adding element at the beginning of linked list.*/
                         case 2:
                              printf("Enter the value\n");
                              scanf("%d",&value);
                              add_At_Beg(value);
                              printf("Your updated list is following:\n");
                              display(head);  //printing inserted node.
                              break;
                              
                    /*Adding element at the end.*/
                         case 3 :
                              printf("Please enter the value\n");
                              scanf("%d",&value);
                              insert(head,value);
                              printf("Your element has been added successfully.Your updated list is folowing:\n");
                              display(head); /printing inserted nodes.
                              break;
                              
                      /*Inserting element at specified position.*/    
                         case 4 :
                               insert_At_Pos();
                               break;
                               
                      /*printing linked list*/
                         case 5:
                              printf("Your list is here :\n");
                              display(head);  //printing inserted nodes.
                              break;
                              
                       /*Deleting element at particular position*/       
                         case 6 :
                              delete_At_Pos();
                              break;
                              
                         /*Deleting element at beginning*/
                         case 7 :
                              delete_At_Beg();
                              printf("Your updated list is :\n");
                              display(head);  //printing inserted nodes.
                              break;
                              
                         /*Deleting element at the end*/     
                         case 8 :
                              delete_At_End();
                              printf("Your updated list is :\n");
                              display(head); //printing inserted nodes.
                              break;  
                               
                       /*Reversing the linked list whole at once if user wants*/
                         case 9 :
                              reversal(head);
                              break;
                              
                       /*Traversing linked list to and fro motion.*/
                         case 10 :
                              trav_Back_N_Forth();
                              
                              exit(0);  //Since originl linked list is modified by this function, so exit.
                              break;
                              
                       /*if user want to exit.*/
                         default :
                              exit(0);
                              break;
               }
               printf("\nTotal number of node are := %d",counter); //printing total umber of nodes in the linked list.
             }while(1);
    free(head);  //Freeing memory of linked list.
    return 0;
}

            
