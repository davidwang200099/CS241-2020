#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;

// Implement your Jacobi Iteration algorithm.
// You can add any standard library if needed.
//

typedef enum{NOSOLUTION, NOTUNIQUE, UNIQUE} State;

double distance2(double *x1, double *x2, int n){
    double sum=0.0;
    for(int i=0;i<n;i++) sum+=(x1[i]-x2[i])*(x1[i]-x2[i]);
    return sum;
}

State iterable(double **A, int n){
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
                    if(A[k][n]!=0) return NOSOLUTION;
                }
                return NOTUNIQUE;

            }
            for (int k = i+1; k < n; k++) {
                double tmp = A[k][j] / A[i][j];
                for (int m = j; m <=n; m++) {A[k][m] -= tmp * A[i][m];}
            }
            j++;
        }
    }
    return UNIQUE;
}

double * Jacobi(double **A, int n){
    double *x=new double [n];
    double *x2=new double [n];
    for(int i=0;i<n;i++) x[i]=0;
    for(int k=0;k<1000000;k++){
        for(int i=0;i<n;i++){
            double sum=0.0;
            for(int j=0;j<n;j++){
                if(j==i) continue;
                sum+=A[i][j]*x[j];
            }
            x2[i]=(1/A[i][i])*(A[i][n]-sum);
        }
        //for(int i=0;i<n;i++) cout<<x2[i]<<" ";
        cout<<endl;
        double *tmp=x;
        x=x2;
        x2=tmp;
        if(distance2(x,x2,n)<1e-10) break;
    }
    delete [] x2;
    return x;
}


// Test your implementation.
int main() {
    // Input processing.
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
    State s=iterable(A, n);
    switch (s){
    case UNIQUE:{
            double *x=Jacobi(A, n);
            for(int i=0;i<n;i++) cout<<x[i]<<" ";
            delete [] x;
        }
        break;
    case NOSOLUTION:
        {cout<<"No solution!\n";}
        break;
    case NOTUNIQUE:
        {cout<<"No unique solution!\n";}
    default:
        break;
    }

    // Solve the linear system and print the results.
    /*try{
        double *x=Jacobi(A, n);
        for(int i=0;i<n;i++) cout<<x[i]<<" ";
        delete [] x; 
    }catch(int a){
        if(a==0) cout<<"No unique solution!\n";
        else cout<<"No solution!\n";
        for(int i=0;i<n;i++) delete [] A[i];
        delete [] A;
        return 0;
    }*/
    /*x=Jacobi(A, n);
    for(int i=0;i<n;i++) cout<<x[i]<<" ";
    delete [] x;
    for(int i=0;i<n;i++) delete [] A[i];
    delete [] A;*/
    for(int i=0;i<n;i++) delete [] A[i];
    delete [] A;
    return 0;
}
