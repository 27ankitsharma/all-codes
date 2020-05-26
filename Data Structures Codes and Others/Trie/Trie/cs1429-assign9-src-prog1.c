/*
Name : Ankit Sharma
Roll No : CS1429
program description : This program implements dictionary using trie data structure.
Submission deadline : 01-oct-2014
*/
#include<stdio.h>
#include<stdlib.h>
#include"cs1429-assign9-prog1.h"
#include<string.h>
/*This function inserts a word in the dictionary.*/
void insertWord (char* word ,int len) {
        int i;

        if (root == NULL)  //if no word then return.
            root = createNode();  //create  new node

        dict* ptr = root, *newNode;
        int indexOfChar;
        for (i = 0; word[i] !='\0'; i++) {

            indexOfChar = indexCalculator(word[i]);  //mapping each character to its index
            if(ptr->next[indexOfChar]==NULL){ //if current node has NULL on corresponding character then add new node.
              newNode = createNode();
              ptr->next[indexOfChar] = newNode; //adding new node's address.

            }
            ptr = ptr->next[indexOfChar];
        }
        ptr->key = word;  //adding word at the leaf node.

    }

/*Function for searching a word in the dictionary.*/
int search(char* str ,int len) {
dict* ptr = root;
 if (ptr == NULL) {
    printf("Dictionary is empty.\n");
     return 0;
  }

  int indexOfChar ,i;
        for (i = 0; str[i] !='\0'; i++) { //untill the last character.

            indexOfChar = indexCalculator(str[i]);
            if(ptr->next[indexOfChar]==NULL){
              return 0;
            }
            ptr = ptr->next[indexOfChar];
        }
        if(ptr->key==NULL && i == len) //if current node is  null ie word not found
           return 0;
        else
          return 1;
}

/*This function maps each character to its corresponding array index using its ascii value.*/
int indexCalculator (char ch) {

   int asci;
   asci = ch;
   if(33<=asci && asci<=126) {  //these are the special characters which are in the file.
    return (asci-33);  //mapping each character index starting with 0 index.
   }
   else {
    printf("%c is a Wrong character\n",ch);
    return 0;
    }
}
/*This function creates a new node and initializes each array index to to NULL.*/
dict* createNode () {

  int i;
  dict* tmpNode;
  tmpNode = (dict*)malloc(sizeof(dict)); //alocating memory to new node dynamicaly.
  for (i = 0; i < 100; i++) //initializing root node's structure array bu NULL.
    tmpNode->next[i] = NULL;
    tmpNode->key = NULL;
  return tmpNode;

}
/*This function generates suggestion if the input word is not found in the dictionary.*/
void suggestion (char* word) {
   printf("\nBy deleting letter:");
   byDeletingLetter(word);
   printf("\n\nBy changing a letter :");
   byChangingLetter (word);
   printf("\n\nBy adding a letter at any position:");
   byAddingLetter(word);
   printf("\n\nBy swapping any two letters:");
   bySwappingLetter(word);
}

/*This function takes input the input word and generates suggestion by deleting any one
letter one by one. */
void byDeletingLetter(char* word) {
 int i, j,len;
 len = strlen(word);
 char tmp[len];

 for (i = 0; word[i] !='\0'; i++) {
    int k=0;
    for (j = 0; j < word[j] !='\0'; j++)
       if(i != j) {   //copying word except one position.
        tmp[k] = word[j];
        k++;
       }
       tmp[k] = '\0';  //putting string terminating character at the end.
       if (search(tmp ,k)==1) //if this word present in dictionary then suggest it.
         printf("\n%s",tmp); //printing suggested word.
    }

}

/*Function for generating suggestion by changing any letter at any position.*/
void byChangingLetter (char* word) {
 int i=0 ,j;
 while( word[i] != '\0') {
       char tmpWord[strlen(word)];
       copyWord(word ,tmpWord);
    for (j = 33 ;j <= 126 ;j++) {  //keeping each character one by one ranging ascii from 33 to 126.
        tmpWord[i] = j;

        if(search(tmpWord ,strlen(tmpWord))==1) //if this word present in dictionary then suggest it.
            printf("\n%s",tmpWord);
        }
    i++;
 }

}

/*Function for generating suggestions by changing any single letter from input word.*/
void byAddingLetter(char* word) {
       int len = strlen(word)+2; //creating new word of size of old word + 2.
       char tmpWord[len];
       int j=0 ,k=0;

       for( k =0 ;k < len; k++){
         for (j = 33 ;j <= 126 ;j++) {  //keeping each character one by one ranging ascii from 33 to 126.
          copyWord2(word ,tmpWord ,k);
          tmpWord[k] = j;

        if(search(tmpWord ,strlen(tmpWord))==1) //if this word present in dictionary then suggest it.
            printf("\n%s",tmpWord);
    }

 }
}

/*This function generates suggestions by swapping any two characters in the input word.*/
void bySwappingLetter(char* word) {

 int i ,j;
 char tmpWord[strlen(word)] ,tmp;
 for( i = 0; word[i]!='\0'; i++ ) {
      copyWord(word , tmpWord); //copying word to newWord.
    for (j = i+1; j < word[j]!='\0'; j++) {
        tmp = tmpWord[i];//swapping each position character one by one.
        tmpWord[i] = tmpWord[j];
        tmpWord[j] = tmp;
        if(search(tmpWord ,strlen(tmpWord))==1) //if this word present in dictionary then suggest it.
          printf("\n%s",tmpWord);
    }
 }
}

char* upperToLower (char* word) {
  char tmp[strlen(word)+1];
  int i =0;
  while (word[i] != '\0') {
    if (65<=word[i] && word[i]<=90){  //converting each capital letter by its corresponding small letter using its ascii  value.
        word[i] = word[i]+32;
        i++;
      }
    else
        i++;
  }
  word[i]='\0';
  return word;
}

/*Function for copying word to another word.*/
void copyWord(char* word ,char* tmpWord) {
   int i=0;

   while(word[i] !='\0') {
      tmpWord[i] = word[i]; //copying character by character.
      i++;
   }
   tmpWord[i] = '\0';

}
/*/This function copies a word into other word except
leaving the position given by int k.*/
void copyWord2(char* word ,char* tmpWord ,int k) {
   int i=0,j=0;

   while(word[i] !='\0') {
      if(i==k){ //copying each character except character at position pointed by k
         j++;
         k=-1; //making k = -1 just to run this while loop.Here -1 doesn't have any specific meaning.
      }
      else {
      tmpWord[j] = word[i];
      j++;
      i++;
    }

   }
   tmpWord[i+1] = '\0';
}

/*Function for freeing memory occupied by various variables etc during the execution of program.*/
void freeing(dict* ptr) {
int i ;
for(i = 0; i < 99; i++) {
    if(ptr->next[i] != NULL)
        freeing(ptr->next[i]);
    free(ptr->next[i]);
  }
}
