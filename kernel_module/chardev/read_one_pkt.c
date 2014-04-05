#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

void read_pkt(char* pkt_pointer){
	//char buff[1600];
	memset(pkt_pointer, 0, sizeof(pkt_pointer));
	unsigned int fd, ret = 0;
	fd=open("/dev/filter", O_RDONLY);
	ret=read(fd,pkt_pointer+1,1590);
    pkt_pointer[0]=ret;//copy the number of bytes into the head
	//if(ret){
		//pkt_pointer[ret]='\0';
		//printf("buff: %d ;length: %d bytes\npkt: %s",pkt_pointer[12], ret, pkt_pointer);
		//printf("pkt: %s\nrtn: %s", buff, buff_rt);
		//memcpy(buff_rt, buff, ret+1);
		//int i;
		//for(i=0;i<ret;i++)
		//	printf(" %x",pkt_pointer[i]);
		//printf("\n");
	//}
	close(fd);
	return;
}

char* init(){
	char *pkt_pointer = malloc(1600);
	return pkt_pointer;
}


void freeme(char *pointer){
	if(pointer != NULL)
		free(pointer);
	else
		printf("null pointer dectected!\n");
	return; 
}

/*int main(){
	read_pkt();
	return 0;
}*/
