import matplotlib.pyplot as plt
from random import randrange
import numpy as np
import os
import pdb
import time
import hull

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
   for ranges in range(5,256,10):
      start = time.time()
      ave1 = 0
      ave2 = 0
      times = 100
      for iter in range(times):
         pointSet = []
         matrix1 = np.arange(256).reshape((16,16))
         matrix2 = np.arange(256).reshape((16,16))
         for j in range(16):
            for k in range(16):
               matrix1[k][j] = -2
               matrix2[k][j] = -2

         added = []
         for i in range(ranges):
            # pure random
            while True:
               num = randrange( 256 )
               if num not in added:
                  added.append(num)
                  break
            pointSet.append([(getCoord256(num)[0]+15 )/ 2,(getCoord256(num)[1]+15) / 2])
            matrix1[(getCoord256(num)[0]+15 )/ 2][(getCoord256(num)[1]+15) / 2] = -1
            matrix2[(getCoord256_2(num)[0]+15)/ 2][(getCoord256_2(num)[1]+15)/ 2] = -1
         ret1 = len(conComp(pointSet))
         ret2 = len(conComp(pointSet))
         ave1 += ret1
         ave2 += ret2
      end = time.time()
      print "average for", ranges,"random: \t\t", ave1, ave2, "{0:.4f}%".format(ave1*100/(ranges*times*1.0)), " {0:.4f}%".format(ave2*100/(ranges*times*1.0)), "\t\t in", end-start, "seconds"

def randomTestContElem( endPoint, step, elemNum ):
   for ranges in range(1, endPoint, step):
      ave1 = 0
      ave2 = 0
      times = 100
      for iter in range(times):
         pointSet = []
         matrix1 = np.arange(256).reshape((16,16))
         matrix2 = np.arange(256).reshape((16,16))
         for j in range(16):
            for k in range(16):
               matrix1[k][j] = -2
               matrix2[k][j] = -2
         added = []
         for i in range(ranges):
            while True:
               num = step*randrange( endPoint )
               if num not in added:
                  added.append(num)
                  break
            for l in range(elemNum):
               pointSet.append([(getCoord256(num+l)[0]+15 )/ 2,(getCoord256(num+l)[1]+15) / 2])
               matrix1[(getCoord256(num+l)[0]+15 )/ 2][(getCoord256(num+l)[1]+15) / 2] = -1
               matrix2[(getCoord256_2(num+l)[0]+15)/ 2][(getCoord256_2(num+l)[1]+15)/ 2] = -1
         ret1 = len(conComp(pointSet))
         ret2 = len(conComp(pointSet))
         ave1 += ret1
         ave2 += ret2
      print "average for", ranges, "random", elemNum, "elem:\t\t", \
            ave1, ave2, "{0:.4f}%".format( ave1 * 100 / ( ranges*10.0*times ) ), \
            " {0:.4f}%".format( ave2 * 100 / ( ranges * 10.0 * times ) )

def useCase( addr ):
   pointSet = []
   matrix1 = np.arange( 256 ).reshape( ( 16, 16 ) )
   for j in range( 16 ):
      for k in range( 16 ):
         matrix1[ k ][ j ] = 0
   for point in addr:
      plt.text( getCoord256( point )[ 0 ], getCoord256( point )[ 1 ], '%s' % ( point ) , color = 'red' )
      pointSet.append( [ ( getCoord256( point ) [ 0 ] + 15 ) / 2, ( getCoord256 ( point ) [ 1 ] + 15 ) / 2 ] )
      matrix1[ ( getCoord256( point )[ 0 ] + 15 ) / 2 ][ ( getCoord256( point )[ 1 ] + 15 ) / 2] = point
   ret = conComp( pointSet )
   print len( ret ), len( addr ), "{0:.4f}%".format( len( ret ) * 100 / ( len( addr ) * 1.0 ) )
   retp = []
   for line in ret:
      points = []
      for elem in line:
         points.append( matrix1[ elem[ 0 ], elem[ 1 ] ] )
      retp.append( points )
   for lines in retp:
      print lines
   for line in ret:
      for elem in hull.convex_hull( line ): 
         plt.text( elem[ 0 ] * 2 - 15, elem[ 1 ] * 2 - 15, '%s' % 'o' , color = 'blue' )
   plt.xlim( -20, 20 )
   plt.ylim( -20, 20 )
   plt.show()

