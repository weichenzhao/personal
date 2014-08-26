#include <stdio.h>
#include <pcap/pcap.h>

int main(int argc, char *argv[]){
	char errbuf[PCAP_ERRBUF_SIZE], somedev[]="eth1";//device to sniff
	pcap_t *handle;//session handle
	const u_char *packet;
	struct pcap_pkthdr header;

	handle = pcap_open_live(somedev, BUFSIZ, 1, 1000, errbuf);//open a device

	if(handle == NULL){//if open fail
		fprintf(stderr, "fail to find the default device: %s\n", errbuf);
		return 2;
	}
	if (pcap_datalink(handle) != DLT_EN10MB) {//if dev does not support link-layer header
		fprintf(stderr, "Device %s doesn't provide Ethernet headers - not supported\n", somedev);
		return 2;
	}
	printf("Device: %s\n", somedev);
	int i;
	for (i=0;i<10;i++){
		packet = pcap_next(handle, &header);
		printf("Jacked a packet with length of [%d]\n", header.len);
	}
	pcap_close(handle);
	return 0;
}
