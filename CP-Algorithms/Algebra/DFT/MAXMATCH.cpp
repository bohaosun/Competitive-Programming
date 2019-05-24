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
typedef pair <LL, LL> pll;

const int dr[] = {-1, 0, 1, 0, -1, -1, 1, 1};
const int dc[] = {0, -1, 0, 1, -1, 1, -1, 1};
// Head

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

void multiply(vector<int> const& a, vector<int> const& b, vector<int> &result) {
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

result.resize(n);
for (int i = 0; i < n; i++)
result[i] = round(fa[i].real());
}

const int N = 112345;

string s;
vector<int> a, b, ans;

int cnt[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;
    int n = s.length();
    a.resize(n * 2);
    b.resize(n * 2);

    for (int i = 0; i < 3; i++) {
        char c = char(i + 'a');

        for (int j = 0; j < n; j++) {
            a[j] = b[n - j - 1] = (s[j] == c);
        }

        multiply(a, b, ans);
        for (int j = n; j < n * 2 - 1; j++) cnt[j - n + 1] += ans[j];
    }

    int maxm = 0;
    for (int i = 1; i < n; i++) {
        maxm = max(maxm, cnt[i]);
        //cout << i << ' ' << cnt[i] << endl;
    }
    cout << maxm << '\n';

    for (int i = 1; i < n; i++) {
        if (cnt[i] == maxm) cout << i << '\n';
    }
    return 0;
}
