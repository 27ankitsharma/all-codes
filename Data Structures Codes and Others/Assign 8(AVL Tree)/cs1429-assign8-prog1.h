 /*
Name : Ankit Sharma
Roll No: CS1429
Submission date :27-oct-2014
Acknowledgement :www.geeksforgeeks.com
Program description : This program implements all the operations of an AVL tree as given in the assignment-8.
*/
 
 typedef struct node {
        struct node *lchild;
        int data;
        int count;
        struct node *rchild;
        //int height;
 }tree;
 
 tree* create (int );
 tree* insert(tree* ,tree*);
 tree* deletion (tree* ,int );
 void printTree (tree*  , int);
 tree* leftRotation (tree* );
 tree* rightRotation (tree*);
 int balanceFactor(tree*);
 int findHeight (tree*);
 int max (int  , int );
 tree* findMinimum (tree* ptr);
 int findPredAndSucc (tree*  ,int);
 tree* findMaximum(tree* );
