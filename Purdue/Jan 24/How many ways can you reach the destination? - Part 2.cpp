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

const int N = 40 + 5;

LL dp[N][N][2];
int n, h;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> h;
    if (h == 0) dp[0][0][1] = 1;
    else dp[0][0][0] = 1;

    for (int j = 0; j < n - 1; j++) {
        for (int i = 0; i < n; i++) {
            for (int d = -1; d <= 1; d++) {
                if (i + d < 0 || i + d >= n) continue;
                if (i + d < h) {
                    dp[i + d][j + 1][0] += dp[i][j][0];
                    dp[i + d][j + 1][1] += dp[i][j][1];
                } else {
                    dp[i + d][j + 1][1] += dp[i][j][0] + dp[i][j][1];
                }
            }
        }
    }
    //cout << dp[2][2][1] << endl;
    cout << dp[0][n - 1][1] << '\n';
    return 0;
}
