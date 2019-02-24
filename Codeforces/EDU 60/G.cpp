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

const int N = 1123456;

int n, q, a[N], lef[N], rig[N];
vector<int> vec[N];
LL c[2][N];
LL ans[N];

int lowbit(int x) { return x & (-x); }

void add(int id, int pos, int val) {
    if (pos == 0) return;
    while (pos <= n) {
        c[id][pos] += val;
        pos += lowbit(pos);
    }
}

LL sum(int id, int pos) {
    LL ret = 0;
    while (pos) {
        ret += c[id][pos];
        pos -= lowbit(pos);
    }
    return ret;
}

LL range(int l, int r) {
    return LL(l + r) * (r - l + 1) / 2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= q; i++) cin >> lef[i];
    for (int i = 1; i <= q; i++) { cin >> rig[i]; vec[rig[i]].pb(i); }

    for (int kase = 0; kase < 2; kase++) {
        stack<int> st;
        for (int i = 1; i <= n; i++) {
            while (!st.empty() && a[st.top()] < a[i]) st.pop();
            int pos = 0;
            if (!st.empty()) pos = st.top();
            st.push(i);

            add(0, pos, -pos - 1);
            add(1, pos, 1);

            for (int id : vec[i]) {
                ans[id] += range(lef[id], rig[id]);
                ans[id] += sum(0, rig[id]) - sum(0, lef[id] - 1);

                LL cnt = sum(1, rig[id]) - sum(1, lef[id] - 1);
                ans[id] += (rig[id] - lef[id] + 1 - cnt) * (-lef[id]);
            }
        }

        reset(c, 0);
        for (int i = 1; i <= n; i++) vec[i].clear();
        reverse(a + 1, a + n + 1);
        for (int i = 1; i <= q; i++) {
            lef[i] = n - lef[i] + 1;
            rig[i] = n - rig[i] + 1;
            swap(lef[i], rig[i]);
        }
        for (int i = 1; i <= q; i++) vec[rig[i]].pb(i);
    }

    for (int i = 1; i <= q; i++) cout << ans[i] + rig[i] - lef[i] + 1 << ' ';
    cout << '\n';
    return 0;
}
