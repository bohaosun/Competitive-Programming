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

/*
 * The second dimension of BIT cannot be assigned directly since (2e5)^2 is not affordable. So first process all the
 * value needed and discretize data. Then use binary search to find the initial position and update/query the second
 * dimension.
 */

const int N = 212345;

vector<int> val[N], f[N];
int n, q, a[N], b[N], tmp[N];

struct Query {
    int id, la, ra, lb, rb;
};
vector<Query> query;

int lowbit(int x) { return x & (-x); }

void pre_add(int pos, int value) {
    if (!pos) return;
    while (pos <= n) {
        val[pos].pb(value);
        pos += lowbit(pos);
    }
}

void pre_query(int pos, int value) {
    while (pos) {
        val[pos].pb(value);
        pos -= lowbit(pos);
    }
}

void add(int x, int y, int value) {
    if (!x) return;
    for (int i = x; i <= n; i += lowbit(i))
        for (int j = lower_bound(val[i].begin(), val[i].end(), y) - val[i].begin() + 1; j < f[i].size(); j += lowbit(j)) {
            f[i][j] += value;
        }
}

int sum(int x, int y) {
    int ans = 0;
    for (int i = x; i; i -= lowbit(i))
        for (int j = lower_bound(val[i].begin(), val[i].end(), y) - val[i].begin() + 1; j; j -= lowbit(j)) {
            ans += f[i][j];
        }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        a[x] = i;
    }
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        b[i] = tmp[i] = a[x];
    }

    for (int i = 1; i <= n; i++) pre_add(i, b[i]);


    for (int i = 0; i < q; i++) {
        int id;
        cin >> id;
        if (id == 1) {
            int la, ra, lb, rb;
            cin >> la >> ra >> lb >> rb;
            query.pb({ id, la, ra, lb, rb });
            pre_query(rb, ra);
            pre_query(rb, la - 1);
            pre_query(lb - 1, ra);
            pre_query(lb - 1, la - 1);
        } else {
            int la, ra;
            cin >> la >> ra;
            query.pb({ id, la, ra, 0, 0 });
            pre_add(ra, b[la]);
            pre_add(ra, b[ra]);
            pre_add(la, b[la]);
            pre_add(la, b[ra]);
            swap(b[la], b[ra]);
        }
    }

    for (int i = 1; i <= n; i++) b[i] = tmp[i];

    for (int i = 1; i <= n; i++) {
        sort(all(val[i]));
        uni(val[i]);
        f[i].resize(val[i].size() + 1);
    }


    for (int i = 1; i <= n; i++) add(i, b[i], 1);
    for (int i = 0; i < q; i++) {
        int id = query[i].id;
        if (id == 1) {
            int la = query[i].la, lb = query[i].lb;
            int ra = query[i].ra, rb = query[i].rb;
            int ans = sum(rb, ra) - sum(lb - 1, ra);
            ans -= sum(rb, la - 1) - sum(lb - 1, la - 1);
            cout << ans << '\n';
        } else {
            int x = query[i].la, y = query[i].ra;
            add(x, b[x], -1);
            add(y, b[y], -1);
            add(x, b[y], 1);
            add(y, b[x], 1);
            swap(b[x], b[y]);
        }
    }
    return 0;
}
