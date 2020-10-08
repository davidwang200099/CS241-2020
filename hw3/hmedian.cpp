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
        int h;
        for(int i=0;i<_size;i++) {
            if(i>citations[i]) {h=i;break;}
        }
        cout<<h<<endl;
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
            if(i>citations[i]) {h=i;break;}
        }
        //for(int i=0;i<h;i++) if(citations[i]<h) return false;
        //for(int i=h;i<_size;i++) if(citations[i]>=h) return false;
        if(citations[h-1]<h) return false;
        if(citations[h]>=h) return false;
        return true;
    }
};

int main(int argc, char** argv) {
    /*std::string line;
    int number;
    std::vector<int> numbers;
	
    std::getline(std::cin, line);
    std::istringstream stream(line);
    while (stream >> number)
        numbers.push_back(number);
	*/
    srand(time(NULL));
    vector<int> numbers;
    for(int i=0;i<500;i++){
    int _size=rand()%20;
    for(int i=0;i<_size;i++) numbers.push_back(rand());
	Solution s;
    if(!s.test(numbers)){
        for(int i=0;i<numbers.size();i++) cout<<numbers[i]<<" ";
        cout<<endl;
    }
    numbers.clear();
	//float res= s.hMedian(numbers);
    //for(int i=0;i<numbers.size();i++) cout<<numbers[i]<<" ";
	//std::cout << std::fixed;
	//std::cout << std::setprecision(1) << res << endl;
	//s.quicksort(numbers,0,numbers.size()-1);
    if(i%20==19) cout<<i<<" times finished.\n";
    }
	return 0;
}
