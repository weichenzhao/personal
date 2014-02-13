#include <stdio.h>
int main(int argc, char* argv[]) {
	int x =10;
	printf("%d,%s\n",argc, argv[1]);
        int j = 0;
        int neg = 0;
        if (x < 0){
            x = x * -1;
            neg = 1;
        }
        
        while(x > 0){
            j = j*10 + x%10;
            x = x/10;
	    //printf("%d\n",x);
        }

        if(neg==1){
	    printf("%d\n",j*-1);
            return j*-1;
        }
        else{
	    printf("%d\n",j);
            return j;
        }
    }
