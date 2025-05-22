#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>
using namespace std;

void print_min_operation(vector<vector<int>>& s, int i, int j) {
    if (i == j) {
        cout << "A" << i;
    }
    else {
        cout << "(";
        print_min_operation(s, i, s[i][j]);
        cout << " x ";
        print_min_operation(s, s[i][j] + 1, j);
        cout << ")";
    }
}

int chained_matrix(const vector<int>& p) {
    int n = p.size() - 1;
    vector<vector<int>> m(n + 1, vector<int>(n + 1, 0));
    vector<vector<int>> s(n + 1, vector<int>(n + 1, 0));

    for (int l = 2; l <= n; ++l) {
        for (int i = 1; i <= n - l + 1; ++i) {
            int j = i + l - 1;
            m[i][j] = numeric_limits<int>::max();
            for (int k = i; k < j; ++k) {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

    // 출력
    cout << "Chained Matrix Multiplication" << endl;
    cout << "================================" << endl;
    cout << "M";
    for (int j = 1; j <= n; ++j) {
        cout << setw(8) << j;
    }
    cout << endl;

    for (int i = 1; i <= n; ++i) {
        cout << i;
        for (int j = 1; j <= n; ++j) {
            if (i > j) {
                cout << setw(8) << "0";
            }
            else {
                cout << setw(8) << m[i][j];
            }
        }
        cout << endl;
    }

    cout << "\nFinal Solution : " << m[1][n] << endl;
    cout << "\nImplicit Order for Matrix Multiplication : ";
    print_min_operation(s, 1, n);
    cout << endl;

    return m[1][n];
}

int main() {
    // A1(10x20), A2(20x5), A3(5x15), A4(15x30)
    vector<int> matrix = { 10, 20, 5, 15, 30 };

    chained_matrix(matrix);

    return 0;
}
