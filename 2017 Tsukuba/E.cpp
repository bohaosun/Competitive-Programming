/*
 * DP with monotonic queue.
 * s[i] == t[i]: dp[i] = dp[i - 1]
 * s[i] != t[i]: dp[i] = min{ i - len <= j < n } (dp[j] + ceiling(cnt[i] - cnt[j + 1]) + 1) 
 * Need to discuss about parity.
 */
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
#define all(x) (x).begin(), (x).end()
#define uni(x) (x).erase(unique(all(x)), (x).end());
#define reset(x, y) memset(x, y, sizeof(x))
#define BUG(x) cerr << #x << " = " << (x) << endl
#define mp make_pair
using namespace std;

typedef long long LL;
typedef pair<int, int> pii;
typedef pair<LL, LL> pll;
// Head

const int N = 512345;
const int INF = int(1e9);

int dp[N], n, len;
int s[N], t[N], cnt[N];
int e_q[N], e_head, e_tail;  // even
int o_q[N], o_head, o_tail;  // odd

int f(int idx) {
    return dp[idx] - cnt[idx + 1] / 2 + 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> len;
    string str;
    cin >> str;
    for (int i = 0; i < str.length(); i++) s[i + 1] = (str[i] == 'W');
    cin >> str;
    for (int i = 0; i < str.length(); i++) t[i + 1] = (str[i] == 'W');

    cnt[1] = 1;
    for (int i = 2; i <= n; i++) {
        cnt[i] = cnt[i - 1] + (t[i] != t[i - 1]);
    }

    e_head = o_head = e_tail;
    o_tail++;

    for (int i = 1; i <= n; i++) {
        if (s[i] == t[i]) dp[i] = dp[i - 1];
        else {
            while (e_head < e_tail && e_q[e_head] < i - len) e_head++;
            while (o_head < o_tail && o_q[o_head] < i - len) o_head++;

            dp[i] = INF;
            if (e_head < e_tail) {
                int j = e_q[e_head];
                dp[i] = min(dp[i], f(j) + cnt[i] / 2);
                if (cnt[i] & 1) dp[i]++;
            }

            if (o_head < o_tail) {
                int j = o_q[o_head];
                dp[i] = min(dp[i], f(j) + cnt[i] / 2);
            }
        }

        if (cnt[i + 1] & 1) {
            while (o_head < o_tail && f(i) <= f(o_q[o_tail - 1])) o_tail--;
            o_q[o_tail++] = i;
        } else {
            while (e_head < e_tail && f(i) <= f(e_q[e_tail - 1])) e_tail--;
            e_q[e_tail++] = i;
        };
    }

    cout << dp[n] << '\n';
    return 0;
}
