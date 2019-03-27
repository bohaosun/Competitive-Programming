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

const int N = 5123;

int m, n, p[N], c[N], t[N];
vector<int> G[N];
bool d[N][N];  // d[potential][club]
bool app[N];

int match[N];
bool check[N];

bool dfs(int u) {
    if (check[u]) return false;
    check[u] = true;
    for (int v : G[u]) {
        if (match[v] == -1 || dfs(match[v])) {
            match[v] = u;
            return true;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> p[i];
    for (int i = 1; i <= n; i++) cin >> c[i];

    int day;
    cin >> day;
    for (int i = 1; i <= day; i++) { cin >> t[i]; app[t[i]] = true; }
    for (int i = 1; i <= n; i++) {
        if (!app[i]) {
            d[p[i]][c[i]] = true;
            G[p[i]].pb(c[i]);
        }
    }

    vector<int> ans;
    int cur = 0;
    reset(match, -1);

    for (int i = day; i >= 1; i--) {
        for (;;) {
            reset(check, 0);
            if (!dfs(cur)) break;
            ++cur;
        }
        ans.pb(cur);

        int id = t[i];
        if (!d[p[id]][c[id]]) {
            d[p[id]][c[id]] = true;
            G[p[id]].pb(c[id]);
        }
    }

    reverse(all(ans));
    for (int i = 0; i < ans.size(); i++) cout << ans[i] << '\n';
    return 0;
}
