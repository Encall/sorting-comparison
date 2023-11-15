#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void swap(unsigned int *a, unsigned int *b){
    unsigned int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(unsigned int *arr, int left, int right){
    unsigned int pivot = arr[left];
    int i = left;
    int j = right + 1;
    while (i < j)
    {
        do
        {
            i++;
        } while (i < right && arr[i] <= pivot);
        do
        {
            j--;
        } while (j >= left && arr[j] > pivot); // it must be while (arr[j] > pivot)
        if (i < j)
        {
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[left], &arr[j]);
    return j;
}

void quickSort(unsigned int arr[], int left, int right) {
    while (left < right) {
        int pivotIndex = partition(arr, left, right);
        if (pivotIndex - left < right - pivotIndex) {
            quickSort(arr, left, pivotIndex - 1);
            left = pivotIndex + 1;
        } else {
            quickSort(arr, pivotIndex + 1, right);
            right = pivotIndex - 1;
        }
    }
    
}

int main(int argc, char *argv[]){
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
    quickSort(arr, 0, n-1);
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC; // in seconds
    char *baseFilename = "output_quickSort_";
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