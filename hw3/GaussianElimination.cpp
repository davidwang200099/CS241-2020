#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
//#define DEBUG
using namespace std;

class Error {
public:
    string str;

    Error(string str) :str(str) {}
    void error() {
        cout << str;
        exit(0);
    }
};

class Matrix {
public:
    double** a;
    int N;

    void init() {
        a = new double* [N];
        for (int i = 0; i < N; ++i) {
            a[i] = new double[N + 1];
        }
    }

    ~Matrix() {
        for (int i = 0; i < N; ++i) {
            delete[] a[i];
        }
        delete[] a;
    }
};

void output(Matrix& matrix) {
    for (int i = 0; i < matrix.N; ++i) {
        for (int j = 0; j < matrix.N + 1; ++j) {
            cout << matrix.a[i][j] << '\t';
        }
        cout << endl;
    }
    cout << endl;
}

void input(Matrix& matrix) {
    double temp;
    vector<double> a;

    string str;
    getline(cin, str);
    stringstream line(str);

    while (line >> temp) {
        a.push_back(temp);
    }

    matrix.N = a.size() - 1;
    matrix.init();
    for (int j = 0; j <= matrix.N; ++j) {
        matrix.a[0][j] = a[j];
    }

    for (int i = 1; i < matrix.N; ++i) {
        a.clear();
        getline(cin, str);
        line.clear();
        line.str(str);
        while (line >> temp) {
            a.push_back(temp);
        }
        for (int j = 0; j <= matrix.N; ++j) {
            matrix.a[i][j] = a[j];
        }
    }
}

void subtract(Matrix& matrix, int i, int& j) {
    int N = matrix.N;
    for (int k = i + 1; k < N; ++k) {
        double q = matrix.a[k][j] / matrix.a[i][j];
        for (int c = j; c <= N; ++c) {
            matrix.a[k][c] -= q * matrix.a[i][c];
        }
    }
    ++j;
}

void reduce(Matrix& matrix) {
    // i is row, j is column
    int j = 0;
    for (int i = 0; i < matrix.N; ++i) {
        if (matrix.a[i][j] != 0) {
            subtract(matrix, i, j);
        }
        else {
            while (j < matrix.N && !matrix.a[i][j]) {
                bool flag = false;
                for (int k = i + 1; k < matrix.N; ++k) {
                    if (matrix.a[k][j]) {
                        double* temp = matrix.a[k];
                        matrix.a[k] = matrix.a[i];
                        matrix.a[i] = temp;
                        flag = true;
                        break;
                    }
                }
                if (!flag) {
                    ++j;
                }
            }

            if (j >= matrix.N) {
                for (int k = i; k < matrix.N; ++k) {
                    if (matrix.a[k][matrix.N] != 0)
                        throw Error("No solution!");
                }
                throw Error("No unique solution!");
            }

            subtract(matrix, i, j);
        }
    }
}

void ans(Matrix& matrix) {
    int N = matrix.N;
    vector<double> ans(N);
    ans[N - 1] = matrix.a[N - 1][N] / matrix.a[N - 1][N - 1];
    for (int i = N - 2; i >= 0; --i) {
        double sum = 0;
        for (int j = i + 1; j < N; ++j) {
            sum += matrix.a[i][j] * ans[j];
        }
        ans[i] = (matrix.a[i][N] - sum) / matrix.a[i][i];
    }
    for (auto i = ans.begin(); i != ans.end(); i++) {
        cout << *i << ' ';
    }
}



int main() {
    cout.setf(ios::fixed);
    cout << fixed << setprecision(3);
    // Input processing.

    Matrix matrix;

    input(matrix);

#ifdef DEBUG
    output(matrix);
#endif // DEBUG

    // Solve the linear system and print the results.
    try {
        reduce(matrix);
    }
    catch (Error error) {
        error.error();
    }


    output(matrix);


    ans(matrix);
    return 0;
}
