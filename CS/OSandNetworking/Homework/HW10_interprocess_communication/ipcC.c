/*
Name: Joshua Corelli
Course: CS330: Operating Systems
Date: 4/20/2021
Homework Label: Interprocess Communication
Made in Visual Studio Code
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
//wait()
#include <sys/wait.h>
//gettimeofday()
#include <sys/time.h>
#include <errno.h>
#include <mqueue.h>
//fork
#include <unistd.h>
//Used for random time generation and nanosleep
#include <time.h>

/* For O_* constants */
#include <fcntl.h>
//Semaphore
#include <semaphore.h>

#define SEM_MUTEX_NAME "/sem-mutex"
#define QUEUE_NAME "/josh"
#define MAX_SIZE 50
#define MAX_MSG 10
#define WAIT_SECS 10

//Prototype functions
void c();
void p(sem_t *, char *);

int main(int argc, char **argv)
{
    //local variables
    sem_t *mutex_sem;

    //Make sure the arguements are the executable, the file, and the number of child processors
    if (argc != 3)
    {
        perror("\nInvalid arguments: Executable, file, number of child processes\n");
        exit(EXIT_FAILURE);
    }

    printf("Executing tasks file ...\n");

    //Open semaphore
    if ((mutex_sem = sem_open(SEM_MUTEX_NAME, O_CREAT, 0660, 0)) == SEM_FAILED)
    {
        perror("\nSemaphore failed to open properly in main.\n");
        exit(EXIT_FAILURE);
    }

    //Loop for the number of child processors specified
    for (int i = 0; i < atoi(argv[2]); i++)
    {
        if (fork() == 0)
        {
            c();
            exit(EXIT_SUCCESS);
        }
    }

    p(mutex_sem, argv[1]);

    printf("\nExecution of task in message queue complete.\n");

    // Remove the message queue after running the program
    if (mq_unlink(QUEUE_NAME) == -1)
    {
        perror("\nMessage queue failed to be removed following execution.\n");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

//Consumer function
void c()
{
    //Local variables
    mqd_t mq;

    char buffer[MAX_SIZE + 1], logFilePath[100], pidChars[100];

    ssize_t bytes_read;

    FILE *logFILE;

    struct mq_attr attr;
    struct timespec wait_time;
    struct timeval arrival_time;

    long CombinedArrivalTime;

    int taskNum, executionTime;

    sem_t *mutex_sem;

    /* initialize the queue attributes */
    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MSG;
    attr.mq_msgsize = MAX_SIZE;
    attr.mq_curmsgs = 0;

    //Create the message queue
    if ((mq = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY, 0644, &attr)) == (mqd_t)-1)
    {
        perror("\nMessage queue failed to open properly.\n");
        exit(EXIT_FAILURE);
    }

    //Open the semaphore
    if ((mutex_sem = sem_open(SEM_MUTEX_NAME, O_RDONLY)) == SEM_FAILED)
    {
        perror("\nSemaphore failed to open properly in consumer.\n");
        exit(EXIT_FAILURE);
    }

    //Create the 3 consumer log files
    strcat(logFilePath, "consumer");
    sprintf(pidChars, "%d", getpid());
    strcat(logFilePath, pidChars);
    strcat(logFilePath, ".log");

    //Open the consumer log file
    logFILE = fopen(logFilePath, "a");
    if (logFILE == NULL)
    {
        perror("\nLog file failed to open properly in a consumer.\n");
        exit(EXIT_FAILURE);
    }
    /*void consumer (void)
    {
    struct buf_slot entity;
        while (true) {
            wait (&occupied); //Wait until there is an entity
            wait (&mutex);
            remove_the_entity(&entity);
            signal (&mutex);
            signal (&available);
            consume_the_entity(&entity);
        }
    }*/
    while (1)
    {
        //Request permission from the producer
        if (sem_wait(mutex_sem) == -1)
        {
            perror("\nSemaphore failed to wait properly in consumer.");
            exit(EXIT_FAILURE);
        }

        //Receive the message from the producer
        bytes_read = mq_receive(mq, buffer, MAX_SIZE, NULL);
        if (bytes_read < 0)
        {
            perror("\nMessage was not properly received\n.");
            exit(EXIT_FAILURE);
        }

        //Process the message
        //waiting the specified execution time
        buffer[bytes_read] = '\0';
        sscanf(buffer, "Work: %d\n with random execution time of: %d", &taskNum, &executionTime);
        wait_time.tv_sec = (time_t)executionTime;
        wait_time.tv_nsec = (long)0;
        nanosleep(&wait_time, NULL);

        //Log execution and arrival time
        gettimeofday(&arrival_time, NULL);
        CombinedArrivalTime = ((long)(arrival_time.tv_sec) * 1000000) + ((long)arrival_time.tv_usec);
        fprintf(logFILE, "%s with arrival time of: %ld\n", buffer, CombinedArrivalTime);

        //Print to the user the lastest message that was processed
        printf("\n%s\n", buffer);
    }
    return;
}

//Producer function
void p(sem_t *mutex_sem, char *userFile)
{
    //Local variables
    mqd_t mq;

    size_t buffer_size = MAX_SIZE;
    char *buffer = (char *)malloc(buffer_size * sizeof(char));
    char logFilePath[100], pidChars[100], waitChars[3];

    FILE *workFILE, *logFILE;

    long combinedArrivalTime;

    struct timespec wait_time;
    struct timeval arrival_time;
    struct mq_attr attr;

    int numSecs, numChars;

    //Open the workfile
    workFILE = fopen(userFile, "r");
    if (workFILE == NULL)
    {
        perror("\nWork file failed to open properly.\n");
        exit(EXIT_FAILURE);
    }

    //Open the message queue
    if ((mq = mq_open(QUEUE_NAME, O_WRONLY)) == (mqd_t)-1)
    {
        perror("\nMessage queue failed to open properly.\n");
        exit(EXIT_FAILURE);
    }

    //Seed the random number generator
    srand(time(NULL));

    //Create the producer log files
    strcat(logFilePath, "producer");
    sprintf(pidChars, "%d", getpid());
    strcat(logFilePath, pidChars);
    strcat(logFilePath, ".log");

    //Open the producer log file
    if ((logFILE = fopen(logFilePath, "a")) == NULL)
    {
        perror("\nLog file failed to open properly in producer.\n");
        exit(EXIT_FAILURE);
    }

    //Wait between 1 to 5 seconds before reading the work file
    numSecs = (rand() % WAIT_SECS) + 1;
    wait_time.tv_sec = (time_t)numSecs;
    wait_time.tv_nsec = (long)0;
    nanosleep(&wait_time, NULL);

    while ((numChars = getline(&buffer, &buffer_size, workFILE)) != -1)
    {
        /*void producer (void){
            struct buffer_slot entity;
            while (true) {
                produce_an_entity(&entity);
                wait (&available); //Wait for a free slot
                206 Operating System
                wait (&mutex); //Get permission
                insert_the_entity(&entity); //Put entity in queue
                signal (&mutex); //Free resource
                signal (&occupied); //One slot is filled
            }
        }*/
        //Replace the \n in the work file with the terminating character
        buffer[numChars - 1] = '\0';

        //Log execution and arrival time
        gettimeofday(&arrival_time, NULL);
        combinedArrivalTime = ((long)(arrival_time.tv_sec) * 1000000) + ((long)arrival_time.tv_usec);
        strcat(buffer, "with random execution time of: ");
        sprintf(waitChars, "%d", numSecs);
        strcat(buffer, waitChars);
        fprintf(logFILE, "%s with arrival time of: %ld\n", buffer, combinedArrivalTime);

        //Send the message
        if (mq_send(mq, buffer, MAX_SIZE, 0) < 0)
        {
            perror("\nMessage failed to send properly.\n");
            exit(EXIT_FAILURE);
        }

        //Give the consumers permission
        if (sem_post(mutex_sem) == -1)
        {
            perror("\nSemaphore failed to post properly in producer.\n");
            exit(EXIT_FAILURE);
        }

        //Wait between 1 to 5 seconds before reading the work file
        numSecs = (rand() % WAIT_SECS) + 1;
        wait_time.tv_sec = (time_t)numSecs;
        wait_time.tv_nsec = (long)0;
        nanosleep(&wait_time, NULL);
    }

    //Wait until the last message was read by the consumers
    mq_getattr(mq, &attr);
    while (attr.mq_curmsgs > 0)
    {
    }

    //Cleanup the messeage queue
    if (mq_close(mq) == ((mqd_t)-1))
    {
        perror("\nMessage queue failed to close properly.\n");
        exit(EXIT_FAILURE);
    }

    //Unlink the semaphore
    if (sem_unlink(SEM_MUTEX_NAME) == -1)
    {
        perror("\nSemaphore failed to unlink properly\n");
        exit(EXIT_FAILURE);
    }

    return;
}