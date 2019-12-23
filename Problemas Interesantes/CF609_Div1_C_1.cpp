#include <bits/stdc++.h>

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

const int N = 212345;

int loc[N], c[N];
int n;

inline int lowbit(int x) { return x & (-x); }

int sum(int pos) {
    int ans = 0;
    while (pos) {
        ans += c[pos];
        pos -= lowbit(pos);
    }
    return ans;
}

void add(int pos) {
    while (pos <= n) {
        ++c[pos];
        pos += lowbit(pos);
    }
}

set<int> lset, rset;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        loc[x] = i;
    }

    LL ans = 0;
    for (int i = 1; i <= n; ++i) {
        int x = loc[i];
        ans += i - 1 - sum(x);
        ans -= min(sum(x), i - 1 - sum(x));  // Get rid of the influence by x
        add(x);

        // insert the element
        if (rset.empty() || *rset.begin() < x) {
            rset.insert(x);
            int num = x - *rset.begin();
            num -= sum(x) - sum(*rset.begin());
            ans += num;
        } else {
            lset.insert(x);
            int num = *rset.begin() - x;
            num -= sum(*rset.begin()) - sum(x);
            ans += num;
        }

        if (lset.size() > rset.size()) {
            int num = *rset.begin() - *lset.rbegin() - 1;
            ans -= LL(num) * lset.size();
            ans += LL(num) * rset.size();
            rset.insert(*lset.rbegin());
            lset.erase(*lset.rbegin());
        }

        if (rset.size() > lset.size() + 1) {
            int num = *next(rset.begin()) - *rset.begin() - 1;
            ans -= LL(num) * (rset.size() - 1);
            ans += LL(num) * (lset.size() + 1);
            lset.insert(*rset.begin());
            rset.erase(*rset.begin());
        }

        cout << ans << ' ';
    }
    cout << '\n';
    return 0;
}
