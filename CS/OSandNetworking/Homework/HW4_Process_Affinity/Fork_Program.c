/*
name: John Sliva
course: CS 330 Operating Systems
Homework Label: repurposed Basic Forking 
Description: The output of this program, when properly implemented, will exemplify the unpredictable order in which the processes are scheduled to run.
//changed function so that it would be able to be called from a seperate file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

void forking(void)
{
    //process markers
    char process[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    //perform exactly 12 "runs"
    for (int runs = 0; runs < 12; runs++)
    {
        //create 26 child proecesses
        for (int childProcess = 0; childProcess < 26; childProcess++)
        {
            pid_t mypid = fork();
            if (mypid == 0)
            {
                putchar(process[childProcess]);
                exit(0);
            }
            else if (mypid < 0)
            {
                perror("Failed to fork");
            }
        }
        while (wait(NULL) != -1)
        {
            /*waiting for loops*/
        }
        printf("\n");
    }
    
}
