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
#include <iomanip>

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

const int N = 12345;
const int INF = int(1e9);

vector<pii> G[N];
int n, k, ans;

bool center[N];
int sz[N];

int get_size(int u, int fa) {
    sz[u] = 1;

    for (int i = 0; i < G[u].size(); i++) {
        pii& v = G[u][i];
        if (v._1 != fa && !center[v._1]) {
            sz[u] += get_size(v._1, u);
        }
    }
    return sz[u];
}

pii get_root(int u, int fa, int cur_sz) {
    pii ans(INF, 0);
    int size = 0, sum = 1;

    for (int i = 0; i < G[u].size(); i++) {
        pii& v = G[u][i];
        if (v._1 != fa && !center[v._1]) {
            ans = min(ans, get_root(v._1, u, cur_sz));
            size = max(size, sz[v._1]);
            sum += sz[v._1];
        }
    }
    size = max(size, cur_sz - sum);
    ans = min(ans, mp(size, u));
    return ans;
}

void get_dis(int u, int fa, int d, vector<int>& dis) {
    dis.pb(d);
    for (int i = 0; i < G[u].size(); i++) {
        pii& v = G[u][i];
        if (v._1 != fa && !center[v._1] && d + v._2 <= k) {
            get_dis(v._1, u, d + v._2, dis);
        }
    }
}

int cnt_pair(vector<int>& dis) {
    sort(all(dis));
    int ret = 0;
    for (int i = 0, j = dis.size() - 1; i < dis.size(); i++) {
        while (j >= 0 && dis[i] + dis[j] > k) j--;
        if (j < 0) break;
        if (j < i) ret += j + 1;
        else ret += j;
    }
    return ret / 2;
}

void solve(int u) {
    get_size(u, 0);
    int root = get_root(u, 0, sz[u])._2;  // Important!!! Put sz[u] inside.
    //cout << root << endl;
    center[root] = true;

    for (int i = 0; i < G[root].size(); i++) {
        pii& v = G[root][i];
        if (!center[v._1]) solve(v._1);
    }

    vector<int> dis;
    dis.pb(0);

    for (int i = 0; i < G[root].size(); i++) {
        pii& v = G[root][i];
        if (!center[v._1] && v._2 <= k) {
            vector<int> s_dis;
            get_dis(v._1, root, v._2, s_dis);
            ans -= cnt_pair(s_dis);
            dis.insert(dis.end(), s_dis.begin(), s_dis.end());
        }
    }

    ans += cnt_pair(dis);
    center[root] = false;
}

int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(0);

    while (scanf("%d%d", &n, &k) && n) {
        ans = 0;
        for (int i = 1; i <= n; i++) G[i].clear();
        for (int i = 0; i < n - 1; i++) {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            G[x].pb({ y, z });
            G[y].pb({ x, z });
        }

        solve(1);
        printf("%d\n", ans);
    }
    return 0;
}
