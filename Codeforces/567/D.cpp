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
#define BUG(x) cerr << #x << " = " << (x) << endl
#define BUGP(x) cout << #x << " = " << (x)._1 << ", " << (x)._2 << endl
using namespace std;

typedef long long LL;
typedef pair<int, int> pii;
typedef pair<LL, LL> pll;

const int dr[] = {-1, 0, 1, 0, -1, -1, 1, 1};
const int dc[] = {0, -1, 0, 1, -1, 1, -1, 1};
// Head

const int N = 512345;

int n, m, q;
int cnt[N], ans[N], f[N];
pair<LL, int> que[N];

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
ordered_set<int> s;

bool cmp(int a, int b) { return cnt[a] < cnt[b]; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);


    cin >> n >> m >> q;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        ++cnt[x];
    }

    for (int i = 1; i <= m; i++) f[i] = i;
    sort(f + 1, f + m + 1, cmp);


    for (int i = 0; i < q; i++) {
        LL x;
        cin >> x;
        x -= n;
        que[i] = { x, i };
    }

    sort(que, que + q);

    int sum = 0, cur = 0;

    for (int i = 1; i <= m; i++) {
        int id = f[i];

        LL need = LL(i - 1) * cnt[id] - sum;

        while (cur < q && que[cur]._1 <= need) {
            LL sub = que[cur]._1 - (LL(i - 1) * cnt[f[i - 1]] - sum);
            sub %= (i - 1);
            sub = (sub - 1 + i - 1) % (i - 1);

            ans[que[cur]._2] = *s.find_by_order(sub);
            ++cur;
        }
        s.insert(id);
        sum += cnt[id];
    }

    while (cur < q) {
        LL sub = que[cur]._1 - (LL(m) * cnt[f[m]] - sum);
        sub %= m;
        sub = (sub - 1 + m) % m;

        ans[que[cur]._2] = *s.find_by_order(sub);
        ++cur;
    }

    for (int i = 0; i < q; i++) cout << ans[i] << '\n';
    return 0;
}
