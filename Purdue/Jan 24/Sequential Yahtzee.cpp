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

const int N = 195 + 10;
const int INF = int(1e7);

int a[1 << 11][10], cnt;
int n, f[N], dp[20][N];
bool vis[20][N];

int card[10], content[10];

int point(int round) {
    for (int i = 0; i < 5; i++) content[i] = f[card[i]];
    if (round <= 6) {
        int ans = 0;
        for (int i = 0; i < 5; i++) {
            if (content[i] == round) ans += round;
        }
        return ans;
    }
    if (round <= 8) {
        int cnt[10] = { 0 }, sum = 0;
        reset(cnt, 0);
        for (int i = 0; i < 5; i++) { cnt[content[i]]++; sum += content[i]; }
        for (int i = 1; i <= 6; i++) {
            if (cnt[i] >= round - 4) return sum;
        }
        return 0;
    }
    if (round == 9) {
        sort(content, content + 5);
        if (content[0] == content[1] && content[1] == content[2] && content[3] == content[4] && content[2] != content[3])
            return 25;
        if (content[0] == content[1] && content[2] == content[3] && content[3] == content[4] && content[1] != content[2])
            return 25;
        return 0;
    }
    // 1, 2, 2, 3, 4
    if (round == 10) {
        int cnt[10] = { 0 };
        for (int i = 0; i < 5; i++) cnt[content[i]]++;
        if ((cnt[1] && cnt[2] && cnt[3] && cnt[4])
        || (cnt[2] && cnt[3] && cnt[4] && cnt[5])
        || (cnt[3] && cnt[4] && cnt[5] && cnt[6])) return 30;

        return 0;
    }
    if (round == 11) {
        sort(content, content + 5);
        for (int i = 1; i < 5; i++) {
            if (content[i] != content[i - 1] + 1) return 0;
        }
        return 40;
    }
    if (round == 12) {
        int sum = 0;
        for (int i = 0; i < 5; i++) sum += content[i];
        return sum;
    }

    for (int i = 1; i < 5; i++) {
        if (content[i] != content[i - 1]) return 0;
    }
    return 50;
}

int solve(int round, int pos) {
    if (round > 13) return 0;
    if (pos + 4 >= n) return -INF;

    int &ans = dp[round][pos];
    if (vis[round][pos]) return ans;

    vis[round][pos] = true;
    ans = -INF;

    for (int i = 0; i < cnt; i++) {
        for (int j = 0; j < 5; j++) card[j] = pos + a[i][j];
        if (card[4] >= n) continue;
        
        vector<int> dice;
        for (int j = 0; j < 5; j++) dice.pb(f[card[j]]);
        ans = max(ans, point(round) + solve(round + 1, card[4] + 1));
    }
    return ans;
}

int main() {
    for (int mask1 = 0; mask1 < (1 << 5); mask1++) {
        for (int mask2 = 0; mask2 < (1 << 5); mask2++) {
            for (int i = 0; i < 5; i++) a[cnt][i] = i;
            int cur = 5;
            for (int i = 0; i < 5; i++) {
                if ((1 << i) & mask1) a[cnt][i] = cur++;
            }
            for (int i = 0; i < 5; i++) {
                if ((1 << i) & mask2) a[cnt][i] = cur++;
            }
            sort(a[cnt], a[cnt] + 5);
            cnt++;
        }
    }


    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 0; i < n; i++) cin >> f[i];

    cout << solve(1, 0) << '\n';
    return 0;
}
