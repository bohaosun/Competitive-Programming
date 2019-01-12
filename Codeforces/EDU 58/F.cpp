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

const int N = 400 + 5;
const int INF = int(1e9);

int n, m, dp[N][N][N], a[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) dp[i][j][0] = a[j] - a[i];
        for (int k = 1; i + k < n; k++) {
            int id = i + k;
            for (int j = i + k + 1; j <= n; j++) {
                dp[i][j][k] = INF;
                while (id + 1 < j && dp[i][id][k - 1] < a[j] - a[id]) {
                    dp[i][j][k] = min(dp[i][j][k], a[j] - a[id++]);
                }
                dp[i][j][k] = min(dp[i][j][k], max(dp[i][id][k - 1], a[j] - a[id]));
            }
        }
    }

    /*for (int j = 2; j <= n; j++) {
        for (int k = 0; k < j - 1; k++) cout << dp[1][j][k] << ' ';
        cout << endl;
    }*/

    LL ans = 0;
    for (int i = 0; i < m; i++) {
        int s, f, r;
        LL c;
        cin >> s >> f >> c >> r;

        r = min(r, f - s - 1);

        //cout << dp[s][f][r] * c << endl;

        ans = max(ans, c * dp[s][f][r]);
    }
    cout << ans << '\n';
    return 0;
}
