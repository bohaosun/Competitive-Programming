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

const int N = 212345;

int n, cnt[N], minm, maxm;
vector<pii> vec;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        //reset(cnt, 0);
        cin >> n;
        maxm = 0, minm = 10000000;
        vec.clear();
        for (int i = 0; i < n; i++) {
            int l, r;
            cin >> l >> r;
            cnt[l]++;
            cnt[r]--;
            minm = min(minm, l);
            maxm = max(maxm, r);
            vec.pb({ l, r });
        }

        int tot = 0, pos = -1;
        for (int i = minm; i < maxm; i++) {
            tot += cnt[i];
            if (tot == 0) { pos = i; break; }
        }

        for (int i = 0; i < n; i++) {
            cnt[vec[i]._1]--;
            cnt[vec[i]._2]++;
        }

        if (pos == -1) { cout << -1 << '\n'; continue; }
        for (int i = 0; i < n; i++) {
            if (vec[i]._2 <= pos) cout << 1 << ' ';
            else cout << 2 << ' ';
        }
        cout << '\n';
    }
    return 0;
}
