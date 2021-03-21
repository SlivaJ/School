//file manager takes input file and stores it in a string. 
//still need to modify this to return string and take input through args.
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
    char fileInputBuffer[100];
    char fullString[5000];
    //File handling
    FILE *file = fopen("loremIpsum.txt", "r");
    // Checks if the file was opened successfully
    if (file == NULL)
    {
        fputs("Failed to open the file\n", stderr);
        return -1;
    }
    while (fgets(fileInputBuffer, sizeof(fileInputBuffer), file) != NULL)
    {
        printf("%s\n", fileInputBuffer);
        strcat(fullString, fileInputBuffer);

    }
    printf("------------------------------------------------------------------------------------------------------\n");
    printf("%s",fullString);
    printf("\n");
    //File is currently fully opened and ready to be divided into smaller parts for tasking.
    
}