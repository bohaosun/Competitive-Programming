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

int n, a[100];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    int cnt = 0;
    while (n) {
        a[cnt++] = n % 10;
        n /= 10;
    }

    reverse(a, a + cnt);

    int ans = 1;
    for (int j = 0; j < cnt - 1; j++) ans *= 9;

    //cout << ans << '\n';

    for (int i = 0; i <= cnt; i++) {
        int cur = 1;
        for (int j = 0; j < i; j++) cur *= a[j];
        if (i == cnt) { ans = max(ans, cur); continue; }

        cur *= (a[i] - 1);
        for (int j = i + 1; j < cnt; j++) cur *= 9;
        ans = max(ans, cur);
    }

    cout << ans << '\n';
    return 0;
}
