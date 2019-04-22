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

int n, t;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> t;
    int minm = 1000000, id = -1;

    for (int i = 0; i < n; i++) {
        int s, d;
        cin >> s >> d;
        if (s >= t) {
            if (s - t < minm) {
                minm = s - t;
                id = i + 1;
            }
        } else {
            int tmp = t - s;
            for (int j = 1; ; j++) {
                if (j * d >= tmp) {
                    int val = j * d - tmp;
                    if (val < minm) {
                        minm = val;
                        id = i + 1;
                    }
                    break;
                }
            }
        }
    }

    cout << id << '\n';
    return 0;
}
