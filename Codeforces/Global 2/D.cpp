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
#define uni(x) (x).erase(unique(all(x)), (x).end())
#define reset(x, y) memset(x, y, sizeof(x))
#define BUG(x) cerr << #x << " = " << (x) << endl
#define BUGP(x) cout << #x << " = " << (x)._1 << ", " << (x)._2 << endl
using namespace std;

typedef long long LL;
typedef pair<int, int> pii;
typedef pair<LL, LL> pll;

const int dr[] = {-1, 0, 1, 0, -1, -1, 1, 1};
const int dc[] = {0, -1, 0, 1, -1, 1, -1, 1};
// Head

const int N = 112345;

LL a[N], diff[N];
int n;
LL sum[N];

int my_find(LL len) {
    int l = 1, r = n;
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (diff[mid] <= len) l = mid + 1;
        else r = mid;
    }
    return l;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) diff[i] = a[i + 1] - a[i];
    sort(diff + 1, diff + n);
    for (int i = 1; i < n; i++) sum[i] = sum[i - 1] + diff[i];

    int q;
    cin >> q;
    while (q--) {
        LL l, r;
        cin >> l >> r;
        LL len = r - l + 1;

        int loc = my_find(len);
        cout << len + sum[loc - 1] + len * (n - loc) << ' ';
    }
    cout << '\n';
    return 0;
}
