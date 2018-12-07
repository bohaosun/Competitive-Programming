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

const int N = 250 + 10;
const int Q = 251234;

int n, m, a[N][N], ans[Q];

struct Query {
    int r, c, s, k;
};
vector<Query> query;
vector<int> q;
vector<pair<int, pii > > triple;

int c[N][N];

int lowbit(int x) { return x & (-x); }

int sum(int i, int j) {
    int ret = 0, from = j;
    while (i) {
        j = from;
        while (j) {
            ret += c[i][j];
            j -= lowbit(j);
        }
        i -= lowbit(i);
    }
    return ret;
}

void add(int i, int j, int d) {
    int from = j;
    while (i <= n) {
        j = from;
        while (j <= n) {
            c[i][j] += d;
            j += lowbit(j);
        }
        i += lowbit(i);
    }
}

void solve(int l, int r, vector<int>& q) {
    if (q.empty() || triple[l]._1 == triple[r]._1) {
        for (int it : q) ans[it] = triple[l]._1;
        return;
    }

    int mid = (l + r) >> 1;
    vector<int> ql, qr;

    reset(c, 0);
    for (int i = l; i <= mid; i++) add(triple[i]._2._1, triple[i]._2._2, 1);
    for (auto it : q) {
        int cur = sum(query[it].r + query[it].s - 1, query[it].c + query[it].s - 1);
        cur -= sum(query[it].r + query[it].s - 1, query[it].c - 1);
        cur -= sum(query[it].r - 1, query[it].c + query[it].s - 1);
        cur += sum(query[it].r - 1, query[it].c - 1);

        if (query[it].k <= cur) ql.pb(it);
        else {
            query[it].k -= cur;
            qr.pb(it);
        }
    }
    solve(l, mid, ql);
    solve(mid + 1, r, qr);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) cin >> a[i][j];

    cin >> m;
    for (int i = 1; i <= m; i++) {
        int r, c, s, k;
        cin >> r >> c >> s >> k;
        query.pb({ r, c, s, k });
        q.pb(i - 1);
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) triple.pb(mp(a[i][j], mp(i, j)));
    sort(all(triple));

    solve(0, n * n - 1, q);
    for (int i = 0; i < m; i++) cout << ans[i] << '\n';
    return 0;
}
