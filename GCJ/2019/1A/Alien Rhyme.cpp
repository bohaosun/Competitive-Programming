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

const int max_node = 51234;
const int sigma_size = 26 + 5;

int ans;

struct Trie {
    int ch[max_node][sigma_size], val[max_node], sz;
    void init() { sz = 1; reset(ch[0], 0); }

    int idx(char c) { return c - 'A'; }

    void insert(string &s, int v) {  // Assume v != 0.
        int u = 0, n = s.length();
        for(int i = 0; i < n; i++) {
            int c = idx(s[i]);
            if(!ch[u][c]) {
                memset(ch[sz], 0, sizeof(ch[sz]));
                val[sz] = 0;
                ch[u][c] = sz++;
            }
            u = ch[u][c];
        }
        val[u] += v;
    }

    int dfs(int u) {
        int tot = val[u];
        for (int i = 0; i < 26; i++) {
            if (ch[u][i]) tot += dfs(ch[u][i]);
        }

        if (u == 0) return 0;
        if (tot >= 2) {
            tot -= 2;
            ans += 2;
        }
        return tot;
    }
};

Trie solver;
int n;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int kase = 1; kase <= T; kase++) {
        cout << "Case #" << kase << ": ";
        solver.init();

        ans = 0;
        cin >> n;
        for (int i = 0; i < n; i++) {
            string s;
            cin >> s;
            reverse(all(s));
            solver.insert(s, 1);
        }

        solver.dfs(0);
        cout << ans << '\n';
    }
    return 0;
}
