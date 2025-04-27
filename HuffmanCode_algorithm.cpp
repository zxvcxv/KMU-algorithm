#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <map>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node* left, * right;

    Node(char ch, int freq) : ch(ch), freq(freq), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

void build_code(Node* root, string str, map<char, string>& huffmanCode) {
    if (!root)
        return;

    if (!root->left && !root->right) {
        huffmanCode[root->ch] = str;
    }

    build_code(root->left, str + "0", huffmanCode);
    build_code(root->right, str + "1", huffmanCode);
}

void delete_node(Node* root) {
    if (!root) return;
    delete_node(root->left);
    delete_node(root->right);
    delete root;
}

int main() {
    // 1. sample.txt 파일에서 사용된 문자와 각 문자의 출현빈도(frequency)를 출력하시오. (예, a: 30, b : 15, ...)
    ifstream input("sample.txt");
    if (!input) {
        cerr << "파일을 여는데 실패했습니다." << endl;
        return 1;
    }

    // 각 문자 당 노드를 만들고, 그 문자의 빈도수를 노드에 저장
    map<char, int> freq;
    char ch;
    string text;

    while (input.get(ch)) {
        freq[ch]++;
        text += ch;
    }
    input.close();

    cout << "Character frequencies:\n";

    for (auto& p : freq) {
        // 문자 출력
        if (p.first == '\n') cout << "\\n";
        else cout << p.first;

        cout << " (ASCII " << (int)(unsigned char)p.first << "): " << p.second << endl;
    }

    // 2. 1에서 추출한 값을 사용하여 huffman code를 완성하시오.
    // n개의 노드의 빈도수에 대해 우선순위 큐 Q를 만든다
    priority_queue<Node*, vector<Node*>, Compare> Q;
    for (auto& p : freq) {
        Q.push(new Node(p.first, p.second));
    }

    // Q에 노드가 2개 이상 있을 동안 계속 트리를 만들어야 하니까 반복
    while (Q.size() != 1) {
        // 빈도수가 가장 작은 2개의 노드 (A와 B)를 Q에서 제거
        Node* left = Q.top();
        Q.pop();
        Node* right = Q.top();
        Q.pop();

        // 새 노드 N을 만들고, A와 B를 N의 자식 노드로 만든다
        Node* N = new Node('\0', left->freq + right->freq); // N의 빈도수 = A의 빈도수 + B의 빈도수
        N->left = left;
        N->right = right;

        // 노드 N을 Q에 삽입한다
        Q.push(N);
    }

    Node* root = Q.top();

    map<char, string> huffmanCode;
    build_code(root, "", huffmanCode);

    // 3. 완성된 huffman code를 사용하여 sample.txt 파일을 encode 하시오. (sample.enc)
    ofstream enc("sample.enc");
    string encodedStr = "";
    for (char c : text) {
        encodedStr += huffmanCode[c];
    }
    enc << encodedStr;
    enc.close();

    // 4. 3번에서 enc된 파일을 원래 sample 파일로 decode 하시오. (sample.dec)
    ofstream dec("sample.dec");
    Node* curr = root;
    for (char bit : encodedStr) {
        if (bit == '0') curr = curr->left;
        else curr = curr->right;

        if (!curr->left && !curr->right) {
            dec << curr->ch;
            curr = root;
        }
    }
    dec.close();

    // 5. 디코드된 sample.dec 파일과 원본인 sample.txt 파일이 일치하는지 확인하시오.
    ifstream original("sample.txt");
    ifstream decoded("sample.dec");

    string originalText((istreambuf_iterator<char>(original)), istreambuf_iterator<char>());
    string decText((istreambuf_iterator<char>(decoded)), istreambuf_iterator<char>());

    cout << "\nsample.dec와 sample.txt는 ";
    if (originalText == decText) {
        cout << "일치합니다" << endl;
    }
    else {
        cout << "불일치합니다" << endl;
    }

    // 6. 압축전과 후의 비트수를 계싼하여 압축률(%)을 계산하시오.
    int originalBits = originalText.size() * 8;
    int encodedBits = encodedStr.size();
    double encodeRate = (1.0 - (double)encodedBits / originalBits) * 100;

    cout << "\n압축 전 비트: " << originalBits << endl;
    cout << "압축 후 비트: " << encodedBits << endl;
    cout << "압축률: " << encodeRate << "%" << endl;

    delete_node(root);
    return 0;
}
