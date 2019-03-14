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
const int M = 1123;

bool dp[N * M];
int n, m, a[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    dp[0] = true;
    cin >> n;
    int sum = 0;
    for (int i = 0; i < n; i++) { cin >> a[i]; sum += a[i]; }

    for (int i = 0; i < n; i++) {
        for (int j = sum; j >= a[i]; j--) dp[j] |= dp[j - a[i]];
    }

    int a = -1, b = -1;
    for (int i = sum / 2; i >= 0; i--) {
        if (dp[i]) {
            a = i; b = sum - i;
            cout << a << ' ' << b << ' ' << b - a << '\n';
            return 0;
        }
    }
    return 0;
}
