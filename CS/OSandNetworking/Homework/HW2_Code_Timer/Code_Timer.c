/*
name: John Sliva
course: CS 330 Operating Systems
date:
Homework Label: Code Timer
Description: Program will be used to view execution times.
*/
#include <stdio.h>
#include <sys/time.h>

//functions
long startTimer();
long endTimer();
void printTime();

int main(){
    //local variables
    long start_Time, end_Time;
    start_Time = startTimer();  
    end_Time =  endTimer();   
    printTime(start_Time,end_Time);
    return 0;
}
//function to get time
long startTimer(){
    struct timeval currect_time;
    long Usec; 
    gettimeofday(&currect_time,NULL);
    Usec = (currect_time.tv_sec * 1000000) + (currect_time.tv_usec); //Seconds converted to microSeconds and then extra microSeconds added for start
   
    return Usec; //microSeconds calculation return
}
//function to get time
long endTimer(){
    struct timeval currect_time;
    long Usec;
    gettimeofday(&currect_time,NULL);
    Usec = (currect_time.tv_sec * 1000000) + (currect_time.tv_usec); //Seconds converted to microSeconds and then extra microSeconds added for end
    
    return Usec; //microseconds calculation return
}
//function prints (Start time, End time, Run time )
void printTime(long start_Time,long end_Time){
    long run_Time;
    run_Time = end_Time - start_Time;//calculation for runtime in Usec (run_Time = end_Time-start_Time)
    printf(
        "Program start Time: %ld microseconds\nProgram end Time: %ld microseconds\nProgram run Time: %ld microseconds \n",start_Time,end_Time,run_Time);
}