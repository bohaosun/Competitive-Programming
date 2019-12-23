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
 
LL lsum[N * 4], rsum[N * 4];
int ladd[N * 4], radd[N * 4];
 
LL query(int o, int l, int r, int ql, int qr, int *add, LL *sum) {
    if (ql <= l && r <= qr) return sum[o];
    int mid = l + (r - l) / 2;
    LL ans = 0;
    if (ql <= mid) ans += query(o * 2, l, mid, ql, qr, add, sum);
    if (qr > mid) ans += query(o * 2 + 1, mid + 1, r, ql, qr, add, sum);
    ans += LL(add[o]) * (min(r, qr) - max(l, ql) + 1);
    return ans;
}
 
void update(int o, int l, int r, int ql, int qr, int *add, LL *sum) {
    if (ql <= l && r <= qr) {
        ++add[o];
        sum[o] += r - l + 1;
    } else {
        int mid = l + (r - l) / 2;
        if (ql <= mid) update(o * 2, l, mid, ql, qr, add, sum);
        if (qr > mid) update(o * 2 + 1, mid + 1, r, ql, qr, add, sum);
        sum[o] = sum[o * 2] + sum[o * 2 + 1];
        sum[o] += LL(add[o]) * (r - l + 1);
    }
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
 
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        loc[x] = i;
    }
 
    LL inv = 0;
 
    for (int i = 1; i <= n; ++i) {
        int x = loc[i];
        inv += (i - 1) - sum(x);
        add(x);
        if (x > 1) update(1, 1, n, 1, x - 1, radd, rsum);
        if (x < n) update(1, 1, n, x + 1, n, ladd, lsum);
 
        int l = 1, r = n + 1;
        while (l < r) {
            int mid = l + (r - l) / 2;
            if (sum(mid) <= i / 2) l = mid + 1;
            else r = mid;
        }
 
        LL ans = 0, num = 0;
        if (l > 1) {
            ans += query(1, 1, n, 1, l - 1, ladd, lsum);
            num = sum(l - 1);
            ans -= num * (num - 1) / 2;
        }
 
        ans += query(1, 1, n, l, n, radd, rsum);
        num = i - num;
        ans -= num * (num - 1) / 2;
        cout << ans + inv << ' ';
    }
    cout << '\n';
    return 0;
}
