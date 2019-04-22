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

const int N = 1123;

int n, h;
int a[N], b[N];

bool check(int val) {
    for (int i = 1; i <= val; i++) b[i] = a[i];
    sort(b + 1, b + val + 1);
    reverse(b + 1, b + val + 1);

    int rem = h;
    for (int i = 1; i <= val; i += 2) {
        if (rem < b[i]) return false;
        rem -= b[i];
    }
    return true;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> h;
    for (int i = 1; i <= n; i++) cin >> a[i];

    int l = 0, r = n + 1;

    while (l < r) {
        int mid = l + (r - l) / 2;
        if (check(mid)) l = mid + 1;
        else r = mid;
    }

    cout << l - 1 << '\n';
    return 0;
}