def showCase( point_number ):
   ranges = point_number
   matrix1 = np.arange( 256 ).reshape( ( 16, 16 ) )
   for j in range( 16 ):
      for k in range( 16 ):
         matrix1[ k ][ j ] = -2
   added = []
   pointSet = []
   for i in range( ranges ):
      while True:
         num = randrange( 256 )
         if num not in added:
            added.append( num )
            break
      plt.text( getCoord256( num )[ 0 ], getCoord256( num )[ 1 ], '%s' % ( num ), color = 'red' )
      pointSet.append([(getCoord256(num)[0]+15 ) / 2, ( getCoord256( num )[ 1 ] + 15 ) / 2 ] )
      matrix1[ ( getCoord256( num )[ 0 ] + 15 ) / 2][ ( getCoord256( num )[ 1 ] + 15 ) / 2] = -1
   np.savetxt( 'matrix1.txt', matrix1, fmt='%1u')

   ret1 = int( os.popen( 'cat matrix1.txt | ./a.out' ).read() )
   print ret1
   print pointSet
   plt.xlim( -20, 20 )
   plt.ylim( -20, 20 )
   plt.show()

def conComp( pointSet ):
   matrix = np.arange( 256 ).reshape( ( 16, 16 ) )
   for j in range( 16 ):
      for k in range( 16 ):
         matrix[ k ][ j ] = -2
   sortedPoints = sorted( pointSet, key=lambda elems: abs( elems[ 1 ] ) + abs( elems[ 0 ] ) )
   for point in sortedPoints:
      matrix[ point[ 0 ] ][ point[ 1 ] ] = -1
      
   union = [] # at first empty
   unionCount = 0
   for point in sortedPoints:
      adjPointNum = 0
      # search 4 directions
      for adjPoint in [ [ ( point[ 0 ] + 1 ) % 16, point[ 1 ] ], [ point[ 0 ], ( point[ 1 ] + 1 ) % 16 ], \
                        [ ( point[ 0 ] - 1 ) % 16, point[ 1 ] ], [ point[ 0 ], ( point[ 1 ] - 1 ) % 16 ] ]:
         if adjPoint[ 0 ] < 0 or adjPoint[ 0 ] > 15 or adjPoint[ 1 ] < 0 or adjPoint[ 1 ] > 15:
            continue
         # rarely: if the other have a union, should combine
         if matrix[ adjPoint[ 0 ], adjPoint[ 1 ] ] > -1: # have point, belong to union
            adjPointNum += 1
            if matrix[ point[ 0 ], point[ 1 ] ] > -1 and \
               matrix[ point[ 0 ], point[ 1 ] ] != matrix[ adjPoint[ 0 ], adjPoint[ 1 ] ]: # current point belong to a different union, merge
               temp = union[ matrix[ point[ 0 ], point[ 1 ] ] ]
               union[ matrix[ point[ 0 ], point[ 1 ] ] ] = []
               union[ matrix[ adjPoint[ 0 ], adjPoint[ 1 ] ] ] += temp
               for movedPoint in temp:
                  matrix[ movedPoint[ 0 ], movedPoint[ 1 ] ] = matrix[ adjPoint[ 0 ], adjPoint[ 1 ] ]
            # still 2 possible situation; point doesnot belong to a union / two point belong to the same union (do nothing)
            elif matrix[ point[ 0 ], point[ 1 ] ] == -1:
               union[ matrix[adjPoint[0],adjPoint[1]]].append(point) 
               matrix[point[0],point[1]] = matrix[adjPoint[0],adjPoint[1]]
         elif matrix[adjPoint[0], adjPoint[1]] == -1: # have point, not belong to union
            adjPointNum += 1
            if matrix[point[0],point[1]] == -1:
               union.append([point, adjPoint])
               matrix[point[0]][point[1]] = unionCount # access point for point
               matrix[adjPoint[0]][adjPoint[1]] = unionCount # access point for adjPoint
               unionCount += 1
            else:
               try:
                  union[matrix[point[0],point[1]]].append( adjPoint )
               except IndexError:
                  print matrix
                  print point, matrix[point[0],point[1]]
                  print "union:",union
                  print "pointSet:", pointSet
                  pdb.set_trace()
                  
               matrix[adjPoint[0], adjPoint[1]] = matrix[point[0],point[1]] 

      # if no point near, add a lonely new union (after search)
      if( not adjPointNum ):
         union.append([point])
         matrix[point[0]][point[1]] = unionCount # access point
         unionCount += 1
      
   ret = []
   for innt in range(len(union)):
      if union[innt] != []:
         ret.append(union[innt])
   return ret 

