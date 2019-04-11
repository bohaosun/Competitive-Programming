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

const int N = 2123;

string s[N];
int n, m;
int vis[N][N], d[N][N];

bool dfs(int r, int c) {
    vis[r][c] = -1;
    int rr = r, cc = c;
    if (s[r][c] == '<') --cc;
    else if (s[r][c] == '>') ++cc;
    else if (s[r][c] == '^') --rr;
    else ++rr;

    if (vis[rr][cc] == -1) return false;
    if (vis[rr][cc]) { d[r][c] = d[rr][cc] + 1; vis[r][c] = 1; return true; }
    if (s[rr][cc] == '#') { d[r][c] = 1; vis[r][c] = 1; return true; }

    if (!dfs(rr, cc)) return false;
    vis[r][c] = 1;
    d[r][c] = d[rr][cc] + 1;
    return true;
}

bool solve(int r, int c) {
    if (s[r][c] == '#') return true;
    if (vis[r][c]) return false;
    vis[r][c] = true;

    if (s[r][c] == '<') return solve(r, c - 1);
    else if (s[r][c] == '>') return solve(r, c + 1);
    else if (s[r][c] == '^') return solve(r - 1, c);
    else return solve(r + 1, c);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;

    for (int i = 0; i < n; i++) cin >> s[i];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (s[i][j] != '#' && !vis[i][j]) {
                if (!dfs(i, j)) {
                    cout << -1 << '\n';
                    return 0;
                }
            }
        }
    }

    int maxm = 0, maxm2 = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (s[i][j] != '#') {
                if (d[i][j] > maxm) {
                    maxm2 = maxm;
                    maxm = d[i][j];
                } else if (d[i][j] > maxm2) {
                    maxm2 = d[i][j];
                }
            }
        }
    }

    if (maxm2 < maxm || maxm == 0) cout << maxm2 + maxm << '\n';
    else {
        int cnt = 0;
        reset(vis, 0);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (d[i][j] == maxm && solve(i, j)) ++cnt;
            }
        }

        if (cnt >= 2) cout << maxm * 2 << '\n';
        else cout << maxm * 2 - 1 << '\n';
    }

    return 0;
}
