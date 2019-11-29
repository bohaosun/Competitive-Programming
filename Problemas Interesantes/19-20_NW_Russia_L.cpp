#include <bits/stdc++.h>

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

const int MAXLEN = 212345;
const int INF = int(1e9);

struct State {
    int len, link;
    int minm = INF;
    map<char, int> next;
    set<int> app;
} st[MAXLEN * 2];

int sz, last;

void sa_init() {
    //st[0].len = 0;
    st[0].link = -1;
    //st[0].next.clear();
    sz = 1;
    //last = 0;
}

void sa_extend(int pos, char c) {
    int cur = sz++;
    //st[cur].next.clear();
    st[cur].len = st[last].len + 1;
    st[cur].app.insert(pos);
    int p = last;
    while (p != -1 && !st[p].next.count(c)) {
        st[p].next[c] = cur;
        p = st[p].link;
    }

    if (p == -1) {
        st[cur].link = 0;
    } else {
        int q = st[p].next[c];
        if (st[p].len + 1 == st[q].len) {
            st[cur].link = q;
        } else {
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            st[clone].next = st[q].next;
            st[clone].link = st[q].link;
            st[clone].app = st[q].app;
            while (p != -1 && st[p].next[c] == q) {
                st[p].next[c] = clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
}

vector<int> G[MAXLEN * 2];
string s;
pii ans(1, 1);

inline void check(pii &cur) {
    LL dem = LL(ans._2) * cur._2 / __gcd(ans._2, cur._2);
    if (dem / ans._2 * ans._1 < dem / cur._2 * cur._1) ans = cur;
}

vector<int> id;

void solve() {
    id.resize(sz - 1);
    for (int i = 1; i < sz; ++i) id[i - 1] = i;
    sort(all(id), [](const int a, const int b) { return st[a].len > st[b].len; });

    for (int i = 0; i < id.size(); ++i) {
        int u = id[i];
        for (int v : G[u]) {
            if (st[v].app.size() > st[u].app.size()) swap(st[u].app, st[v].app);
            st[u].minm = min(st[u].minm, st[v].minm);
            for (int val : st[v].app) {
                auto it = st[u].app.insert(val);
                if (it._1 != st[u].app.begin()) st[u].minm = min(st[u].minm, *it._1 - *prev(it._1));
                if (next(it._1) != st[u].app.end()) st[u].minm = min(st[u].minm, *next(it._1) - *it._1);
            }
        }
        if (st[u].minm == INF) continue;
        pii cur = mp(st[u].minm + st[u].len, st[u].minm);
        check(cur);
    }
}

void dfs(int u) {
    for (int v : G[u]) {
        dfs(v);
        if (st[v].app.size() > st[u].app.size()) swap(st[u].app, st[v].app);
        st[u].minm = min(st[u].minm, st[v].minm);
        for (auto val : st[v].app) {
            auto it = st[u].app.insert(val);
            if (it._1 != st[u].app.begin()) st[u].minm = min(st[u].minm, *it._1 - *prev(it._1));
            if (next(it._1) != st[u].app.end()) st[u].minm = min(st[u].minm, *next(it._1) - *it._1);
        }
    }
    if (u == 0) return;

    if (st[u].minm == INF) return;
    pii cur = mp(st[u].minm + st[u].len, st[u].minm);
    check(cur);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;
    sa_init();
    for (int i = 0; i < s.length(); ++i) {
        sa_extend(i + 1, s[i]);
    }

    for (int i = 1; i < sz; ++i) G[st[i].link].pb(i);

    solve();

    //dfs(0);

    int d = __gcd(ans._1, ans._2);
    cout << ans._1 / d << '/' << ans._2 / d << '\n';
    return 0;
}
