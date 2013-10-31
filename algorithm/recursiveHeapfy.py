# recursive heapify Vs build a hew heap

import time
import math

def siftDown(list, k):
    j = 0
    #if ((k<<1)+2 > len(list)-1):
    #    return
    if ((k<<1)+2 <= len(list)-1):
        if (list[(k<<1)+1]<list[(k<<1)+2]):
            j = (k<<1) + 1
            if (list[j]<list[k]):
                list[k], list[j] = list[j], list[k]
                siftDown(list, j)
        elif (list[(k<<1)+1]>list[(k<<1)+2]):
            j = (k<<1) + 2
            if (list[j]<list[k]):
                list[k], list[j] = list[j], list[k]
                siftDown(list, j)
    elif ((k<<1)+1 <= len(list)-1):
        if (list[(k<<1)+1]<list[k]):
            j = (k<<1)+1
            list[k], list[j] = list[j], list[k]
            siftDown(list, j)

def siftUp(list, k):
    if (k > 0):
        if list[k] < list[k>>1]:
            list[k], list[k>>1] = list[k>>1], list[k]
        siftUp(list, k>>1)

def recursiveHeapfy(list, k):
    if ((k<<1)+1<=len(list)):
        recursiveHeapfy(list, (k<<1)+1)
    if ((k<<1)+2<=len(list)):
        recursiveHeapfy(list, (k<<1)+2)
    siftDown(list, k)

def buildHeap(list):
    heap = []
    for element in list:
        heap.append(element)
        siftUp(heap, len(heap)-1)
    return heap

if __name__ == '__main__':
    timeRec = []
    timeBuild = []
    for i in range(51)[1:]:
        print i*100000
        list = range(i*100000)
        #list = range(10)
        list.reverse()

        startingPoint1= time.time()
        heap = buildHeap(list)
        endingPoint1 = time.time()
        timeRec.append(endingPoint1 - startingPoint1)
        totalTime = "%.4f" % (endingPoint1 - startingPoint1)
        print "Time BuildHeap :", totalTime, "s  Ratio with O(nlgn):", '%.5f' %(100*(endingPoint1 - startingPoint1)/(2*i*math.log(2*i,2)))

        startingPoint2 = time.time()
        recursiveHeapfy(list, 0)
        endingPoint2 = time.time()
        timeBuild.append(endingPoint2 - startingPoint2)
        totalTime = "%.4f" % (endingPoint2 - startingPoint2)
        print "Time RecHeapify:", totalTime, "s  Ratio  with  O(n) :", '%.5f' %(100*(endingPoint2 - startingPoint2)/(2*i))

    f = open("result.txt", "a")
    f.write(str(timeRec))
    f.write(str(timeBuild))
