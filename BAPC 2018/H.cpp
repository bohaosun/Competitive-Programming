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

const int N = 212345;
const LL INF = LL(1e18);

vector<pii> G[N];
int n, m, in[N], s, t;
LL d[N][2];

struct Node {
    int u;
    LL d;
    bool operator < (const Node& rhs) const {
        return d > rhs.d;
    }
};

int upd[N];
bool vis[N];

void solve() {
    for (int i = 0; i < n; i++) d[i][0] = INF;
    d[t][0] = 0;

    queue<int> q;
    priority_queue<Node> pq;
    q.push(t);
    pq.push({ t, 0 });

    while (!q.empty() || !pq.empty()) {
        if (!q.empty()) {
            int u = q.front(); q.pop();
            vis[u] = true;
            for (int i = 0; i < G[u].size(); i++) {
                int v = G[u][i]._1, w = G[u][i]._2;
                if (d[u][1] + w < d[v][0]) {
                    d[v][0] = d[u][1] + w;
                    pq.push({ v, d[v][0] });
                }
            }
        } else {
            Node u = pq.top(); pq.pop();
            if (d[u.u][0] < u.d) continue;
            for (int i = 0; i < G[u.u].size(); i++) {
                int v = G[u.u][i]._1, w = G[u.u][i]._2;
                upd[v]++;
                d[v][1] = max(d[v][1], d[u.u][0] + w);
                if (in[v] == upd[v]) q.push(v);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> s >> t;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        G[v].pb({ u, w });
        in[u]++;
    }

    solve();
    if (vis[s]) cout << d[s][1] << '\n';
    else cout << "infinity\n";
    return 0;
}
