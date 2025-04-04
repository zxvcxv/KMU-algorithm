#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>

using namespace std;

// 랜덤 숫자 생성 함수
int rand_num(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// 배열을 피벗을 기준으로 나누는 함수
int partition(int list[], int left, int right) {
    int pivot = list[right];  // 마지막 요소를 피벗으로 설정
    int i = left - 1;

    for (int j = left; j < right; j++) {
        if (list[j] <= pivot) {
            i++;
            swap(list[i], list[j]);
        }
    }
    swap(list[i + 1], list[right]);
    return i + 1;
}

// 퀵 정렬 함수
void quick_sort(int list[], int left, int right) {
    if (left < right) {
        int pi = partition(list, left, right);
        quick_sort(list, left, pi - 1);
        quick_sort(list, pi + 1, right);
    }
}

// 배열의 k번째 작은 값을 퀵 정렬 후 찾는 방법
int search_small_k_sort(const vector<vector<int>>& arr, int k) {
    vector<int> flatArr;
    for (const auto& row : arr) {
        for (int val : row) {
            flatArr.push_back(val);
        }
    }

    // 퀵 정렬을 사용하여 배열 정렬
    int n = flatArr.size();
    quick_sort(flatArr.data(), 0, n - 1);

    // k번째 작은 값을 반환
    return flatArr[k - 1];
}

// 배열의 k번째 작은 값을 MIN값부터 차례로 찾는 방법
int search_small_k_min(const vector<vector<int>>& arr, int k) {
    int minVal = 1;
    int maxVal = 100000;
    vector<int> count(maxVal + 1, 0);  // 각 값의 등장 횟수를 추적하는 배열
    int count_find = 0;

    // 2차원 배열에서 각 값의 등장 횟수를 계산
    for (const auto& row : arr) {
        for (int val : row) {
            count[val]++;
        }
    }

    // 중복을 고려하여 k번째 작은 값을 찾기
    for (int i = minVal; i <= maxVal; ++i) {
        while (count[i] > 0 && count_find < k) {
            count_find++;
            if (count_find == k) {
                return i;
            }
            count[i]--;
        }
    }

    return -1;
}

int main() {
    srand(time(0));

    // n 입력 받기 (500~1000)
    int n;
    do {
        cout << "배열 크기를 입력하세요(500~1000): ";
        cin >> n;
    } while (n < 500 || n > 1000);

    // n x n 크기의 2D 배열 생성
    vector<vector<int>> arr(n, vector<int>(n));

    // 배열을 랜덤 값으로 채우기
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            arr[i][j] = rand_num(1, 100000);
        }
    }

    // 랜덤으로 k 선택하기
    int k = rand_num(1, n * n);
    cout << k <<"번째로 작은 값 찾기" << endl;

    // 정렬 후 k번째 작은 값 찾기
    auto start = chrono::high_resolution_clock::now();
    int result_sort = search_small_k_sort(arr, k);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> sort_time = end - start;
    cout << "\n정렬 후 탐색" << endl;
    cout << "찾은 값: " << result_sort << endl;
    cout << "걸린 시간: " << sort_time.count() << " 초" << endl;

    // MIN값부터 차례로 k번째 작은 값 찾기
    start = chrono::high_resolution_clock::now();
    int result_min = search_small_k_min(arr, k);
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> min_time = end - start;
    cout << "\nMIN값부터 차례로 탐색" << endl;
    cout << "찾은 값: " << result_min << endl;
    cout << "걸린 시간: " << min_time.count() << " 초" << endl;
    return 0;
}
