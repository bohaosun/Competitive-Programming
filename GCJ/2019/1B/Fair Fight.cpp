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
#include <complex>

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

int n, k, a[N], b[N], f[N][20], g[N][20];

void preprocess() {
    for (int i = 1; i <= n; i++) {
        f[i][0] = a[i];
        g[i][0] = b[i];
    }

    for (int i = 1; i < 18; i++) {
        for (int j = 1; j + (1 << i) - 1 <= n; j++) {
            f[j][i] = max(f[j][i - 1], f[j + (1 << (i - 1))][i - 1]);
            g[j][i] = max(g[j][i - 1], g[j + (1 << (i - 1))][i - 1]);
        }
    }
}

int get_max(int (*arr)[20], int l, int r) {
    int pw = 0;

    while ((1 << (pw + 1)) < r - l + 1) pw++;
    return max(arr[l][pw], arr[r - (1 << pw) + 1][pw]);
}

LL get_num(int lef, int x, int rig, int upp) {
    if (b[x] > upp) return 0;
    int l = lef, r = x;

    while (l < r) {
        int mid = l + (r - l) / 2;
        if (get_max(g, mid, x) <= upp) r = mid;
        else l = mid + 1;
    }

    LL num = x - l + 1;

    l = x, r = rig + 1;

    while (l < r) {
        int mid = l + (r - l) / 2;
        if (get_max(g, x, mid) <= upp) l = mid + 1;
        else r = mid;
    }

    return num * (l - x);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int kase = 1; kase <= T; kase++) {
        cout << "Case #" << kase << ": ";
        cin >> n >> k;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> b[i];

        preprocess();

        LL ans = 0;
        for (int i = 1; i <= n; i++) {
            int l = 1, r = i;
            while (l < r) {
                int mid = l + (r - l) / 2;
                if (get_max(f, mid, i - 1) < a[i]) r = mid;
                else l = mid + 1;
            }
            int lef = l;

            l = i + 1, r = n + 1;
            while (l < r) {
                int mid = l + (r - l) / 2;
                if (get_max(f, i + 1, mid) <= a[i]) l = mid + 1;
                else r = mid;
            }
            int rig = l - 1;

            ans += get_num(lef, i, rig, a[i] + k) - get_num(lef, i, rig, a[i] - k - 1);
        }
        cout << ans << '\n';
    }
    return 0;
}
