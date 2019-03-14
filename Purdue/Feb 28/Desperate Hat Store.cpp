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

const int N = 1123;

int n, m;
int h[N], p[N];
int x[N], y[N];

bool check[N];
int match[N];
vector<int> G[N];

bool dfs(int u) {
    for (int v : G[u]) {
        if (!check[v]) {
            check[v] = true;
            if (match[v] == -1 || dfs(match[v])) {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> h[i] >> p[i];
    for (int i = 1; i <= m; i++) cin >> x[i] >> y[i];

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (x[j] > h[i] && y[j] <= p[i]) G[i].pb(j);
        }
    }

    reset(match, -1);
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        reset(check, 0);
        if (dfs(i)) cnt++;
    }

    cout << cnt << '\n';
    return 0;
}
