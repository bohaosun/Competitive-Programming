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

const int dr[] = {-1, 0, 1, 0, -1, -1, 1, 1};
const int dc[] = {0, -1, 0, 1, -1, 1, -1, 1};
// Head

struct Node {
    int t, b;
    bool operator < (const Node &rhs) const {
        return b > rhs.b;
    }
};

vector<Node> node;
int n, k;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        int t, b;
        cin >> t >> b;
        node.pb({ t, b });
    }

    sort(all(node));

    multiset<int> s;
    LL sum = 0, ans = 0;
    for (int i = 0; i < k; i++) {
        s.insert(node[i].t);
        sum += node[i].t;
        ans = max(ans, sum * node[i].b);
    }

    for (int i = k; i < n; i++) {
        s.insert(node[i].t);
        sum += node[i].t;
        sum -= *(s.begin());
        s.erase(s.begin());
        ans = max(ans, sum * node[i].b);
    }

    cout << ans << '\n';
    return 0;
}
