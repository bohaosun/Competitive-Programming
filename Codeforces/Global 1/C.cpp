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

int q;

map<int, int> pic;

// gcd(a + b, b) == gcd(a, b)!!!

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    pic = {
            { 3, 1 },
            { 7, 1 },
            { 15, 5 },
            { 31, 1 },
            { 63, 21 },
            { 127, 1 },
            { 255, 85 },
            { 511, 73 },
            { 1023, 341 },
            { 2047, 89 },
            { 4095, 1365 },
            { 8191, 1 },
            { 16383, 5461 },
            { 32767, 4681 },
            { 65535, 21845 },
            { 131071, 1 },
            { 262143, 87381 },
            { 524287, 1 },
            { 1048575, 349525 },
            { 2097151, 299593 },
            { 4194303, 1398101 },
            { 8388607, 178481 },
            { 16777215, 5592405 },
            { 33554431, 1082401 },
            { 67108863, 22369621 }
    };

    cin >> q;
    while (q--) {
        int a, b = 0;
        cin >> a;
        //if (pic.count(a)) { cout << pic[a] << '\n'; continue; }
        for (int i = 0; (1 << i) <= a; i++) {
            if (!((1 << i) & a)) b |= (1 << i);
        }
        if (b == 0) {
            bool ok = false;
            int r = sqrt(a + 0.5);

            for (int i = 2; i <= r; i++) {
                if (a % i == 0) {
                    cout << a / i << '\n';
                    ok = true;
                    break;
                }
            }
            if (!ok) cout << 1 << '\n';
        } else {
            cout << (a | b) << '\n';
        }
    }
    return 0;
}
