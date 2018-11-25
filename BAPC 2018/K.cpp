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

const int N = 112345;

int n, h;
vector<int> G[N];
vector<int> leaf;
bool vis[N];

void dfs(int u, int fa) {
    if (G[u].size() == 1) leaf.pb(u);
    for (int v : G[u]) {
        if (v == fa) continue;
        dfs(v, u);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> h;
    if (n == 2) {
        cout << 1 << '\n';
        cout << 0 << ' ' << 1 << '\n';
        return 0;
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        G[u].pb(v);
        G[v].pb(u);
    }

    dfs(h, -1);
    int sz = leaf.size();
    cout << (sz + 1) / 2 << '\n';
    for (int i = 0; i < (sz + 1) / 2; i++) cout << leaf[i] << ' ' << leaf[i + sz / 2] << '\n';
    return 0;
}
