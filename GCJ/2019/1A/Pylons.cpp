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

int n, m;
bool rev;

vector<pii> ans;
vector<pii> ans2;

vector<pii> tmp34 = {
        { 1, 1 },
        { 2, 3 },
        { 3, 1 },
        { 1, 2 },
        { 2, 4 },
        { 3, 2 },
        { 1, 3 },
        { 2, 1 },
        { 3, 3 },
        { 1, 4 },
        { 2, 2 },
        { 3, 4 }
};

vector<pii> tmp35 = {
        { 1, 1 },
        { 2, 3 },
        { 1, 5 },
        { 2, 1 },
        { 1, 3 },
        { 2, 5 },
        { 3, 2 },
        { 2, 4 },
        { 3, 1 },
        { 1, 2 },
        { 3, 3 },
        { 1, 4 },
        { 3, 5 },
        { 2, 2 },
        { 3, 4 }
};

vector<pii> tmp36 = {
        { 1, 1 },
        { 2, 3 },
        { 1, 5 },
        { 2, 1 },
        { 1, 3 },
        { 2, 5 },
        { 1, 2 },
        { 3, 1 },
        { 1, 4 },
        { 3, 3 },
        { 1, 6 },
        { 3, 5 },
        { 2, 2 },
        { 3, 4 },
        { 2, 6 },
        { 3, 2 },
        { 2, 4 },
        { 3, 6 }
};

vector<pii> tmp37 = {
        { 1, 1 },
        { 2, 3 },
        { 1, 5 },
        { 2, 1 },
        { 1, 3 },
        { 2, 5 },
        { 1, 2 },
        { 2, 4 },
        { 3, 1 },
        { 1, 4 },
        { 3, 3 },
        { 1, 6 },
        { 3, 5 },
        { 2, 7 },
        { 3, 2 },
        { 2, 6 },
        { 3, 4 },
        { 1, 7 },
        { 3, 6 },
        { 2, 2 },
        { 3, 7 }
};

vector<pii> ans4 = {
        { 1, 1 },
        { 2, 3 },
        { 3, 1 },
        { 1, 2 },
        { 2, 4 },
        { 3, 2 },
        { 1, 3 },
        { 3, 4 },
        { 4, 2 },
        { 1, 4 },
        { 4, 3 },
        { 2, 2 },
        { 4, 1 },
        { 3, 3 },
        { 2, 1 },
        { 4, 4 }
};

void solve3(int r) {
    vector<pii> ans3[10];
    ans3[4] = tmp34;
    ans3[5] = tmp35;
    ans3[6] = tmp36;
    ans3[7] = tmp37;

    int acc = 0;
    for (int i = 1; ; i += 4) {
        if (m - i + 1 <= 7) {
            int val = m - i + 1;
            for (auto it : ans3[val]) ans.pb({ r + it._1 - 1, it._2 + acc });
            break;
        }
        for (auto it : ans3[4]) ans.pb({ r + it._1 - 1, it._2 + acc });
        acc += 4;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);


    int T;
    cin >> T;

    for (int kase = 1; kase <= T; kase++) {
        cout << "Case #" << kase << ": ";
        cin >> n >> m;

        ans.clear();
        ans2.clear();
        rev = false;
        if (n > m) {
            swap(n, m);
            rev = true;
        }

        if (n == 4 && m == 4) {
            cout << "POSSIBLE\n";
            for (auto it : ans4) cout << it._1 << ' ' << it._2 << '\n';
            continue;
        }

        if (n % 3 == 0) {
            if (m < 4) {
                cout << "IMPOSSIBLE\n";
                continue;
            }
        } else {
            if (m < 5) {
                cout << "IMPOSSIBLE\n";
                continue;
            }
        }
        cout << "POSSIBLE\n";

        for (int i = 1; i + 3 <= m; i++) { ans2.pb({ 1, i }); ans2.pb({ 2, i + 3 }); }
        for (int i = m - 2; i <= m; i++) { ans2.pb({ 1, i }); ans2.pb({ 2, i - m + 3 }); }

        if (n % 3 == 0) {
            for (int i = 1; i <= n; i += 3) solve3(i);
        } else {
            for (int i = 1; i <= n; i += 2) {
                if (n - i == 2) { solve3(i); break; }
                else {
                    for (pii it : ans2) ans.pb({ it._1 + i - 1, it._2 });
                }
            }
        }

        if (rev) {
            for (auto it : ans) cout << it._2 << ' ' << it._1 << '\n';
        } else {
            for (auto it : ans) cout << it._1 << ' ' << it._2 << '\n';
        }
    }
    return 0;
}
