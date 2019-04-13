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

const int N = 1123456;
const int a[] = { 3, 4, 5, 7, 11, 13, 17 };

int rnd[10];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T, n, m;
    cin >> T >> n >> m;
    for (int kase = 1; kase <= T; kase++) {
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 18; j++) cout << a[i] << ' ';
            cout << endl;

            int tot = 0;
            for (int j = 0; j < 18; j++) {
                int x;
                cin >> x;
                tot = (tot + x) % a[i];
            }
            rnd[i] = tot;
        }

        for (int i = 1; i <= 1000000; i++) {
            bool ok = true;
            for (int j = 0; j < 7; j++) {
                if (i % a[j] != rnd[j]) { ok = false; break; }
            }

            if (ok) {
                cout << i << endl;
                int ret;
                cin >> ret;
                assert(ret == 1);
                break;
            }
        }
    }

    return 0;
}
