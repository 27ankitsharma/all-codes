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

/*Function for printing the list elements.*/
void display(struct node *current){

     if(current == NULL){  //checking if the linked list is empty
     
                  printf("Linked list is empty\n");
                  return;
     }
    
     while (current!=NULL){  //traverse upto the end
       
                          printf("%d, ",current->data);
                          current=current->next;
       }
       return;
}

/*Function for creating linked list*/
void insert (struct node *current, int value){
   
   struct node *tmp;
   
   tmp = (struct node*)malloc(sizeof(struct node)); //Dynamically allocating memory to node
   tmp->data = value;  //setting value in new node
   tmp->next = NULL;   //setting address part to NULL
   
   if(current == NULL){ //checking if the linked list is empty
    
                current = tmp;
                head = current;
                counter++;  //Incrementing node counter value by 1
                return;
    }
    
    
    while(current->next!=NULL){ //traverse upto the end
    
        
         current=current->next;
    }
    current->next = tmp;
    counter++; //Incrementing node counter value by 1
    
}

/*Functiojn for adding node at begining.*/
void add_At_Beg (int value) {

     struct node *tmp;
     tmp=(struct node *)malloc(sizeof(struct node)); //Dynamically allocating memory to node
     tmp->data = value;  //setting value in new node
     tmp->next = head;   //setting address part to NULL
     head = tmp;
     counter++;  //Incrementing node counter value by 1
     printf ("The key %d has been inserted successfully\n",value);
     
}

/*Inserting node after a given node.*/
void insert_At_Pos() {   

     int node_Pos,value;
     struct node *current;
     current = head;
     if (current == NULL){ //checking if the linked list is empty
     
           printf("List is empty.Please create Linked list first.\n");
           return;
     }
     
     printf("Enter the position at which you want to add\n");
     scanf ("%d",&node_Pos);
     if (node_Pos>counter+1||node_Pos<0) {  //checking for invalid positions
       
         printf ("Insertion can not be done at this position.\n");
         return;
       }
     printf ("Enter the value of node which you want to add\n");
     scanf ("%d",&value);
     
     if( node_Pos==1 ){  //adding at the first position
        struct node *tmp;
        tmp =(struct node *)malloc(sizeof(struct node)); //Dynamically allocating memory to node
        tmp->data =value;  //setting value in new node
        tmp->next =head;   //setting address part to NULL
        head =tmp;
        counter++;        //Incrementing node counter value by 1
        printf("The key %d has been inserted successfully\n",value);
        display (head);   //printing inserted element.
        return;
      }
      
     if( node_Pos==2 ) {  //Inserting at 2nd position 
        
              struct node *tmp;
              tmp =(struct node *)malloc(sizeof(struct node)); //Dynamically allocating memory to node
              tmp->data =value;  //setting value in new node
              tmp->next =current->next;  
              current->next =tmp;   //finally adding to the previous list
              printf("The key %d has been inserted successfully at position = %d.\n",value,node_Pos);
              display (head); //printing inserted element.
              counter++;  //Incrementing node counter value by 1
              return;
        }
        int i = 1;
        while ( i!=(counter-2)) { //traverse upto just before the specified position.  
          current =current->next;
           i++;
          }

              struct node *tmp;
              tmp =(struct node *)malloc(sizeof(struct node)); //Dynamically allocating memory to node
              tmp->data =value;  //setting value in new node
              tmp->next =NULL;   //setting address part to NULL
              tmp->next =current->next;
              current->next =tmp;  //finally adding to the previous list
              counter++; //Incrementing node counter value by 1
              printf ("The key %d has been inserted successfully at position = %d.\n",value,node_Pos);
              display (head);  //printing inserted element.
              return;
 }

void delete_At_Pos (){

     int node_Position;
     if(head == NULL) {//checking if the linked list is empty
     
           printf("List is empty\n");
           return;
     }
     printf("Enter the node position on which do you want to delete\n");
     scanf("%d",&node_Position);
     if(node_Position > counter)  {//checking for invalid position.
        
          printf("This position is not available in the list\n");
          return;
        }
     struct node *current,*prev_current;
     current =head;
     if(node_Position == 1){
     
                head =current->next;
                free (current);  //Freeing memory occupied by node
                counter--; //Decrementing node counter value by 1
                printf("The node value %d has been deleted successfully\n",node_Position);
                printf("Your updated list is folowing :\n");
                display(head);  //printing updated list
                return;
                
     }
     int i=1;
     while(i!=(node_Position-1)){  //Traversing just before upto the specified position.  
      
     current=current->next;
     i++;
     }
     
       
           prev_current =current->next;  //saving adderess to free this address
           current->next =current->next->next;  //deleting this element
           free(prev_current);  //Freeing memory occupied by node
           counter--;   //Decrementing node counter value by 1
           printf ("The node value %d has been deleted successfully\n",node_Position);
           printf ("Your updated list is folowing :\n");
           display (head);   //printing updated list
           return;
}

