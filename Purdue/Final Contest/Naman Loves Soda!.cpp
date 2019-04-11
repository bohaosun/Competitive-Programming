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

const int N = 112;
const int INF = int(1e9);

struct Node {
    int num, water;
    bool operator < (const Node &rhs) const {
        return num < rhs.num || (num == rhs.num && water > rhs.water);
    }
};

Node dp[N][N * N];
int n, a[N], b[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    int tot = 0;
    for (int i = 1; i <= n; i++) { cin >> a[i]; tot += a[i]; }
    for (int i = 1; i <= n; i++) cin >> b[i];

    for (int j = 1; j <= 10000; j++) dp[0][j] = { INF, INF };
    dp[0][0] = { 0, 0 };

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= 10000; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j >= b[i]) {
                int num = dp[i - 1][j - b[i]].num;
                int water = dp[i - 1][j - b[i]].water;

                dp[i][j] = min(dp[i][j], { num + 1, water + a[i] });
            }
        }
    }

    Node ans{ INF, INF };

    for (int i = tot; i <= 10000; i++) ans = min(ans, dp[n][i]);

    cout << ans.num << ' ' << tot - ans.water << '\n';
    return 0;
}
