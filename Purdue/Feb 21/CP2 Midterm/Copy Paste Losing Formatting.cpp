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
const int MOD = int(1e9) + 7;

LL dp[N][N], sum[N];
int n;
char s[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> s[i];

    dp[1][1] = 1;
    sum[1] = 1;
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (s[i - 1] == 'f') dp[i][j] = dp[i - 1][j - 1];
            else dp[i][j] = sum[j];
        }

        sum[n] = dp[i][n];
        for (int j = n - 1; j >= 1; j--) sum[j] = (sum[j + 1] + dp[i][j]) % MOD;
    }

    cout << sum[1] << '\n';
    return 0;
}
