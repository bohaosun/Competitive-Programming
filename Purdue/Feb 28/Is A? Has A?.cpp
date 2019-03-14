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

const int N = 512;

unordered_map<string, int> pic;
bool isa[N][N];
bool hasa[N][N];

int ID(string &s, int &tot) {
    if (pic.count(s)) return pic[s];
    pic[s] = tot++;
    return pic[s];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    int tot = 0;
    for (int i = 0; i < n; i++) {
        string x, s, y;
        cin >> x >> s >> y;
        int a = ID(x, tot);
        int b = ID(y, tot);

        if (s[0] == 'i') isa[a][b] = true;
        else hasa[a][b] = true;
    }

    for (int i = 0; i < tot; i++) isa[i][i] = true;

    for (int k = 0; k < tot; k++) {
        for (int i = 0; i < tot; i++) {
            for (int j = 0; j < tot; j++) {
                isa[i][j] |= (isa[i][k] & isa[k][j]);
            }
        }
    }

    for (int k = 0; k < tot; k++) {
        for (int i = 0; i < tot; i++) {
            for (int j = 0; j < tot; j++) {
                hasa[i][j] |= (hasa[i][k] & hasa[k][j]);
                hasa[i][j] |= (hasa[i][k] & isa[k][j]);
                hasa[i][j] |= (isa[i][k] & hasa[k][j]);
            }
        }
    }

    for (int i = 1; i <= m; i++) {
        string x, s, y;
        cin >> x >> s >> y;
        int a = ID(x, tot);
        int b = ID(y, tot);

        cout << "Query " << i << ": ";
        if (s[0] == 'i') {
            if (isa[a][b]) cout << "true\n";
            else cout << "false\n";
        } else {
            if (hasa[a][b]) cout << "true\n";
            else cout << "false\n";
        }
    }
    return 0;
}
