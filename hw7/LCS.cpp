#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

typedef enum{LEFTUP, UP, LEFT, TIE} Direction;

vector<vector<int> > buildLCS(const string &X, const string &Y, vector<vector<int> > &LCS,vector<vector<Direction> > &dirLCS){
    int m=X.length();
    int n=Y.length();
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if(X[i-1]==Y[j-1]) {
                LCS[i][j]=LCS[i-1][j-1]+1;
                dirLCS[i-1][j-1]=LEFTUP;
            }else{
                if(LCS[i-1][j]>LCS[i][j-1]){
                    LCS[i][j]=LCS[i-1][j];
                    dirLCS[i-1][j-1]=UP;
                }else{
                    LCS[i][j]=LCS[i][j-1];
                    dirLCS[i-1][j-1]=(LCS[i-1][j]==LCS[i][j-1])?TIE:LEFT;
                }
            }
        }
    }
    return LCS;
}

void printLCS(set<string> &s, const vector<vector<int> > &LCS, vector<vector<Direction> > &dirLCS, const string &X, const string &Y, int i, int j, string suffix){
    if(i<0 || j<0) {reverse(suffix.begin(),suffix.end());s.insert(suffix);return;}
    switch(dirLCS[i][j]){
        case LEFTUP:
            printLCS(s, LCS, dirLCS, X, Y, i-1, j-1, suffix+X[i]);
            break;
        case UP:
            printLCS(s, LCS, dirLCS, X, Y, i-1, j, suffix);
            break;
        case LEFT:
            printLCS(s, LCS, dirLCS, X, Y, i, j-1, suffix);
            break;
        case TIE:
            printLCS(s, LCS, dirLCS, X, Y, i, j-1, suffix);
            printLCS(s, LCS, dirLCS, X, Y, i-1, j, suffix);
    }
}

void printAllLCS(set<string> &s, vector<vector<int> > &LCS, vector<vector<Direction> > &dirLCS,const string &X, const string &Y, int m, int n){
    string str="";
    printLCS(s, LCS, dirLCS, X, Y, m-1, n-1, str);
}

set<string> LCS(const string &X, const string &Y){
    vector<vector<int> > LCS(X.length()+1, vector<int>(Y.length()+1,0));
    vector<vector<Direction> > dirLCS(X.length(),vector<Direction>(Y.length()));
    buildLCS(X, Y, LCS, dirLCS);
    set<string> s;
    printAllLCS(s,LCS,dirLCS,X,Y,X.length(),Y.length());
    return s;
}

int main()
{
    string X, Y;
    cin >> X;
    cin >> Y;

    set<string> lcs = LCS(X, Y);

    // print set elements
    for (string str : lcs)
        cout << str << endl;
    return 0;
}

