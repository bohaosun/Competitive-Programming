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

const int N = 30 + 5;

int n, m;
bool G[N][N], vis[N];
map<vector<int>, double> dp;

int dfs(int u) {
    vis[u] = true;
    int sz = 1;
    for (int i = 1; i <= n; i++) {
        if (G[u][i] && !vis[i]) sz += dfs(i);
    }
    return sz;
}

double solve(vector<int> &vec) {
    if (vec[0] == n) return 0;
    if (dp.count(vec)) return dp[vec];

    //for (int i = 0; i <= n; i++) cout << i << " " << vec[i] << endl;
    //cout << endl << endl;

    double &ans = dp[vec] = 1;
    vector<int> vec2 = vec;

    for (int i = 1; i <= n; i++) {
        if (vec[i] > 1 || (vec[i] == 1 && i != vec[0])) {
            vec2[i + vec[0]]++;
            vec2[i]--;
            vec2[vec[0]]--;
            vec2[0] = i + vec[0];

            if (i == vec[0]) {
                ans += solve(vec2) * (vec[i] - 1) * i / (n - 1);
            } else {
                ans += solve(vec2) * vec[i] * i / (n - 1);
            }

            vec2[i + vec[0]]--;
            vec2[i]++;
            vec2[vec[0]]++;
            vec2[0] = vec[0];
        }
    }

    ans = ans * (n - 1) / (n - vec[0]);
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed;
    cout.precision(8);

    int T;
    cin >> T;
    for (int kase = 1; kase <= T; kase++) {
        reset(G, 0);
        reset(vis, 0);
        dp.clear();
        cin >> n >> m;
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            G[a][b] = G[b][a] = true;
        }

        vector<int> vec(n + 1);
        int loc = 0;
        for (int i = 1; i <= n; i++) {
            if (!vis[i]) {
                int cur = dfs(i);
                if (i == 1) loc = cur;
                vec[cur]++;
            }
        }
        vec[0] = loc;

        cout << "Case " << kase << ": ";
        cout << solve(vec) << '\n';
    }
    return 0;
}
