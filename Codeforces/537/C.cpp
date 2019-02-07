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

const int N = 30 + 5;

vector<int> pos;
LL dp[N][N];

int n, m;
LL A, B;

int get_num(int l, int r) {
    return upper_bound(all(pos), r) - upper_bound(all(pos), l - 1);
}

LL solve(int l, int r) {
    //cout << l << ' ' << r << endl;
    LL num = get_num(l, r);

    //cout << num << endl;
    if (num == 0) return A;
    if (l == r) return num * B;

    int mid = l + (r - l) / 2;
    LL num1 = get_num(l, mid);
    LL num2 = num - num1;
    if (num1 && num2) return solve(l, mid) + solve(mid + 1, r);

    if (num1) return min(B * num * (r - l + 1), A + solve(l, mid));
    return min(B * num * (r - l + 1), A + solve(mid + 1, r));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> A >> B;
    for (int i = 0; i < m; i++) {
        int x;
        cin >> x;
        pos.pb(x);
    }
    //for (int i = 0; i < pos.size(); i++) cout << pos[i] << endl;
    sort(all(pos));


    cout << solve(1, (1 << n)) << '\n';
    return 0;
}
