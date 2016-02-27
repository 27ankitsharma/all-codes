/*
Name : Ankit Sharma
Roll No : CS1429
program description : This program implements dictionary using trie data structure.
Submission deadline : 01-oct-2014
*/


//structure for trie node.
typedef struct node {
       char *key;  //This key stores pointer to actual word.
       struct node* next[100];  //array of 100 structures.assuming 100 distinct
       //characters are to be stored.
}dict;
dict* root ; //root node

void insertWord (char* ,int); //function for inserting word.
int indexCalculator (char ); //functions for mapping each character to its corresponding index.
int search(char* ,int);  //function for searching a word in the dictionary.
dict* createNode ();    //function for creating new node.
void copyWord(char* ,char*);  //function for copying a word into a new word
void copyWord2(char* ,char*  ,int ); //This function copies a word into other word except
//leaving the position given by int k.


void byDeletingLetter(char* );/*This function takes input the input word and generates suggestion by deleting any one
letter one by one. */
void byAddingLetter (char* ); /*Function for generating suggestions by changing any single letter from input word.*/
void byChangingLetter(char*); /*Function for generating suggestion by changing any letter at any position.*/
void bySwappingLetter(char*); /*This function generates suggestions by swapping any two characters in the input word.*/
