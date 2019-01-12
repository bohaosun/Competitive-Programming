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

int pvis[N];

int n, a[N];
vector<int> G[N];

int h[N], dp[N];

int dfs(int u, int fa, int val, int height) {
    h[u] = height;
    a[u] /= val;
    dp[u] = 1;

    int maxm1 = height, maxm2 = height;

    for (int v : G[u]) {
        if (v != fa) {
            if (a[v] % val) continue;
            int cur = dfs(v, u, val, height + 1);

            dp[u] = max(dp[u], dp[v]);
            if (cur > maxm1) { maxm2 = maxm1; maxm1 = cur; }
            else if (cur > maxm2) { maxm2 = cur; }
        }
    }

    if (maxm2 > height) {
        dp[u] = max(dp[u], maxm1 + maxm2 - height * 2 + 1);
    } else if (maxm1 > height) {
        dp[u] = max(dp[u], maxm1 - height + 1);
    }
    return maxm1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int m = sqrt(200000 + 0.5);
    for (int i = 2; i <= m; i++) if (!pvis[i]) {
        for (int j = i * i; j <= 200000; j += i) pvis[j] = i;
    }

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        G[x].pb(y);
        G[y].pb(x);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        while (pvis[a[i]]) {
            dfs(i, -1, pvis[a[i]], 0);
            ans = max(ans, dp[i]);
        }

        if (a[i] > 1) {
            dfs(i, -1, a[i], 0);
            ans = max(ans, dp[i]);
        }
    }
    cout << ans << '\n';
    return 0;
}
