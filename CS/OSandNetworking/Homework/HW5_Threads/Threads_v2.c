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


typedef struct pass_values
{
    //values to pass to thread
    char str[10000];
    char search_value;
    int char_count;
    int offset ; 
    

} pass_values;
//function counts the instances of a character in a section of a string.
void *thread_function(void *arg)
{
    pass_values *dataset = (void *)arg;
    //printf("passed data in thread:\n string: %s\n search char: %c\n start char count: %d\n", dataset->str, dataset->search_value, dataset->char_count);
    int local_thread_id = dataset->offset;
    dataset->offset++;
    char str[10000];
    strcpy(str, dataset->str);
    int local_counter = 0;
    int i = 0;
    //simulated add value 
    for(i;i<10000;i++){
        local_counter++;;
    }

    // while (i < strlen(str))
    // {
    //     if (str[i] == dataset->search_value)
    //     {
    //         local_counter++;
    //     }

    //     i++;
    // }
    //mutex lock char_count var for update
    dataset->char_count= dataset->char_count+local_counter;
    //unlock after update
    printf("This is thread: %d\n",local_thread_id+1);
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

    //string handling
    char str[10000];
    int l = 0;
    int thread_id = 0;
    get_String(str, input_file);
    // printf("%s\n", str);
    //convert string to lowercase
    while (l < strlen(str))
    {
        str[l] = tolower(str[l]);
        l++;
    }
    // printf("lowercase: %s",str);
    //struct setup
    pass_values data;
    strcpy(data.str,str);
    data.search_value = search_char;
    //thread handling 
    
    pthread_t my_threads[thread_count];

    for(thread_id;thread_id<thread_count;thread_id++){
        pthread_create(&my_threads[thread_id],NULL,thread_function,&data);
        //pthread_create(&my_threads[thread_id],NULL,thread_function,&data);
        //data offset incriment will be used to help threads target their section
        
    }
    for(thread_id=0;thread_id<thread_count;thread_id++){
        pthread_join(my_threads[thread_id],NULL);
    }
    printf("The final count result: %d",data.char_count);

    return 0;
}