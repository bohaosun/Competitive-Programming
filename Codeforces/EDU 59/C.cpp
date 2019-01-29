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

LL a[N];
LL ans;
int n, k;
string s;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 0; i < n; i++) cin >> a[i];
    cin >> s;

    for (int i = 0; i < n; i++) {
        int r = i;
        while (r + 1 < n && s[r + 1] == s[i]) r++;
        sort(a + i, a + r + 1);
        reverse(a + i, a + r + 1);

        for (int j = i; j <= r && j - i + 1 <= k; j++) ans += a[j];
        i = r;
    }
    cout << ans << '\n';
    return 0;
}
