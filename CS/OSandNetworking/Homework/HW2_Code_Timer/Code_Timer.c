/*
name: John Sliva
course: CS 330 Operating Systems
date:
Homework Label: Code Timer
Description: Program will be used to view execution times.
*/
//libs used
#include <stdio.h>
#include <sys/time.h>

//struct defined and renamed
typedef struct time
{
    long seconds;
    long uSeconds;
} time;

//functions
time startTimer();
time endTimer();
void timedCode();
void printTime();

int main()
{
    //local vars
    time start_Time;
    time end_Time;
    //getting time values
    start_Time = startTimer();
    timedCode();
    end_Time = endTimer();
    //output
    printTime(start_Time, end_Time);
    return 0;
}
//function returns the time.
time startTimer()
{
    //vars
    struct timeval current_time;
    time startTime;
    //getting time values
    gettimeofday(&current_time, NULL);
    startTime.seconds = (current_time.tv_sec);
    startTime.uSeconds = (current_time.tv_usec);
    return startTime;
}
//function returns the time.
time endTimer()
{
    //vars
    struct timeval current_time;
    time endTime;
    //getting time values
    gettimeofday(&current_time, NULL);
    endTime.seconds = (current_time.tv_sec);
    endTime.uSeconds = (current_time.tv_usec);
    return endTime;
}

//function calculates and outputs the results
void printTime(time start_Time, time end_Time)
{
    //vars
    long startSeconds,
        startuSeconds,
        endSeconds,
        enduSeconds,
        resultSeconds,
        resultuSeconds;
    time resultTime;
    //setting values from input
    startSeconds = start_Time.seconds;
    startuSeconds = start_Time.uSeconds;
    endSeconds = end_Time.seconds;
    enduSeconds = end_Time.uSeconds;
    // condition check for if uSec is larger in end time than start time.
    if (startuSeconds > enduSeconds)
    {
        endSeconds = endSeconds - 1;
    }
    /* testing special condition specifically
    startSeconds = 3;
    startuSeconds = 999999;
    endSeconds = 4;
    enduSeconds = 1; */

    //calculate the result time
    resultSeconds = endSeconds - startSeconds;
    resultuSeconds = enduSeconds - startuSeconds;
    printf("The program started at Seconds:%ld uSeconds:%ld\n", startSeconds, startuSeconds);
    printf("The program ended at Seconds:%ld uSeconds:%ld\n", endSeconds, enduSeconds);
    printf("Time required to run Seconds:%ld uSeconds:%ld\n", resultSeconds, resultuSeconds);
}

// function runs the code that will be timed by this program.
void timedCode()
{
    printf("This is the code that will be timed.\n");
}