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
#include <unistd.h>

//struct defined and renamed
typedef struct time
{
    long seconds;
    long uSeconds;
} timeVal;

//functions
timeVal startTimer();
timeVal endTimer();
void timedCode();
void printTime();

int main()
{
    //local vars
    timeVal start_Time;
    timeVal end_Time;
    //getting time values
    start_Time = startTimer();
    timedCode();
    end_Time = endTimer();
    //output
    printTime(start_Time, end_Time);
    return 0;
}
//function returns the time.
timeVal startTimer()
{
    //vars
    struct timeval current_time;
    timeVal startTime;
    //getting time values
    gettimeofday(&current_time, NULL);
    startTime.seconds = (current_time.tv_sec);
    startTime.uSeconds = (current_time.tv_usec);
    return startTime;
}
//function returns the time.
timeVal endTimer()
{
    //vars
    struct timeval current_time;
    timeVal endTime;
    //getting time values
    gettimeofday(&current_time, NULL);
    endTime.seconds = (current_time.tv_sec);
    endTime.uSeconds = (current_time.tv_usec);
    return endTime;
}

//function calculates and outputs the results
void printTime(timeVal start_Time, timeVal end_Time)
{
    //vars
    long startSeconds,
        startuSeconds,
        resultCalc,
        endSeconds,
        enduSeconds,
        enduSecondsVal,
        resultSeconds,
        resultuSeconds;
    timeVal resultTime;
    //setting values from input
    startSeconds = start_Time.seconds;
    startuSeconds = start_Time.uSeconds;
    endSeconds = end_Time.seconds;
    enduSeconds = end_Time.uSeconds;
    enduSecondsVal = enduSeconds;
    // condition test (End uSecond value is smaller than Start uSecond value)
    /*  // testing special condition specifically
    startSeconds = 3;
    startuSeconds = 999999;
    endSeconds = 4;
    enduSeconds = 1;
    enduSecondsVal = enduSeconds; */
    //Calculate results
    //condition fix (if usec of end time is smaller than usec of start then 1 min hasnt passed)
    resultSeconds = endSeconds - startSeconds;
    if (startuSeconds > enduSeconds)
    {
        resultSeconds = resultSeconds - 1;
        enduSeconds = enduSeconds + 1000000;
    }

    resultuSeconds = enduSeconds - startuSeconds;
    printf("The program started at Seconds:%ld uSeconds:%ld\n", startSeconds, startuSeconds);
    printf("The program ended at Seconds:%ld uSeconds:%ld\n", endSeconds, enduSecondsVal);
    printf("Time required to run Seconds:%ld uSeconds:%ld\n", resultSeconds, resultuSeconds);
}

// function runs the code that will be timed by this program.
void timedCode()
{
    printf("This is the code that will be timed.\n");
    //sleep(10);
}