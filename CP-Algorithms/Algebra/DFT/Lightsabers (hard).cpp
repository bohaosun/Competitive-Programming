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

const int MOD = 1009;

using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd> & a, bool invert) {
    int n = a.size();

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert) {
        for (cd & x : a)
            x /= n;
    }
}

vector<int> multiply(vector<int> const& a, vector<int> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size())
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    vector<int> result;
    result.resize(n);
    for (int i = 0; i < n; i++)
        result[i] = (LL)round(fa[i].real()) % MOD;  // Important, need long long here!!!
    return result;
}

const int N = 212345;

int n, m, k;
int cnt[N];

vector<int> a[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        ++cnt[x];
    }

    priority_queue<pii> pq;

    int tot = 0;
    for (int i = 1; i <= m; i++) {
        if (cnt[i]) {
            cnt[i] %= MOD;
            pq.push({ -cnt[i], i });
            for (int j = 0; j <= min(cnt[i], k); j++) a[i].pb(1);
            ++tot;
        }
    }

    //for (int i = 1; i <= m; i++) cout << a[i].size() << endl;

    while (tot >= 2) {
        pii cur1 = pq.top(); pq.pop();
        pii cur2 = pq.top(); pq.pop();
        int id1 = cur1._2, id2 = cur2._2;
        int sz = -cur1._1 - cur2._1;

        //cout << id1 << ' ' << id2 << endl;

        a[id1] = multiply(a[id1], a[id2]);

        if (sz > k) sz = k;

        pq.push({ -sz, id1 });
        a[id1].resize(sz + 1);

        //for (auto it : a[id1]) cout << it << ' ';
        //cout << endl;
        --tot;
    }

    int ans = pq.top()._2;
    a[ans].resize(k + 1);

    cout << a[ans][k] << '\n';
    return 0;
}
