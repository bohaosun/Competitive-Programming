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

const int N = 212345;
const int M = 1123456;
const int R = 1000000;

int n, fa[N];
LL T, x[N], t[N], l[N];
vector<pll> G[N];

LL val[N];

LL ct[M], cnum[M];

int lowbit(int x) { return x & (-x); }

void update_t(int pos, LL val) {
    while (pos <= R) {
        ct[pos] += val;
        pos += lowbit(pos);
    }
}

void update_num(int pos, LL val) {
    while (pos <= R) {
        cnum[pos] += val;
        pos += lowbit(pos);
    }
}

LL sum_num(int pos) {
    LL ans = 0;
    while (pos) {
        ans += cnum[pos];
        pos -= lowbit(pos);
    }
    return ans;
}

LL sum_t(int pos) {
    LL ans = 0;
    while (pos) {
        ans += ct[pos];
        pos -= lowbit(pos);
    }
    return ans;
}

int cal_pos(LL tim) {
    int l = 0, r = R + 1;
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (sum_t(mid) <= tim) l = mid + 1;
        else r = mid;
    }
    return l;
}

void cal_val(int u, LL tot) {
    //cout << u << endl;
    LL tim = T - tot;

    if (tim < 0) return;
    update_t(t[u], x[u] * t[u]);
    update_num(t[u], x[u]);

    int pos = cal_pos(tim);
    if (pos) {
        val[u] = sum_num(pos - 1);
        LL cur = sum_num(pos) - sum_num(pos - 1);
        val[u] += min(cur, (tim - sum_t(pos - 1)) / pos);
    }

    for (pll v : G[u]) {
        cal_val(v._1, tot + v._2 * 2);
    }
    update_t(t[u], -x[u] * t[u]);
    update_num(t[u], -x[u]);
}

LL dfs(int u) {
    LL maxm = val[u], maxm2 = val[u];
    for (pll v : G[u]) {
        LL cur = dfs(v._1);
        if (cur > maxm) {
            maxm2 = maxm;
            maxm = cur;
        } else if (cur > maxm2) {
            maxm2 = cur;
        }
    }

    if (u == 1) return maxm;
    return maxm2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> T;
    for (int i = 1; i <= n; i++) cin >> x[i];
    for (int i = 1; i <= n; i++) cin >> t[i];
    for (int i = 2; i <= n; i++) {
        cin >> fa[i] >> l[i];
        G[fa[i]].pb({ i, l[i] });
        //cout << i << endl;
    }

    cal_val(1, 0);


    //for (int i = 1; i <= n; i++) cout << val[i] << endl;

    cout << dfs(1) << '\n';
    return 0;
}
