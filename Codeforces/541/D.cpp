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
#define uni(x) (x).erase(unique(all(x)), (x).end());
#define reset(x, y) memset(x, y, sizeof(x))
#define BUG(x) cerr << #x << " = " << (x) << endl
#define BUGP(x) cout << #x << " = " << (x)._1 << ", " << (x)._2 << endl
using namespace std;

typedef long long LL;
typedef pair<int, int> pii;
typedef pair<LL, LL> pll;
// Head

const int N = 1123 * 2;

int n, m;
int fa[N];
string s[N];
vector<int> G[N];
vector<int> order;
int vis[N];
int val[N];

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

bool dfs(int u) {
    vis[u] = -1;
    for (int v : G[u]) {
        if (vis[v] == -1) return false;
        if (!vis[v] && !dfs(v)) return false;
    }
    order.pb(u);
    vis[u] = 1;
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> s[i];
    for (int i = 0; i < n + m; i++) fa[i] = i;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (s[i][j] == '=') {
                int x = find(i);
                int y = find(j + n);
                fa[x] = y;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        int x = find(i);
        for (int j = 0; j < m; j++) {
            if (s[i][j] == '>') {
                G[x].pb(find(j + n));
            } else if (s[i][j] == '<') {
                G[find(j + n)].pb(x);
            }
        }
    }

    for (int i = 0; i < n + m; i++) {
        sort(all(G[i]));
        uni(G[i]);
    }

    for (int i = 0; i < n + m; i++) {
        int x = find(i);
        if (x != i) continue;
        if (!vis[x] && !dfs(x)) { cout << "No\n"; return 0; }
    }

    reset(vis, 0);
    for (auto u : order) {
        int cur = 1;
        for (int v : G[u]) {
            if (vis[v]) cur = max(cur, val[v] + 1);
        }
        val[u] = cur;
        vis[u] = 1;
    }

    cout << "Yes\n";
    for (int i = 0; i < n; i++) cout << val[find(i)] << ' ';
    cout << '\n';
    for (int i = n; i < n + m; i++) cout << val[find(i)] << ' ';
    cout << '\n';
    return 0;
}
