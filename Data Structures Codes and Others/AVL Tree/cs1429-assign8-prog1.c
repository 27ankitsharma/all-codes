/*
Name : Ankit Sharma
Roll No: CS1429
Submission date :27-oct-2014
Acknowledgement :www.geeksforgeeks.com
Program description : This program implements all the operations of an AVL tree as given in the assignment-8.
*/
            #include<stdio.h>
            #include<conio.h>
            #include"cs1429-assign8-prog1.h"
            
            
            tree* root = NULL;
            //typedef struct node tree;
            
            int main () {
            int i , choice;
            int value;
            tree* newNode;
            printf(" \nEnter your choice :\n");
            printf("1. Create AVL tree.\n");
            printf("2. Inserting a node in AVL tree.\n");
            printf("3. Delete a node from the tree.\n");
            printf("4. Perform binary search.\n");
            printf("5. Find predecessor and successor of a node.\n");
            printf("6. Print AVL Tree\n");
            printf("\n   Press any other key to Exit.\n");
            scanf("%d" , &choice);
            
            
            while (1) {
            switch( choice ) {
            int n ,i , key;
            case 1 : //creation
            printf("How many nodes you want to insert\n");
            scanf("%d",&n);
            for ( i = 0 ; i < n ; i++) {
            printf("Enter the value\n");
            scanf("%d" ,&value);
            newNode = create (value);
            if (root == NULL)  //tree is empty.
            root = newNode;
            else
            root = insert( root , newNode);
            }
            break;
            
            case 2 : //inserte a node.
            printf("Enter the value\n");
            scanf("%d" ,&value);
            newNode = create (value);
            if (root == NULL) { //tree is empty.
            root = newNode;
            return;
            }
            root = insert ( root , newNode );
            //inorder(root);
            break;
            
            case 3 : //delete a node
            if(root == NULL) {
               printf("Tree is empty.\n");
               break;
            }
            printf("Enter the key which you want to delete :\n");
            scanf ("%d" ,&key);
            root = deletion (root , key);  
            //inorder(root);
            break;
            case 4 :
            if(root == NULL) {
               printf("Tree is empty.\n");
               break;
            }
            printf("Enter the key which you want to search :\n");
            scanf ("%d" ,&key);
            tree* loc;
            loc = (tree*)binarySearch ( root , key);
            if (loc==NULL)
              printf("The key %d is not present in AVL tree.\n",key);
            else
              printf("The key %d is present in AVL tree and its occurrence is =%d\n",key,loc->count);
            break;
            case 5 :
            printf("Enter the key for which you want to find predecessor and successor :\n");
            scanf ("%d" ,&key);
            findPredAndSucc ( root , key);
            break;
            
            case 6 :
                 printf("\n\n");
                 printTree ( root , 0); //printing tree in vertical fashion.
            break;
              
            default :
             exit(0);
            }
            printf(" \nEnter your choice :\n");
            printf("1. Create AVL tree.\n");
            printf("2. Inserting a node in AVL tree.\n");
            printf("3. Delete a node from the tree.\n");
            printf("4. Perform binary search.\n");
            printf("5. Find predecessor and successor of a node.\n");
            printf("6. Print AVL Tree\n");
            printf("\n   Press any other key to Exit.\n");
            scanf("%d" , &choice);
            
            }
            getch();
            return 0;
            }
            
            
            
            
            
            
            
            
            
            
            
