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

/*Structure declaration*/
struct node
{
  int data;
  struct node *next;
};
extern int counter;
extern struct node *head;
extern struct node* print_In_Reverse(struct node*);
extern void display(struct node*);
extern void insert(struct node*, int);
extern void add_At_Beg(int);
extern void insert_At_Pos();
extern void delete_At_Pos();
extern void delete_At_Beg();
extern void delete_At_End();
extern void reversal(struct node *current);
extern void trav_Back_N_Forth();
extern struct node* print_In_Reverse(struct node* ptr);
