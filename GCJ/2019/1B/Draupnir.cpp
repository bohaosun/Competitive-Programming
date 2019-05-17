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
using ULL = unsigned long long;

const int dr[] = {-1, 0, 1, 0, -1, -1, 1, 1};
const int dc[] = {0, -1, 0, 1, -1, 1, -1, 1};
// Head

const int N = 63;

ULL pw[N], num;
int r[10];

int main() {
    pw[0] = 1;
    for (int i = 1; i <= N; i++) pw[i] = pw[i - 1] * 2;

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T, w;
    cin >> T >> w;
    while (T--) {

        cout << 210 << endl;
        cin >> num;

        r[6] = num % pw[42] / pw[35];
        num -= r[6] * pw[33];
        r[5] = num % pw[52] / pw[42];
        num -= r[5] * pw[42];
        r[4] = num / pw[52];

        cout << 42 << endl;
        cin >> num;

        for (int i = 4; i <= 6; i++) num -= pw[42 / i] * r[i];
        r[3] = num % pw[21] / pw[14];
        num -= r[3] * pw[14];
        r[2] = num % pw[42] / pw[21];
        num -= r[2] * pw[21];
        r[1] = num / pw[42];

        cout << r[1];
        for (int i = 2; i <= 6; i++) cout << ' ' << r[i];
        cout << endl;

        cin >> num;
        assert(num == 1);
    }
    return 0;
}
