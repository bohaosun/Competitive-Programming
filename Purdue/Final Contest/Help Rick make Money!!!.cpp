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
#define mp make_pair
#define sqr(x) ((x) * (x))
#define all(x) (x).begin(), (x).end()
#define uni(x) (x).erase(unique(all(x)), (x).end())
#define reset(x, y) memset(x, y, sizeof(x))
#define BUG(x) cerr << #x << " = " << (x) << endl
#define BUGP(x) cout << #x << " = " << (x)._1 << ", " << (x)._2 << endl
using namespace std;

typedef long long LL;
typedef pair<int, int> pii;
typedef pair<LL, LL> pll;

const int dr[] = {-1, 0, 1, 0, -1, -1, 1, 1};
const int dc[] = {0, -1, 0, 1, -1, 1, -1, 1};
// Head

const int N = 800;
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

    bool BFS() {       
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

int n, id, p[N], m, tot;
Dinic solver;
int S, T;

struct Node {
    int x, y, z;
};
vector<Node> node;

bool check(int val) {
    for (int i = 1; i <= n; i++) {
        if (p[i] > p[id] + val) return false;
    }

    solver.init(n + m + 5);

    int maxm = p[id] + val;
    tot = 0;
    for (int i = 0; i < m; i++) {
        solver.AddEdge(S, i + 1, node[i].z);
        solver.AddEdge(i + 1, node[i].x + m, node[i].z);
        solver.AddEdge(i + 1, node[i].y + m, node[i].z);
        tot += node[i].z;
    }

    for (int i = 1; i <= n; i++) {
        solver.AddEdge(m + i, T, maxm - p[i]);
    }

    return solver.Maxflow(S, T) == tot;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int l = 0, r = 0;
    cin >> n >> id;
    for (int i = 1; i <= n; i++) { cin >> p[i]; }

    int x, y, z;

    //int cnt = 0;
    while (cin >> x >> y >> z) {
        if (z == 0) continue;
        node.pb({ x, y, z });
        if (x == id || y == id) r += z;
        //if (++cnt == 3) break;
    }

    //for (int i = 0; i < node.size(); i++) cout << node[i].x << ' ' << node[i].y << ' ' << node[i].z << endl;

    m = node.size();
    S = 0, T = n + m + 1;

    int ans = -1;
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (check(mid)) {
            ans = mid;
            r = mid;
        } else l = mid + 1;
    }

    if (ans == -1) cout << "Victory not possible\n";
    else cout << ans << '\n';
    return 0;
}
