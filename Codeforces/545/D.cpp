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
typedef unsigned long long ULL;
typedef pair<int, int> pii;
typedef pair<LL, LL> pll;

const int dr[] = { -1, 0, 1, 0, -1, -1, 1, 1 };
const int dc[] = { 0, -1, 0, 1, -1, 1, -1, 1 };
// Head

const int N = 512345;
const ULL x = 7;
const ULL MOD = 1e11 + 7;

int cnt[2], cnt0, cnt1, n;
string s;

ULL h[N], pw[N];

bool check() {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '1') ++cnt1;
        else ++cnt0;
    }

    return cnt[0] >= cnt0 && cnt[1] >= cnt1;
}

void rprint() {
    for (int i = 0; i < cnt[0]; i++) cout << '0';
    for (int i = 0; i < cnt[1]; i++) cout << '1';
}

int f[N];

void process() {
    f[0] = f[1] = 0;
    for (int i = 1; i < n; i++) {
        int j = f[i];
        while (j && s[i] != s[j]) j = f[j];
        f[i + 1] = s[i] == s[j] ? j + 1 : 0;
    }
}

int main() {
    pw[0] = 1;
    for (int i = 1; i <= 500005; i++) pw[i] = pw[i - 1] * x % MOD;

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;
    for (int i = 0; i < s.length(); i++) {
        ++cnt[s[i] - '0'];
    }

    cin >> s;
    n = s.length();

    if (!check()) {
        rprint();
        cout << '\n';
        return 0;
    }

    process();
    string key = s.substr(f[n]);

    string ans = s;

    cnt[0] -= cnt0;
    cnt[1] -= cnt1;

    cnt0 = cnt1 = 0;
    for (int i = 0; i < key.length(); i++) {
        if (key[i] == '0') ++cnt0;
        else ++cnt1;
    }

    while (cnt[0] >= cnt0 && cnt[1] >= cnt1) {
        ans += key;
        cnt[0] -= cnt0;
        cnt[1] -= cnt1;
    }

    cout << ans;
    rprint();
    cout << '\n';
    return 0;
}
