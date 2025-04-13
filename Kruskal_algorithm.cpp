#include <iostream>
#include <vector>
#include <tuple>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iomanip>

using namespace std;

const int VER_NUM = 10;
const int MAX_WEIGHT = 20;

// DFS를 사용해 u에서 v로 가는 경로가 있는지 확인 (사이클 여부 판단용)
bool search_path_dfs(vector<vector<int>>& adj, int u, int v, vector<bool>& visited) {
    if (u == v) return true;
    visited[u] = true;

    for (int neighbor : adj[u]) {
        if (!visited[neighbor]) {
            if (search_path_dfs(adj, neighbor, v, visited)) return true;
        }
    }
    return false;
}

// 연결 그래프를 생성하는 함수
void generate_link(vector<tuple<int, int, int>>& graphEdges, int adjMatrix[VER_NUM][VER_NUM], tuple<int, int, int>& firstEdge) {
    vector<vector<int>> adj(VER_NUM);
    int edgeCount = 0;

    while (edgeCount < VER_NUM - 1) {
        int u = rand() % VER_NUM;
        int v = rand() % VER_NUM;
        if (u == v) continue;

        bool exists = false;
        for (auto& e : graphEdges) {
            int a, b, w;
            tie(a, b, w) = e;
            if ((a == u && b == v) || (a == v && b == u)) {
                exists = true;
                break;
            }
        }
        if (exists) continue;

        int weight = 1 + rand() % MAX_WEIGHT;

        vector<bool> visited(VER_NUM, false);
        if (!search_path_dfs(adj, u, v, visited)) {
            graphEdges.push_back({ u, v, weight });
            adj[u].push_back(v);
            adj[v].push_back(u);
            adjMatrix[u][v] = adjMatrix[v][u] = weight;
            if (graphEdges.size() == 1) firstEdge = { u, v, weight };
            edgeCount++;
        }
    }

    // 추가 간선 (사이클 포함)
    int extraEdges = rand() % 5 + 3;
    while (extraEdges--) {
        int u = rand() % VER_NUM;
        int v = rand() % VER_NUM;
        if (u == v) continue;

        bool exists = false;
        for (auto& e : graphEdges) {
            int a, b, w;
            tie(a, b, w) = e;
            if ((a == u && b == v) || (a == v && b == u)) {
                exists = true;
                break;
            }
        }
        if (exists) continue;

        int weight = 1 + rand() % MAX_WEIGHT;
        graphEdges.push_back({ u, v, weight });
        adjMatrix[u][v] = adjMatrix[v][u] = weight;
    }
}

// Kruskal MST
void kruskal_MST(vector<tuple<int, int, int>>& graphEdges, tuple<int, int, int> firstEdge) {
    sort(graphEdges.begin(), graphEdges.end(), [](const tuple<int, int, int>& a, const tuple<int, int, int>& b) {
            return get<2>(a) < get<2>(b);
        });

    vector<vector<int>> mstAdj(VER_NUM); // MST 연결 상태 저장
    vector<tuple<int, int, int>> mstEdges;

    int u, v, w;
    tie(u, v, w) = firstEdge;
    mstAdj[u].push_back(v);
    mstAdj[v].push_back(u);
    mstEdges.push_back(firstEdge);

    cout << "\nKruskal MST\n";
    cout << "(" << u << "," << v << "), (" << v << "," << u << "), weight: " << w << endl;

    for (auto& e : graphEdges) {
        int a, b, weight;
        tie(a, b, weight) = e;

        if ((a == u && b == v) || (a == v && b == u)) continue;

        vector<bool> visited(VER_NUM, false);
        if (!search_path_dfs(mstAdj, a, b, visited)) {
            mstAdj[a].push_back(b);
            mstAdj[b].push_back(a);
            mstEdges.push_back({ a, b, weight });
            cout << "(" << a << "," << b << "), (" << a << "," << b << "), weight: " << weight << endl;
        }
        else {
            cout << "Edge (" << a << "," << b << ") is excluded because it creates a cycle.\n";
        }

        if (mstEdges.size() == VER_NUM - 1) break;
    }
}

// 인접 행렬 출력
void print_matrix(int adjMatrix[VER_NUM][VER_NUM]) {
    cout << "\nAdjacency Matrix of Direct Graph\n";
    for (int i = 0; i < VER_NUM; i++) {
        for (int j = 0; j < VER_NUM; j++) {
            cout << setw(2) << adjMatrix[i][j] << " ";
        }
        cout << "\n";
    }
}

// 전체 간선 출력
void print_edges(const vector<tuple<int, int, int>>& graphEdges) {
    cout << "Random Matrix Generation!!\n";
    int count = 1;
    for (auto& e : graphEdges) {
        int u, v, w;
        tie(u, v, w) = e;
        cout << count++ << ". random edge : (" << u << "," << v << "), (" << v << "," << u << "), weight: " << w << endl;
    }
}

int main() {
    srand(time(0));
    vector<tuple<int, int, int>> graphEdges;
    int adjMatrix[VER_NUM][VER_NUM] = { 0 };
    tuple<int, int, int> firstEdge;

    generate_link(graphEdges, adjMatrix, firstEdge);
    print_edges(graphEdges);

    cout << "\nNumber of Vertices : " << VER_NUM << endl;
    cout << "Number of Edges : " << graphEdges.size() << endl;

    kruskal_MST(graphEdges, firstEdge);
    print_matrix(adjMatrix);

    return 0;
}
