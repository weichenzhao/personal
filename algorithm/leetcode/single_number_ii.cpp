#include<stdio.h>
#include<stdlib.h>

int singleNumber(int A[], int n);

int main(){
    printf("test case 11\n");
    int a[] = {-401451,-177656,-2147483646,-473874,-814645,-2147483646,-852036,-457533,-401451,-473874,-401451,-216555,-917279,-457533,-852036,-457533,-177656,-2147483646,-177656,-917279,-473874,-852036,-917279,-216555,-814645,2147483645,-2147483648,2147483645,-814645,2147483645,-216555};
    int num = singleNumber(a, sizeof(a)/sizeof(a[0]));
    if(num == -2147483648){printf("Passed\n");}
    else{printf("error\n");return 0;}
    char result[32] = "q";

    printf("test case 7\n");
    int b[] = {-2,-2,1,1,-3,1,-3,-3,-4,-2};
    num = singleNumber(b, sizeof(b)/sizeof(b[0]));
    if(num == -4){printf("Passed\n");}
    else{printf("error\n");return 0;}
}

int singleNumber(int A[], int n) {
    // Note: The Solution object is instantiated only once and is reused by each test case.
    int ones = 0, twos = 0, xthrees = 0;
    for(int i = 0; i < n; ++i) {
        twos |= (ones & A[i]);
        ones ^= A[i];
        xthrees = ~(ones & twos);
        ones &= xthrees;
        twos &= xthrees;
    }
    return ones;
}

