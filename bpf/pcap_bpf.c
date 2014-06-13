#include <pcap.h>
#include <pcap/bpf.h>
#include <stdio.h>

#define DLT_EN10MB 1

int main(){
    int snaplen = 65535;
    pcap_t *pcap = pcap_open_dead( DLT_EN10MB, snaplen );
    struct bpf_program prog;
    int netmask = 0;
    char *rule = "ether[0] & 1 != 0";
    if(pcap_compile( pcap, &prog, rule, 0, netmask )<0){
        printf("Fail to generate rule\n");
        return -1;
    }
    printf("len: %d\n", prog.bf_len);
    int i=0;
    for(i; i<prog.bf_len; i++){
        printf("instruction: %2d %d %d 0x%04x\n", 
                prog.bf_insns[i].code, 
                prog.bf_insns[i].jt,
                prog.bf_insns[i].jf,
                prog.bf_insns[i].k);
    }
    return 0;
}
