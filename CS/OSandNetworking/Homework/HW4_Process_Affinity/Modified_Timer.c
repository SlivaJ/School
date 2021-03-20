/*
name: John Sliva
course: CS 330 Operating Systems
date:
Modified Code from: Code Timer
Description: Program modified to take an input string. Input should be the name of the file you want to run. It will then run the file inside the timer.
How to: compile file as usual and add argument of file name to a.out. (ie.  a.out HelloWorld.c)
*/
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

//functions
long startTimer();
long endTimer();
void printTime();

int main(int argc, char *argv[]){
    //local variables
    long start_Time, end_Time;
    char fileName[41] = "";
    char compileCommand[51]= "gcc ";
    char runCommand[11]="./a.out";
    //commands
    strcpy(fileName,argv[1]);
    strcat(compileCommand,argv[1]);

    if(argc>1){
        printf("File to be timed: %s \n",fileName);
    }
    else{
        
    }
    
    
    //Timer start
    start_Time = startTimer();
    //commands to run program being timed based on file input.
    system(compileCommand);
    system(runCommand);
    //Timer end  
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
    printf("Program start Time: %ld microseconds\nProgram end Time: %ld microseconds\nProgram run Time: %ld microseconds \n",start_Time,end_Time,run_Time);
}