# Definition for a  binary tree node
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Solution:
    # @param root, a tree node
    # @return a list of integers
    def inorderTraversal(self, root):
        if root == None:
            return []
        ret = []
        stack = []
        current = root
        #print ( current != None and len( stack ) != 0 )
        while ( current != None or len( stack ) != 0 ):
            while ( current != None ):
                stack.append( current )
                #print id( current ), id( current.left )
                current = current.left
            if ( len( stack ) != 0 ):
                current = stack.pop()
                ret.append( current.val )
                current = current.right
        return ret

if __name__ == '__main__':
    a = []
    for inter in range( 10 ):
        a.append( TreeNode( inter ) )
    a[ 0 ].left = a[ 1 ]
    a[ 0 ].right = a[ 2 ]
    a[ 1 ].left = a[ 3 ]
    a[ 1 ].right = a[ 4 ]
    a[ 2 ].left = a[ 5 ]
    a[ 2 ].right = a[ 6 ]
    a[ 3 ].left = a[ 7 ]
    a[ 3 ].right = a[ 8 ]
    a[ 4 ].left = a[ 9 ]
    #print a
    test = Solution()
    print test.inorderTraversal( a[ 0 ] )
