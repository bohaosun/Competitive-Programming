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

const int N = 112345;

struct Splay {
    int root, tot, fa[N], ch[N][2], val[N], cnt[N], sz[N];
    void init() { root = tot = 0; }
    void maintain(int x) { sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + cnt[x]; }
    bool get(int x) { return x == ch[fa[x]][1]; }  // left son: 0 or right son: 1
    void clear(int x) { ch[x][0] = ch[x][1] = fa[x] = val[x] = sz[x] = cnt[x] = 0; }

    void rotate(int x) {
        int y = fa[x], z = fa[y], chk = get(x);
        ch[y][chk] = ch[x][chk ^ 1];
        fa[ch[x][chk ^ 1]] = y;
        ch[x][chk ^ 1] = y;
        fa[y] = x;
        fa[x] = z;
        if (z) ch[z][y == ch[z][1]] = x;
        maintain(y);
        maintain(x);
    }

    void splay(int x) {
        for (int f; (f = fa[x]); rotate(x)) {
            if (fa[f]) rotate(get(x) == get(f) ? f : x);
        }
        root = x;
    }

    void insert(int x) {
        if (!root) {
            val[++tot] = x;
            ++cnt[tot];
            root = tot;
            maintain(root);
            return;
        }

        int cur = root, f = 0;
        for (;;) {
            if (val[cur] == x) {
                ++cnt[cur];
                maintain(cur);
                splay(cur);
                break;
            }
            f = cur;
            cur = ch[cur][val[cur] < x];
            if (!cur) {
                val[++tot] = x;
                cnt[tot] = 1;
                fa[tot] = f;
                ch[f][val[f] < x] = tot;
                ch[tot][0] = ch[tot][1] = 0;
                maintain(tot);
                splay(tot);
                break;
            }
        }
    }

    int rank(int x) {  // get the rank of x && splay x if exists
        int ans = 0, cur = root;
        for (;;) {
            if (cur == 0) return ans + 1;
            if (x < val[cur]) cur = ch[cur][0];
            else {
                ans += sz[ch[cur][0]];
                if (x == val[cur]) {
                    splay(cur);
                    return ans + 1;
                }
                ans += cnt[cur];
                cur = ch[cur][1];
            }
        }
    }

    int kth(int k) {  // need k <= size
        int cur = root;
        for (;;) {
            if (ch[cur][0] && k <= sz[ch[cur][0]]) cur = ch[cur][0];
            else {
                k -= cnt[cur] + sz[ch[cur][0]];
                if (k <= 0) return val[cur];
                cur = ch[cur][1];
            }
        }
    }

    // The node with the number smaller than root (if doesn't exists return 0)
    int pre() {
        int cur = ch[root][0];
        while (ch[cur][1]) cur = ch[cur][1];
        return cur;
    }

    // The node with the number larger than root (if doesn't exists return 0)
    int nxt() {
        int cur = ch[root][1];
        while (ch[cur][0]) cur = ch[cur][0];
        return cur;
    }

    void erase(int x) {
        rank(x);  // splay x to root
        if (cnt[root] > 1) {
            --cnt[root];
            maintain(root);
            return;
        }
        if (!ch[root][0]) {
            int cur = root;
            root = ch[root][1];
            fa[root] = 0;
            clear(cur);
            return;
        }
        if (!ch[root][1]) {
            int cur = root;
            root = ch[root][0];
            fa[root] = 0;
            clear(cur);
            return;
        }
        int p = pre(), cur = root;
        splay(p);
        fa[ch[cur][1]] = p;
        ch[p][1] = ch[cur][1];
        clear(cur);
        maintain(root);
    }
};

Splay tree;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int op, x;
        cin >> op >> x;
        if (op == 1) tree.insert(x);
        else if (op == 2) tree.erase(x);
        else if (op == 3) cout << tree.rank(x) << '\n';
        else if (op == 4) cout << tree.kth(x) << '\n';
        else if (op == 5) {
            tree.insert(x);
            cout << tree.val[tree.pre()] << '\n';
            tree.erase(x);
        } else {
            tree.insert(x);
            cout << tree.val[tree.nxt()] << '\n';
            tree.erase(x);
        }
    }
    return 0;
}
