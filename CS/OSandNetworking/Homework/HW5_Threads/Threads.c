/*
Name: John Sliva
Course: CS330: Operating Systems
Date: 3/20/2021
Homework Label: Threading
//input for threads.c include   |||search char, number of threads, input file|||
//assumed max file input size == 10,000
//variable thread count to divide work.
//string is read in from file and will be divided into smaller strings based on the thread count (1-4)
//each of these threads will count it's given section of string and return a value that will be summed for the total instances in the doc
*/
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>
#include <string.h>
#include <ctype.h>
#include "fileManager.c"
#include "Code_Timer_mod.c"

#define _GNU_SOURCE
#define BUFFER1 = 50;
#define BUFFER2 = 50;

typedef struct pass_values
{
    //values to pass to thread
    char str[10000];
    char search_value;
    int char_count;

} pass_values;
//function counts the instances of a character in a section of a string.
void *thread_function(void *arg)
{
    pass_values *dataset = (void *)arg;
    //printf("passed data in thread:\n string: %s\n search char: %c\n start char count: %d\n", dataset->str, dataset->search_value, dataset->char_count);
    char str[10000];
    strcpy(str, dataset->str);

    long i = 0;

    while (i < strlen(str))
    {
        if (str[i] == dataset->search_value)
        {
            dataset->char_count++;
        }

        i++;
    }
    return dataset;
}

int main(int argc, char *argv[])
{
    //vars from the input
    char search_char;    //input char
    char input_file[25]; //name of the file to be tested
    char threadCountStr;
    int thread_count = 5;

    //input handling
    //file name
    printf("File name: ");
    scanf("%s", input_file);
    fflush(stdin);
    //char to look for
    printf("Char: ");
    scanf("%s", &search_char);
    search_char = tolower(search_char);

    // printf("char input:\n 0: %s\n 1:%s \n",&search_char[0],&search_char[1]);
    // fflush(stdin);

    //number of threads
    while (thread_count > 4 || thread_count < 1)
    {
        printf("Thread Count (1-4): ");
        scanf("%s", &threadCountStr);
        thread_count = atoi(&threadCountStr);
        if (thread_count > 4 || thread_count < 1)
        {
            printf("Thread count must range from 1-4\n");
        }
        fflush(stdin);
    }

    printf("input data:\nfile: %s\nchar: %c\nthreads: %d\n", input_file, search_char, thread_count);

    //string
    char str[10000];
    int l = 0;
    get_String(str, input_file);
    // printf("%s\n", str);
    //convert string to lowercase
    while (l < strlen(str))
    {
        str[l] = tolower(str[l]);
        l++;
    }
    // printf("lowercase: %s",str);
    switch (thread_count)
    {
    case 1: // counting with one thread
    {
        timeVal threads_start, threads_end;
        pass_values data_set;
        strcpy(data_set.str, str);
        data_set.search_value = search_char;
        int *count_val;
        threads_start = startTimer();
        pthread_t thread1;
        pthread_create(&thread1, NULL, thread_function, &data_set);
        pthread_join(thread1, (void *)&data_set);
        printf("returned char count: %d\n", data_set.char_count);
        threads_end = endTimer();
        printTime(threads_start, threads_end);
        break;
    }
    case 2: //split in half and count with two threads.
    {
        //string segments
        timeVal threads_start, threads_end;
        pass_values data_set;
        char string_part1[10000], string_part2[10000];
        
        //counter values
        int *count_one;
        int *count_two;
        int total;
        //time starts with threads called

        //time ends after threads join
        break;
    }
    case 3: //split in thirds and count with three threads.
    {
        //string segments
        char string_part1[10000], string_part2[10000], string_part3[10000];
        //counter values
        int *count_one;
        int *count_two;
        int *count_three;
        int total;
        //time starts with threads calls
        //time ends after thread joins
        break;
    }
    case 4: //split in 4 and count with four threads.
    {
        //string segments
        char string_part1[10000], string_part2[10000], string_part3[10000], string_part4[10000];
        //counter values
        
        int total;
        //time starts with threads calls
        //time ends after thread joins
        break;
    }
    default:
        break;
    }

    return 0;
}