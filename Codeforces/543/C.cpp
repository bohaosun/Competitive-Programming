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

const int N = 1123;

struct Node {
    int a, b, id;
    bool operator < (const Node &rhs) const {
        return b > rhs.b;
    }
};

pii t[N], r[N];
int n, m;
int a[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    //for (int i = 0; i <= 100; i++) t[i] = { -1, -1 };

    priority_queue<Node> pq;
    for (int i = 1; i <= min(n, m); i++) {
        pq.push({ 0, a[i], i });
        r[i] = { 0, a[i] };
    }

    int cur = m + 1, cur_t = 0, cnt = 0, last = 0;
    while (!pq.empty()) {
        Node u = pq.top(); pq.pop();
        ++cnt;
        cur_t = u.b;

        int ratio = 100 * double(cnt) / n + 0.5;
        if (last < ratio) {
            t[last]._2 = cur_t;
            t[ratio]._1 = cur_t;
            last = ratio;
        } else {
            t[ratio]._2 = cur_t;
        }

        if (cur <= n) {
            pq.push({ cur_t, cur_t + a[cur], cur });
            r[cur] = { cur_t, cur_t + a[cur] };
            ++cur;
        }
    }

    t[100]._2 = 10000000;

    /*for (int i = 0; i <= 100; i++) {
        if (t[i]._2) cout << i << ' ' << t[i]._1 << ' ' << t[i]._2 << endl;
    }*/

    //for (int i = 1; i <= n; i++) cout << r[i]._1 << ' ' << r[i]._2 << endl;


    int ans = 0;
    for (int i = 1; i <= n; i++) {
        bool ok = false;
        for (int j = 1; j <= a[i]; j++) {
            int x = r[i]._1 + j;
            if (x > t[j]._1 && x <= t[j]._2) { ok = true; break; }
        }
        if (ok) ans++;
    }

    cout << ans << '\n';
    return 0;
}
