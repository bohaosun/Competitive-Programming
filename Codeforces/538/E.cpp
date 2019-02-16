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

int gcd(int a, int b) { return !b ? a : gcd(b, a % b); }

int n;

mt19937 rand_generator;
int int_rand(int l, int r) {
    uniform_int_distribution<int> rand_distribution(l, r);
    return rand_distribution(rand_generator);
}

int main() {
    //random_device rdev;
    srand(time(0));
    rand_generator.seed(rand());

    //for (int i = 0; i < 10; i++) cout << int_rand(1, 1000) << endl;

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    int l = 0, r = int(1e9);

    int tot = 0;
    while (l < r) {
        tot++;
        int mid = (l + r) / 2;
        cout << "> " << mid << endl;
        int ok;
        cin >> ok;
        if (ok) l = mid + 1;
        else r = mid;
    }

    int maxm = l;
    vector<int> vec;

    for (int i = 0; i < 60 - tot; i++) {
        cout << "? " << int_rand(1, n) << endl;
        int val;
        cin >> val;
        vec.pb(val);
    }

    sort(all(vec));
    uni(vec);
    int d = 0;
    for (int i = 0; i < vec.size() - 1; i++) d = gcd(d, vec[i + 1] - vec[i]);
    assert(vec.size() > 1);
    cout << "! " << maxm - d * (n - 1) << ' ' << d << endl;
    return 0;
}
