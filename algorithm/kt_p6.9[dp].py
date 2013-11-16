'''You are helping to run a high-performance computing system capable of processing several terabytes 
of data per day. For each of n days, you are presented with a quantity of data: on day t, you're 
presented with xt terabytes. For each terabyte you process, you receive a fixed revenue, but any 
unprocessed data becomes unavailable at the end of the day. Your system is running with software that 
is not totally reliable, and so the amount you can process goes down with each day that passes since 
the most recent reboot of the system. On the first day after a reboot, you can process s1 terabytes, 
on the second day after a reboot you can process s2 terabytes, and so on down to sn; we assume 
s1 > s2 > s3> … > sn . (Of course you can only process up to xt terabytes on day t now matter how 
fast your system is.) To get the system back to peak performance, you can choose to reboot it, but on 
any day you choose to reboot the system, you can't process any data at all. Given the amounts of available 
data for the next n days x1 , x2 , x3, …, xn and given the profile of your system as expressed by s1, s2, 
s3, …, sn (and from a freshly rebooted system on day 1) choose the days on which you're going to reboot 
so as to maximize the total amount of data you process. Give an efficient algorithm that takes values 
for x1 , x2 , x3, …, xn and s1 , s2 , s 3, …, sn and returns the total number of terabytes processed by 
an optimal solution.'''

def test(list, func):
    v = [0]*(len(list)+2)
    f_ = 0
    for j in range(len(func)):
        v[j] = max(v[j-2] + min(func[0],list[j]), v[j-1]+min(list[j], func[f_]))
        if v[j] == v[j-2] + min(func[0],list[j]):
            f_ = 0
        #print "func[f_]:", func[f_], v[j-2], min(func[0],list[j]), v[j-1] + min(list[j], func[f_])
        f_ += 1
    print "max:", v[len(list)-1], v[:len(list)]

if __name__ == "__main__":
    test([10,10,10,10,10], [1,1,1,1,1])
    test([10,10,10,10,10], [9,4,3,2,1])
    test([0,10,10,10,10], [9,4,3,2,1])
    test([0,0,10,10,10], [9,4,3,2,1])
    test([10,0,10,0,10], [9,4,3,2,1])
    test([10,1,7,7], [8,4,2,1])
