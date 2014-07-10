#!/usr/bin/env python
import eunuchs.tuntap
from subprocess import call
import os

class Tap():
   def __init__( self, ifname=None, hw=None, ip=None, netMask=None,
                 ip6Addr=None, ifprefix='tap'):
      usr = os.popen("whoami").read()
      ret = call(["/usr/bin/sudo", "/usr/sbin/tunctl", "-u", usr[0:len(usr)-1], "-t", "tap0"])
      call(["/usr/bin/sudo", "/usr/sbin/tunctl", "-d", "tap0"])

#dev = Tap()
import fcntl
#import os
import struct
import subprocess
# Some constants used to ioctl the device file. I got them by a simple C
# program.
TUNSETIFF = 0x400454ca
TUNSETOWNER = TUNSETIFF + 2
IFF_TUN = 0x0001
IFF_TAP = 0x0002
IFF_NO_PI = 0x1000
 
# Open TUN device file.
tap = open('/dev/net/tun', 'r+b')
# Tall it we want a TUN device named tun0.
ifr = struct.pack('16sH', 'tap0', IFF_TAP | IFF_NO_PI)
fcntl.ioctl(tap, TUNSETIFF, ifr)
# Optionally, we want it be accessed by the normal user.
fcntl.ioctl(tap, TUNSETOWNER, 1000)

# Bring it up and assign addresses.
#subprocess.check_call('ifconfig tun0 192.168.7.1 pointopoint 192.168.7.2 up',
#               shell=True)

import pdb
pdb.set_trace()
