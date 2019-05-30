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

string s;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;

    int n = s.length();
    int last = n;

    LL ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 1; i + 2 * j < last; j++) {
            if (s[i] == s[i + j] && s[i + j] == s[i + j * 2]) {
                last = i + 2 * j;
                break;
            }
        }
        ans += n - last;
        //cout << i << ": " << last << endl;
    }

    cout << ans << '\n';
    return 0;
}
