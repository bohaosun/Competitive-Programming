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

const int N = 112345;
const int M = 26 + 5;

LL dp[N][M];
int n;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < 26; j++) {
            int cur = 0, maxm = 0;
            for (int k = 0; k < s.length(); k++) {
                if (s[k] - 'a' == j) {
                    maxm = max(maxm, ++cur);
                } else cur = 0;
            }

            if (maxm == s.length()) {
                dp[i][j] = (dp[i - 1][j] + 1) * maxm + dp[i - 1][j];
            } else {
                dp[i][j] = maxm;

                if (dp[i - 1][j]) {
                    int len = 0;
                    for (int k = 0; k < s.length(); k++) {
                        if (s[k] - 'a' == j) len++;
                        else break;
                    }

                    for (int k = s.length() - 1; k >= 0; k--) {
                        if (s[k] - 'a' == j) len++;
                        else break;
                    }

                    dp[i][j] = max(dp[i][j], LL(len) + 1);
                }
            }
        }
    }

    LL ans = 0;
    for (int i = 0; i < 26; i++) ans = max(ans, dp[n][i]);
    cout << ans << '\n';
    return 0;
}
