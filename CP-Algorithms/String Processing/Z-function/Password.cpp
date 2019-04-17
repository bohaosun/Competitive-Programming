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

const int dr[] = { -1, 0, 1, 0, -1, -1, 1, 1 };
const int dc[] = { 0, -1, 0, 1, -1, 1, -1, 1 };
// Head

const int N = 1123456;

string s;
vector<int> z;
int cnt[2][N];

void z_function() {
    int n = s.length();
    z.resize(n);

    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r) z[i] = min(z[i - l], r - i + 1);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if (i + z[i] - 1 >= r) { l = i; r = i + z[i] - 1; }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;
    z_function();

    int n = s.length();
    for (int i = 1; i < n; i++) {
        if (i + z[i] == n) { cnt[1][z[i]]++; cnt[0][z[i] - 1]++; }
        else cnt[0][z[i]]++;
    }

    bool ok = false;
    for (int i = n; i >= 0; i--) {
        if (cnt[0][i]) ok = true;
        if (cnt[1][i] && ok) {
            for (int j = 0; j < i; j++) cout << s[j];
            cout << '\n';
            return 0;
        }
    }
    cout << "Just a legend\n";
    return 0;
}
