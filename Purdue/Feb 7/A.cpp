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

const int N = 20;

int a[N];

bool check(int l, int r) {
    int minm = a[l], maxm = a[l];
    for (int i = l + 1; i <= r; i++) {
        minm = min(minm, a[i]);
    }
    if (l > 0) {
        if (minm <= a[l - 1]) return false;
    }
    if (r < 14) {
        if (minm <= a[r + 1]) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 0; i < 15; i++) cin >> a[i];
    int ans = 0;
    for (int i = 1; i < 14; i++) {
        for (int j = i; j < 14; j++) {
            if (check(i, j)) ans++;
        }
    }
    cout << ans << '\n';
    return 0;
}
