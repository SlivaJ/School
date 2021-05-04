/*
Name: John Sliva
Course: CS330: Operating Systems
Date: 4/26/2021
Homework Label: Scheduling
//Using nice levels to change scheduling 
//Includes Pthreads 
//Includes Forking
//Uses modified Code Timer from assignment two to display time 
//******************************************************************************************
//The threading code from HW5_Threads_v2 has been modified to have static values for inputs.
//It will have 4 threads, and search for the char x, The input file is also included "" 
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/resource.h>

#include "Code_Timer_mod.c"

#define _GNU_Source
/*
//global vars
*/
int sleep_time = 5;
/*
//Waits for a few seconds to simulate doing work 
*/
void *thread_function(void *arg)
{
    
    int big_number = 1000000;
    volatile long sigma = 0;
    // printf("This is in the thread.\n");
    for(int i=0;i<big_number;i++){
        sigma = sigma+i;  
    }
    // sleep(sleep_time);
    return NULL;
}
/*
//Waits for a few seconds to simulate doing work 
*/
void process_function()
{
    int big_number = 1000000;
    for(int j=0;j<1000;j++){
    volatile long sigma = 0;
    // printf("This is in the thread.\n");
    for(int i=0;i<big_number;i++){
        sigma = sigma+i;  
    }
    }
    // sleep(sleep_time);
}
/*
//creates 2 threads 1:high nice 2:no nice
//creates 2 forks   1:high nice 2:no nice
*/
int main()
{
    printf("main start(0)\n");
    
    /*
    //timers for the program 
    //these will be used for both threads and forks
    */
    timeVal start_no_nice, end_no_nice;
    timeVal start_nice, end_nice;
    /*
    //Start off with the two threads
    //thread one will change the nice
   */
    pthread_t nice_thread, not_nice_thread;
    //******************************************************
    //no nice
    //******************************************************
    start_no_nice = startTimer();
    pthread_create(&nice_thread, NULL, thread_function, NULL);
    pthread_join(nice_thread, NULL);
    end_no_nice = endTimer();
    
    //******************************************************
    //nice level increased
    //******************************************************
    sleep(sleep_time);
    start_nice = startTimer();
    nice(-10);
    pthread_create(&not_nice_thread, NULL, thread_function, NULL);
    pthread_join(not_nice_thread, NULL);
    end_nice = endTimer();
    printf("***************************************This thread is timed with no nice:***************************************\n");
    printTime(start_no_nice, end_no_nice);
    printf("***************************************This thread is timed with low nice***************************************\n");
    printTime(start_nice, end_nice);
    //******************************************************
    //Threading time confirmed above: Below is for forking
    //******************************************************
    
    printf("\n\n***************************************Below is forking***************************************\n\n");
    // fork program
    // child will split off and do the function task with a lower nice value.
    // main will wait for child then end the timer. 
    // nice will be reverted and main will call process function again and time it
    //reset nice
    nice(0);
    
    
    int pid = fork();

    if (pid == -1)
    {
        perror("failed to fork\n");
    }
    if (pid == 0)
    {
        nice(-19);
        start_nice = startTimer();
        process_function();
        end_nice = endTimer();
    }
    if (pid > 0)
    {
        wait(NULL);
        
        //reset nice
        nice(0);
        start_no_nice = startTimer();
        process_function();
        end_no_nice = endTimer();
        printf("***************************************This process is timed with no nice:***************************************\n");
        printTime(start_no_nice, end_no_nice);
        printf("***************************************This process is timed with low nice:***************************************\n");
        printTime(start_nice,end_nice);
    }
    
   return 0;
}