def testConComp():
   for ranges in range(20,256,10):
      times = 100
      tot1 = 0
      tot2 = 0
      for iter in range(times):
         matrix1 = np.arange(256).reshape((16,16))
         matrix2 = np.arange(256).reshape((16,16))
         for j in range(16):
            for k in range(16):
               matrix1[k][j] = -2
               matrix2[k][j] = 0
         added = []
         pointSet = []
         pointmap = {}
         for i in range(ranges):
            while True:
               num = randrange( 1, 256 )
               if num not in added:
                  added.append(num)
                  break
            pointSet.append([(getCoord256(num)[0]+15 )/ 2,(getCoord256(num)[1]+15) / 2])
            matrix1[(getCoord256(num)[0]+15 )/ 2][(getCoord256(num)[1]+15) / 2] = -1
            matrix2[(getCoord256(num)[0]+15 )/ 2][(getCoord256(num)[1]+15) / 2] = num
            pointmap[ ((getCoord256(num)[0]+15 )/ 2, (getCoord256(num)[1]+15) / 2) ] = num
         np.savetxt('matrix1.txt', matrix1, fmt='%1u')
         ret1 = int(os.popen('cat matrix1.txt | ./a.out').read())
         ret2 = conComp( pointSet )
         tot1+=ret1
         tot2+=len(ret2)
         # print relative info when ret1 != ret2
         """
         if ret1 != len(ret2):
            print ret1, len(ret2)
            print matrix2
            pointss = []
            for items in ret2:
                line = []
                for elems in items:
                   line.append(pointmap[(elems[0],elems[1])])
                pointss.append(line)
            print pointss
            pdb.set_trace()
         assert ret1 == len(ret2)
         """
      print "testing ranges", ranges, "pass", tot2/(tot1*1.0)
   
def cornerCase():
   matrix1 = np.arange(256).reshape((16,16))
   matrixs = [[ -2, -2, -1, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -1, -2],
              [ -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2],
              [ -2, -2, -2, -1, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2],
              [ -2, -2, -2, -2, -1, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2],
              [ -2, -2, -2, -2, -1, -2, -2, -2, -2, -2, -1, -2, -2, -2, -1, -2],
              [ -2, -1, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -1, -2, -2, -2],
              [ -2, -2, -2, -2, -2, -2, -1, -2, -2, -2, -1, -2, -1, -2, -2, -2],
              [ -2, -2, -2, -1, -2, -2, -2, -2, -2, -2, -1, -1, -2, -2, -2, -2],
              [ -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2],
              [ -2, -2, -2, -2, -2, -2, -2, -2, -2, -1, -2, -2, -2, -2, -2, -1],
              [ -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2],
              [ -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2],
              [ -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2],
              [ -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -1, -2],
              [ -2, -1, -2, -2, -1, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2],
              [ -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2]]

   matrix2 = [[  0,  0,252,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,246,  0],
              [  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0],
              [  0,  0,  0,205,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0],
              [  0,  0,  0,  0,217,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0],
              [  0,  0,  0,  0,153,  0,  0,  0,  0,  0,144,  0,  0,  0,150,  0],
              [  0,142,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,133,  0,  0,  0],
              [  0,  0,  0,  0,  0,  0,170,  0,  0,  0,160,  0,165,  0,  0,  0],
              [  0,  0,  0,189,  0,  0,  0,  0,  0,  0,176,177,  0,  0,  0,  0],
              [  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0],
              [  0,  0,  0,  0,  0,  0,  0,  0,  0, 34,  0,  0,  0,  0,  0, 39],
              [  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0],
              [  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0],
              [  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0],
              [  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 70,  0],
              [  0,110,  0,  0,105,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0],
              [  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0]]

   pointSet = [[0,  2], [2,  3], [5,  1], [3,  4], [4,  4], [7,  3], [6,  6], \
               [4, 10], [0, 14], [6, 10], [7, 10], [14, 1], [7, 11], [5, 12], \
               [6, 12], [9,  9], [14, 4], [4, 14], [9, 15], [13, 14]]
   for i in range(16):
      for j in range(16):
         matrix1[i][j] = matrixs[i][j]
   np.savetxt('matrix1.txt', matrix1, fmt='%1u')
   ret1 = int(os.popen('cat matrix1.txt | ./a.out').read())
   ret2 = conComp(matrix1, matrix2, pointSet)
   print ret1, len(ret2)
   print ret2
   for line in matrix2:
      print line

if __name__ == "__main__":
   randomTest()
   randomTestContElem( 12, 2, 20)
   randomTestContElem( 15, 3, 17)
   randomTestContElem( 25, 3, 10)
   #randomTestContElem( 35, 5, 7)
   #randomTestContElem( 50, 5, 5)
   #showCase( 50 )
   #showCase( 10 )
   #testConComp()
