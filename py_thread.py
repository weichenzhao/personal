from threading import (Thread, Condition,
                       Lock, RLock, Semaphore)
class MyThread(Thread):
    def run(self):
        while True:
            print "running"
        pass

class My2ndThread(Thread):
    def run(self):
        while True:
            print "testing"
        pass

t = MyThread()
u = My2ndThread()
u.start()
t.start()
u.join()
t.join()
