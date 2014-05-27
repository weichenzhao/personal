# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#        self.val = x
#        self.next = None

class Solution:
    # @param head, a ListNode
    # @return a ListNode
    def insertionSortList(self, head):
        if not head: return None
        if not head.next: return head
        if not hasattr(head, "next"): return None
        rh = ListNode(0) # real head
        rh.next = head 
        prev_p = head
        while prev_p.next:
            if(prev_p.next.val >= prev_p.val): #if sorted
                prev_p = prev_p.next # need to move proc_p forward
                continue
            prev_c = rh
            while (prev_c.next.val < prev_p.next.val):
                prev_c = prev_c.next
            t = prev_p.next
            prev_p.next = t.next
            t.next = prev_c.next
            prev_c.next = t 
            # no need to move prov_p forward
        return rh.next
