#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

class Solution {
public:
    void quicksort(vector<int> &v, int lo, int hi){
        int i=lo; int j=hi;
        int middle=v[(lo+hi)>>1];
        do{
            while(i<hi && v[i]>middle) i++;
            while(j>lo && v[j]<middle) j--;
            if(i<=j) {int tmp=v[i];v[i]=v[j];v[j]=tmp;i++;j--;}
        }while(i<=j);
        if(lo<j) quicksort(v,lo,j);
        if(hi>i) quicksort(v,i,hi);
    }
    float hMedian(vector<int>& citations) {
        int _size=citations.size();
        quicksort(citations,0,_size-1);
        if(citations[0]==0) return 0;
        int h;
        for(int i=0;i<_size;i++) {
            if(citations[i]>i) {h=i+1;}
            else break;
        }
        //cout<<h<<endl;
        if(h&1){
            return citations[h>>1];
        }else{
            return (citations[h>>1]+citations[(h>>1)-1])/2.0;
        }
    }
    bool test(vector<int> &citations){
        int _size=citations.size();
        quicksort(citations,0,_size-1);
        int h;
        for(int i=0;i<_size;i++) {
            if(citations[i]>i) {h=i+1;}
            else break;
        }
        //for(int i=0;i<h;i++) if(citations[i]<h) return false;
        //for(int i=h;i<_size;i++) if(citations[i]>=h) return false;
        if(citations[h-1]<h) {cout<<"h index is "<<h<<": ";return false;}
        if(h<citations.size()&&citations[h]>h) {cout<<"h index is "<<h<<": ";return false;}
        return true;
    }
};

int main(int argc, char** argv) {
    std::string line;
    int number;
    std::vector<int> numbers;

    std::getline(std::cin, line);
    std::istringstream stream(line);
    while (stream >> number)
        numbers.push_back(number);
    Solution s;
    float res=s.hMedian(numbers);
    cout<<fixed;
    cout <<setprecision(1) << res << endl;
    return 0;
}
