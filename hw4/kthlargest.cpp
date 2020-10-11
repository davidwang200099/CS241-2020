#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

// Implement your selection algorithm. You can add any standard library if needed.
//
int kthlargest(vector<int> &v, int lo, int hi, int k){
    int pivot=v[hi];
    int i=lo-1;
    int j=lo;
    for(;j<hi;j++){
        if(v[j]<=pivot) {int tmp=v[j];v[j]=v[i+1];v[i+1]=tmp;i++;}
    }
    {int tmp=v[i+1];v[i+1]=v[hi];v[hi]=tmp;}
    if(i+1==k) return v[k];
    else{
        return (i+1<k)?kthlargest(v,i+2,hi,k):kthlargest(v,lo,i,k);
    }
}




int main() {
    // Input processing.
    vector<int> v;
    string str;
    getline(cin,str);
    stringstream ss(str);
    int input;
    while(ss>>input) v.push_back(input);
    int k;
    cin>>k;
    cout<<kthlargest(v,0,v.size()-1,v.size()-k);
    return 0;
}
