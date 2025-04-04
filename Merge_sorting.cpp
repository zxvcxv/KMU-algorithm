#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

const int SIZE=8;

// 온도 데이터를 저장할 구조체
struct Weather {
    string date;        // 날짜
    int temperature;    // 온도
};

// 최소 비교
int min(int a, int b) {
    return (a < b) ? a : b;
}

// 배열 병합 정렬 함수
void merge(int list[], int sorted[], int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;

    while (i <= mid && j <= right) {
        if (list[i] <= list[j])
            sorted[k++] = list[i++];
        else
            sorted[k++] = list[j++];
    }

    while (i <= mid) 
        sorted[k++] = list[i++];
    while (j <= right) 
        sorted[k++] = list[j++];

    for (int l = left; l <= right; l++) {
        list[l] = sorted[l];
    }
}

// 배열 병합 정렬 수행하는 함수
void merge_sort(int list[]) {
    int sorted[SIZE];  // 정렬을 위한 배열

    for (int current_size = 1; current_size <= SIZE - 1; current_size *= 2) {
        for (int left = 0; left < SIZE - 1; left += 2 * current_size) {
            int mid = min(left + current_size - 1, SIZE - 1);
            int right = min(left + 2 * current_size - 1, SIZE - 1);
            merge(list, sorted, left, mid, right);
        }
    }
}

// 날씨 데이터 병합 정렬 함수
void merge_w(vector<Weather>& weatherData, vector<Weather>& sorted, int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;

    while (i <= mid && j <= right) {
        if (weatherData[i].temperature >= weatherData[j].temperature)
            sorted[k++] = weatherData[i++];
        else
            sorted[k++] = weatherData[j++];
    }

    while (i <= mid) sorted[k++] = weatherData[i++];
    while (j <= right) sorted[k++] = weatherData[j++];

    for (int l = left; l <= right; l++) {
        weatherData[l] = sorted[l];
    }
}

// 날씨 데이터 병합 정렬 수행하는 함수
void merge_sort_w(vector<Weather>& weatherData, int size) {
    vector<Weather> sorted(size);  // vector로 동적 배열을 생성

    for (int current_size = 1; current_size <= size - 1; current_size *= 2) {
        for (int left = 0; left < size - 1; left += 2 * current_size) {
            int mid = min(left + current_size - 1, size - 1);
            int right = min(left + 2 * current_size - 1, size - 1);
            merge_w(weatherData, sorted, left, mid, right);
        }
    }
}

// 날씨 정보를 파일에서 읽어와서 벡터에 저장
vector<Weather> read_data(const string& filename) {
    vector<Weather> weatherData;
    ifstream file(filename);
    string date;
    int temperature;

    if (file.is_open()) {
        while (file >> date >> temperature) {
            weatherData.push_back({ date, temperature });
        }
        file.close();
    }
    else {
        cout << "파일을 열 수 없습니다." << endl;
    }

    return weatherData;
}

// 날씨 데이터를 정렬
void sort_weather(vector<Weather>& weatherData) {
    merge_sort_w(weatherData, weatherData.size());
}

// 날씨 데이터를 파일로 저장
void save_weather_file(const vector<Weather>& weatherData, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& entry : weatherData) {
            file << entry.date << " " << entry.temperature << endl;
        }
        file.close();
    }
    else {
        cout << "파일을 저장할 수 없습니다." << endl;
    }
}

// 배열 출력
void print_array(const int A[]) {
    for (int i = 0; i < SIZE; i++) {
        cout << "[" << A[i] << "] ";
    }
    cout << endl;
}
 
// 가장 더웠던 날 3개를 출력
void print_top3(const vector<Weather>& weatherData) {
    cout << "2024년 가장 더웠던 날 3개:" << endl;
    for (int i = 0; i < 3 && i < weatherData.size(); i++) {
        cout << weatherData[i].date << " | " << weatherData[i].temperature << endl;
    }
}

int main() {

    // 배열 정렬
    int arr[] = { 37, 10, 22, 30, 35, 13, 25, 24 };
    
    cout << "정렬 전 배열:\n";
    print_array(arr);
    
    merge_sort(arr);
    
    cout << "\n정렬 후 배열:\n";
    print_array(arr);
    cout << endl;

    // 날씨 데이터 정렬
    vector<Weather> weatherData = read_data("daegu_weather_2024.txt");

    merge_sort_w(weatherData, weatherData.size());

    save_weather_file(weatherData, "daegu_weather_2024_sorted.txt");
    cout << "날씨 데이터 정렬 후 저장 완료!\n" << endl;

    print_top3(weatherData);

    
    return 0;
}
