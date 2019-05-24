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
#include <complex>

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

const int N = 1123456;

int n, m;
vector<int> l[N], r[N];
pii a[N];
int vis[N];
int f[N], sz;

bool dfs(int u) {
    vis[u] = -1;
    for (int v : l[u]) {
        if (vis[v] == -1) return false;
        if (vis[v]) continue;
        if (!dfs(v)) return false;
    }

    f[sz--] = u;
    vis[u] = 1;
    return true;
}

vector<int> vec[N];
set<pii> s;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i]._1 >> a[i]._2;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        l[u].pb(v);
        r[v].pb(u);
    }

    sz = n;
    for (int i = 1; i <= n; i++) {
        if (!vis[i] && !dfs(i)) {
            cout << -1 << '\n';
            return 0;
        }
    }

    //for (int i = 1; i <= n; i++) cout << f[i] << endl;

    for (int i = 1; i <= n; i++) {
        int id = f[i];
        for (int v : l[id]) {
            a[v]._1 = max(a[v]._1, a[id]._1 + 1);
        }
    }

    for (int i = n; i >= 1; i--) {
        int id = f[i];
        for (int u : r[id]) {
            a[u]._2 = min(a[u]._2, a[id]._2 - 1);
        }
    }

    //for (int i = 1; i <= n; i++) cout << a[i]._1 << ' ' << a[i]._2 << endl;

    for (int i = 1; i <= n; i++) {
        if (a[i]._1 > a[i]._2) { cout << -1 << '\n'; return 0; }
        vec[a[i]._1].pb(i);
        vec[a[i]._2 + 1].pb(-i);
    }

    vector<int> ans;
    reset(vis, 0);
    for (int i = 1; i <= n; i++) {
        for (int id : vec[i]) {
            if (id < 0) {
                if (!vis[-id]) { cout << -1 << '\n'; return 0; }
            } else {
                s.insert({ a[id]._2, id });
            }
        }

        if (s.empty()) { cout << -1 << '\n'; return 0; }

        pii cur = *s.begin();
        s.erase(cur);
        int id = cur._2;
        vis[id] = true;
        ans.pb(id);
    }

    for (auto it : ans) cout << it << '\n';
    return 0;
}
