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

int n, a, b, len[N];
char s[N];
int dp[N];

int f[N];

bool check(int pos, int val) {
    int loc = pos - val;

    char *s1 = s + 1;
    char *s2 = s + loc + 1;
    int n1 = loc;
    int n2 = pos - loc;

    f[0] = f[1] = 0;
    for (int i = 1; i < n2; i++) {
        int j = f[i];
        while (j && s2[j] != s2[i]) j = f[j];
        f[i + 1] = s2[i] == s2[j] ? j + 1 : 0;
    }

    int j = 0;
    for (int i = 0; i < n1; i++) {
        while (j && s1[i] != s2[j]) j = f[j];
        if (s1[i] == s2[j]) j++;
        if (j == n2) return true;
    }

    return false;
}

int main() {
    scanf("%d%d%d", &n, &a, &b);
    scanf("%s", s + 1);

    for (int i = 1; i <= n; i++) {
        int l = 1, r = i / 2 + 1;
        while (l < r) {
            int mid = l + (r - l) / 2;
            if (check(i, mid)) l = mid + 1;
            else r = mid;
        }

        len[i] = l - 1;
    }


    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1] + a;
        if (len[i]) dp[i] = min(dp[i], dp[i - len[i]] + b);
    }
    cout << dp[n] << '\n';
    return 0;
}
