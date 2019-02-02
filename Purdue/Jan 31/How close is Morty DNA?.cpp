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

const int N = 65;
const int INF = int(1e9);

int n, ci, crm, crp, val[N];
string s[N], s1;

vector<string> ans;
int dp[N][N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> ci >> crm >> crp;
    cin >> s1;
    s1 = "0" + s1;

    reset(dp, 0x3f);

    dp[0][0] = 0;
    dp[1][0] = crm;
    dp[0][1] = ci;

    int minm = INF;
    for (int kase = 0; kase < n; kase++) {
        cin >> s[kase];
        s[kase] = "0" + s[kase];
        for (int i = 1; i < s1.length(); i++) {
            for (int j = 1; j < s[kase].length(); j++) {
                dp[i][j] = INF;
                if (s1[i] == s[kase][j]) dp[i][j] = dp[i - 1][j - 1];

                int val = min(dp[i - 1][j] + crm, dp[i][j - 1] + ci);
                val = min(val, dp[i - 1][j - 1] + crp);
                dp[i][j] = min(dp[i][j], val);
            }
        }
        val[kase] = dp[s1.length() - 1][s[kase].length() - 1];
        minm = min(minm, val[kase]);
    }

    for (int i = 0; i < n; i++) {
        if (val[i] == minm) ans.pb(s[i]);
    }
    sort(all(ans));
    cout << minm << '\n';
    for (int i = 0; i < ans.size(); i++) {
        for (int j = 1; j < ans[i].length(); j++) cout << ans[i][j];
        cout << '\n';
    }
    return 0;
}
