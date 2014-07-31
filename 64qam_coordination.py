import matplotlib.pyplot as plt
from random import randrange
import numpy as np
import os

def getSection( cur, x, y ):
   _x = x
   _y = y 
   if cur == 1:
      _x = 1 - _x
      _y = 1 - _y
   elif cur == 2:
      _y = 1 - _y
   elif cur == 4:
      _x = 1 - _x
   
   if _x == 1 and _y == 1:
      ret = 3
   elif _x == 0 and _y == 1:
      ret = 4
   elif _x == 0 and _y == 0:
      ret = 1
   elif _x == 1 and _y == 0:
      ret = 2
   return ret

def getSection2( cur, x, y ):
   _x = x
   _y = y 
   if cur == 1:
      _x = 1 - _x
      _y = 1 - _y
   elif cur == 2:
      _y = 1 - _y
   elif cur == 4:
      _x = 1 - _x

   if _x == 1 and _y == 1:
      ret = 1
   elif _x == 0 and _y == 1:
      ret = 2
   elif _x == 0 and _y == 0:
      ret = 3
   elif _x == 1 and _y == 0:
      ret = 4
   return ret

def getSign( section ):
   if section == 1:
      return [ 1, 1 ]
   elif section == 2:
      return [ -1, 1 ]
   elif section == 3:
      return [ -1, -1 ]
   else:
      return [ 1, -1 ]

def getCoord64( num ):
   cord1 = getSection( 3, num >> 5 & 1 , num >> 2 & 1 )
   cord2 = getSection( cord1, num >> 4 & 1, num >> 1 & 1 )
   cord3 = getSection( cord2, num >> 3 & 1, num & 1 )
   coordx = 4 * getSign(cord1)[0] + 2 * getSign(cord2)[0] + 1 * getSign(cord3)[0]
   coordy = 4 * getSign(cord1)[1] + 2 * getSign(cord2)[1] + 1 * getSign(cord3)[1]
   print coordx, coordy

def getCoord256( num ):
   cord1 = getSection( 3, num >> 7 & 1 , num >> 3 & 1 )
   cord2 = getSection( cord1, num >> 6 & 1, num >> 2 & 1 )
   cord3 = getSection( cord2, num >> 5 & 1, num >> 1 & 1 )
   cord4 = getSection( cord3, num >> 4 & 1, num & 1 )
   coordx = 8 * getSign(cord1)[0] + 4 * getSign(cord2)[0] + 2 * getSign(cord3)[0] + 1 * getSign(cord4)[0] 
   coordy = 8 * getSign(cord1)[1] + 4 * getSign(cord2)[1] + 2 * getSign(cord3)[1] + 1 * getSign(cord4)[1] 
   return coordx, coordy

def getCoord256_2( num ):
   cord1 = getSection( 3, num >> 7 & 1 , num >> 6 & 1 )
   cord2 = getSection( cord1, num >> 5 & 1, num >> 2 & 1 )
   cord3 = getSection( cord2, num >> 4 & 1, num >> 1 & 1 )
   cord4 = getSection( cord3, num >> 3 & 1, num & 1 )
   coordx = 8 * getSign(cord1)[0] + 4 * getSign(cord2)[0] + 2 * getSign(cord3)[0] + 1 * getSign(cord4)[0] 
   coordy = 8 * getSign(cord1)[1] + 4 * getSign(cord2)[1] + 2 * getSign(cord3)[1] + 1 * getSign(cord4)[1] 
   return coordx, coordy

def randomTest():
   for ranges in range(5,256,5):
      ave1 = 0
      ave2 = 0
      times = 500
      for iter in range(times):
         matrix1 = np.arange(256).reshape((16,16))
         matrix2 = np.arange(256).reshape((16,16))
         for j in range(16):
            for k in range(16):
               matrix1[k][j] = 0
               matrix2[k][j] = 0

         added = []
         for i in range(ranges):
            # pure random
            while True:
               num = randrange( 256 )
               if num not in added:
                  added.append(num)
                  break
            #plt.text(getCoord256(num)[0], getCoord256(num)[1], '%s' % num , color='red')
            #plt.text(getCoord2562(num)[0], getCoord2562(num)[1], '%s' % num , color='blue')   
            matrix1[(getCoord256(num)[0]+15 )/ 2][(getCoord256(num)[1]+15) / 2] = 1
            matrix2[(getCoord256_2(num)[0]+15)/ 2][(getCoord256_2(num)[1]+15)/ 2] = 1
         np.savetxt('matrix1.txt', matrix1, fmt='%1u') 
         np.savetxt('matrix2.txt', matrix2, fmt='%1u')

         ret1 = int(os.popen('cat matrix1.txt | ./a.out').read())
         ret2 = int(os.popen('cat matrix2.txt | ./a.out').read())
         ave1 += ret1
         ave2 += ret2

         #plt.xlim(-20, 20)
         #plt.ylim(-20, 20)
         #plt.show()

      print "average for", ranges,"random:\t\t", "{0:.4f}".format(ave1/(ranges*times*1.0)), " {0:.4f}".format(ave2/(ranges*times*1.0))

def randomTest10Elem():
   for ranges in range(1,26,1):
      ave1 = 0
      ave2 = 0
      times = 500
      for iter in range(times):
         matrix1 = np.arange(256).reshape((16,16))
         matrix2 = np.arange(256).reshape((16,16))
         for j in range(16):
            for k in range(16):
               matrix1[k][j] = 0
               matrix2[k][j] = 0
         added = []
         for i in range(ranges):
            while True:
               num = 10*randrange( 26 )
               if num not in added:
                  added.append(num)
                  break
            for l in range(10):
               #plt.text(getCoord256(num+l)[0], getCoord256(num+l)[1], '%s' % (num+l) , color='red')
               #plt.text(getCoord2562(num+l)[0], getCoord2562(num+l)[1], '%s' % (num+l) , color='blue')   
               matrix1[(getCoord256(num+l)[0]+15 )/ 2][(getCoord256(num+l)[1]+15) / 2] = 1
               matrix2[(getCoord256_2(num+l)[0]+15)/ 2][(getCoord256_2(num+l)[1]+15)/ 2] = 1

         np.savetxt('matrix1.txt', matrix1, fmt='%1u') 
         np.savetxt('matrix2.txt', matrix2, fmt='%1u')

         ret1 = int(os.popen('cat matrix1.txt | ./a.out').read())
         ret2 = int(os.popen('cat matrix2.txt | ./a.out').read())
         ave1 += ret1
         ave2 += ret2

         #plt.xlim(-20, 20)
         #plt.ylim(-20, 20)
         #plt.show()

      print "average for", ranges*10,"random 10 elem:\t\t", "{0:.4f}".format(ave1/(ranges*10.0*times)), " {0:.4f}".format(ave2/(ranges*10.0*times))

randomTest()
randomTest10Elem()
