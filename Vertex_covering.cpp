#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

struct Graph {
    int V, E;
    vector<pair<int, int>> edges;
    vector<set<int>> adjList;
};

// 그래프 생성
Graph create_graph() {
    int V = rand() % 11 + 10;  // 10~20
    int E = rand() % 11 + 20;  // 20~30
    set<pair<int, int>> edgeSet;

    while ((int)edgeSet.size() < E) {
        int u = rand() % V;
        int v = rand() % V;
        if (u == v)
            continue;
        if (u > v)
            swap(u, v);
        edgeSet.insert(make_pair(u, v));
    }

    vector<set<int>> adj(V);
    for (set<pair<int, int>>::iterator it = edgeSet.begin(); it != edgeSet.end(); ++it) {
        int u = it->first;
        int v = it->second;
        adj[u].insert(v);
        adj[v].insert(u);
    }

    vector<pair<int, int>> edgeVec(edgeSet.begin(), edgeSet.end());
    return { V, (int)edgeSet.size(), edgeVec, adj };
}

// Vertex Priority Selection
vector<int> vertex_priority(const Graph& g) {
    vector<set<int>> tempAdj = g.adjList;
    vector<int> cover;

    while (true) {
        int maxDeg = 0, sel = -1;
        for (int i = 0; i < g.V; ++i) {
            if ((int)tempAdj[i].size() > maxDeg) {
                maxDeg = tempAdj[i].size();
                sel = i;
            }
        }
        if (maxDeg == 0)
            break;

        cover.push_back(sel);
        for (set<int>::iterator it = tempAdj[sel].begin(); it != tempAdj[sel].end(); ++it) {
            tempAdj[*it].erase(sel);
        }
        tempAdj[sel].clear();
    }
    return cover;
}

// Maximal Matching
vector<int> maximal_matching(const Graph& g) {
    vector<int> cover;
    set<pair<int, int>> edgeSet(g.edges.begin(), g.edges.end());
    set<int> chosen;

    while (!edgeSet.empty()) {
        pair<int, int> e = *edgeSet.begin();
        int u = e.first;
        int v = e.second;

        if (chosen.find(u) == chosen.end()) {
            cover.push_back(u);
            chosen.insert(u);
        }
        if (chosen.find(v) == chosen.end()) {
            cover.push_back(v);
            chosen.insert(v);
        }

        vector<pair<int, int>> toRemove;
        for (set<pair<int, int>>::iterator it = edgeSet.begin(); it != edgeSet.end(); ++it) {
            int a = it->first;
            int b = it->second;
            if (a == u || b == u || a == v || b == v) {
                toRemove.push_back(*it);
            }
        }
        for (size_t i = 0; i < toRemove.size(); ++i) {
            edgeSet.erase(toRemove[i]);
        }
    }

    return cover;
}

int main() {
    srand(time(NULL));
    int totalVP = 0, totalMM = 0;

    for (int i = 1; i <= 10; ++i) {
        cout << i << "번째\n";
        Graph g = create_graph();

        cout << "Graph: (Vertex=" << g.V << ", Edge=" << g.E << ")\n";

        vector<int> vp = vertex_priority(g);
        vector<int> mm = maximal_matching(g);

        int vpSize = vp.size();
        int mmSize = mm.size();

        totalVP += vpSize;
        totalMM += mmSize;


        cout << "Vertex Priority : " << vpSize << " => ";
        for (size_t i = 0; i < vp.size(); ++i) cout << vp[i] << " ";
        cout << "\n";

        cout << "Maximal Matching: " << mmSize << " => ";
        for (size_t i = 0; i < mm.size(); ++i) cout << mm[i] << " ";
        cout << "\n";

        cout << "==============================\n";
    }

    double avgVP = totalVP / 10.0;
    double avgMM = totalMM / 10.0;

    cout << "비교\n";
    cout << "Vertex Priority 평균 개수: " << avgVP << "\n";
    cout << "Maximal Matching 평균 개수 : " << avgMM << "\n";

    if (avgVP < avgMM) 
        cout << "Vertex Priority 방식이 평균적으로 " << avgMM / avgVP << "배 더 우수합니다.\n";
    else if (avgMM < avgVP)
        cout << "Maximal Matching 방식이 평균적으로 " << avgVP / avgMM << "배 더 우수합니다.\n";
    else 
        cout << "두 방식의 평균 성능은 동일합니다.\n";

    return 0;
}
