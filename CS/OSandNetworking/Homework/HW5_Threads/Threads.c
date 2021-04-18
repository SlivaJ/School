/*
Name: John Sliva
Course: CS330: Operating Systems
Date: 3/20/2021
Homework Label: Threading
//input for threads.c include   |||search char, number of threads, input file|||
//assumed max file input size == 10,000
//variable thread count to divide work.
// 
*/
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>
#include <string.h>
#include "fileManager.c"

#define _GNU_SOURCE
#define BUFFER1 = 50;
#define BUFFER2 = 50;

typedef struct data
{
    int countVal;
    long startTime, endTime;

} data;

//function counts the instances of a character in a section of a string.
data tCount(char *section, char searchVal)
{
    int charCount = 0;
    int i = 0;
    while (section[i] != '\0')
    {
        if (section[i] == searchVal)
        {
            charCount++;
        }

        i++;
    }
    return charCount;
}

int main(int argc, char *argv[])
{
    //vars from the input
    char searchChar[1]; //input char
    char inputFile[25]; //name of the file to be tested
    char threadCountStr[3];
    int threadCount = 5;

    //input handling
    //file name
    printf("File name: ");
    scanf("%s", inputFile);
    fflush(stdin);

    //char to look for
    printf("Char: ");
    scanf("%s", searchChar);
    fflush(stdin);

    //threads to use
    while (threadCount > 4 || threadCount < 1)
    {
        printf("Thread Count (1-4): ");
        scanf("%s", threadCountStr);
        threadCount = atoi(threadCountStr);
        if (threadCount > 4 || threadCount < 1)
        {
            printf("Thread count must range from 1-4\n");
        }
        fflush(stdin);
    }
    pthread_t thread_ID[threadCount];

    //String setup
    char str[10000];
    get_String(str, inputFile);

    //divide string into sections based on threadCount input

    //threads
    // for (i = 0; i < noOfThread; i++)
    // {
    //     pthread_create(&thread_id[i], NULL, &thread_function, NULL);
    // }
    pthread_create(thread_ID[0], NULL, tCount(data), NULL);

    return 0;
}