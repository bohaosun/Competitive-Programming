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

const int N = 2123;
const int INF = int(1e9);

int n, m, g;
int dp[N][N];
bool sun[N];
int pos[N], p[N];

vector<int> vec[N];

int solve(int loc, int gla) {
    if (loc == n) return 0;

    int &ans = dp[loc][gla];
    if (ans > -1) return ans;
    ans = INF;

    if (sun[loc]) {
        if (gla) ans = min(ans, solve(loc + 1, gla) + p[gla]);
    } else {
        ans = min(ans, solve(loc + 1, gla) + p[gla]);
        ans = min(ans, solve(loc + 1, 0));
    }

    for (int u : vec[loc]) {
        ans = min(ans, solve(loc + 1, u) + p[u]);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> g;
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        for (int j = l; j < r; j++) sun[j] = true;
    }

    for (int i = 1; i <= g; i++) {
        cin >> pos[i] >> p[i];
        vec[pos[i]].pb(i);

    }
    reset(dp, -1);

    int ans = solve(0, 0);
    if (ans >= INF) cout << -1 << '\n';
    else cout << ans << '\n';
    return 0;
}
