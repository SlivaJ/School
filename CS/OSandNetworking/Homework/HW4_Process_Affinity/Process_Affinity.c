/*
name: John Sliva
course: CS 330 Operating Systems
date:
Homework Label: Process Affinity
Description: Showing the difference in performance of using 1 core vs multi-programming. Uses code for basic forking and Code timer.
//includes print_affinity code from Spetka agenda to display affinity.
*/

//libs
#define _GNU_SOURCE
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>
//external c files
#include "Code_Timer.c"
#include "Fork_Program.c"
#include "print_Affinity.c"

int main()
{
    //test var
    int m1,m2;
    //timing vars
    timeVal singleStartTime, SingleEndTime, multiStartTime, multiEndTime;

    //Masks
    cpu_set_t maskSingleProcessor, maskMultiProcessor;
    print_affinity();
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

    //Case 1: Forking program run while using 1 core.------------------------------------------------------------------
    //set first mask that uses single core (0).
    m1 = sched_setaffinity(0, sizeof(cpu_set_t), &maskSingleProcessor);
    // sched_getaffinity();
    printf("Running on one core.\n");
    print_affinity();
    //get a starting time and hold in struct for singleStart.
    singleStartTime = startTimer();
    //call forking function reused from previous homework as something to time.
    for(int i=0;i<5;i++){
        forking();
    }
    //get a end time and hold in struct for singleEnd.
    SingleEndTime = endTimer();

    //Case 2: Forking program is run while using four cores.-----------------------------------------------------------
    //swap to second mask that has affinity set for core (0,1,2,3).
    m2 = sched_setaffinity(0, sizeof(cpu_set_t), &maskMultiProcessor);
    printf("Running on multiple cores.\n");
    print_affinity();
    //get a starting time and hold in struct for multiStart.
    multiStartTime = startTimer();
    //run forking function again
    for(int i=0;i<5;i++){
        forking();
    }
    //get a starting time and hold in struct for multiEnd.
    multiEndTime = endTimer();

    //results follow
    printf("While running on 1 core.\n");
    printTime(singleStartTime,SingleEndTime);
    printf("while running on all cores\n");
    printTime(multiStartTime,multiEndTime);
    printf("first mask:%d second mask:%d",m1, m2);

    return 0;
}
