#include <stdio.h>

int main(){
	int n = 11;
	int A[11] = {1,2,3,4,5,6,5,4,3,2,1};
	int x = 0;
	int i = 0;
        // Note: The Solution object is instantiated only once and is reused by each test case.
        for (i=0; i<n; i++){
            x = x ^ A[i];
        }
	printf("%d\n",x);
        return x;
}
