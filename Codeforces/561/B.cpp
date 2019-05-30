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
#include <complex>

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

const char *v = "aeiou";

int main() {
    int n;
    cin >> n;

    for (int i = 5; i <= 100; i++) {
        if (n % i == 0 && n / i >= 5) {
            int id = 0;

            for (int j = 0; j < i; j++) {
                int cur = id;
                for (int k = 0; k < n / i; k++) {
                    cout << v[cur];
                    cur = (cur + 1) % 5;
                }
                id = (id + 1) % 5;
                //cout << '\n';
            }

            cout << '\n';
            return 0;
        }
    }

    cout << -1 << '\n';
    return 0;
}