void delete_At_Beg()
{
     struct node* ptr=NULL;
      if(head==NULL){  //checking if the linked list is empty
  
      printf("Linked list is empty.So deletion is not possible.\n");
      return;
  }
  else {
  
      printf("Deletion at the first position has been performed successfully.\n");
      ptr=head;
      free(ptr);   //Freeing memory occupied by node
      head =head->next;  //deleting the element
      counter--;       //Decrementing node counter value by 1
      return;
  }
}

void delete_At_End(){

    struct node *current,*ptr;
    current=head;
    if(current==NULL){   //checking if the linked list is empty
    
      printf("Linked list is empty.");
      return;
    }
    if(current->next==NULL){  //if list contains only one element.
    
      ptr=head;
      head=NULL;
      counter--;  //Decrementing node counter value by 1
      free(ptr);  //Freeing memory occupied by node
      return;                      
    }
   while(current->next->next!=NULL){  //traverse upto just before the end.
    
       current=current->next;  //incrementing the pointer.
    }  
    ptr=current->next->next;
    current->next=NULL;
    free(ptr);   //Freeing memory occupied by node
    return;
}

/*Function for reversal*/
void reversal(struct node *current){

      struct node *left,*right;
      if(current==NULL) { //checking if the linked list is empty
        
                    printf("Linked list is empty.Reversal operation is not possible on empty list.\n");
                    return;
        }
      left=NULL;
      
      while(current!=NULL){  //traverse upto the end using three pointers
      
             right=current->next;  
             current->next=left;
             left=current;
             current=right;
      }
      current =left;
      display (current); //printing reversed list
      head =current;   //Freeing memory occupied by node
      return;
}

void trav_Back_N_Forth(){

     int choice;
     struct node *current,*left,*right,*print_LPtr,*print_RPtr,*print_LPtr2;
     current=head;
     if(current==NULL) { //checking if the linked list is empty
       
          printf("Linked list is empty.This operation is not possible on empty linked list.\n");
          return;
       }
     if(current->next==NULL){  //if list contains only one element.
       
          printf("There is only one element in the list.Which is = %d.So back and forth are not possible on single element.\n",current->data);
          printf("Please insert more elements and try again.\n");
          return;
       }
     right=current->next;
     left=NULL;
      printf("Right now you are on the very first element of the linked list which is = %d\n",current->data);
     do {
         
         printf("\n\nNow enter your choice:Press\n");
         printf("\t0.For back\n");
         printf("\t1.For forth\n");
         printf("\t2.For printing current list\n");
         printf("\t3.For exit\n");
         scanf("%d",&choice);
         switch(choice){
          
          //For moving back.
          case 0 :
               
            if(left==NULL){ //checking if the left portion of linked list is empty
               
                   printf("You are at the very first element of linked list.So moving back is not possible.\n");
                   
               }
           else{
                 
                 if(left->next==NULL){ //if user is at the first element.
                   
                    left->next=NULL;  
                    printf("You are at the first element which is = %d\n",left->data);
                    }
                 else{  //reversing the links.
                     right =current;
                     current =left;
                     left =left->next; 
                     current->next =right;
                     printf("Your have moved back and you are now at element = %d\n",current->data);
                     }    
                 }
                 break;
              //For moving right.   
             case 1 :
                   if(current==NULL) { //checking if the right portion of linked list is empty
                   
                      printf("Linked list is empty.You can not move ahead.\n");
                      break;
                   }
            if(current->next == NULL){  //if user is at the rightmost element.
              
             printf("You have reached at the end of linked list and you can not move ahead further\n");
              }
            else {
                //moving right and reversing the links.
                current->next=left;
                left =current;
                current =right;
                right =right->next;
                printf(" You have moved ahead and you are now at element = %d\n",current->data);
              }
              break;
            //For printing current list  
           case 2:
                      print_LPtr=left;  //keeping different variables for printing left and right portion of list
                      print_LPtr2=left;  //keeping different variables for printing left and right portion of list
                      printf("Your current list is following\n");
                      printf("\nLeft portion is : ");
                      if(print_LPtr==NULL){ //checking if the left portion of linked list is empty
                      
                         printf("Nothing is in left portion.\n");
                      }
                      print_In_Reverse(print_LPtr); //printing left portion of list in reverse order using recursive function.
                      
                      print_RPtr = current;
                      printf("\nRight portion is :\n");
                      if(print_RPtr == NULL) {  //reached at right end of right portion of list
                        
                            printf("End of the linked list\n");
                            break;
                        }
                      while(print_RPtr!=NULL){ //traverse upto the end
                      
                         printf("%d, ",print_RPtr->data);
                         print_RPtr=print_RPtr->next;
                      }
                      break;
                  //For exit of the program    
                 case 3 :
                        exit(0);
                        break;
                  //Default if user enters wrong choice.      
                 default :
                        
                         printf("Please enter a valid choice and try again.\n");

                         break;
        }
   } while (1);            
}

struct node* print_In_Reverse (struct node* ptr){

     if(ptr == NULL) { //checking if the end node is reached.
     
       return;
     }
     print_In_Reverse(ptr->next);  //caling recursively to print the element.
     printf("%d, ",ptr->data);  //printing the element
     
 }
