#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

// Implement your Gaussian Elimination algorithm.
// You can add any standard library if needed.
//

vector<double> solve(vector<vector<double> > &A) {
    int n = A[0].size()-1;
    vector<double> x0(n);
    for (int k = 1; k < n; k++) {
        if(A[k-1][k-1]==0){
            bool flag=false;
            for(int j=k;j<n;j++){
                if(A[j][k-1]!=0) {
                    for(int i=0;i<=n;i++) {double tmp=A[j][i];A[j][i]=A[k-1][i];A[k-1][i]=tmp;}
                    flag=true;
                    break;
                }
            }
            if(!flag) throw 0;
        }
        for (int i = k; i < n; i++) {
            double tmp = A[i][k-1] / A[k-1][k-1];
            for (int j = k-1; j <=n; j++) {A[i][j] -= tmp * A[k-1][j];printf("A[%d][%d]=%lf ",i,j,A[i][j]);}
            printf("\n");
        }
    }
    vector<double> x(n);
    if(A[n-1][n-1]==0){
        if(A[n-1][n]==0) throw 0;
        else throw -1;
    }
    x[n-1]=A[n-1][n]/A[n-1][n-1];
    for(int i=n-2;i>=0;i--) {
        double tmp=0;
        for(int j=i+1;j<n;j++) tmp+=A[i][j]*x[j];
        x[i]=(A[i][n]-tmp)/A[i][i];
    }
    return x;
}

// Test your implementation.
int main() {
    // Input processing.
    string str;
    int a;
    int i=0;
    vector<vector<double> > A;
    while(getline(cin,str)){
        A.push_back(vector<double>());
        stringstream ss(str);
        while(ss>>a) A[i].push_back(double(a));
        i++;
    }
    // Solve the linear system and print the results.
    try{
        vector<double> x=solve(A);
        int _size=x.size();
        for(int i=0;i<_size;i++) cout<<x[i]<<" ";
    }
    catch(int a){
        if(a==0) cout<<"Not unique!\n";
        else cout<<"No solution!\n";
    }
    return 0;
}
