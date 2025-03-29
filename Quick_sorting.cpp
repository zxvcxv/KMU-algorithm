#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <random>

using namespace std;

const int SIZE = 12;
int pivot_count = 0;

// 온도 데이터를 저장할 구조체
struct Weather {
    string date;        // 날짜
    int temperature;    // 온도
};

int pivotRandom = 0, pivotMedian = 0, pivotThreeWay = 0;

// 두 요소를 교환하는 함수
void swap(vector<Weather>& data, int i, int j) {
    Weather temp = data[i];
    data[i] = data[j];
    data[j] = temp;
}

// Weather 구조체 비교 함수 (내림차순 정렬)
int weather_compare(const Weather& w1, const Weather& w2) {
    return w2.temperature - w1.temperature;
}

// 배열을 피벗을 기준으로 파티션을 나누는 함수
int partition(int list[], int left, int right) {
    int pivot = list[right];  // 마지막 요소를 피벗으로 설정
    int i = left - 1;
    pivot_count++;  // 피벗 선택 횟수 증가

    // 피벗보다 작은 값은 왼쪽으로 배치
    for (int j = left; j < right; j++) {
        if (list[j] <= pivot) {
            i++;
            swap(list[i], list[j]);
        }
    }
    swap(list[i + 1], list[right]);  // 피벗을 최종 위치로 이동
    return i + 1;
}

// Weather 데이터를 피벗을 기준으로 나누는 파티션 함수
int partition_w(vector<Weather>& data, int left, int right, const Weather& pivot) {
    int i = left + 1, j = right;
    while (i <= j) {
        while (i <= j && weather_compare(data[i], pivot) < 0) i++;
        while (i <= j && weather_compare(data[j], pivot) > 0) j--;
        if (i <= j) {
            swap(data, i, j);
            i++; j--;
        }
    }
    swap(data, left, j);
    return j;
}

// 기본 퀵 정렬 함수
void quick_sort(int list[], int left, int right) {
    if (left < right) {
        int pi = partition(list, left, right);
        quick_sort(list, left, pi - 1);
        quick_sort(list, pi + 1, right);
    }
}

// 랜덤 피벗을 사용하는 퀵 정렬
void quick_sort_rand(vector<Weather>& data, int left, int right) {
    if (left < right) {
        pivotRandom++;
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dist(left, right);
        int randomIndex = dist(gen);
        swap(data, left, randomIndex);
        int pivotIndex = partition_w(data, left, right, data[left]);
        quick_sort_rand(data, left, pivotIndex - 1);
        quick_sort_rand(data, pivotIndex + 1, right);
    }
}

// 세 개의 요소 중 중앙값을 피벗으로 선택하는 함수
Weather select_midian(const Weather& a, const Weather& b, const Weather& c) {
    if ((a.temperature >= b.temperature && a.temperature <= c.temperature) || (a.temperature <= b.temperature && a.temperature >= c.temperature)) return a;
    else if ((b.temperature >= a.temperature && b.temperature <= c.temperature) || (b.temperature <= a.temperature && b.temperature >= c.temperature)) return b;
    else return c;
}

// 미디언 피벗을 사용하는 퀵 정렬
void quick_sort_mid(vector<Weather>& data, int left, int right) {
    if (left < right) {
        pivotMedian++;
        int mid = (left + right) / 2;
        Weather pivot = select_midian(data[left], data[mid], data[right]);
        swap(data, left, (pivot.temperature == data[mid].temperature) ? mid : (pivot.temperature == data[right].temperature) ? right : left);
        int pivotIndex = partition_w(data, left, right, data[left]);
        quick_sort_mid(data, left, pivotIndex - 1);
        quick_sort_mid(data, pivotIndex + 1, right);
    }
}

// 3-way 퀵 정렬
void quick_sort_3way(vector<Weather>& data, int low, int high) {
    if (low >= high) return;
    pivotThreeWay++;
    int lt = low, gt = high;
    Weather pivot = data[low];
    int i = low + 1;
    while (i <= gt) {
        int cmp = weather_compare(data[i], pivot);
        if (cmp < 0) swap(data, lt++, i++);
        else if (cmp > 0) swap(data, i, gt--);
        else i++;
    }
    quick_sort_3way(data, low, lt - 1);
    quick_sort_3way(data, gt + 1, high);
}

// 배열 출력 함수
void print_array(const int A[]) {
    for (int i = 0; i < SIZE; i++) {
        cout << "[" << A[i] << "] ";
    }
    cout << endl;
}

int main() {
    ifstream file("daegu_weather_2024 (1).txt");
    vector<Weather> originalData;
    string date;
    int temperature;
    while (file >> date >> temperature) {
        originalData.push_back({ date, temperature });
    }
    file.close();

    int arr[] = { 6, 3, 11, 9, 12, 2, 8, 15, 18, 10, 7, 14 };
    cout << "정렬 전 배열:\n";
    print_array(arr);
    quick_sort(arr, 0, SIZE - 1);
    cout << "\n정렬 후 배열:\n";
    print_array(arr);
    cout << "\n피벗 선택 횟수: " << pivot_count << endl;

    vector<Weather> dataRandom = originalData;
    quick_sort_rand(dataRandom, 0, dataRandom.size() - 1);

    vector<Weather> dataMedian = originalData;
    quick_sort_mid(dataMedian, 0, dataMedian.size() - 1);

    vector<Weather> dataThreeWay = originalData;
    quick_sort_3way(dataThreeWay, 0, dataThreeWay.size() - 1);

    cout << "\n랜덤 피벗 선택 횟수: " << pivotRandom << endl;
    cout << "미디언 피벗 선택 횟수: " << pivotMedian << endl;
    cout << "3-way 피벗 선택 횟수: " << pivotThreeWay << endl;

    return 0;
}
