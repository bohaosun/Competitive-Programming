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

const int N = 100;

int n, m;
string s[N];

pii st;

const int dr[] = { -1, 0, 1, 0 };
const int dc[] = { 0, 1, 0, -1 };

void solve(pii p, int dir) {
    //cout << p._1 << ' ' << p._2 << endl;
    //cout << dir << endl;
    for (int i = 1; ; i++) {
        pii cur = { p._1 + dr[dir] * i, p._2 + dc[dir] * i };
        if (cur._1 == 0 || cur._2 == 0 || cur._1 == n - 1 || cur._2 == m - 1) {
            s[cur._1][cur._2] = '&';
            return;
        }
        if (s[cur._1][cur._2] == '/') {
            if (dir % 2 == 0) dir++;
            else dir--;
            solve(cur, dir);
            return;
        }
        if (s[cur._1][cur._2] == '\\') {
            solve(cur, 3 - dir);
            return;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> m >> n;
    for (int i = 0; i < n; i++) cin >> s[i];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (s[i][j] == '*') st = { i, j };
        }
    }

    //cout << st._1 << ' ' << st._2 << endl;

    if (st._1 == 0) solve(st, 2);
    else if (st._1 == n - 1) solve(st, 0);
    else if (st._2 == 0) solve(st, 1);
    else solve(st, 3);

    for (int i = 0; i < n; i++) cout << s[i] << '\n';
    return 0;
}
