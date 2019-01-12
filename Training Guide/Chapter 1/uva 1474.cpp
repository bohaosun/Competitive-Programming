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

const int N = 4123;

int n, m;
pii a[N], b[N];
LL dp[N][N];
int ans[N];

void print(int i, int j) {
    if (i == 0) return;
    ans[a[i]._2] = b[j]._2;
    if (dp[i - 1][j - 1] + abs(a[i]._1 - b[j]._1) == dp[i][j]) print(i - 1, j - 1);
    else print(i - 1, j);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> n) {
        for (int i = 1; i <= n; i++) {
            cin >> a[i]._1;
            a[i]._2 = i;
        }
        cin >> m;
        for (int i = 1; i <= m; i++) {
            cin >> b[i]._1;
            b[i]._2 = i;
        }
        sort(a + 1, a + n + 1);
        sort(b + 1, b + m + 1);

        reset(dp, 0x3f);
        dp[0][0] = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= min(m, i); j++) {
                dp[i][j] = min(dp[i - 1][j], dp[i - 1][j - 1]) + abs(a[i]._1 - b[j]._1);
            }
        }

        cout << dp[n][m] << endl;
        print(n, m);
        cout << ans[1];
        for (int i = 2; i <= n; i++) cout << ' ' << ans[i];
        cout << '\n';
    }
    return 0;
}
