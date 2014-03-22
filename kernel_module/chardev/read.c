#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(){
	char buff[1600]="testestestestestestestestestestest";
	unsigned int fd, ret = 0;
	fd=open("/dev/filter", O_RDONLY);
	ret=read(fd,buff,1590);
	if(ret){
		buff[ret]='\0';
		printf("buff: %d ;length: %d bytes\n",buff[12], ret);
		int i;
		for(i=0;i<20;i++){
		printf(" %x",buff[i]);}
		printf("\n");
	}
	close(fd);
}
