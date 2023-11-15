#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/time.h>


void bubbleSort(unsigned int *arr, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                unsigned int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main(int argc, char *argv[]){
    struct timeval start, end;
    struct rusage usage;
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("Can't open this File : %s\n", argv[1]);
        return -1;
    }
    int n;
    fscanf(fp, "%d", &n);
    unsigned int *arr = malloc(sizeof(int) * n);
    unsigned int j;
    for (j = 0; j < n; j++)
    {
        fscanf(fp, "%u", &arr[j]);
    }
    getrusage(RUSAGE_SELF, &usage);
    start = usage.ru_utime;
    bubbleSort(arr, n);
    getrusage(RUSAGE_SELF, &usage);
    end = usage.ru_utime;
    double time_taken = ((double)(end.tv_sec - start.tv_sec)) + ( ((double)(end.tv_usec - start.tv_usec)) / 1000000.00);
    char *baseFilename = "output_";
    char *newFilename = malloc(strlen(baseFilename) + strlen(argv[1]) + 1);
    if(newFilename == NULL) {
        printf("Memory allocation failed\n");
        return 1; // or handle error as you wish
    }
    strcpy(newFilename, baseFilename);
    strcat(newFilename, argv[1]);
    // Remove path from name
    char *substring = "./../dataset/";
    char *found = strstr(newFilename, substring);
    if (found)
    {
        strcpy(found, found + strlen(substring));
    }

    FILE *res = fopen(newFilename, "a");
    if (res == NULL)
    {
        printf("Could not open file %s\n", newFilename);
        return 1; // or handle error as you wish
    }
    
    fprintf(res, "%lf\n", time_taken * 1000); // convert to milliseconds
    
    fclose(res);
    fclose(fp);
    free(newFilename);
    free(arr);
    return 0;
}
