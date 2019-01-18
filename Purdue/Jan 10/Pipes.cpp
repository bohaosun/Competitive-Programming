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

const int N = 12 + 5;

int a[N][N], f[N][N];
int r, c;

bool solve(int x, int y) {
    if (x == r) return true;

    if (a[x][y] == 0) {
        if (f[x][y]) return false;
        int rr = x, cc = y + 1;
        if (cc == c) {
            rr++;
            cc = 0;
        }
        return solve(rr, cc);
    } else if (a[x][y] == 1) {
        if (f[x][y] == 3) return false;
        if (f[x][y]) {
            int rr = x, cc = y + 1;
            if (cc == c) { rr++; cc = 0; }
            return solve(rr, cc);
        }
        if (y < c - 1) {
            f[x][y + 1]++;
            if (solve(x, y + 1)) return true;
            f[x][y + 1]--;
        }
        if (x < r - 1) {
            f[x + 1][y] += 2;
            int rr = x, cc = y + 1;
            if (cc == c) { rr++; cc = 0; }
            if (solve(rr, cc)) return true;
            f[x + 1][y] -= 2;
        }
        return false;
    } else if (a[x][y] == 2) {
        if (f[x][y] == 0) {
            if (x == r - 1 || y == c - 1) return false;
            f[x][y + 1]++;
            f[x + 1][y] += 2;
            if (solve(x, y + 1)) return true;
            f[x][y + 1]--;
            f[x + 1][y] -= 2;
            return false;
        } else if (f[x][y] == 1) {
            if (x == r - 1) return false;
            f[x + 1][y] += 2;
            int rr = x, cc = y + 1;
            if (cc == c) { rr++; cc = 0; }
            if (solve(rr, cc)) return true;
            f[x + 1][y] -= 2;
            return false;
        } else if (f[x][y] == 2) {
            if (y == c - 1) return false;
            f[x][y + 1]++;
            if (solve(x, y + 1)) return true;
            f[x][y + 1]--;
            return false;
        } else {
            int rr = x, cc = y + 1;
            if (cc == c) { rr++; cc = 0; }
            return solve(rr, cc);
        }
    } else if (a[x][y] == 3) {
        if (f[x][y] == 0) return false;
        if (f[x][y] == 1 || f[x][y] == 2) {
            if (x == r - 1 || y == c - 1) return false;
            f[x][y + 1]++;
            f[x + 1][y] += 2;
            if (solve(x, y + 1)) return true;
            f[x][y + 1]--;
            f[x + 1][y] -= 2;
            return false;
        }
        if (y < c - 1) {
            f[x][y + 1]++;
            if (solve(x, y + 1)) return true;
            f[x][y + 1]--;
        }
        if (x < r - 1) {
            f[x + 1][y] += 2;
            int rr = x, cc = y + 1;
            if (cc == c) { rr++; cc = 0; }
            if (solve(rr, cc)) return true;
            f[x + 1][y] -= 2;
        }
        return false;
    } else {
        if (f[x][y] != 3) return false;
        if (x == r - 1 || y == c - 1) return false;
        f[x][y + 1]++;
        f[x + 1][y] += 2;
        if (solve(x, y + 1)) return true;
        f[x][y + 1]--;
        f[x + 1][y] -= 2;
        return false;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> r >> c && r && c) {
        reset(f, 0);
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++) {
                string s;
                cin >> s;
                if (s[0] == 'x') {
                    a[i][j] = 0;
                } else {
                    a[i][j] = s.length();
                }
            }

        if (solve(0, 0)) cout << "SOLVABLE\n";
        else cout << "UNSOLVABLE\n";
    }

    return 0;
}
