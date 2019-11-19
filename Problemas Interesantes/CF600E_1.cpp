#include <bits/stdc++.h>
 
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
 
const int N = 85;
const int M = 112345;
 
int dp[N][M];
pii a[N];
int n, m;
vector<pii> vec;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
 
    cin >> n >> m;
 
    for (int i = 1; i <= n; ++i) {
        int len;
        cin >> a[i]._1 >> len;
        a[i]._2 = a[i]._1 + len;
        a[i]._1 = a[i]._1 - len;
    }
 
    sort(a + 1, a + n + 1);
 
    reset(dp[0], 0x3f);
    dp[0][0] = 0;
 
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            dp[i][j] = dp[i - 1][j];
            if (j <= a[i]._2) {
                dp[i][j] = min(dp[i][j], max(0, a[i]._1 - 1));
                dp[i][j] = min(dp[i][j], dp[i - 1][max(0, a[i]._1 - 1)]);
            } else {
                int dis = j - a[i]._2;
                dp[i][j] = min(dp[i][j], dp[i - 1][max(0, a[i]._1 - dis - 1)] + dis);
                dp[i][j] = min(dp[i][j], max(a[i]._1 - 1, dis));
            }
        }
    }
 
    cout << dp[n][m] << '\n';
    return 0;
}
