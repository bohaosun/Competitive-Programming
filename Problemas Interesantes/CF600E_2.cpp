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

int dp[M];
int n, m;
pii a[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        int x, y;
        cin >> x >> y;
        a[i]._1 = x - y;
        a[i]._2 = x + y;
    }

    for (int i = 1; i <= m; ++i) {
        dp[i] = i;

        for (int j = 1; j <= n; ++j) {
            if (a[j]._1 <= i && i <= a[j]._2) dp[i] = dp[i - 1];
            else if (i > a[j]._2) {
                int dis = i - a[j]._2;
                dp[i] = min(dp[i], dp[max(0, a[j]._1 - dis - 1)] + dis);
            }
        }
    }

    cout << dp[m] << '\n';
    return 0;
}
