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

const int N = 1123456;

int maxm[N * 4], lef[N * 4], rig[N * 4];
int n, m;
string s;
vector<pii> vec;
int ans;

void build(int o, int l, int r) {
    if (l == r) {
        if (s[l] == '(') lef[o] = 1;
        else rig[o] = 1;
        return;
    }

    int mid = l + (r - l) / 2;
    build(o * 2, l, mid);
    build(o * 2 + 1, mid + 1, r);

    int lcnt = 0;
    for (int i = l; i <= r; i++) {
        if (s[i] == '(') { lcnt++; lef[o]++; }
        else {
            if (lcnt) { lcnt--; maxm[o] += 2; }
            rig[o]++;
        }
    }
    lef[o] -= maxm[o] / 2;
    rig[o] -= maxm[o] / 2;
}

void query(int o, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        ans += maxm[o];
        vec.pb({ lef[o], rig[o] });
        return;
    }

    int mid = l + (r - l) / 2;
    if (ql <= mid) query(o * 2, l, mid, ql, qr);
    if (qr > mid) query(o * 2 + 1, mid + 1, r, ql, qr);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;
    n = s.length();

    build(1, 0, n - 1);

    //query(1, 0, n - 1, 0, 3);
    //cout << ans << endl;
    //for (int i = 0; i < vec.size(); i++) cout << vec[i]._1 << ' ' << vec[i]._2 << endl;

    cin >> m;
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        l--; r--;
        vec.clear();
        ans = 0;
        query(1, 0, n - 1, l, r);

        //cout << ans << endl;
        //for (int j = 0; j < vec.size(); j++) cout << vec[j]._1 << ' ' << vec[j]._2 << endl;

        int lcnt = 0;
        for (int j = 0; j < vec.size(); j++) {
            int rcnt = vec[j]._2;
            ans += min(lcnt, rcnt) * 2;
            lcnt -= min(lcnt, rcnt);
            lcnt += vec[j]._1;
        }
        cout << ans << '\n';
    }
    return 0;
}
