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

/**
 * vec[0] = -1
 * Suppose vec[1] + ... + vec[r - 1] = s
 * Then we need (s - 1) * r - s * (r - 1) = s - r == k
 * Just add values by greedily
 */

vector<int> vec;
int k;

int main() {
    cin >> k;

    int s = 0, r = 1;
    vec.pb(-1);
    for (;;) {
        r++;
        if (k - (s - r) <= 1000000) {
            vec.pb(k - (s - r));
            break;
        } else {
            vec.pb(1000000);
            s += 1000000;
        }
    }

    cout << vec.size() << '\n';
    for (int it : vec) cout << it << ' ';
    cout << '\n';
    return 0;
}
