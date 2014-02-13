import threading
import time

e = threading.Event()
threads = []
_quit = False

def runner():
    tname = threading.current_thread().name
    counter = 0
    while not _quit:
        counter = counter + 1
        print 'Thread waiting', counter, ' times for event: %s' % tname 
        time.sleep(0.1)
        e.wait()
        print 'Thread got event: %s' % tname
    #return

for t in range(100):
    t = threading.Thread(target=runner)
    threads.append(t)
    t.start()

while not _quit:
    raw_input('Press enter to set and clear the event:')
    e.set()
    e.clear()
    a = raw_input('quit?')
    if a == 'y':
      e.set()# if not set, all the thread will in the e.wait() and cannot be terminated[zombie thread?]
      print "quitting" 
      print "quitting" 
      print "quitting" 
      _quit = True
      for t in threads:
        t.join()
      print 'All done.'
