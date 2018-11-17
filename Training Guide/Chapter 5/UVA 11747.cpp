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

const int M = 25000 + 10;
const int N = 1234;

int u[M], v[M], w[M], f[M];
int fa[N];
int n, m;

bool cmp(int x, int y) {
    return w[x] < w[y];
}

int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n >> m && n) {
        for (int i = 0; i < m; i++) cin >> u[i] >> v[i] >> w[i];
        for (int i = 0; i < m; i++) f[i] = i;
        for (int i = 0; i < n; i++) fa[i] = i;

        sort(f, f + m, cmp);
        vector<int> ans;
        for (int i = 0; i < m; i++) {
            int id = f[i];
            int x = find(u[id]), y = find(v[id]);
            if (x == y) ans.pb(w[id]);
            else fa[x] = y;
        }

        if (ans.empty()) cout << "forest\n";
        else {
            sort(all(ans));
            cout << ans[0];
            for (int i = 1; i < ans.size(); i++) cout << ' ' << ans[i];
            cout << '\n';
        }
    }
    return 0;
}
