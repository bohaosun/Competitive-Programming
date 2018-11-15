/*
 * Not easy to code.
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

const int N = 1000;
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

    void Mincut(vector<int>& ans) {
        BFS();
        for(int i = 0; i < m; i++) {
            Edge& e = edges[i];
            if(vis[e.from] && !vis[e.to] && e.cap > 0) ans.push_back(i);
        }
    }

};

int n, m;
Dinic solver;
vector<pair<int, pii> > ppl;
vector<int> tim;

int my_find(int val) {
    int l = 0, r = tim.size();
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (tim[mid] < val) l = mid + 1;
        else r = mid;
    }
    return l;
}

vector<pii> supply[N];
vector<pii> ans[N];

void print() {
    for (int i = 0; i < tim.size() - 1; i++) supply[i].clear();
    for (int i = 0; i < n; i++) ans[i].clear();
    for (int i = 0; i < solver.m; i += 2) {
        int u = solver.edges[i].from, v = solver.edges[i].to, f = solver.edges[i].flow;
        if (u < tim.size() && v >= tim.size() && f) supply[u].pb({ v - tim.size(), f });
    }

    for (int i = 0; i < tim.size() - 1; i++) {
        int cur = tim[i], upp = tim[i + 1];
        for (int j = 0; j < supply[i].size(); j++) {
            int rem = supply[i][j]._2, id = supply[i][j]._1;
            if (rem <= upp - cur) {
                ans[id].pb(mp(cur, cur + rem));
                cur += rem;
            } else {
                ans[id].pb(mp(cur, upp));
                rem -= upp - cur;
                cur = tim[i] + rem;
                ans[id].pb(mp(tim[i], cur));
            }
            if (cur == upp) cur = tim[i];
        }
    }

    for (int i = 0; i < n; i++) {
        sort(all(ans[i]));
        int cur = 0;
        for (int j = 1; j < ans[i].size(); j++) {
            if (ans[i][j]._1 == ans[i][cur]._2) ans[i][cur]._2 = ans[i][j]._2;
            else ans[i][++cur] = ans[i][j];
        }
        cout << cur + 1;
        for (int j = 0; j <= cur; j++) cout << " (" << ans[i][j]._1 << ',' << ans[i][j]._2 << ')';
        cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int kase = 0;
    while (cin >> n && n) {
        cin >> m;
        ppl.clear();
        tim.clear();
        for (int i = 0; i < n; i++) {
            int x, y, z;
            cin >> x >> y >> z;
            ppl.pb(mp(x, mp(y, z)));
            tim.pb(y); tim.pb(z);
        }

        sort(all(tim));
        uni(tim);


        solver.init(n + 5 + tim.size());
        int s = n + tim.size();
        int t = s + 1;
        for (int i = 0; i < tim.size() - 1; i++) solver.AddEdge(s, i, m * (tim[i + 1] - tim[i]));
        int tot = 0;
        for (int i = 0; i < n; i++) {
            int l = my_find(ppl[i]._2._1), r = my_find(ppl[i]._2._2);
            for (int j = l; j < r; j++) solver.AddEdge(j, i + tim.size(), tim[j + 1] - tim[j]);
            tot += ppl[i]._1;
            solver.AddEdge(i + tim.size(), t, ppl[i]._1);
        }

        cout << "Case " << ++kase << ": ";
        if (solver.Maxflow(s, t) < tot) cout << "No\n";
        else {
            cout << "Yes\n";
            print();
        }
    }
    return 0;
}
