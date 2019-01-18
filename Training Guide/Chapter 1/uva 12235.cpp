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

const int N = 112;
const int H = 8;
const int INF = 0x3f3f3f3f;

int dp[N][N][H][1 << 8], n, m, a[N];

// dp[i][j][k][mask]: the minm mess, at postion i, have changed j times, the last is k, mask has appeared before

int cnt(int num) {
    int ans = 0;
    while (num) {
        ans += (num & 1);
        num >>= 1;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int kase = 0;
    while (cin >> n >> m && n && m) {
        reset(dp, 0x3f);

        int app = 0;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            a[i] -= 25;
            app |= (1 << a[i]);
        }

        const int ALL = (1 << 8);
        dp[1][0][a[1]][1 << a[1]] = 1;
        dp[1][1][0][0] = 0;


        for (int i = 1; i < n; i++) {
            for (int j = 0; j <= min(i, m); j++) {
                for (int k = 0; k < 8; k++) {
                    for (int mask = 0; mask < ALL; mask++) {
                        if (dp[i][j][k][mask] < INF) {
                            //cout << i << ' ' << dp[i][j][k][mask] << endl;
                            if (k == a[i + 1]) {
                                int &ans = dp[i + 1][j][k][mask | (1 << k)];
                                if (mask == 0) ans = min(ans, dp[i][j][k][mask] + 1);
                                else ans = min(ans, dp[i][j][k][mask]);

                                if (j < m) {
                                    int &ans = dp[i + 1][j + 1][k][mask];
                                    ans = min(ans, dp[i][j][k][mask]);
                                }
                            } else {
                                int &ans = dp[i + 1][j][a[i + 1]][mask | (1 << a[i + 1])];
                                ans = min(ans, dp[i][j][k][mask] + 1);
                                if (j < m) {
                                    int &ans = dp[i + 1][j + 1][k][mask];
                                    ans = min(ans, dp[i][j][k][mask]);
                                }
                            }
                        }
                    }
                }
            }
        }

        int ans = INF;
        for (int i = 0; i < 8; i++)
            for (int mask = 0; mask < ALL; mask++) {
                ans = min(ans, dp[n][m][i][mask] + cnt(mask ^ app));
            }
        cout << "Case " << ++kase << ": " << ans << "\n\n";
    }
    return 0;
}
