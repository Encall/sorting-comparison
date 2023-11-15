#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include <string.h>

void merge(unsigned int* arr, int l, int r, int mid){
    int sizeLeft = (mid - l) + 1;
    int sizeRight = (r - (mid+1)) +1;
    unsigned int* newArr = malloc(sizeof(int)*(r-l+1));
    int i =0;
    int j=0;
    int k=0;
    while(i < sizeLeft && j < sizeRight){
        if (arr[l+i] < arr[(mid+1)+j]){
            newArr[k] = arr[l+i];
            i++;
            k++;
        }
        else{
            newArr[k] = arr[(mid+1)+j];
            j++;
            k++;
        }
    }

    if (i == sizeLeft){
        while (j < sizeRight){
            newArr[k] = arr[(mid+1)+j];
            j++;
            k++;
        }
    }
    else{
        while (i < sizeLeft){
            newArr[k] = arr[l+i];
            i++;
            k++;
        }
    }

    for (i =0;i<(r-l)+1;i++){
        arr[l+i] = newArr[i];
    }
}

void mergeSort(unsigned int* arr, int l, int r){
    if (r > l){
        int mid = ((l+r)/2);
        mergeSort(arr,l,mid);
        mergeSort(arr,mid+1,r);
        merge(arr,l,r,mid);
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
    mergeSort(arr, 0, n-1);
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC; // in seconds
    char *baseFilename = "output_mergeSort_";
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