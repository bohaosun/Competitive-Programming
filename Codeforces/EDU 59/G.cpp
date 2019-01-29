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

const int N = 312345;
const LL INF = LL(1e15);

LL d[N], c[N], sum[N], a;
int n;
pll q[N];

LL value(pll x, LL gap) { return x._1 + max(x._2, gap); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> a;
    LL ans = INF;

    for (int i = 1; i <= n; i++) {
        cin >> d[i] >> c[i];
        c[i] -= a;
        ans = min(ans, c[i]);
    }
    for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + c[i];

    int head = 0, tail = 0;
    q[tail++] = mp(0, 0);

    for (int i = 1; i <= n; i++) {
        ans = min(ans, sum[i] + q[tail - 1]._2 + q[tail - 1]._1);

        while (head < tail && q[tail - 1]._1 >= -sum[i - 1]) tail--;

        LL gap = sqr(d[i + 1] - d[i]);

        while (head < tail - 1 && value(q[tail - 2], gap) <= value(q[tail - 1], gap)) tail--;
        if (head < tail) q[tail - 1]._2 = max(q[tail - 1]._2, gap);

        if (head == tail || -sum[i - 1] + gap < value(q[tail - 1], gap)) {
            if (head < tail) assert(-sum[i - 1] > q[tail - 1]._1);
            q[tail++] = mp(-sum[i - 1], gap);
        }
    }
    cout << max(-ans, 0ll) << '\n';
    return 0;
}
