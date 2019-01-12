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

const int N = 212345;

int a[N], f[N], n;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        f[i] = f[i - 1] ^ a[i];
    }
    
    if (!f[n]) { cout << -1 << '\n'; return 0; }

    int ans = 0, st = 1;
    for (int i = 29; i >= 0; i--) {
        int pos = -1;
        for (int j = st; j <= n; j++) {
            if (f[j] & (1 << i)) { pos = j; break; }
        }

        if (pos == -1) continue;

        swap(f[pos], f[st]);
        for (int j = st + 1; j <= n; j++) {
            if (f[j] & (1 << i)) f[j] ^= f[st];
        }
        ans++;
        st++;
    }

    if (ans) cout << ans << '\n';
    else cout << -1 << '\n';
    return 0;
}
