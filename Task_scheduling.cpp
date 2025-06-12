#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// List Scheduling 
int list_scheduling(const vector<int>& jobs, int m) {
    int n = jobs.size();
    vector<int> L(m, 0); // 각 머신의 종료시간
    vector<vector<int>> assignedJobs(m); // 각 머신에 배정된 작업

    for (int i = 0; i < n; ++i) {
        int minIndex = 0;

        for (int j = 1; j < m; ++j) {
            if (L[j] < L[minIndex]) {
                minIndex = j;
            }
        }

        assignedJobs[minIndex].push_back(jobs[i]);
        L[minIndex] += jobs[i];
    }

    // 출력
    int maxEndTime = 0;
    for (int i = 0; i < m; ++i) {
        cout << "머신" << (i + 1) << ": ";
        for (int job : assignedJobs[i]) {
            cout << job << " ";
        }
        cout << endl;
        maxEndTime = max(maxEndTime, L[i]);
    }
    cout << "종료시간: " << maxEndTime << endl << endl;
    return maxEndTime;
}

// LPT 방식
int LPT(const vector<int>& jobs, int m) {
    vector<int> sortedJobs = jobs;
    sort(sortedJobs.rbegin(), sortedJobs.rend()); // 내림차순 정렬
    return list_scheduling(sortedJobs, m);
}

int main() {
    vector<int> jobs = { 2, 5, 1, 7, 3, 4 };
    int m = 3;

    cout << "작업 목록: ";
    for (int job : jobs) {
        cout << job << " ";
    }
    cout << "\n\na) LPT(Longest Processing Time first)\n";
    int timeLPT = LPT(jobs, m);

    cout << "b) List Scheduling (순서대로)\n";
    int timeLS = list_scheduling(jobs, m);

    int totalTime = 0;
    for (int job : jobs) {
        totalTime += job;
    }
  
    // 전체 작업시간을 머신 수로 나눈 값과, 가장 긴 작업시간 중 큰 값을 선택
    int optTime = max((int)ceil((double)totalTime / m), *max_element(jobs.begin(), jobs.end()));

    cout << "총 작업시간: " << totalTime << endl;
    cout << "최적 종료시간: " << optTime << endl;
    cout << "LPT 오차율: " << (double)timeLPT / optTime << endl;
    cout << "List Scheduling 오차율: " << (double)timeLS / optTime << endl;

    return 0;
}
