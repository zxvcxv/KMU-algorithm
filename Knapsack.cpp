#include <iostream>
#include <vector>
#include <string>
using namespace std;

// 1. 기본 문제
void Knapsack(const vector<int>& weight, const vector<int>& value, int capacity) {
    int n = weight.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= capacity; ++w) {
            if (w < weight[i - 1]) {
                dp[i][w] = dp[i - 1][w];
            }
            else {
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - weight[i - 1]] + value[i - 1]);
            }
        }
    }

    // 결과 출력
    cout << "무게 제한: " << capacity << "kg\n";
    cout << "--------------------------------\n";
    cout << "최대 가치: " << dp[n][capacity] << "만원\n";
    cout << "--------------------------------\n";
    cout << "선택된 아이템\n";

    int w = capacity;
    for (int i = n; i > 0; --i) {
        if (dp[i][w] != dp[i - 1][w]) {
            cout << "Item " << i << ": " << weight[i - 1] << "kg, " << value[i - 1] << "만원\n";
            w -= weight[i - 1];
        }
    }
}

// 2. 응용 문제
const int INF = 10000;
void Knapsack_2(const vector<int>& weight, const vector<int>& value, int valueLimit) {
    int n = weight.size();

    vector<vector<int>> dp(n + 1, vector<int>(valueLimit + 1, INF));
    dp[0][0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int v = 0; v <= valueLimit; ++v) {
            dp[i][v] = dp[i - 1][v];
            if (v >= value[i - 1] && dp[i - 1][v - value[i - 1]] != INF) {
                dp[i][v] = min(dp[i][v], dp[i - 1][v - value[i - 1]] + weight[i - 1]);
            }
        }
    }

    int bestValue = 0;
    int minWeight = INF;
    for (int v = 0; v <= valueLimit; ++v) {
        if (dp[n][v] != INF) {
            if (v > bestValue || (v == bestValue && dp[n][v] < minWeight)) {
                bestValue = v;
                minWeight = dp[n][v];
            }
        }
    }

    // 결과 출력
    cout << "가치 제한: " << valueLimit << "만원 이하, 무게 최소\n";
    cout << "--------------------------------\n";
    cout << "총 가치: " << bestValue << "만원, " << "총 무게: " << minWeight << "kg\n";
    cout << "--------------------------------\n";
    cout << "선택된 아이템\n";

    int v = bestValue, w = minWeight;
    vector<int> selected;
    for (int i = n; i >= 1; --i) {
        if (v >= value[i - 1] &&
            dp[i][v] == dp[i - 1][v - value[i - 1]] + weight[i - 1]) {
            selected.push_back(i);
            v -= value[i - 1];
            w -= weight[i - 1];
        }
    }

    for (int i = 0; i < selected.size(); ++i) {
        int idx = selected[i] - 1;
        cout << "Item " << selected[i]
            << ": " << weight[idx]
            << "kg, " << value[idx] << "만원\n";
    }
}

int main() {
    vector<int> weight = { 5, 4, 6, 3 };
    vector<int> value = { 10, 40, 30, 50 };  // 만원 단위
    int capacity = 10;
    int valueLimit = 80;

    cout << "1. 기본 문제" << endl;
    Knapsack(weight, value, capacity);

    cout << "================================\n";
    cout << "2. 응용 문제" << endl;
    Knapsack_2(weight, value, valueLimit);
    return 0;
}
