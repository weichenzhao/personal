#!/usr/bin/python
# -*- coding: utf-8 -*-


def solveIt(inputData):
    # Modify this code to run your optimization algorithm

    # parse the input
    lines = inputData.split('\n')

    firstLine = lines[0].split()
    items = int(firstLine[0])
    capacity = int(firstLine[1])

    values = [0,]
    weights = [0,]

    for i in range(1, items+1):
        line = lines[i]
        parts = line.split()

        values.append(int(parts[0]))
        weights.append(int(parts[1]))

    items = len(values)-1
            
    # a dynamic access
    list = []
    taken = []
    for i in range(0, items+1):
        temp = []
        for j in range(0, capacity+1):
            #print i, j
            if i == 0:
                temp.append(0)
            elif weights[i]>j:
                temp.append(list[i-1][j])#if the weight is bigger than the current limit, use the previous value
            else:
                temp.append(max(list[i-1][j],values[i]+list[i-1][j-weights[i]]))
        #compare between the two value, previous max value, and value that current item plus the value under
        #capacity j(one of 1 to k) - weight of item i
        list.append(temp)
    #for i in range(len(list)):
    #print list[i]
    tracer = capacity
    for k in range(1,items+1):
        #print tracer
        if list[items-k+1][tracer] == list[items-k][tracer]:
            taken.append(0)#in the end, need reverse output
        else:
            taken.append(1)
            tracer = tracer - weights[items-k+1]
    
    value = list[items][capacity]


    # prepare the solution in the specified output format
    outputData = str(value) + ' ' + str(0) + '\n'
    outputData += ' '.join(map(str, taken))
    return outputData


import sys

if __name__ == '__main__':
    if len(sys.argv) > 1:
        fileLocation = sys.argv[1].strip()
        inputDataFile = open(fileLocation, 'r')
        inputData = ''.join(inputDataFile.readlines())
        inputDataFile.close()
        print solveIt(inputData)
    else:
        print 'This test requires an input file.  Please select one from the data directory. (i.e. python solver.py ./data/ks_4_0)'

