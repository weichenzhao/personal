#!/bin/bash
for VAR in `seq 1 1 10`
do
    cat $VAR.txt
done

for files in ./*
do
    ls -l $files
done
