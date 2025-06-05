#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// 1
int edit_distance(const string& str1, const string& str2, vector<vector<int>>& dyTable) {
    int m = str1.size();
    int n = str2.size();
    dyTable.assign(m + 1, vector<int>(n + 1));

    // 초기값 설정
    for (int i = 0; i <= m; i++) dyTable[i][0] = i;
    for (int j = 0; j <= n; j++) dyTable[0][j] = j;

    // 테이블 채우기
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (str1[i - 1] == str2[j - 1])
                dyTable[i][j] = dyTable[i - 1][j - 1]; // 문자가 같으면
            else
                dyTable[i][j] = min({ dyTable[i - 1][j] + 1,     // 삭제
                                 dyTable[i][j - 1] + 1,     // 삽입
                                 dyTable[i - 1][j - 1] + 1  // 치환
                    });
        }
    }

    return dyTable[m][n];
}

// 테이블 출력
void print_table(const vector<vector<int>>& dyTable) {
    for (const auto& row : dyTable) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << "\n";
    }
}

// 단어 추천
string spell_check(const string& input, const vector<string>& dictionary) {
    int minDist = 1e9;
    string bestMatch;
    vector<vector<int>> dyTable;

    for (const auto& word : dictionary) {
        int dist = edit_distance(input, word, dyTable);
        if (dist < minDist) {
            minDist = dist;
            bestMatch = word;
        }
    }

    cout << "\n추천: \"" << bestMatch << "\" (edit distance " << minDist << ")\n";
    return bestMatch;
}

int main() {
    // 1
    string str1 = "strong";
    string str2 = "stone"; 
    vector<vector<int>> dyTable;

    int dist = edit_distance(str1, str2, dyTable);
    cout << "str1: " << str1 << "\n" << "str2: " << str2 << "\n";
    cout << "----------------------------\n";
    cout << "Edit Distance: " << dist << "\n";  // 1-1. 삽입, 삭제, 치환 연산만으로 str1을 str2로 바꾸는 최소 연산 횟수를 구하시오.
    cout << "Edit Distance Table:\n";           // 1-2. Edit Distance Table을 출력하시오.
    print_table(dyTable);
    cout << "\n";

    // 2. 사전에 다음 세단어 있을 때, 사용자가 입력한 단어를 수정해서 출력하시오.
    vector<string> dictionary = { "definitely", "defiantly", "define" };
    string userInput;
    cout << "단어를 입력하세요: ";
    cin >> userInput;
    cout << "사전 단어: [";
    for (size_t i = 0; i < dictionary.size(); ++i) {
        cout << "\"" << dictionary[i] << "\"";
        if (i != dictionary.size() - 1) cout << ", ";
    }
    cout << "]";
    spell_check(userInput, dictionary);

    return 0;
}
