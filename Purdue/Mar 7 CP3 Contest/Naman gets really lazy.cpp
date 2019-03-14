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

const int N = 1000000;

int cnt1[N], cnt2[N];

int gcd(int a, int b) { return !b ? a : gcd(b, a % b); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 1; i <= N / 2; i++) {
        for (int j = i * 2; j <= N; j += i) ++cnt1[j];
    }

    int m = sqrt(N + 0.5);
    for (int i = 2; i <= m; i++) {
        if (i % 2 == 0) {
            int cur = i * i;
            for (int j = cur * 2; j <= N; j += cur) ++cnt2[j];
        }
    }

    int T;
    cin >> T;
    while (T--) {
        int x;
        cin >> x;
        if (cnt2[x] == 0) cout << 0 << '\n';
        else {
            int g = gcd(cnt2[x], cnt1[x]);
            cout << cnt2[x] / g << '/' << cnt1[x] / g << '\n';
        }
    }
    return 0;
}
