#include <stdlib.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>

void print_hex_ascii_line(const u_char *payload, int len, int offset){
	int i;
	int gap;
	const u_char *ch;
	/* offset */
	printf("%05d   ", offset);
	/* hex */
	ch = payload;
	for(i = 0; i < len; i++) {
		printf("%02x ", *ch);
		ch++;
		/* print extra space after 8th byte for visual aid */
		if (i == 7)
			printf(" ");
	}
	/* print space to handle line less than 8 bytes */
	if (len < 8)
		printf(" ");
	/* fill hex gap with spaces if not full line */
	if (len < 16) {
		gap = 16 - len;
		for (i = 0; i < gap; i++) {
			printf("   ");
		}
	}
	printf("   ");
	/* ascii (if printable) */
	ch = payload;
	for(i = 0; i < len; i++) {
		if (isprint(*ch))
			printf("%c", *ch);
		else
			printf(".");
		ch++;
	}
	printf("\n");
return;
}

int main(){
   int handle = 0;
   handle = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

   struct ifreq ifr;
   memset(&ifr, 0, sizeof(ifr));
   //strncpy(ifr.ifr_name, "vxlan", sizeof(ifr.ifr_name));
   //if( ioctl(handle, SIOCGIFINDEX, &ifr) == -1 ){
   //   printf("no such device\n");
   //   return 0;
   //}


   // according to the kernel, if the type field ( after smac and dmac )
   // is smaler than 500, the kernel will consider it as the length of the
   // packet, and check if it is true. Therefore, if you are listening for
   // this particular protocol family, then you will have trouble.
   struct sockaddr_ll   sll;
   memset(&sll, 0, sizeof(sll));
   sll.sll_family       = AF_PACKET;
   //sll.sll_ifindex      = ifr.ifr_ifindex;
   sll.sll_protocol     = htons(ETH_P_ALL);//htons(0x3333)
   if ( bind( handle, (struct sockaddr *) &sll, sizeof(sll)) == -1 ){
      printf("fail binding\n");
      return 0;
   }
   printf("binding %x\n", sll.sll_protocol);

   //send(handle, "100", 3, 0);
   u_char buffer[1024];
   int ret = 0;
   while(1){
      memset(&buffer, 0, sizeof(buffer));
      ret = recv(handle, buffer, sizeof(buffer), 0);
      if(ret > 0)
         print_hex_ascii_line(buffer, ret, 0);
      //printf("%s \n", buffer);
   }

   return 0;
}
