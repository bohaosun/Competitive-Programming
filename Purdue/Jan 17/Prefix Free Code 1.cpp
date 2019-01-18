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

const int max_node = 1123456;
const int sigma_size = 26 + 5;
const int MOD = int(1e9) + 7;

struct Trie {
    int ch[max_node][sigma_size], val[max_node], sz;
    void init() { sz = 1; memset(ch[0], 0, sizeof(ch[0])); }

    int idx(char c) { return c - 'a'; }

    void insert(string &s, int v) {  // Assume v != 0.
        int u = 0;
        int n = s.length();
        for(int i = 0; i < n; i++) {
            int c = idx(s[i]);
            if(!ch[u][c]) {
                memset(ch[sz], 0, sizeof(ch[sz]));
                val[sz] = 0;
                ch[u][c] = sz++;
            }
            u = ch[u][c];
        }
        val[u] = v;
    }
};

string s[max_node], q;
int n, k;
Trie solver;

LL perm[max_node];

LL inv(LL x) {
    int pw = MOD - 2;
    LL ans = 1;
    while (pw) {
        if (pw & 1) ans = ans * x % MOD;
        x = x * x % MOD;
        pw >>= 1;
    }
    return ans;
}

LL A(int a, int b) {
    return perm[a] * inv(perm[a - b]) % MOD;
}

vector<int> vec;

void query() {
    int pos = 0;
    for (int i = 0; i < k; i++) {
        int u = 0;
        while (pos < q.length()) {
            int c = solver.idx(q[pos++]);
            u = solver.ch[u][c];
            if (solver.val[u]) { vec.pb(solver.val[u]); break; }
        }
    }
    assert(vec.size() == k);
}

LL c[max_node];

int lowbit(int x) { return x & (-x); }

LL sum(int pos) {
    LL ans = 0;
    while (pos) {
        ans += c[pos];
        pos -= lowbit(pos);
    }
    return ans;
}

void add(int pos, int val) {
    while (pos < max_node) {
        c[pos] += val;
        pos += lowbit(pos);
    }
}

LL solve() {
    LL ans = 1;
    for (int i = 1; i <= n; i++) add(i, 1);
    for (int i = 0; i < k; i++) {
        LL rem = sum(vec[i] - 1);
        ans = (ans + (rem * A(n - i - 1, k - i - 1) % MOD)) % MOD;
        add(vec[i], -1);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // preprocess:
    perm[0] = 1;
    for (int i = 1; i <= 1000000; i++) perm[i] = perm[i - 1] * i % MOD;

    solver.init();

    cin >> n >> k;
    for (int i = 0; i < n; i++) cin >> s[i];
    sort(s, s + n);
    for (int i = 0; i < n; i++) {
        solver.insert(s[i], i + 1);
    }

    cin >> q;
    query();
    cout << solve() << '\n';
    return 0;
}
