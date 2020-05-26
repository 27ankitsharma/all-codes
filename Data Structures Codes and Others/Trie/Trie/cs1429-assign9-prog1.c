/*
Name : Ankit Sharma
Roll No : CS1429
program description : This program implements dictionary using trie data structure.
Submission deadline : 01-oct-2014
*/
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include"cs1429-assign9-prog1.h"
#include<stdio.h>


int main(void)
{

    root = NULL;
    FILE *fp=NULL;
    fp = fopen( "words" , "r");  //opening file in read mode.

    char ch;
    char tmpWord[50]; //Assuming file is having words at most 50 characters long.
    char* tmpWord2 =NULL;
    //piece of code for measuring time taken in insertion.
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    while ( (fscanf(fp,"%s",tmpWord))!=EOF )    //reading character into tmpWord word by word..
    {
        tmpWord2 = upperToLower(tmpWord);  //converting each capital letter into its corresponding small letter
        insertWord(tmpWord2 ,50);  //inserting word into trie.


    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Insertion has been done in %f seconds.",cpu_time_used);//printing taken time in insertion
    int choice;
    do
    {
        char word[50]; //assuming input word can be 50 characters long at most.
        char* word2 =NULL;
        printf("\nEnter the word you want to search:\n");
        scanf("%s",word);
        word2 = upperToLower(word);  //converting each capital letter into its corresponding small letter

        //piece of code for measuring time taken in insertion.
        clock_t start, end;
        double cpu_time_used =0;
        start = clock();
        int status = search(word2 ,strlen(word2));
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

        if (status ==1)  //if search was successful
            printf("Word is found in %f seconds.\n",cpu_time_used); //printing taken time in searching word.

        else   //if search was not successful then printing suggestions.
        {
            printf("'%s' is not present in dictionary.Some suggestions are following:\n",word2);
            suggestion(word2);
        }
        printf("\nDo you want to search more words?\n");
        printf("if yes press 1 otherwise press any other key to exit\n");
        scanf("%d",&choice);
    }
    while(choice == 1);
//free(root);
    fclose(fp); //closing file.
    freeing(root);
    return 0;
}
