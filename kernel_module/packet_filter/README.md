#Simple Kernel Module For Packet Filtering

##IP Hooks in netfilter

The packet filtering architecture of Linux 2.4 (netfilter):  
![center](https://raw.github.com/09zwcbupt/personal/master/kernel_module/packet_filter/netfilter.gif)


In `linux/netfilter_ipv4.h`, IP hooks' definition are listed as follow:  

| Hooks                 | Num   | Discription                                      |
| --------------------- |:-----:| ------------------------------------------------ |
| NF\_IP\_PRE_ROUTING   | 0     | After promisc drops, checksum checks             |
| NF\_IP\_LOCAL_IN      | 1     | If the packet is destined for this box           |
| NF\_IP\_FORWARD       | 2     | If the packet is destined for another interface  |
| NF\_IP\_LOCAL_OUT     | 3     | Packets coming from a local process              |
| NF\_IP\_POST_ROUTING  | 4     | Packets about to hit the wire                    |
| NF\_IP\_NUMHOOKS      | 5     |                                                  |

##Reference
[1] https://github.com/jvns/kernel-module-fun  
[2] By Shawn the R0ck, http://kernelnewbies.org/Networking?action=AttachFile&do=get&target=hacking_the_wholism_of_linux_net.txt  
[3] Netfilter Architecture of Linux 2.4, http://www.6test.edu.cn/~lujx/linux_networking/index.html?page=0131777203_ch19lev1sec3.html
