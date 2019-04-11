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
#define uni(x) (x).erase(unique(all(x)), (x).end())
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

const int N = 212345;

int n, m, q, p[N], a[N];
int f[N], g[N], last[N];
vector<int> loc[N];
int maxm[N];

int my_find(int id, int val) {
    int l = 0, r = loc[id].size();

    while (l < r) {
        int mid = l + (r - l) / 2;
        int x = loc[id][mid];
        if (f[x] > val) r = mid;
        else l = mid + 1;
    }

    if (l == loc[id].size()) return m + 1;
    else return loc[id][l];
}

int tmin[N * 4];

void build(int o, int l, int r) {
    if (l == r) tmin[o] = maxm[l];
    else {
        int mid = l + (r - l) / 2;
        build(o * 2, l, mid);
        build(o * 2 + 1, mid + 1, r);
        tmin[o] = min(tmin[o * 2], tmin[o * 2 + 1]);
    }
}

const int INF = int(1e9);

int query(int o, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        return tmin[o];
    } else {
        int mid = l + (r - l) / 2;
        int lmax = INF, rmax = INF;
        if (ql <= mid) lmax = query(o * 2, l, mid, ql, qr);
        if (qr > mid) rmax = query(o * 2 + 1, mid + 1, r, ql, qr);
        return min(lmax, rmax);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        p[x] = i;
    }

    for (int i = 1; i <= m; i++) {
        cin >> a[i];
        a[i] = p[a[i]];
        loc[a[i]].pb(i);
    }

    //for (int i = 1; i <= m; i++) cout << a[i] << ' ';
    //cout << endl;

    for (int i = 1; i <= n; i++) sort(all(loc[i]));

    for (int i = 1; i <= m; i++) {
        last[a[i]] = i;
        if (a[i] == 1) f[i] = i;
        else f[i] = f[last[a[i] - 1]];
    }

    for (int i = 1; i <= n; i++) last[i] = m + 1;
    g[m + 1] = m + 1;

    for (int i = m; i >= 1; i--) {
        last[a[i]] = i;
        if (a[i] == n) g[i] = i;
        else g[i] = g[last[a[i] + 1]];
    }

    //for (int i = 1; i <= m; i++) cout << f[i] << ' ' << g[i] << endl;


    for (int i = 1; i <= m; i++) {
        if (a[i] == 1) maxm[i] = g[i];
        else maxm[i] = my_find(a[i] - 1, g[i]);
    }

    //for (int i = 1; i <= m; i++) cout << maxm[i] << ' ';
    //cout << endl;

    build(1, 1, m);
    string ans;
    while (q--) {
        int l, r;
        cin >> l >> r;
        if (query(1, 1, m, l, r) <= r) ans.pb('1');
        else ans.pb('0');
    }

    cout << ans << '\n';
    return 0;
}
