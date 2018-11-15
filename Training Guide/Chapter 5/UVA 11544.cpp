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

const int N = 1500 + 10;

int n, m, l[N], r[N], type[N];
vector<int> pref[N];

vector<int> G[N];

bool check[N];
int l_match[N];
int match[N];

bool dfs(int u, int val) {
    if (u < val) return false;
    for (int v : G[u])
        if (!check[v]) {
            check[v] = true;
            if (match[v] == -1 || dfs(match[v], val)) {
                match[v] = u;
                l_match[u] = v;
                return true;
            }
        }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int kase = 1; kase <= T; kase++) {
        cin >> n >> m;
        int cur = 0;
        for (int i = 1; i <= m; i++) {
            int sz;
            cin >> sz;
            l[i] = cur; r[i] = cur + sz;
            for (int j = cur; j < cur + sz; j++) type[j] = i;
            cur += sz;
        }

        for (int i = 0; i < n; i++) {
            pref[i].clear();
            G[i].clear();
            int sz;
            cin >> sz;
            for (int j = 0; j < sz; j++) {
                int x;
                cin >> x;
                pref[i].pb(x);
                for (int k = l[x]; k < r[x]; k++) G[i].pb(k);
            }
        }

        int ans = 0;
        fill(match, match + cur, -1);
        fill(l_match, l_match + n, -1);
        for (int i = 0; i < n; i++) {
            fill(check, check + cur, false);
            if (dfs(i, 0)) ans++;
        }

        cout << "Case #" << kase << ":\n";
        cout << ans << " applicant(s) can be hired.\n";

        for (int i = 0; i < n; i++) {
            if (l_match[i] == -1) continue;
            int mt = type[l_match[i]];
            for (int j = 0; j < pref[i].size(); j++) {
                if (pref[i][j] == mt) break;

                bool ok = false;
                for (int id = l[pref[i][j]]; id < r[pref[i][j]]; id++) {
                    fill(check, check + cur, false);
                    check[id] = true;
                    match[l_match[i]] = -1;
                    if (match[id] == -1 || dfs(match[id], i)) {
                        match[id] = i;
                        l_match[i] = id;
                        ok = true;
                        break;
                    } else match[l_match[i]] = i;
                }
                if (ok) break;
            }
        }
        
        for (int i = 0; i < n; i++)
            if (l_match[i] > -1)
                cout << i + 1 << ' ' << type[l_match[i]] << '\n';
    }
    return 0;
}
