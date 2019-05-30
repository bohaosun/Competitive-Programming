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

vector<LL> ans;

LL a, b, m;

LL sum(LL val, int len) {
    LL sum = a;
    LL cur = a;

    for (int i = 0; i < len - 1; i++) {
        cur = sum + val;
        if (cur > b) return cur;
        sum += cur;
    }

    return cur;
}

LL value(int cur, int len) {
    if (cur == len) return 1;
    return 1ll << (len - cur - 1);
}

bool check(int len) {

    if (sum(m, len) < b) return false;
    if (sum(1, len) > b) return false;

    LL l = 1, r = m + 1;

    while (l < r) {
        LL mid = l + (r - l) / 2;
        if (sum(mid, len) > b) r = mid;
        else l = mid + 1;
    }

    LL sub = b - sum(l - 1, len);

    ans.clear();
    ans.pb(a);
    LL sum = a;

    for (int i = 2; i <= len; i++) {
        LL cur = sum + l - 1;
        if (sub >= value(i, len)) { ++cur; sub -= value(i, len); }
        ans.pb(cur);
        sum += cur;
    }

    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;

    while (q--) {
        cin >> a >> b >> m;

        for (int i = 1; i <= 50; i++) {
            if (check(i)) {
                cout << i;
                for (auto it : ans) cout << ' ' << it;
                cout << '\n';
                goto label;
            }
        }

        cout << -1 << '\n';
        label:;
    }
    return 0;
}
