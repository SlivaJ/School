/*
name: John Sliva
course: CS 330 Operating Systems
date:
Homework Label: Process Affinity
Description: Showing the difference in performance of using 1 core vs multi-programming. Uses code for basic forking and Code timer.
*/
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>

int main(){
    //Masks
    cpu_set_t maskMultiProcessor, maskSingleProcessor;
    
    //Case 1: Forking program is run while using only one cpu.
    //initialize to zero
    CPU_ZERO(&maskSingleProcessor);
    //Core zero
    CPU_SET(0,&maskSingleProcessor);
    sched_setaffinity(0,sizeof(cpu_set_t),&maskSingleProcessor);
    printf("Running on one core.");
    system("gcc Modified_Timer.c");
    system("./a.out ForkProgram.c");
    printf("Running code timer!");
    
    //Case 2: Forking program is run while using two cores.
    printf("Running on multiple processors.");
    sched_setaffinity(0,sizeof(cpu_set_t),&maskMultiProcessor);
    printf("Running on one core.");
    system("gcc Modified_Timer.c");
    system("./a.out ForkProgram.c");
    printf("Running code timer!");

    return 0;
}
