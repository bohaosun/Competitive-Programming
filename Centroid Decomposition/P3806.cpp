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

const int N = 11234;
const int INF = int(1e9);

int n, m;
vector<pii> G[N];
int sz[N], q[N], ans[N];
bool centroid[N];

int get_sz(int u, int fa) {
    sz[u] = 1;
    for (pii v : G[u])
        if (v._1 != fa && !centroid[v._1]) {
            sz[u] += get_sz(v._1, u);
        }
    return sz[u];
}

pii get_root(int u, int fa, int tot_sz) {
    pii ans(INF, 0);
    int sum = 1, max_sz = 0;
    for (pii v : G[u])
        if (v._1 != fa && !centroid[v._1]) {
            max_sz = max(max_sz, sz[v._1]);
            sum += sz[v._1];
            ans = min(ans, get_root(v._1, u, tot_sz));
        }
    max_sz = max(max_sz, tot_sz - sum);
    ans = min(ans, { max_sz, u });
    return ans;
}

void get_dis(int u, int fa, int cur, vector<int>& dis) {
    dis.pb(cur);
    for (pii v : G[u]) {
        if (v._1 != fa && !centroid[v._1]) get_dis(v._1, u, cur + v._2, dis);
    }
}

void judge(vector<int>& dis, int d) {
    set<int> s;
    for (int u : dis) {
        for (int i = 0; i < m; i++) {
            if (s.count(q[i] - u)) ans[i] += d;
        }
        s.insert(u);
    }
}

void solve(int u) {
    get_sz(u, 0);
    int root = get_root(u, 0, sz[u])._2;
    centroid[root] = true;

    for (pii v : G[root]) {
        if (!centroid[v._1]) solve(v._1);
    }

    vector<int> dis;
    dis.pb(0);
    for (pii v : G[root]) {
        vector<int> cur_dis;
        if (!centroid[v._1]) get_dis(v._1, root, v._2, cur_dis);
        judge(cur_dis, -1);
        dis.insert(dis.end(), all(cur_dis));
    }

    judge(dis, 1);

    centroid[root] = false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < n - 1; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        G[x].pb({ y, w });
        G[y].pb({ x, w });
    }

    for (int i = 0; i < m; i++) cin >> q[i];

    solve(1);

    for (int i = 0; i < m; i++) {
        if (ans[i]) cout << "AYE\n";
        else cout << "NAY\n";
    }
    return 0;
}
