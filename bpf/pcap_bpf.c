#include <pcap.h>
#include <pcap/bpf.h>
#include <stdio.h>

int main(){
    int ret = 0;
    int snaplen = 65535;
    char dev[] = "eth1";
    char errbuf[PCAP_ERRBUF_SIZE];
    const u_char *packet;
    struct pcap_pkthdr header;	/* The header that pcap gives us */
    pcap_t *handle;
    bpf_u_int32 mask;		/* The netmask of our sniffing device */
    bpf_u_int32 net;		/* The IP of our sniffing device */
    if (pcap_lookupnet(dev, &net, &mask, errbuf) == -1) {
        fprintf(stderr, "Can't get netmask for device %s\n", dev);
        net = 0;
        mask = 0;
    }
    handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Couldn't open device %s: %s\n", dev, errbuf);
        ret = 2;
        goto fail;
    }
    struct bpf_program prog;
    //char *rule = "ether[0:2] == 0x0180";
    //char *rule = "ip[1:1] != 0";
    //char *rule = "ip6[0:2] & 0x0ff0 != 0";
    char *rule = "ether[0:2] == 0x0180 or ip[1:1] != 0 or ip6[0:2] & 0x0ff0 != 0";
    if(pcap_compile( handle, &prog, rule, 0, net )<0){
        printf("Fail to generate rule\n");
        ret = 1;
        goto exit;
    }
    printf("rule: %s\n", rule);
    printf("len: %d\n", prog.bf_len);
    printf("struct sock_filter code2[] = { \n");
    int i=0;
    for(i; i<prog.bf_len; i++){
        printf("    { 0x%02d, %2d, %2d, 0x%08x },\n", 
                prog.bf_insns[i].code, 
                prog.bf_insns[i].jt,
                prog.bf_insns[i].jf,
                prog.bf_insns[i].k);
    }
    printf("};\n");

    if (pcap_setfilter(handle, &prog) == -1) {
        fprintf(stderr, "Couldn't install filter %s: %s\n", rule, pcap_geterr(handle));
        ret = 3;
        goto exit;
    }

    while (1){
        packet = pcap_next(handle, &header);
        if(!packet)
            continue;
        printf("read %d bytes\n", header.len);
        int i=0;
	for(i;i<header.len;i++){
	    printf("%02hx ", packet[i]);
            if((i+1)%16 == 0){
                printf(" ");
                if((i+1)%32 == 0)
                    printf("\n");
            }
	}        
        printf("\n\n");
    }

exit:
    pcap_freecode(&prog); 
    pcap_close(handle);
fail:
    return ret;
}
