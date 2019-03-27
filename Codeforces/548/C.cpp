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

const int dr[] = {-1, 0, 1, 0, -1, -1, 1, 1};
const int dc[] = {0, -1, 0, 1, -1, 1, -1, 1};
// Head

const int MOD = int(1e9) + 7;
const int N = 112345;

LL pw[N][105];
int n, k;
vector<int> G[N];
bool vis[N];
int tot;

void dfs(int u) {
    ++tot;
    vis[u] = true;
    for (int v : G[u]) {
        if (!vis[v]) dfs(v);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        pw[i][0] = 1;
        for (int j = 1; j <= k; j++) pw[i][j] = pw[i][j - 1] * i % MOD;
    }

    for (int i = 0; i < n - 1; i++) {
        int x, y, val;
        cin >> x >> y >> val;
        if (val == 1) continue;
        G[x].pb(y);
        G[y].pb(x);
    }

    LL ans = 0;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            tot = 0;
            dfs(i);
            ans = (ans + pw[tot][k]) % MOD;
        }
    }

    cout << (pw[n][k] - ans + MOD) % MOD << '\n';
    return 0;
}
