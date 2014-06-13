#include <pcap.h>
#include <pcap/bpf.h>
#include <stdio.h>

#define DLT_EN10MB 1

int main(){
    int ret = 0;
    int snaplen = 65535;
    pcap_t *pcap = pcap_open_dead( DLT_EN10MB, snaplen );
    struct bpf_program prog;
    int netmask = 0;
    char *rule = "ether[0:2] != 0x0180";
    if(pcap_compile( pcap, &prog, rule, 0, netmask )<0){
        printf("Fail to generate rule\n");
        ret = -1;
        goto exit;
    }
    printf("len: %d\n", prog.bf_len);
    int i=0;
    printf("struct sock_filter code2[] = { \n");
    for(i; i<prog.bf_len; i++){
        printf("    { 0x%02d, %2d, %2d, 0x%08x },\n", 
                prog.bf_insns[i].code, 
                prog.bf_insns[i].jt,
                prog.bf_insns[i].jf,
                prog.bf_insns[i].k);
    }
    printf("};\n");
exit:
    pcap_freecode(&prog); 
    pcap_close(pcap);
    return ret;
}
