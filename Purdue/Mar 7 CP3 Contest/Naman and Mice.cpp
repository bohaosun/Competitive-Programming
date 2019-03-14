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

const int N = 5123;
const LL INF = 0x3f3f3f3f3f3f3f3f;

LL dp[N][N];
int n, m;
LL x[N];
pll y[N];

int q[N];
LL sum[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
    }

    for (int i = 1; i <= m; i++) {
        cin >> y[i]._1 >> y[i]._2;
    }

    sort(x + 1, x + n + 1);
    sort(y + 1, y + m + 1);

    reset(dp, 0x3f);

    for (int j = 1; j <= m; j++) {
        sum[0] = 0;
        for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + abs(x[i] - y[j]._1);

        int front = 0, tail = 0;
        q[tail++] = 0;
        dp[0][j - 1] = 0;

        for (int i = 1; i <= n; i++) {
            while (front < tail && dp[q[tail - 1]][j - 1] - sum[q[tail - 1]] >= dp[i][j - 1] - sum[i]) tail--;
            q[tail++] = i;

            while (front < tail && i - q[front] > y[j]._2) front++;
            dp[i][j] = dp[q[front]][j - 1] - sum[q[front]] + sum[i];
        }
    }
    

    if (dp[n][m] < INF) cout << dp[n][m] << '\n';
    else cout << -1 << '\n';

    return 0;
}
