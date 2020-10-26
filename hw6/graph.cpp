// Add any standard library if needed.
#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
using namespace std;

typedef struct edge{
    int from;
    int to;
    unsigned char weight;
    edge(int from, int to, unsigned char weight):from(from), to(to), weight(weight){}
}Edge;

bool operator<(const Edge &a, const Edge &b){
    return a.weight>b.weight;
}

// Implement your minimum spinning tree algorithm
int MST(vector<vector<unsigned char> > &v){
    int _size=v.size();
    int num_visited=1;
    int sum=0;
    vector<bool> visited(_size,false);
    priority_queue<Edge> pq;
    for(int i=1; i<_size;i++){
        if(v[0][i]!=0) pq.push(Edge(0,i,v[0][i]));
    }
    visited[0]=true;
    while(num_visited!=_size){
        Edge edge=pq.top();
        pq.pop();
        int rank=edge.to;
        if(visited[rank]) continue;
        sum+=edge.weight;
        visited[rank]=true;
        num_visited++;
        if(num_visited==_size) break;
        for(int i=0;i<_size;i++) 
            if(!visited[i]&&v[rank][i]!=0) pq.push(Edge(rank,i,v[rank][i]));
    }
    return sum;
}





// Test your implementation
int main () {
    vector<int> v;
    int input;
    while(cin>>input){
        v.push_back(input);
    }
    int _size=sqrt(v.size());
    vector<vector<unsigned char> >graph(_size, vector<unsigned char>(_size));
    int i=0,j=0;
    for(auto item:v){
        graph[i][j]=static_cast<unsigned char>(item);
        if(j==_size-1) i++;
        j=(j+1)%_size;
    }
    cout<<MST(graph);
    return 0;
}