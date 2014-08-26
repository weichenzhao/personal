#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <linux/if_ether.h>
#include <linux/filter.h>
#include <string.h>
#include <stdio.h>
/* ... */

/* From the example above: tcpdump -i em1 port 22 -dd */
struct sock_filter code[] = {
	{ 0x28,  0,  0, 0x0000000c },
	{ 0x15,  0,  8, 0x000086dd },
	{ 0x30,  0,  0, 0x00000014 },
	{ 0x15,  2,  0, 0x00000084 },
	{ 0x15,  1,  0, 0x00000006 },
	{ 0x15,  0, 17, 0x00000011 },
	{ 0x28,  0,  0, 0x00000036 },
	{ 0x15, 14,  0, 0x00000016 },
	{ 0x28,  0,  0, 0x00000038 },
	{ 0x15, 12, 13, 0x00000016 },
	{ 0x15,  0, 12, 0x00000800 },
	{ 0x30,  0,  0, 0x00000017 },
	{ 0x15,  2,  0, 0x00000084 },
	{ 0x15,  1,  0, 0x00000006 },
	{ 0x15,  0,  8, 0x00000011 },
	{ 0x28,  0,  0, 0x00000014 },
	{ 0x45,  6,  0, 0x00001fff },
	{ 0xb1,  0,  0, 0x0000000e },
	{ 0x48,  0,  0, 0x0000000e },
	{ 0x15,  2,  0, 0x00000016 },
	{ 0x48,  0,  0, 0x00000010 },
	{ 0x15,  0,  1, 0x00000016 },
	{ 0x06,  0,  0, 0x0000ffff },
	{ 0x06,  0,  0, 0x00000000 },
};

struct sock_fprog bpf;

int main(){
    bpf.len = sizeof(code)/sizeof(code[0]); //ARRAY_SIZE(code);
    bpf.filter = code;

    int sock, ret;
    sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sock < 0){
        printf("Error creating socket\n");
        return 1;
    }
	/* ... bail out ... */

    ret = setsockopt(sock, SOL_SOCKET, SO_ATTACH_FILTER, &bpf, sizeof(bpf));
    if (ret < 0){
        printf("Error attaching BPF\n");
        return 1;
        /* ... bail out ... */
    }
    
    ret = 0;
    unsigned short buffer[1500];
    memset(buffer, 0xff, 1500);
    while (1){
        ret = read(sock,buffer,1500);
        printf("read %d bytes\n", ret);
        int i=0;
	for(i;i<ret/2;i++){
	    printf("%04hx ", buffer[i]);
            if((i+1)%16 == 0)
                printf("\n");
	}        
        printf("\n\n");
    }
    /* ... */
    close(sock);
    return 0;
}
