#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

#define binTofloat(x) (x)/4096.0
#define NUM_POP 1000
#define NUM_ITER 10000000

void crossover(unsigned short &x, unsigned short &y){
    unsigned short mask=rand();
    unsigned short a=(x&(~mask))|(y&mask);
    unsigned short b=(y&(~mask))|(x&mask);
    x=a;
    y=b;
}

void mutation(unsigned short *pop){
    int rank=rand()%NUM_POP;
    pop[rank]=(unsigned short)(rand());
}

float fitness(unsigned short x){
    float xx=binTofloat(x);
    return xx*sin(xx);
}


bool smaller(unsigned short a, unsigned short b){
    return fitness(a)<fitness(b);
}

int main(){
    unsigned short pop[NUM_POP];
    srand(time(NULL));
    for(int i=0;i<NUM_POP;i++) pop[i]=(unsigned short)rand();
    sort(pop,pop+NUM_POP,smaller);
    for(int i=0;i<NUM_ITER;i++){
        int a=rand()%NUM_POP;
        int b=rand()%NUM_POP;
        if(rand()%4){
            crossover(pop[a],pop[b]);
        }
        //crossover(pop[0],pop[1]);
        if(rand()%10==0) mutation(pop);
        //sort(pop, pop+NUM_POP, smaller);
    }
    sort(pop,pop+NUM_POP,smaller);
    //cout<<binTofloat(0xffff)<<endl;
    //cout<<binTofloat(pop[NUM_POP-1])<<endl;
    cout<<binTofloat(pop[0])<<endl;
    //cout<<fitness(pop[NUM_POP-1])<<endl;
    cout<<fitness(pop[0])<<endl;
    //cout<<fitness(0xb000)<<endl;
    cout<<11.0857*sin(11.0857)<<endl;
    return 0;
}