#include <bits/stdc++.h>

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

const int N = 7;

string tem;
bool vis[N][N];
int ans;

bool valid(int r, int c) {
    return r >= 0 && c >= 0 && r < N && c < N && !vis[r][c];
}

void dfs(int r, int c, int num) {
    if (r == N - 1 && c == 0) {
        if (num == sqr(N) - 1) ++ans;
        return;
    }

    if (num == sqr(N) - 1) return;

    vis[r][c] = true;

    if (tem[num] == '?' || tem[num] == 'L') {
        if (valid(r, c - 1) && !(!valid(r, c - 2) && valid(r - 1, c - 1) && valid(r + 1, c - 1)))
            dfs(r, c - 1, num + 1);
    }

    if (tem[num] == '?' || tem[num] == 'R') {
        if (valid(r, c + 1) && !(!valid(r, c + 2) && valid(r - 1, c + 1) && valid(r + 1, c + 1)))
            dfs(r, c + 1, num + 1);
    }

    if (tem[num] == '?' || tem[num] == 'U') {
        if (valid(r - 1, c) && !(!valid(r - 2, c) && valid(r - 1, c - 1) && valid(r - 1, c + 1)))
            dfs(r - 1, c, num + 1);
    }

    if (tem[num] == '?' || tem[num] == 'D') {
        if (valid(r + 1, c) && !(!valid(r + 2, c) && valid(r + 1, c - 1) && valid(r + 1, c + 1)))
            dfs(r + 1, c, num + 1);
    }

    vis[r][c] = false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> tem;
    dfs(0, 0, 0);

    cout << ans << '\n';
    return 0;
}
