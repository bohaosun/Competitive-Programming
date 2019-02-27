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

const int N = 11234;
int n;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int last[2] = { }, a[2];
    cin >> n;


    int ans = 0, count = -1;
    for (int i = 0; i < n; i++) {
        cin >> a[0] >> a[1];

        int minm = max(last[0], last[1]);
        int maxm = min(a[0], a[1]);
        int cur = maxm - minm + 1;

        if (cur > 0) {
            if (count >= minm) cur--;
            ans += cur;
            count = maxm;
        }
        last[0] = a[0]; last[1] = a[1];
    }


    cout << ans << '\n';
    return 0;
}
