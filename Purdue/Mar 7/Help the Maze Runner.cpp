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

const int N = 212;
const int INF = 0x3f3f3f3f;
const int dr[] = { -1, 0, 1, 0 };
const int dc[] = { 0, -1, 0, 1 };

int n, m, a[N][N];

int d[N][N];
pii s, t;

int bfs() {
    if (a[s._1][s._2] == 0) return -1;

    reset(d, 0x3f);
    d[s._1][s._2] = 0;
    queue<pii> q;
    q.push(s);

    while (!q.empty()) {
        pii u = q.front(); q.pop();
        int r = u._1, c = u._2;
        if (u == t) return d[r][c];

        for (int i = 0; i < 4; i++) {
            int rr = r + dr[i], cc = c + dc[i];
            if (rr < 0 || cc < 0 || rr >= n || cc >= m) continue;
            if (a[rr][cc] == 0) continue;
            if (d[rr][cc] < INF) continue;

            d[rr][cc] = d[r][c] + 1;
            q.push(mp(rr, cc));
        }
    }

    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    cin >> s._1 >> s._2;
    cin >> t._1 >> t._2;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) cin >> a[i][j];
    }

    int cur = bfs();
    if (cur == -1) cout << "No route.\n";
    else cout << d[t._1][t._2] << '\n';

    return 0;
}
