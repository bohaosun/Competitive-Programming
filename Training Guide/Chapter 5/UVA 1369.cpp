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

const int N = 1000 + 10;

int n, m, u[N], v[N];

struct Edge {
    int u, v;
};

bool cut[N];
int pre[N], bccno[N], dfs_clock, bcc_cnt;
vector<int> G[N], bcc[N];
stack<Edge> S;

int dfs(int u, int fa) {
    int lowu = pre[u] = ++dfs_clock;
    int child = 0;
    for(int i = 0; i < G[u].size(); i++) {
        int v =  G[u][i];
        Edge e = (Edge) { u, v };
        if(!pre[v]) {
            S.push(e);
            child++;
            int lowv = dfs(v, u);
            lowu = min(lowu, lowv);
            if(lowv >= pre[u]) {
                cut[u] = true;
                bcc_cnt++; bcc[bcc_cnt].clear();
                for(;;) {
                    Edge x = S.top(); S.pop();
                    if(bccno[x.u] != bcc_cnt) { bcc[bcc_cnt].push_back(x.u); bccno[x.u] = bcc_cnt; }
                    if(bccno[x.v] != bcc_cnt) { bcc[bcc_cnt].push_back(x.v); bccno[x.v] = bcc_cnt; }
                    if(x.u == u && x.v == v) break;
                }
            }
        } else if(pre[v] < pre[u] && v != fa) {
            S.push(e);
            lowu = min(lowu, pre[v]);
        }
    }
    if(fa < 0 && child == 1) cut[u] = false;
    return lowu;
}

void find_bcc(int n) {
    memset(pre, 0, sizeof(pre));
    memset(cut, 0, sizeof(cut));
    memset(bccno, 0, sizeof(bccno));
    dfs_clock = bcc_cnt = 0;
    for(int i = 1; i <= n; i++)
        if(!pre[i]) dfs(i, -1);
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) G[i].clear();
        for (int i = 0; i < m; i++) {
            cin >> u[i] >> v[i];
            if (u[i] > v[i]) swap(u[i], v[i]);
        }

        vector<int> vec;
        for (int i = 0; i < 4; i++) {
            int x;
            cin >> x;
            vec.pb(x);
        }

        sort(all(vec));
        uni(vec);

        int f;
        cin >> f;
        vector<pii> ban;
        for (int i = 0; i < f; i++) {
            int x, y;
            cin >> x >> y;
            if (x > y) swap(x, y);
            ban.pb({ x, y });
        }

        for (int i = 0; i < n; i++) {
            bool ok = true;
            for (int j = 0; j < ban.size(); j++)
                if (u[i] == ban[j]._1 && v[i] == ban[j]._2) { ok = false; break; }
            if (!ok) continue;
            G[u[i]].pb(v[i]);
            G[v[i]].pb(u[i]);
        }

        find_bcc(n);
        bool ok = false;
        for (int i = 1; i <= bcc_cnt; i++) {
            int cnt = 0;
            for (int j : vec)
                for (int k : bcc[i])
                    if (j == k) { cnt++; break; }
            if (cnt == vec.size()) { ok = true; break; }
        }
        if (ok) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}
