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

const int dr[] = {-1, 0, 1, 0, -1, -1, 1, 1};
const int dc[] = {0, -1, 0, 1, -1, 1, -1, 1};
// Head

void gcd(LL a, LL b, LL& d, LL& x, LL& y) {
    if(!b) { d = a; x = 1; y = 0; }
    else { gcd(b, a % b, d, y, x); y -= x * (a / b); }
}

// n equations: x = a[i] mod m[i]     0 <= i < n
LL china(int n, int* a, int* m) {
    LL M = 1, d, y, x = 0;
    for(int i = 0; i < n; i++) M *= m[i];
    for(int i = 0; i < n; i++) {
        LL w = M / m[i];
        gcd(m[i], w, d, d, y);
        x = (x + y * w * a[i]) % M;
    }
    return (x + M) % M;
}

const int N = 112345;

int a[N], m[N], n;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> m[i];
    }

    cout << china(n, a, m) << '\n';
    return 0;
}
