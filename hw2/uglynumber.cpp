#include <iostream>
#include <vector>
using namespace std;

int ugly[1700]={0};

#define MIN(x,y,z) ((x)<(y)&&(x)<(z))?(x):((y)<(z)?(y):(z))

class Solution {
public:
    int nthUglyNumber(int n) {
        int a=1,b=1,c=1;
        int u1,u2,u3,u;
        int i=1;
        ugly[1]=1;
        while(i<n){
            u1=ugly[a]*2;
            u2=ugly[b]*3;
            u3=ugly[c]*5;
            u=MIN(u1,u2,u3);
            ugly[++i]=u;
            if(u==u1) a++;
            if(u==u2) b++;
            if(u==u3) c++;
        }
        return ugly[n];
        /*while(index<n){
            if(isUglyNumber(i)){
                if(index==n-1) return i;
                else index++;
            }
            i++;  
        }*/

    }
    /*int isUglyNumber(int n){
        while(n%2==0) n>>=1;
        while(n%3==0) n/=3;
        while(n%5==0) n/=5;
        return n==1;
    }*/
};

int main(){
	Solution s;
	int n;
	cin >> n;
	cout << s.nthUglyNumber(n) << endl;
	return 0;
}