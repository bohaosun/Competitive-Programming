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
#include <complex>

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

const int N = 1123;

string s[N];

int rig[N][N], down[N][N], minmd[N][N], minmu[N][N], n, m;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 0; i < n; i++) cin >> s[i];

    for (int i = 0; i < n; i++) {
        rig[i][m - 1] = m - 1;
        for (int j = m - 2; j >= 0; j--) {
            if (s[i][j] == s[i][j + 1]) rig[i][j] = rig[i][j + 1];
            else rig[i][j] = j;
        }
    }

    for (int j = 0; j < m; j++) {
        down[n - 1][j] = n - 1;
        for (int i = n - 2; i >= 0; i--) {
            if (s[i][j] == s[i + 1][j]) down[i][j] = down[i + 1][j];
            else down[i][j] = i;
        }
    }

    for (int j = 0; j < m; j++) {
        minmu[0][j] = rig[0][j];
        for (int i = 1; i < n; i++) {
            if (s[i][j] != s[i - 1][j]) minmu[i][j] = rig[i][j];
            else minmu[i][j] = min(minmu[i - 1][j], rig[i][j]);
        }

        minmd[n - 1][j] = rig[n - 1][j];
        for (int i = n - 2; i >= 0; i--) {
            if (s[i][j] != s[i + 1][j]) minmd[i][j] = rig[i][j];
            else minmd[i][j] = min(minmd[i + 1][j], rig[i][j]);
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int len = down[i][j] - i + 1;
            int fir = i + len;
            if (down[fir][j] - fir + 1 != len) continue;
            int sec = i + len * 2;
            if (down[sec][j] - sec + 1 < len) continue;

            ans += min(minmd[i][j], min(minmd[fir][j], minmu[sec + len - 1][j])) - j + 1;
            //cout << i << ' ' << j << endl;
            //cout << min(minmd[i][j], min(minmd[fir][j], minmu[sec][j])) - j + 1 << endl;
        }
    }

//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < m; j++) cout << minmd[i][j] << ' ';
//        cout << endl;
//    }

    cout << ans << '\n';
    return 0;
}
