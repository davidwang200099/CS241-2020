#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;


// You can add additional standard libraries if necessary.
// Implement the Newton interpolation!

class Newton {
public:
    Newton(vector<double> x, vector<double> y): X(x), Y(y) {}
    double regression(double interp_x);


private:
    vector<double> X, Y;
};

double Newton::regression(double interp_x){
    double h=X[1]-X[0];
    double t=(interp_x-X[0])/h;
    int n=X.size()-1;
    double sum=Y[0];
    double S=1.0;
    vector<int> factorial;
    vector< vector<double> > delta(n+1,vector<double>(n+1,0.0));
    factorial.push_back(1);
    for(int i=1;i<=n;i++) {
        int tmp=factorial[i-1]*i;
        factorial.push_back(tmp);
    }
    for(int i=0;i<=n;i++) delta[0][i]=Y[i];
    for(int i=1;i<=n;i++){//difference
        for(int j=0;j<=n-i;j++)//indice
            delta[i][j]=delta[i-1][j+1]-delta[i-1][j];
    }
    
    for(int k=1;k<=n;k++){
        for(int i=0;i<=k-1;i++){
            S*=t-i;
        }
        //cout<<S<<" ";
        S*=delta[k][0]/factorial[k];
        //cout<<S<<endl;
        sum+=S;
        S=1.0;
    }
    return sum;
}

// Test your implementation.
int main(int argc, const char * argv[]) {
    //  Input preprocessing.
    string str;
    getline(cin, str);
    stringstream xstr(str);
    getline(cin, str);
    stringstream ystr(str);
    
    // X and Y are two vectors of equal length to be traversed.
    vector<double> X, Y;
    double a;
    while (xstr >> a)
        X.push_back(a);
    while (ystr >> a)
        Y.push_back(a);
    
    // interp_x is the point to be interpolated.
    double interp_x;
    cin >> interp_x;

    // Do Newton interpolation for interp_x using X and Y, and print your results
    // Note: The result retains three decimal places (rounded)!
    Newton newton(X,Y);
    double interp_y=newton.regression(interp_x);
    cout.setf(ios::fixed);
    cout<<fixed<<setprecision(3)<<interp_y<<endl;
    // End
    return 0;
}
