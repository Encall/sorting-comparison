#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void insertionSort(unsigned int *arr, int n)
{
    for (int i = 1; i < n; i++)
    {
        unsigned int what = arr[i];
        int j;
        for (j = i - 1; j >= 0 && arr[j] > what; j--)
        {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = what;
    }
}

int main(int argc, char *argv[])
{
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
    clock_t start = clock();
    insertionSort(arr, n);
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC; // in seconds
    char *baseFilename = "output_insertionSort_";
    char *newFilename = malloc(strlen(baseFilename) + strlen(argv[1]) + 1);
    if (newFilename == NULL)
    {
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
