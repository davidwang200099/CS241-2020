#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;


// You can add additional standard libraries if necessary.
// Implement the Lagrange interpolation!
class Lagrange {
public:
    Lagrange(vector<double> x, vector<double> y): X(x), Y(y) {}
    double regression(double interp_x);
    
    

private:
    vector<double> X, Y;
};

double Lagrange::regression(double interp_x){
    double sum=0.0;
    double S;
    int n=X.size();
    for(int k=0;k<n;k++){
        S=Y[k];
        for(int j=0;j<n;j++)
            if(j!=k) S=S*(interp_x-X[j])/(X[k]-X[j]);
        sum+=S;
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

    Lagrange lang(X,Y);
    double interp_y=lang.regression(interp_x);

    // Do Lagrange interpolation for interp_x using X and Y, and print your results
    // Note: The result retains three decimal places (rounded)!
    cout.setf(ios::fixed);
    cout<<fixed<<setprecision(3)<<interp_y<<endl;
    
    
    // End
    return 0;
}
