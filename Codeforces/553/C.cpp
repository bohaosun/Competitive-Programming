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

const int MOD = 1000000007;

LL sum(LL n) {
    LL cnt[] = { 0, 0 };
    int cur = 1;
    LL tot = 0, num = 1;

    for (;;) {
        if (tot + num <= n) {
            cnt[cur] += num;
            tot += num;
            cur ^= 1;
            num *= 2;
        } else {
            cnt[cur] += n - tot;
            break;
        }
    }

    LL odd = (cnt[1] % MOD) * (cnt[1] % MOD) % MOD;
    LL even = ((cnt[0] + 1) % MOD) * (cnt[0] % MOD) % MOD;

    return (odd + even) % MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    LL l, r;
    cin >> l >> r;
    cout << (sum(r) - sum(l - 1) + MOD) % MOD << '\n';
    return 0;
}
