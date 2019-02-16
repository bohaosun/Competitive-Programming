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
const int INF = int(1e9);

int dp[N][N], a[N], n;
int lef[N], rig[N];

int solve(int l, int r) {
    if (rig[l] >= r) return 0;
    int &ans = dp[l][r];
    if (ans > -1) return ans;

    ans = INF;
    if (a[l] == a[r]) return ans = solve(rig[l] + 1, lef[r] - 1) + 1;
    else return ans = min(solve(rig[l] + 1, r), solve(l, lef[r] - 1)) + 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    for (int i = 1; i <= n; i++) {
        if (a[i] == a[i - 1]) lef[i] = lef[i - 1];
        else lef[i] = i;
    }

    for (int i = n; i >= 1; i--) {
        if (a[i] == a[i + 1]) rig[i] = rig[i + 1];
        else rig[i] = i;
    }

    reset(dp, -1);
    cout << solve(1, n) << '\n';
    return 0;
}
