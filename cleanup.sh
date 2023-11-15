#!/bin/bash

echo "This script will delete all output files from previous runs."
echo "Are you sure you want to continue? (y/n)"
read answer

if [ "$answer" != "${answer#[Yy]}" ] ;then
    echo "Cleaning up output from previous runs..."

    cd bubble-sort/
    rm memory.*.csv
    rm *.txt

    cd ..
    cd insertion-sort/
    rm memory.*.csv
    rm *.txt

    cd ..
    cd merge-sort/
    rm memory.*.csv
    rm *.txt

    cd ..
    cd quick-sort/
    rm memory.*.csv
    rm *.txt

    cd ..
    cd selection-sort/
    rm memory.*.csv
    rm *.txt

    echo "Clean up complete!"
else
    echo "Clean up cancelled by the user."
fi