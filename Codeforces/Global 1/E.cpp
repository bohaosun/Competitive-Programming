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

const int N = 112345;

int n, a[N], b[N];

vector<int> v1, v2;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];

    if (a[1] != b[1] || a[n] != b[n]) { cout << "No\n"; return 0; }

    for (int i = 1; i < n; i++) {
        v1.pb(a[i + 1] - a[i]);
        v2.pb(b[i + 1] - b[i]);
    }

    sort(all(v1));
    sort(all(v2));

    if (v1 == v2) cout << "Yes\n";
    else cout << "No\n";
    return 0;
}
