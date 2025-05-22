#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>
#include <cstdlib>
#include <ctime>

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
    cout << "매트릭스 개수: " << n << endl;
    cout << "matrix: ";
    for (auto d : p) cout << d << " ";
    cout << endl;

    cout << "최소 연산 횟수: " << m[1][n] << endl;
    cout << "최적의 연산 순서: ";
    print_min_operation(s, 1, n);
    cout << endl;
    cout << "---------------------------------------" << endl;

    return m[1][n];
}

int main() {
    srand((unsigned)time(0));

    for (int num_matrices = 5; num_matrices <= 10; ++num_matrices) {
        vector<int> matrix;

        // 랜덤 매트릭스 생성
        for (int i = 0; i <= num_matrices; ++i) {
            int dim = 5 + rand() % 46;
            matrix.push_back(dim);
        }

        chained_matrix(matrix);
    }

    return 0;
}
