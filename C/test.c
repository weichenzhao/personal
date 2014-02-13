#include<stdio.h>

struct a{
	int i;
};

int main(){
	int x = 1, y = 2;
	if (x == 1 || y == 2){
		printf("x = 1, y = 2\n");
	}
	printf("Testing:\n");
	int i = 0;
	for(i; i<10; i++){
		printf("%d\n",i);
	}
	struct a abc;
	abc.i = 0;
	printf("%d\n", abc.i);
	abc.i = 1;
	int j = -13;
	printf("%d,%d\n",abc.i,abs(j));
	return 0;
}
