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

void ask(int r1, int c1, int r2, int c2) {
    cout << "? " << r1 << ' ' << c1 << ' ' << r2 << ' ' << c2 << endl;
}

void answer(int r1, int c1, int r2, int c2) {
    cout << "! " << r1 << ' ' << c1 << ' ' << r2 << ' ' << c2 << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;

    vector<int> r, c;
    for (int i = 1; i <= n; i++) {
        ask(i, 1, i, n);
        int num;
        cin >> num;
        if (num & 1) r.pb(i);

        ask(1, i, n, i);
        cin >> num;
        if (num & 1) c.pb(i);
    }

    if (!r.empty() && !c.empty()) {
        vector<pii> ans;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                ask(r[i], c[j], r[i], c[j]);
                int num;
                cin >> num;
                if (num & 1) ans.pb({ r[i], c[j] });
            }
        }
        answer(ans[0]._1, ans[0]._2, ans[1]._1, ans[1]._2);
        int num;
        cin >> num;
        assert(num != -1);
    } else if (r.empty()) {
        int lef = 1, rig = n + 1;
        while (lef < rig) {
            int mid = lef + (rig - lef) / 2;
            ask(1, c[0], mid, c[0]);
            int num;
            cin >> num;
            if (num & 1) rig = mid;
            else lef = mid + 1;
        }
        answer(lef, c[0], lef, c[1]);
        int num;
        cin >> num;
        assert(num != -1);
    } else {
        int lef = 1, rig = n + 1;
        while (lef < rig) {
            int mid = lef + (rig - lef) / 2;
            ask(r[0], 1, r[0], mid);
            int num;
            cin >> num;
            if (num & 1) rig = mid;
            else lef = mid + 1;
        }
        answer(r[0], lef, r[1], lef);
        int num;
        cin >> num;
        assert(num != -1);
    }
    return 0;
}
