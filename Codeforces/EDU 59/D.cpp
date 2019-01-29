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


const int N = 5250;

int n, f[N][N], sum[N][N];
string s[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> s[i];

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < s[i].length(); j++) {
            int cur;
            if (isalpha(s[i][j])) cur = s[i][j] - 'A' + 10;
            else cur = s[i][j] - '0';

            for (int k = 0; k < 4; k++) {
                if (cur & (1 << (3 - k))) f[i][4 * j + k + 1] = 1;
            }
        }
    }

    /*for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) cout << f[i][j];
        cout << endl;
    }*/

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + f[i][j];
    }

    int ans = 1;
    for (int x = n; x >= 2; x--) {
        if (n % x) continue;
        int len = n / x;
        bool ok = true;
        for (int i = 1; i <= len; i++) {
            for (int j = 1; j <= len; j++) {

                if (sum[i * x][j * x] - sum[(i - 1) * x][j * x] - sum[i * x][(j - 1) * x] + sum[(i - 1) * x][(j - 1) * x] != x * x
                && sum[i * x][j * x] - sum[(i - 1) * x][j * x] - sum[i * x][(j - 1) * x] + sum[(i - 1) * x][(j - 1) * x] != 0) ok = false;

                if (!ok) break;
            }
            if (!ok) break;
        }
        if (ok) { ans = x; break; }
    }
    cout << ans << '\n';
    return 0;
}
