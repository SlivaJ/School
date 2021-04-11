/*
name: John Sliva
course: CS 330 Operating Systems
date:
Homework Label: Process Affinity
Description: Showing the difference in performance of using 1 core vs multi-programming. Uses code for basic forking and Code timer.
*/
//external c files
#include "Code_Timer.c"

//libs
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>

int main(){
    //timing vars
    struct time singleStartTime,SingleendTime,multiStartTime,multiEndTime;


    //Masks
    cpu_set_t maskSingleProcessor, maskMultiProcessor;
    //init the threads
    CPU_ZERO(&maskSingleProcessor);
    CPU_ZERO(&maskMultiProcessor);
    //set the cores for the masks
    //single
    CPU_SET(0, &maskSingleProcessor);
    //multi
    CPU_SET(0, &maskMultiProcessor);
    CPU_SET(1, &maskMultiProcessor);
    CPU_SET(2, &maskMultiProcessor);
    CPU_SET(3, &maskMultiProcessor);

    sched_setaffinity(0,sizeof(cpu_set_t),&maskSingleProcessor);
    printf("Running on one core.");
    
    system("gcc Modified_Timer.c");
    system("./a.out ForkProgram.c");
    printf("Running code timer!");
    
    //Case 2: Forking program is run while using four cores.
    printf("Running on multiple processors.");
    sched_setaffinity(0,sizeof(cpu_set_t),&maskMultiProcessor);
    printf("Running on one core.");
    system("gcc Modified_Timer.c");
    system("./a.out ForkProgram.c");
    printf("Running code timer!");

    return 0;
}
