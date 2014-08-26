class ListNode:
     def __init__(self, x):
         self.val = x
         self.next = None

class Solution:
    # @param head, a ListNode
    # @return a boolean
    
    #Time Limit Exceeded
    """
    explored = []
    def hasCycle(self, head):
        if head == None:
            return True
        elif head not in self.explored:
            self.explored.append(head)
            return self.hasCycle(head.next)
        else:
            return False
    """

    # possibly run out of recursion depth
    """
    def hasCycle(self, head):
        if head == None:
            return True
        elif head.val != None:
            head.val = None
            return self.hasCycle(head.next)
        else:
            return False
    """

    def hasCycle(self, head):
        if head == None:
            return False
        node = head.next
        while(node):
            if node.val == "explored":
                return True
            else:
                node.val = "explored"
                node = node.next
        return False

if __name__ == "__main__":
   S = Solution()
   case = ListNode(10)
   case2 = ListNode(-1)
   case.next = case
   print S.hasCycle(case)
   
