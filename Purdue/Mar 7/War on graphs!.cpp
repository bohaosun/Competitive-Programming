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

const int N = 11234;

vector<int> G[N];
int n, sz[N];

void cal_sz(int u, int fa) {
    sz[u] = 1;
    for (int v : G[u]) {
        if (v != fa) {
            cal_sz(v, u);
            sz[u] += sz[v];
        }
    }
}

vector<int> vec;

pll dfs(int u, int size, int fa) {
    int sum = 0;
    vec.clear();
    for (int v : G[u]) {
        if (v != fa) vec.pb(sz[v]);
    }
    if (size) vec.pb(size);

    sort(all(vec));
    reverse(all(vec));

    pll ans(0, 0);
    for (int it : vec) {
        ans._1 += it * sum;
        sum += it;
    }

    //cout << u << ' ' << sum << ' ' << size << endl;

    if (vec.size() > 1) ans._2 = ans._1 - vec[0] * vec[1];

    for (int v : G[u]) {
        if (v != fa) ans = max(ans, dfs(v, sum + 1 - sz[v], u));
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        G[x].pb(y);
        G[y].pb(x);
    }

    cal_sz(0, -1);

    //for (int i = 0; i <= n; i++) cout << sz[i] << endl;

    pll ans = dfs(0, 0, -1);
    cout << ans._1 << ' ' << ans._2 << '\n';

    return 0;
}
