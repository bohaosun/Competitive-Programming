/*
 * Greedy algorithm which always chooses the task with the nearest deadline solves the maximum.
 * Find the minimum cut to solve the minimum part.
 */
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <string>
#include <bitset>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>
#include <random>

#define _1 first
#define _2 second
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define uni(x) (x).erase(unique(all(x)), (x).end());
#define reset(x, y) memset(x, y, sizeof(x))
#define BUG(x) cerr << #x << " = " << (x) << endl
#define mp make_pair
using namespace std;

typedef long long LL;
typedef pair<int, int> pii;
typedef pair<LL, LL> pll;
// Head

const int N = 400 * 5;
const int INF = int(1e9);

struct Dinic {
    struct Edge {
        int from, to, cap, flow;
        Edge(int from, int to, int cap, int flow): from(from), to(to), cap(cap), flow(flow) {}
    };

    int n, m, s, t;
    vector<Edge> edges;
    vector<int> G[N];
    bool vis[N];         
    int d[N];            
    int cur[N];          

    void init(int n) {
        this->n = n;
        for(int i = 0; i < n; i++) G[i].clear();
        edges.clear();
    }

    void AddEdge(int from, int to, int cap) {
        edges.push_back(Edge(from, to, cap, 0));
        edges.push_back(Edge(to, from, 0, 0));
        m = edges.size();
        G[to].push_back(m - 1);
        G[from].push_back(m - 2);
    }

    bool BFS() {       // 构建层次图
        memset(vis, false, sizeof(vis));
        queue<int> Q;
        Q.push(s);
        d[s] = 0;
        vis[s] = true;
        while(!Q.empty()) {
            int x = Q.front(); Q.pop();
            for(int i = 0; i < G[x].size(); i++) {
                Edge& e = edges[G[x][i]];
                if(!vis[e.to] && e.cap > e.flow) {  
                    vis[e.to] = true;
                    d[e.to] = d[x] + 1;
                    Q.push(e.to);
                }
            }
        }
        return vis[t];
    }

    int DFS(int x, int a) {  
        if(x == t || a == 0) return a;
        int flow = 0, f;
        for(int& i = cur[x]; i < G[x].size(); i++) {  
            Edge& e = edges[G[x][i]];
            if(d[x] + 1 == d[e.to] && (f = DFS(e.to, min(a, e.cap - e.flow))) > 0) {
                e.flow += f;
                edges[G[x][i] ^ 1].flow -= f;
                flow += f;
                a -= f;
                if(a == 0) break;
            }
        }
        return flow;
    }

    int Maxflow(int s, int t) {
        this->s = s; this->t = t;
        int flow = 0;
        while(BFS()) {
            memset(cur, 0, sizeof(cur));
            flow += DFS(s, INF);
        }
        return flow;
    }
};


int n, m;

struct Node {
    int s, t, id;
    bool operator < (const Node& rhs) const {
        return s < rhs.s;
    }
};

vector<Node> node;

Dinic solver;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int s, t;
        cin >> s >> t;
        node.pb({ s, t, i });
    }

    sort(all(node));

    int cur = 0, maxm = 0;
    multiset<int> s;
    for (int i = 1; i <= 400; i++) {
        while (cur < node.size() && node[cur].s <= i) s.insert(node[cur++].t);
        while (!s.empty()) {
            auto it = s.begin();
            if (*it < i) s.erase(it);
            else {
                maxm++;
                s.erase(it);
                break;
            }
        }
    }

    cout << maxm << '\n';

    solver.init(400 * 3 + 5);

    for (int i = 1; i <= 400; i++) solver.AddEdge(i, i + 400, 1);
    for (int i = 0; i < n; i++) {
        if (node[i].id <= m) {
            solver.AddEdge(0, node[i].id + 800, 1);
            for (int j = node[i].s; j <= node[i].t; j++) solver.AddEdge(node[i].id + 800, j, 1);
        } else {
            solver.AddEdge(node[i].id + 800, 800 + n + 1, 1);
            for (int j = node[i].s; j <= node[i].t; j++) solver.AddEdge(j + 400, node[i].id + 800, 1);
        }
    }
    cout << solver.Maxflow(0, 800 + n + 1) << '\n';
    return 0;
}
