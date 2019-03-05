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

const int N = 512345;

int n, m, k, s;
int a[N], re[N], tot, cnt[N], cur, rem;

vector<int> useless;
void print(int l, int r) {
    reset(cnt, 0);
    for (int i = l; i <= r; i++) {
        ++cnt[a[i]];
        if (cnt[a[i]] > re[a[i]]) useless.pb(i);
    }

    cout << rem << '\n';
    for (int i = 0; i < useless.size(); i++) {
        if (i >= rem) break;
        cout << useless[i] << ' ';
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> m >> k >> n >> s;
    for (int i = 1; i <= m; i++) cin >> a[i];
    for (int i = 1; i <= s; i++) {
        int x;
        cin >> x;
        if (!re[x]) tot++;
        re[x]++;
    }

    rem = m - n * k;
    int l = 1, r = 1;

    for (int i = 1; i <= m; i += k) {
        while (l < i) {
            --cnt[a[l]];
            if (re[a[l]] && cnt[a[l]] == re[a[l]] - 1) --cur;
            ++l;
        }

        while (r <= min(m, i + k + rem - 1)) {
            ++cnt[a[r]];
            if (re[a[r]] && cnt[a[r]] == re[a[r]]) ++cur;
            ++r;
        }

        if (cur == tot) { print(l, r - 1); return 0; }
    }

    cout << -1 << '\n';
    return 0;
}
