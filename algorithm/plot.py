import sys
sys.path.append("/usr/local/lib/python2.7/site-packages")
import matplotlib.pyplot as plt

f = open('result.txt')
line = f.readline()
line1 = map(float,line.split(','))
line = f.readline()
line2 = map(float,line.split(','))

fig1 = plt.figure()
l, = plt.plot(range(50), line1, 'r-', label="Build New Heap O(nlgn)")
m, = plt.plot(range(50), line2, 'b-', label="Recursive Heapify O(n)")
plt.xlim(0, 50)
plt.ylim(0, 80)
plt.ylabel('time (s)')
plt.xlabel('tree size (10000x)')
plt.title('recursive heapify Vs build a hew heap')
plt.legend()
plt.show()
