#include <iostream>
#include <vector>
#include <queue>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

// 간선 정보를 담는 구조체
struct Edge {
    int u, v, weight;

    // 가중치를 기준으로 오름차순 정렬하기 위한 연산자 오버로딩
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// 부모 노드를 찾기
int find_parent(int u, vector<int>& parent) {
    if (parent[u] != u)
        parent[u] = find_parent(parent[u], parent);
    return parent[u];
}

// 두 노드를 같은 집합으로 합침 (사이클 방지)
bool set_union(int u, int v, vector<int>& parent) {
    int pu = find_parent(u, parent);
    int pv = find_parent(v, parent);

    if (pu == pv)       // 같은 집합 = 사이클 발생
        return false; 

    parent[pu] = pv;
    return true;
}

// MST 그래프 생성
vector<vector<pair<int, int>>> create_MST_graph(int V, int E) {
    srand(time(0));
    vector<Edge> edges;

    // 랜덤 간선 생성 (무방향)
    while (edges.size() < E) {
        int u = rand() % V + 1;
        int v = rand() % V + 1;

        if (u == v)
            continue;

        int w = rand() % 10 + 1; // 가중치 설정
        edges.push_back({ u, v, w });
    }

    
    sort(edges.begin(), edges.end());

    // 초기 부모 설정 (자기 자신)
    vector<int> parent(V + 1);
    for (int i = 1; i <= V; i++)
        parent[i] = i;

    vector<vector<pair<int, int>>> graph(V + 1);
    int count = 0;

    // MST 생성
    for (Edge& e : edges) {
        if (set_union(e.u, e.v, parent)) {
            graph[e.u].push_back({ e.v, e.weight });
            graph[e.v].push_back({ e.u, e.weight });
            count++;
            if (count == V - 1)
                break;
        }
    }
    return graph;
}

// 다익스트라 알고리즘
void dijkstra(const vector<vector<pair<int, int>>>& graph, int start) {
    int V = graph.size() - 1;
    vector<int> dist(V + 1, 10000); // 10000은 가중치 초기값을 큰 수로 지정한 것
    vector<int> prev(V + 1, -1);    
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    dist[start] = 0;
    pq.push({ 0, start });

    while (!pq.empty()) {
        auto top = pq.top(); pq.pop();
        int cost = top.first;
        int u = top.second;

        if (cost > dist[u])
            continue;

        for (auto& edge : graph[u]) {
            int v = edge.first;
            int w = edge.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                prev[v] = u;
                pq.push({ dist[v], v });
            }
        }
    }

    // 결과 출력
    for (int i = 1; i <= V; i++) {
        if (i == start)
            continue;

        vector<int> path;
        int cur = i;
        while (cur != -1) {
            path.push_back(cur);
            cur = prev[cur];
        }
        reverse(path.begin(), path.end());

        cout << path[0];
        for (int j = 1; j < path.size(); j++) {
            cout << " -> " << path[j];
        }
        cout << " (Cost: " << dist[i] << ")" << endl;
    }
}

int main() {
    int V = 10; // 정점 수
    int E = 20; // 최대 간선 수

    auto graph = create_MST_graph(V, E); 
    dijkstra(graph, 1);                  

    return 0;
}
