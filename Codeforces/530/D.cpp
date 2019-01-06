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

const int N = 212345;
const LL INF = LL(1e15);

LL a[N], s[N], fa[N], minm[N];
int n;
vector<int> G[N];

LL get_minm(int u) {
    minm[u] = INF;
    if (s[u] > -1) minm[u] = s[u];

    for (int v : G[u]) {
        minm[u] = min(minm[u], get_minm(v));
    }
    return minm[u];
}

void dfs(int u, LL tot) {
    if (G[u].empty()) {
        if (s[u] > -1) {
            a[u] = s[u] - tot;
        }
        return;
    }
    a[u] = minm[u] - tot;
    for (int v : G[u]) dfs(v, minm[u]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 2; i <= n; i++) { cin >> fa[i]; G[fa[i]].pb(i); }
    for (int i = 1; i <= n; i++) cin >> s[i];

    get_minm(1);
    for (int i = 1; i <= n; i++) {
        if (s[i] == -1) continue;
        if (s[i] > minm[i]) { cout << -1 << '\n'; return 0; }
    }

    dfs(1, 0);
    LL ans = 0;
    for (int i = 1; i <= n; i++) ans += a[i];
    cout << ans << '\n';
    return 0;
}
