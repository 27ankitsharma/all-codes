/*
Name : Ankit Sharma
Roll No: CS1429
Submission date :27-oct-2014
Program description : This program implements all the operations of an AVL tree as given in the assignment-8.
*/
   #include<stdio.h>
   #include<conio.h>
   #include"cs1429-assign8-prog1.h"
   
   
   /*Function for creating a new node.*/
    tree* create (int value) {
      tree* newNode = NULL;
      newNode = (tree*)malloc(sizeof(tree));
      if(newNode == NULL) {
                 printf("Malloc failed\n ");
                 exit(0);
      }
      newNode->lchild = NULL;
      newNode->data = value;
      newNode->count = 1;
      newNode->rchild = NULL;
      //newNode->height = 1;
      return newNode;
    }
    
    /*Function for inserting a node in the binary search tree.*/
    tree* insert (tree* current , tree* newNode) {
          if (current == NULL)
               return newNode;
          else if (newNode->data < current->data)        //leftsubtree is to be searched.
                 current->lchild = insert(current->lchild, newNode); //recurse on left subtree.
          else if (newNode->data > current->data)  //right subtree is not emoty.
                 current->rchild = insert(current->rchild , newNode);  //recurse}
          else
               current->count = current->count+1;
               
          //current->height = max (findHeight(current->lchild), findHeight(current->rchild))+1;
          int bf;
          bf = findHeight(current->lchild)-findHeight(current->rchild);
         
          if (bf > 1 && current->lchild->data > newNode->data) //insertion is done in left subtree of left child of unbalanaced node.
                return(rightRotation(current));
         
          if (bf > 1 && current->lchild->data < newNode->data) {//insertion is done in right subtree of left child of unbalanaced node.
                current->lchild = leftRotation(current->lchild);
                return(rightRotation(current)); 
          }
         
          if (bf < -1 && current->rchild->data < newNode->data) //insertion is done in right subtree of right child of unbalanaced node.
              return(leftRotation(current));
         
          if (bf < -1 && current->rchild->data > newNode->data){ //insertion is done in left subtree of right child of unbalanaced node.
                 current->rchild = rightRotation(current->rchild);
                 return(leftRotation(current)); 
          }
          return current;
   }
   
   /*Function for deleteting elements from AVL tree.*/
   tree* deletion (tree* current,int key) {
          if (current == NULL)
              return current;
          
          else if (key < current->data)        //leftsubtree is to be searched.
                 current->lchild = deletion(current->lchild, key); //recurse on left subtree.
          else if (key > current->data) //right subtree is not emoty.
                 current->rchild = deletion(current->rchild , key);  //recurse
          else if (key == current->data) { //current->data==key
                  if (current->lchild==NULL && current->rchild==NULL)
                     return NULL;
                  else if (current->lchild == NULL) {  //current node has only right child.
                   tree* tmp = (tree*)malloc(sizeof(tree));
                   tmp = current->rchild;
                   current = tmp;
                   free(tmp);
                   
                    }
                   else if (current->rchild==NULL){  //current node has only left child.
                   tree* tmp = (tree*)malloc(sizeof(tree));
                   tmp = current->lchild;
                   current = tmp;
                   free(tmp);
                   }
                   else {  ////current node has both left and right children.
                   tree* successor = (tree*) malloc(sizeof(tree));
                   successor = findMinimum(current->rchild);   
                   current->data = successor->data;
                   current->count= successor->count;
                   //printf("successor->data =%d",successor->data);
                   current->rchild = deletion(current->rchild,successor->data);  
                  } 
               } 
               else {//key not found.
                printf("The key %d is not present in the AVL tree.\n",key);
                return;
               }
               if(current == NULL) //if deleted node was the only node in the tree then return.
                 return current; 
          int bf;
          bf = findHeight(current->lchild)-findHeight(current->rchild);
         
          if (bf > 1 && current->lchild->data > key) //insertion is done in left subtree of left child of unbalanaced node.
                return(rightRotation(current));
         
          if (bf > 1 && current->lchild->data < key) {//insertion is done in right subtree of left child of unbalanaced node.
                current->lchild = leftRotation(current->lchild);
                return(rightRotation(current)); 
          }
         
          if (bf < -1 && current->rchild->data < key) //insertion is done in right subtree of right child of unbalanaced node.
              return(leftRotation(current));
         
          if (bf < -1 && current->rchild->data > key){ //insertion is done in left subtree of right child of unbalanaced node.
                 current->rchild = rightRotation(current->rchild);
                 return(leftRotation(current)); 
          }
          return current;
         
   }
   /*Function for performing binary search.*/
   tree* binarySearch (tree* current,int key) {
          if (current == NULL) {
              //
              return NULL;
            }
          else if (key == current->data) { //current->data==key
              
              return current;
            }
          else if (key < current->data)        //leftsubtree is to be searched.
              return(binarySearch(current->lchild, key)); //recurse on left subtree.
          else if (key > current->data) //right subtree is not emoty.
              return(binarySearch(current->rchild , key));  //recurse
   }
          
   
   /*Function for performing left rotation.*/
   tree* leftRotation (tree* ptr) {
         tree* tmp;
         //printf("\nHii in left rotation(prev)..\n");
         tmp = ptr->rchild;
         ptr->rchild = tmp->lchild;
         tmp->lchild = ptr;
         return tmp;
   }
   
   /*Function for performing right rotation.*/
   tree* rightRotation (tree* ptr) {
         tree* tmp;
         //printf("Hi in right rotation(last)\n");
         tmp = ptr->lchild;
         ptr->lchild = tmp->rchild;
         tmp->rchild = ptr;
         return tmp;
   }
   /*Function for finding inorder predecessor and inorder successor of a node.*/
   int findPredAndSucc (tree* ptr ,int key) {
        if (ptr==NULL) {
           printf("Tree is empty\n");
           return 0;
           }
           
             tree *loc,*pred ,*succ,*root;
             root = ptr;
             loc = binarySearch(ptr , key);
             //printf("hii..\n");
             if(loc==NULL) {
               printf("This node is not present in the AVL tree.\n");
               return 0;
             }
             /*computation for inorder predecessor*/
             if(loc->lchild!=NULL){
               pred = (tree*)findMaximum(loc->lchild);
               printf("Predecessor of %d is =%d and its occurrence is =%d\n",key,pred->data,pred->count);
             }
             else {
                 tree* tmp=root;
                 
                 while (tmp != NULL) {
                       //printf("hii.in while.\n");
                       if(loc->data > tmp->data){
                                    
                         pred = tmp;
                         tmp = tmp->rchild;
                         
                         }
                       else if(loc->data < tmp->data){
                            
                         tmp = tmp->lchild;
                         //printf("hii..\n");
                         }
                       else
                        break;
                 }
                 printf("Predecessor of %d is =%d and its occurrence is =%d\n",key,pred->data,pred->count);
               }
               /*computation for inorder successor*/
              if(loc->rchild!=NULL) {
                succ = (tree*)findMinimum(loc->rchild);
                printf("Successor of %d is =%d and its occurrence is =%d\n",key,succ->data,succ->count);
                }
              else {
                   tree* tmp=root;
                   while (tmp != NULL) {
                       if(loc->data < tmp->data){
                         succ = tmp;
                         tmp = tmp->lchild;
                         }
                       else {
                         tmp = tmp->rchild;
                         }
                 }
               printf("Successor of %d is =%d and its occurrence is =%d\n",key,succ->data,succ->count);
              }
              return 0;
   }
   
   /*Function for finding inorder Successor of a node in a tree.*/
   tree* findMinimum (tree* ptr) {
         if (ptr->lchild==NULL)
             return ptr;
         else 
             return findMinimum(ptr->lchild);
   }
  
   /*Function for finding inorder prdecessor of a node in AVL tree.*/
   tree* findMaximum(tree* ptr) {
         if (ptr->rchild==NULL)
            return ptr;
         else 
            return findMaximum(ptr->rchild);
         }
   /*Function for finding height of the tree.*/
    int findHeight (tree* ptr) {
        if(ptr==NULL)
           return 0;
        else {
           int h1 = findHeight(ptr->lchild);
           int h2 = findHeight(ptr->rchild);
           return (1+max( h1 ,h2));   
        }
    }
   
   /*Function for finding maximum of two values.*/
   int max (int a , int b) {
       if (a >= b )
          return a;
       else 
          return b;
   } 
   

   /*Function for printing tree.*/
   void printTree (tree* ptr , int level) {
        int i;
        if ( ptr != NULL ) {
           printTree ( ptr->rchild , level+1 );
           for ( i = 0; i < level; i++ )
               printf( "\t" );
               printf( "%d" , ptr->data);
               printf( "\n\n" );
               printTree ( ptr->lchild ,level+1 );
           }
      }
