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

const LL UPP = LL(1e16);

LL cal(LL val, LL x) {
    LL cnt2 = 0, cnt5 = 0;
    for (LL cur = 2; cur <= UPP; cur *= 2) {
        cnt2 += val / cur;
        if (cnt2 >= x) break;
    }

    for (LL cur = 5; cur <= UPP; cur *= 5) {
        cnt5 += val / cur;
        if (cnt5 >= x) break;
    }

    return min(cnt2, cnt5) >= x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        LL x;
        cin >> x;

        LL l = 0, r = LL(1e18);
        while (l < r) {
            LL mid = l + (r - l) / 2;
            if (cal(mid, x)) r = mid;
            else l = mid + 1;
        }
        cout << l << '\n';
    }
    return 0;
}
