#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

void solve(double **A, int n){
    int j=0;
    for (int i = 0; i < n; i++) {
        if(A[i][j]!=0){
            for (int k = i+1; k < n; k++) {
                double tmp = A[k][j] / A[i][j];
                for (int m = j; m <=n; m++) {A[k][m] -= tmp * A[i][m];}
            }
            j++;
        }else{
            while(j<n&&A[i][j]==0){
                bool flag=false;
                for(int k=i+1;k<n;k++){
                    if(A[k][j]!=0){
                        double *tmp=A[k];
                        A[k]=A[i];
                        A[i]=tmp;
                        flag=true;
                        break;
                    }
                }
                if(!flag) j++;
            }
            if(j>=n) {
                for(int k=i;k<n;k++){
                    if(A[k][n]!=0) throw -1;
                }
                throw 0;

            }
            for (int k = i+1; k < n; k++) {
                double tmp = A[k][j] / A[i][j];
                for (int m = j; m <=n; m++) {A[k][m] -= tmp * A[i][m];}
            }
            j++;
        }
    }
    
}

double *getsolution(double **A, int n){
    double *x=new double[n];
    x[n-1]=A[n-1][n]/A[n-1][n-1];
    for(int i=n-2;i>=0;i--) {
        double tmp=0;
        for(int j=i+1;j<n;j++) tmp+=A[i][j]*x[j];
        x[i]=(A[i][n]-tmp)/A[i][i];
    }
    return x;
}

void print(double **A, int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n+1;j++) cout<<A[i][j]<<"\t";
        cout<<endl;
    }
        
}

int main(){
    string str;
    int n=0;
    double **A;
    double input;
    cout.setf(ios::fixed);
    cout<<fixed<<setprecision(3);
    vector<double> coefficient;
    getline(cin,str);
    stringstream ss(str);
    while(ss>>input)
        coefficient.push_back(input);
    A=new double *[n=(coefficient.size()-1)];
    for(int i=0;i<n;i++) A[i]=new double[n+1];
    for(int i=0;i<n+1;i++) A[0][i]=coefficient[i];
    coefficient.clear();
    for(int i=1;i<n;i++){
        ss.clear();
        getline(cin,str);
        ss.str(str);
        while(ss>>input) coefficient.push_back(input);
        for(int j=0;j<n+1;j++) A[i][j]=double(coefficient[j]);
        coefficient.clear();
    }
    try{
        solve(A,n);
        //print(A,n);
    }catch(int a){
        if(a==0) cout<<"No unique solution!\n";
        else cout<<"No solution!\n";
        return 0;
    }
    double *x=getsolution(A,n);
    for(int i=0;i<n;i++) cout<<x[i]<<" ";
    delete [] x;
    for(int i=0;i<n;i++) delete [] A[i];
    delete [] A; 
    return 0;
}