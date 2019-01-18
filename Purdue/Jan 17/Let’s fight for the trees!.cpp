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

int n, m;
int len[N * 4], lef[N * 4], rig[N * 4];

void update(int o, int l, int r, int pos, int val) {
    if (l == r) {
        if (val == 1) len[o] = lef[o] = rig[o] = 1;
        else len[o] = lef[o] = rig[o] = 0;
        return;
    }
    int mid = l + (r - l) / 2;
    if (pos <= mid) update(o * 2, l, mid, pos, val);
    else update(o * 2 + 1, mid + 1, r, pos, val);
    len[o] = max(max(len[o * 2], len[o * 2 + 1]), rig[o * 2] + lef[o * 2 + 1]);

    if (lef[o * 2] == mid - l + 1) lef[o] = lef[o * 2] + lef[o * 2 + 1];
    else lef[o] = lef[o * 2];
    if (rig[o * 2 + 1] == r - mid) rig[o] = rig[o * 2 + 1] + rig[o * 2];
    else rig[o] = rig[o * 2 + 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        update(1, 1, n, b, a);
        cout << len[1] << '\n';
    }
    return 0;
}
