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

const int N = 30 + 5;

LL dp[N][10];

int main() {
    dp[0][0] = 1;
    dp[1][0] = 0;
    dp[1][1] = 1;
    dp[1][2] = 1;
    dp[1][3] = 0;
    dp[1][4] = 0;

    for (int i = 2; i <= 30; i++) {
        dp[i][0] = dp[i - 2][0] + dp[i - 1][1] + dp[i - 1][2];
        dp[i][1] = dp[i - 1][0] + dp[i - 1][3];
        dp[i][2] = dp[i - 1][0] + dp[i - 1][4];
        dp[i][3] = dp[i - 1][1];
        dp[i][4] = dp[i - 1][2];
    }

    int n;
    while (cin >> n) {
        if (n == -1) break;
        cout << dp[n][0] << '\n';
    }
    return 0;
}
