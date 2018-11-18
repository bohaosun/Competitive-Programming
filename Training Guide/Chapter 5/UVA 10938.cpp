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

const int N = 5123;

int d[N], p[N];
int n, q;
vector<int> G[N];

void bfs(int s, int t) {
    reset(d, -1);
    queue<int> q;
    q.push(s);
    d[s] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : G[u])
            if (d[v] == -1) {
                d[v] = d[u] + 1;
                p[v] = u;
                q.push(v);
            }
    }

    int dis = d[t];
    if (dis & 1) {
        int l = -1, r = -1;
        int cur = t, tim = 0, need = (dis + 1) / 2;
        while (tim <= need) {
            if (tim == need - 1) l = cur;
            else if (tim == need) r = cur;
            cur = p[cur];
            tim++;
        }

        cout << "The fleas jump forever between " << min(l, r) << " and " << max(l, r) << ".\n";
    } else {
        int cur = t, tim = 0, need = dis / 2;
        while (tim < need) { cur = p[cur]; tim++; }
        cout << "The fleas meet at " << cur << ".\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> n && n) {
        for (int i = 1; i <= n; i++) G[i].clear();
        for (int i = 0; i < n - 1; i++) {
            int x, y;
            cin >> x >> y;
            G[x].pb(y);
            G[y].pb(x);
        }
        cin >> q;
        for (int i = 0; i < q; i++) {
            int x, y;
            cin >> x >> y;
            bfs(x, y);
        }
    }
    return 0;
}
