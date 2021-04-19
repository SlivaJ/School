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

typedef struct pass_values{
//values to pass to thread
char str[10000];
char search_value[1];
int char_count;

}pass_values;
//function counts the instances of a character in a section of a string.
void *thread_function(void *arg)
{
    pass_values *dataset = (void*)arg;
    printf("passed data in thread:\n string: %s\n search char: %s\n char count: %d\n", dataset->str,dataset->search_value,dataset->char_count);
    // int *char_count = (void*)arg;
    char str[1000];
    //strcpy(str, (void *)arg);
    // int *char_count = malloc(sizeof(int));
    // *char_count = 10;
    int i = 0;
    //printf("string in thread:\n%s\n", str);

    // while (section[i] != '\0')
    // {
    //     if (section[i] == searchVal)
    //     {
    //         charCount++;
    //     }

    //     i++;
    // }
    return dataset;
}

int main(int argc, char *argv[])
{
    //vars from the input
    char search_char[1]; //input char
    char input_file[25]; //name of the file to be tested
    char threadCountStr[3];
    int thread_count = 5;

    //input handling
    //file name
    printf("File name: ");
    scanf("%s", input_file);
    fflush(stdin);

    //char to look for
    printf("Char: ");
    scanf("%s", search_char);
    fflush(stdin);

    //number of threads
    while (thread_count > 4 || thread_count < 1)
    {
        printf("Thread Count (1-4): ");
        scanf("%s", threadCountStr);
        thread_count = atoi(threadCountStr);
        if (thread_count > 4 || thread_count < 1)
        {
            printf("Thread count must range from 1-4\n");
        }
        fflush(stdin);
    }

    printf("input data:\nfile: %s\nchar: %s\nthreads: %d\n", input_file, search_char, thread_count);

    //string
    char str[10000];
    get_String(str, input_file);
    printf("%s\n", str);

    switch (thread_count)
    {
    case 1: // counting with one thread
    {
        pass_values data_set;
        strcpy(data_set.str,str);
        strcpy(data_set.search_value,search_char);
        int *count_val;
        pthread_t thread1;
        pthread_create(&thread1, NULL, thread_function, &data_set);
        pthread_join(thread1, (void *)&data_set);
        printf("returned val %d\n", data_set.char_count);
        break;
    }
    case 2: //split in half and count with two threads.
    {
        int *count_one;
        int *count_two;
        int total;
        break;
    }
    case 3: //split in thirds and count with three threads.
    {
        int *count_one;
        int *count_two;
        int *count_three;
        int total;
        break;
    }
    case 4: //split in 4 and count with four threads.
    {
        int *count_one;
        int *count_two;
        int *count_three;
        int *count_four;
        int total;
        break;
    }
    default:
        break;
    }

    return 0;
}