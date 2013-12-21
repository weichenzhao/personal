a = [[1,3,'a'],[4,10,'b'],[11,12,'c'],[13,20,'d'],[21,30,'e'],[30,31,'f'],[31,32,'g']]

def bsearch(num):
    bound = [0, len(a)-1]
    while(bound[1]-bound[0]>1):
        pos = (bound[0] + bound[1])>>1
        if num<a[pos][0]: #left
            bound[1] = pos # upper bound
        elif num>a[pos][1]: #right
            bound[0] = pos # lower bound
        else: # in pos
            return pos
    if num>=a[bound[0]][0] and num<=a[bound[0]][1]:
        return bound[0]
    elif num>=a[bound[1]][0] and num<=a[bound[1]][1]:
        return bound[1]
    return None

print bsearch(1)
print bsearch(3)
print bsearch(4)
print bsearch(5)
print bsearch(11)
print bsearch(19)
print bsearch(31)
print bsearch(32)
print bsearch(33)
