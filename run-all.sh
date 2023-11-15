#!/bin/bash

echo "DO YOU WANT TO RUN ALL THE SORTING ALGORITHMS? (y/n)"
read answer

if [ "$answer" != "${answer#[Yy]}" ] ;then
    echo "Running all sorting algorithms..."

    echo "Running bubble sort..."
    cd bubble-sort/
    ./bubbleSort.sh
    echo "Running bubble sort complete!"

    echo "Running insertion sort..."
    cd ..
    cd insertion-sort/
    ./insertionSort.sh
    echo "Running insertion sort complete!"

    echo "Running merge sort..."
    cd ..
    cd merge-sort/
    ./mergeSort.sh
    echo "Running merge sort complete!"

    echo "Running quick sort..."
    cd ..
    cd quick-sort/
    ./quickSort.sh
    echo "Running quick sort complete!"

    echo "Running selection sort..."
    cd ..
    cd selection-sort/
    ./selectionSort.sh
    echo "Running selection sort complete!"

    echo "Running all sorting algorithms complete!"
else
    echo "Running all sorting algorithms cancelled by the user."
fi