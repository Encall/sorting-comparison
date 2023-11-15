#!/bin/bash

sort="./mergeSort"
num_runs=5
script_directory="$(dirname "$0")"
dataset_folder="$script_directory/../dataset"  # Update this if needed

# Find all dataset files in the dataset folder
datasets=($(find "$dataset_folder" -maxdepth 1 -type f))

# Compile the sorting algorithm
echo "Compiling $sort..."
gcc mergeSort.c -o mergeSort
wait $!
echo "Compilation complete!"

for dataset in "${datasets[@]}"
do
  for ((run=1; run<=$num_runs; run++))
  do
    echo "Running iteration $run for dataset: $dataset..."
    # Extract just the filename from the path
    dataset_filename=$(basename "$dataset")
    
    # Capture memory usage of that sort
    valgrind --tool=massif --time-unit=ms --massif-out-file=massif.out.$run.$dataset_filename "$sort" "$dataset"
    wait $!
    
    # Extract just the filename from the path for massif-to-csv as well
    massif-to-csv massif.out.$run.$dataset_filename memory.$dataset_filename.$run.csv
  done
done

echo "All $num_runs runs complete!"
echo "Data set are ${datasets[@]}"
echo "Cleaning up..."
rm massif.out.*
