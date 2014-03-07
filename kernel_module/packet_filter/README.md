#Simple Kernel Module For Packet Filtering
----
##IP Hooks in netfilter
In netfilter_ipv4.h, IP Hooks definition are listed as follow:

| Hooks                 | Num   | Discription                                       |
| --------------------- |:-----:| ------------------------------------------------- |
| NF\_IP\_PRE_ROUTING   | 0     | After promisc drops, checksum checks.             |
| NF\_IP\_LOCAL_IN      | 1     | If the packet is destined for this box.           |
| NF\_IP\_FORWARD       | 2     | If the packet is destined for another interface.  |
| NF\_IP\_LOCAL_OUT     | 3     | Packets coming from a local process.              |
| NF\_IP\_POST_ROUTING  | 4     | Packets coming from a local process.              |
| NF\_IP\_NUMHOOKS      | 5     |                                                   |

The packet filtering architecture of Linux 2.4 (netfilter): 
![center](https://github.com/09zwcbupt/personal/blob/master/kernel_module/packet_filter/netfilter.gif)

[1] https://github.com/jvns/kernel-module-fun  
[2] By Shawn the R0ck, http://kernelnewbies.org/Networking?action=AttachFile&do=get&target=hacking_the_wholism_of_linux_net.txt

