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

#include "Code_Timer_mod.c"

#define _GNU_Source

/*
//incriment value to count to 1,000,000,000
//
*/
void *thread_function(void *arg)
{
    int i;
    volatile int count_result;
    int count_number = 1000000000;
    for (i = 0; i < count_number; i++)
    {
        count_result = i;
    }
    return NULL;
}
/*
//incriment value to count to 1,000,000,000
//
*/
void process_function()
{
    printf("This is the function task.(2)\n");
    // int i;
    // volatile int count_result;
    // int count_number = 1000000000;
    // for (i = 0; i < count_number; i++)
    // {
    //     count_result = i;
    // }
    
}
/*
//creates 2 forks   1:high nice 2:low nice
//creates 2 threads 1:high nice 2:low nice
*/
int main()
{
    printf("main start(0)\n");
    // pid_t pid = fork();
    int pid = fork();
    
    
    if(pid==-1){
        perror("failed to fork\n");
    }
    if(pid==0){
        printf("The child will now start the timer and run the process function.(1)\n");
        process_function();
    }
    if(pid!=0){
        wait(NULL);
        printf("the main function will wait for the child and end the timer.(3)\n");
        
        printf("timer end(4)\n");
    }

}