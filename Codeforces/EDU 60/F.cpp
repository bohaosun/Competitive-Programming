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
typedef pair <LL, LL> pll;
// Head

const int N = 112345;
const int P = 17 + 1;

int n, p, a[P][P];
string s;
int invalid[1 << P], len[1 << P];
int cnt[P];
bool vis[1 << P];

int id(char c) { return c - 'a'; }

void make_invalid(int mask, int a, int b) {
    //if (mask == 14) cout << a << ' ' << b << endl;
    invalid[mask] = true;
    vis[mask] = true;

    for (int i = 0; i < p; i++) {
        if (((1 << i) & mask) && i != a && i != b && !vis[mask ^ (1 << i)]) make_invalid(mask ^ (1 << i), a, b);
    }
}

void dfs(int mask, int &minm) {
    minm = min(minm, len[mask]);
    vis[mask] = true;
    for (int i = 0; i < p; i++) {
        if (((1 << i) & mask) && !invalid[mask ^ (1 << i)] && !vis[mask ^ (1 << i)]) dfs(mask ^ (1 << i), minm);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> p >> s;
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < p; j++) cin >> a[i][j];
    }

    int all = 0;
    for (int i = 0; i < s.length(); i++) {
        cnt[id(s[i])]++;
        all |= (1 << id(s[i]));
    }

    for (int mask = all; mask; mask = (mask - 1) & all) {
        for (int j = 0; j < p; j++) {
            if ((1 << j) & mask) len[mask] += cnt[j];
        }
    }

    for (int i = 0; i < p; i++) {
        if (!(all & (1 << i))) continue;
        for (int j = i + 1; j < p; j++) {
            if (!(all & (1 << j))) continue;
            if (a[i][j]) continue;

            reset(vis, 0);
            int last = -1, tot = 0;
            for (int k = 0; k < s.length(); k++) {
                int cur = id(s[k]);
                if (cur == i || cur == j) {
                    if (last != -1 && cur != last && !vis[all ^ tot]) make_invalid(all ^ tot, i, j);
                    last = cur;
                    tot = 0;
                } else tot |= (1 << cur);
            }
        }
    }

    for (int i = 0; i < p; i++) {
        if (!(all & (1 << i))) continue;
        if (a[i][i]) continue;

        reset(vis, 0);
        bool first = true;
        int tot = 0;
        for (int j = 0; j < s.length(); j++) {
            int cur = id(s[j]);
            if (cur == i) {
                if (!first && !vis[all ^ tot]) make_invalid(all ^ tot, i, i);
                first = false;
                tot = 0;
            } else tot |= (1 << cur);
        }
    }

    int minm = s.length();
    reset(vis, 0);
    dfs(all, minm);
    cout << minm << '\n';
    return 0;
}
