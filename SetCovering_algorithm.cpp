#include <iostream>
#include <vector>
#include <set>
#include <string>

using namespace std;

// set 출력함수
void print_set(const set<int>& s) {
    cout << "{ ";
    for (int element : s) cout << element << " ";
    cout << "}";
}

int main() {

    set<int> U = { 1,2,3,4,5,6,7,8,9,10 };

    vector<string> F = { "S1", "S2", "S3", "S4", "S5", "S6", "S7", "S8", "S9", "S10" };
    vector<set<int>> subsets = {
        {1, 2, 3, 8},
        {1, 2, 3, 4, 8},
        {1, 2, 3, 4},
        {2, 3, 4, 5, 7, 8},
        {4, 5, 6, 7},
        {5, 6, 7, 9, 10},
        {4, 5, 6, 7},
        {1, 2, 4, 8},
        {6, 9},
        {6, 10}
    };
    vector<int> costs = { 6, 10, 4, 12, 4, 8, 4, 4, 3, 4 };

    vector<string> C;  // 선택된 subset 이름
    int totalCost = 0;
    int step = 1;

    while (!U.empty()) {
        int bestIndex = -1;
        double bestEffect;
        set<int> bestCover;

        // 유효한 첫 후보 찾기
        for (int i = 0; i < subsets.size(); ++i) {
            set<int> uncovered;  // U와 subsets의 교집합
            for (int element : subsets[i]) {
                if (U.count(element)) uncovered.insert(element);
            }

            if (!uncovered.empty()) {
                bestIndex = i;
                bestCover = uncovered;
                bestEffect = static_cast<double>(costs[i]) / uncovered.size();

                // 나머지 후보들과 비교
                for (int j = i + 1; j < subsets.size(); ++j) {
                    set<int> uncovered_2;
                    for (int element : subsets[j]) {
                        if (U.count(element)) uncovered_2.insert(element);
                    }

                    if (uncovered_2.empty()) continue;

                    double effect = static_cast<double>(costs[j]) / uncovered_2.size();
                    if (effect < bestEffect) {
                        bestEffect = effect;
                        bestIndex = j;
                        bestCover = uncovered_2;
                    }
                }
                break;
            }
        }
      
        if (bestIndex == -1) {
            cout << "오류: 유효한 커버 없음.\n";
            return 1;
        }

        // 출력
        cout << "[" << step++ << "단계]\n";
        cout << "선택된 F = " << F[bestIndex] << " (Cost: " << costs[bestIndex] << ")\n";
        cout << "남은 U element: ";
        print_set(U);

        cout << "\n" << F[bestIndex] << "의 elements: ";
        print_set(subsets[bestIndex]);

        // 실제로 제거
        for (int element : subsets[bestIndex]) {
            U.erase(element);
        }

        cout << "\nU - " << F[bestIndex] << " = ";
        print_set(U);
        cout << "\n\n";

        // 결과 기록
        C.push_back(F[bestIndex]);
        totalCost += costs[bestIndex];

        // 사용한 subset 제거
        subsets.erase(subsets.begin() + bestIndex);
        F.erase(F.begin() + bestIndex);
        costs.erase(costs.begin() + bestIndex);
    }

    // 최종 결과 출력
    cout << "선택된 전체 subsets\n";
    for (const string& name : C) {
        cout << name << " ";
    }
    cout << "\n총 cost: " << totalCost << endl;

    return 0;
}
