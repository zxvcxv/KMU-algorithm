#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <random>
#include <limits>

using namespace std;
using namespace chrono;

const int INF = 1000000;

// Dijkstra 알고리즘
void dijkstra(int start, const vector<vector<int>>& graph, vector<int>& dist, vector<int>& prev) {
    int V = graph.size();
    dist.assign(V, INF);
    prev.assign(V, -1);
    dist[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({ 0, start });

    while (!pq.empty()) {
        int cost = pq.top().first;
        int here = pq.top().second;
        pq.pop();

        if (cost > dist[here]) continue;

        for (int i = 0; i < V; ++i) {
            if (graph[here][i] != INF) {
                int nextDist = cost + graph[here][i];
                if (nextDist < dist[i]) {
                    dist[i] = nextDist;
                    prev[i] = here; // 경로 저장
                    pq.push({ nextDist, i });
                }
            }
        }
    }
}

// Floyd-Warshall 알고리즘
void floyd(const vector<vector<int>>& graph, vector<vector<int>>& dist) {
    int V = graph.size();
    dist = graph;
    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    if (dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }
}

// 경로 출력 함수
void print_path(int start, int end, const vector<int>& prev) {
    vector<int> path;
    for (int at = end; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());

    if (path[0] != start) {
        cout << "경로가 존재하지 않습니다.\n";
        return;
    }

    cout << "최단 경로: ";
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i] + 1; // 1-based index 출력
        if (i != path.size() - 1) cout << " -> ";
    }
    cout << '\n';
}

// 랜덤 그래프 생성
vector<vector<int>> create_random_graph(int V) {
    vector<vector<int>> graph(V, vector<int>(V, INF));
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> weightDist(1, 20);

    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (i != j) {
                // 50% 확률로 간선 추가
                if (rand() % 2) {
                    graph[i][j] = weightDist(gen);
                }
            }
            else {
                graph[i][j] = 0;
            }
        }
    }

    // 최소 연결성 보장
    for (int i = 0; i < V - 1; ++i) {
        graph[i][i + 1] = weightDist(gen);
    }

    return graph;
}

// Basic Version
void basic_version() {
    cout << "=== Basic Version ===\n";

    vector<vector<int>> baseGraph = {
        { 0, 15, 12, INF, INF, INF, INF, INF, INF, INF },
        { 15, 0, INF, INF, INF, 21, INF, 7, INF, INF },
        { 12, INF, 0, 4, 10, INF, INF, INF, INF, INF },
        { INF, INF, 4, 0, 3, INF, 13, INF, INF, INF },
        { INF, INF, 10, 3, 0, INF, INF, 10, INF, INF },
        { INF, 21, INF, INF, INF, 0, INF, INF, 25, INF },
        { INF, INF, INF, 13, INF, INF, 0, INF, INF, 15 },
        { INF, 7, INF, INF, 10, INF, INF, 0, 19, 9 },
        { INF, INF, INF, INF, INF, 25, INF, 19, 0, 5 },
        { INF, INF, INF, INF, INF, INF, 15, 9, 5, 0 }
    };

    auto start_dij = high_resolution_clock::now();
    for (int i = 0; i < 10; ++i) {
        vector<int> dist, prev;
        dijkstra(i, baseGraph, dist, prev);
    }
    auto end_dij = high_resolution_clock::now();
    auto duration_dij = duration_cast<microseconds>(end_dij - start_dij);
    cout << "1. Dijkstra 10회 수행 시간: " << duration_dij.count() << "\n";

    auto start_fl = high_resolution_clock::now();
    vector<vector<int>> dist_matrix;
    floyd(baseGraph, dist_matrix);
    auto end_fl = high_resolution_clock::now();
    auto duration_fl = duration_cast<microseconds>(end_fl - start_fl);
    cout << "2. Floyd-Warshall 수행 시간: " << duration_fl.count() << "\n";
}

// Extended Version
void extended_version() {
    cout << "\n=== Extended Version ===\n";

    for (int V = 10; V <= 20; ++V) {
        cout << "\n[Vertex: " << V << "]\n";

        vector<vector<int>> graph = create_random_graph(V);

        auto start_dij = high_resolution_clock::now();
        for (int i = 0; i < V; ++i) {
            vector<int> dist, prev;
            dijkstra(i, graph, dist, prev);
        }
        auto end_dij = high_resolution_clock::now();
        auto duration_dij = duration_cast<milliseconds>(end_dij - start_dij);
        cout << "Dijkstra: " << duration_dij.count() << "\n";

        auto start_fl
            = high_resolution_clock::now();
        vector<vector<int>> dist_matrix;
        floyd(graph, dist_matrix);
        auto end_fl = high_resolution_clock::now();
        auto duration_fl = duration_cast<milliseconds>(end_fl - start_fl);
        cout << "Floyd: " << duration_fl.count() << "\n";
    }
}

// Advanced Version
void advanced_version() {
    cout << "\n====== Advanced Version ======\n";

    int V = 10;
    vector<vector<int>> graph = {
        { 0, 15, 12, INF, INF, INF, INF, INF, INF, INF },
        { 15, 0, INF, INF, INF, 21, INF, 7, INF, INF },
        { 12, INF, 0, 4, 10, INF, INF, INF, INF, INF },
        { INF, INF, 4, 0, 3, INF, 13, INF, INF, INF },
        { INF, INF, 10, 3, 0, INF, INF, 10, INF, INF },
        { INF, 21, INF, INF, INF, 0, INF, INF, 25, INF },
        { INF, INF, INF, 13, INF, INF, 0, INF, INF, 15 },
        { INF, 7, INF, INF, 10, INF, INF, 0, 19, 9 },
        { INF, INF, INF, INF, INF, 25, INF, 19, 0, 5 },
        { INF, INF, INF, INF, INF, INF, 15, 9, 5, 0 }
    };

    while (1) {
        int from, to;
        cout << "\n출발 노드와 도착 노드를 입력하세요 (1~10, 0 0 입력시 종료): ";
        cin >> from >> to;

        if (from == 0 || to == 0) break;

        if (from < 1 || from > 10 || to < 1 || to > 10) {
            cout << "유효한 노드 번호(1~10)를 입력하세요.\n";
            continue;
        }

        vector<int> dist, prev;
        dijkstra(from - 1, graph, dist, prev);

        if (dist[to - 1] == INF) {
            cout << "경로가 존재하지 않습니다.\n";
        }
        else {
            cout << "최단 거리: " << dist[to - 1] << '\n';
            print_path(from - 1, to - 1, prev);
        }
    }
}

int main() {
    basic_version();
    extended_version();
    advanced_version();
    return 0;
}
