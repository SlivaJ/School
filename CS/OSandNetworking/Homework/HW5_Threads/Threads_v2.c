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
pthread_mutex_t update_lock;
/*
//the struct contains all shared values :
//String that will be searched
//char that is being looked for
//final count result
//thread_id value will be the length of the section that each thread is responsable for
*/
typedef struct pass_values
{
    //values to pass to thread
    char str[10000];
    char search_value;
    int final_char_count;
    int thread_id;
    int last_thread; 
    int section_size;
    // pthread_mutex_t update_lock;
    

} pass_values;
/*
//Thread function 
//Counts the instances of the search char based on thread_id
//thread_id is multiplied by thread_id to find start position
//thread_id value is the length of section except for the final section
//to account for odd number sections getting truncated final thread will continue to end of string rather than length of thread_id
//commented out print statements will show processes
*/

void *thread_function(void *arg)
{
    pass_values *dataset = (void *)arg;
    int local_thread_id = dataset->thread_id;
    int first_search_val;
    int last_search_val;
    
    dataset->thread_id++;
    //printf("Thread_ID: %d\n",local_thread_id);
    first_search_val = (dataset->section_size)*(dataset->thread_id-1);
    last_search_val = (dataset->section_size)+first_search_val;
    //printf("First val: %d Last val: %d\n",first_search_val,last_search_val);
    if(dataset->thread_id==dataset->last_thread){
        last_search_val = strlen(dataset->str);
    }
    int local_counter = 0;
    
    for(first_search_val;first_search_val<last_search_val;first_search_val++){
        //printf("Compare: %c : %c :%d\n",dataset->str[first_search_val],dataset->search_value,first_search_val);
        if(dataset->str[first_search_val]==dataset->search_value){
            local_counter++;
        }
    }

    /*
    //Results getting stored
    //mutex lock any vars that are changed below
    */
    pthread_mutex_lock(&update_lock);
    dataset->final_char_count= dataset->final_char_count+local_counter;
    pthread_mutex_unlock(&update_lock);
    // printf("This is thread: %d\n",local_thread_id+1);
    // printf("This threads final count is: %d\n",local_counter);
    return dataset;
}

int main(int argc, char *argv[])
{
    //vars from the input
    char search_char;    //input char
    char input_file[25]; //name of the file to be tested
    char threadCountStr;
    int thread_count = 5;

    /*
    //input handling
    //file name
    //char to search for
    */
    printf("File name: ");
    scanf("%s", input_file);
    fflush(stdin);
    //char 
    printf("Char: ");
    scanf("%s", &search_char);
    search_char = tolower(search_char);

    // printf("char input:\n 0: %s\n 1:%s \n",&search_char[0],&search_char[1]);
    /*
    //Thread input 
    //Thread range needs to be adjusted here
    */
    
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
    /*****************************************
    //string handling
    //pull string form doc
    //convert string to lower
    */
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
    /************************************************************
    //struct setup
    //string section search parameters 
    */
    pass_values data;
    strcpy(data.str,str);
    data.search_value = search_char;
    data.last_thread = thread_count;
    // printf("String length: %ld\n", strlen(str));
    // printf("Section length per thread: %ld\n",(strlen(str)/thread_count));
    data.section_size = (strlen(str)/thread_count);
    /*
    //thread handling
    //timer starts before create loop
    //timer ends after join loop
    */ 
    timeVal program_starttime,program_endtime;

    program_starttime = startTimer();
    pthread_t my_threads[thread_count];
    for(thread_id;thread_id<thread_count;thread_id++){
        pthread_create(&my_threads[thread_id],NULL,thread_function,&data);
        //pthread_create(&my_threads[thread_id],NULL,thread_function,&data);
        //data thread_id incriment will be used to help threads target their section
        
    }
    for(thread_id=0;thread_id<thread_count;thread_id++){
        pthread_join(my_threads[thread_id],NULL);
    }
    program_endtime = endTimer();
    /*
    //final output:
    //char count result
    //time to run
    */
    printf("The final count result: %d\n",data.final_char_count);
    printTime(program_starttime,program_endtime);
    return 0;
}