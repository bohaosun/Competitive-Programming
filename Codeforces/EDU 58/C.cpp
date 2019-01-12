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

const int N = 112345;

vector<pair<pii, int>> vec;
int n, ans[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        vec.clear();
        for (int i = 0; i < n; i++) {
            int l, r;
            cin >> l >> r;
            vec.pb({ { l, r }, i});
        }
        sort(all(vec));
        int pos = -1, maxm = vec[0]._1._2;
        for (int i = 1; i < n; i++) {
            if (vec[i]._1._1 > maxm) {
                pos = maxm;
                break;
            }
            maxm = max(maxm, vec[i]._1._2);
        }
        if (pos == -1) { cout << -1 << '\n'; continue; }

        for (int i = 0; i < n; i++) {
            if (vec[i]._1._2 <= pos) ans[vec[i]._2] = 1;
            else ans[vec[i]._2] = 2;
        }
        for (int i = 0; i < n; i++) cout << ans[i] << ' ';
        cout << '\n';
    }
    return 0;
}
