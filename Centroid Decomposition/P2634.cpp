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

const int N = 21234;
const int INF = int(1e9);

int n, cnt, sz[N];
bool centroid[N];
vector<pii> G[N];

int get_sz(int u, int fa) {
    sz[u] = 1;
    for (pii v : G[u]) {
        if (v._1 != fa && !centroid[v._1]) sz[u] += get_sz(v._1, u);
    }
    return sz[u];
}

pii get_root(int u, int fa, int tot_sz) {
    int sum = 1;
    int max_sz = 0;
    pii ans(INF, 0);

    for (pii v : G[u]) {
        if (v._1 != fa && !centroid[v._1]) {
            sum += sz[v._1];
            max_sz = max(max_sz, sz[v._1]);
            ans = min(ans, get_root(v._1, u, tot_sz));
        }
    }
    max_sz = max(max_sz, tot_sz - sum);
    ans = min(ans, mp(max_sz, u));
    return ans;
}

void get_dis(int u, int fa, int cur, vector<int>& dis) {
    dis.pb(cur);
    for (pii v : G[u]) {
        if (v._1 != fa && !centroid[v._1]) get_dis(v._1, u, cur + v._2, dis);
    }
}

void my_stat(vector<int>& dis, int sym) {
    int cur[3] = { 0, 0, 0 };
    for (int u : dis) cur[u % 3]++;
    //cout << dis.size() << ' ' << cur[0] << ' ' << cur[1] << ' ' << cur[2] << endl;
    cnt += sym * cur[0] * (cur[0] - 1);
    cnt += sym * 2 * cur[1] * cur[2];
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
        if (!centroid[v._1]) {
            vector<int> s_dis;
            get_dis(v._1, root, v._2, s_dis);
            my_stat(s_dis, -1);
            dis.insert(dis.end(), all(s_dis));
        }
    }
    my_stat(dis, 1);
    centroid[root] = false;
}

int gcd(int a, int b) { return !b ? a : gcd(b, a % b); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        w %= 3;
        G[x].pb({ y, w });
        G[y].pb({ x, w });
    }

    solve(1);
    cnt += n;
    int d = gcd(cnt, n * n);
    cout << cnt / d << '/' << n * n / d << '\n';
    return 0;
}
