#include<iostream>
using namespace std;

class Solution {
public:
    int singleNumber(int A[], int n) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        int a[33]={0,0};
        int i = 0;
        int bit_num = 0;
        int result = 0;
        long one = 1;
        for(i=0;i<n;i++){
            for(bit_num=0;bit_num<32;bit_num++){
                if ((abs(A[i])&(one<<bit_num))>0){
                    a[bit_num]++;
                }
            }
            if (A[i] < 0){
                a[32]++;//for sign
            }
        }
        int j = 0;
        for(j=0;j<32;j++){
                result |= (a[j]%3)<<j;
        }
        if (a[32]%3 == 0){return result;}
        else{return result*-1;}
    }
};

int main(){
	int test[]= {-401451,-177656,-2147483646,-473874,-814645,-2147483646,-852036,-457533,-401451,-473874,-401451,-216555,-917279,-457533,-852036,-457533,-177656,-2147483646,-177656,-917279,-473874,-852036,-917279,-216555,-814645,2147483645,-2147483648,2147483645,-814645,2147483645,-216555};
	Solution test2;
	int i = test2.singleNumber(test, 31);
	cout<<i<<"\n";
	return 0;
}
