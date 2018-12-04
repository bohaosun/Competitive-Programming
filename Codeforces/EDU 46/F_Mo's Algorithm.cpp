#include <bits/stdc++.h>
using namespace std;

// Mo's algorithm needs to start from 0!!!

const int N = 512345;

int n, a[N], q, ans[N];

struct Interval {
    int l, r, grp, idx;
    bool operator < (const Interval& rhs) const {
        if (grp != rhs.grp) return grp < rhs.grp;
        if (grp & 1) return r > rhs.r;
        return r < rhs.r;
    }
};

Interval node[N];
int cnt[N], block[N];
int divider, answer;

inline void add(int pos) {  // inline!!!!
    if (++cnt[a[pos]] == 1) { block[a[pos] / divider]++; answer++; }
    else if (cnt[a[pos]] == 2) { block[a[pos] / divider]--; answer--; }
}

inline void sub(int pos) {  // inline!!!!
    if (--cnt[a[pos]] == 1) { block[a[pos] / divider]++; answer++; }
    else if (cnt[a[pos]] == 0) { block[a[pos] / divider]--; answer--; }
}

inline int solve(){
    if (answer == 0) {
        return 0;
    }
    for (int i = 0; i < divider; i++) {
        if (block[i] > 0) {
            for (int j = i * divider; j < i * divider + divider; j++) {
                if (cnt[j] == 1) {
                    return j;
                }
            }
        }
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    divider = 708;
    for (int i = 0; i < n; i++) cin >> a[i];
    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> node[i].l >> node[i].r;
        node[i].l--; node[i].r--;
        node[i].grp = node[i].l / divider;
        node[i].idx = i;
    }


    int l = 0, r = 0;
    cnt[a[0]]++;
    block[a[l] / divider]++;
    answer++;

    sort(node, node + q);
    for (int i = 0; i < q; i++) {
        while (r < node[i].r) add(++r);
        while (l > node[i].l) add(--l);
        while (r > node[i].r) sub(r--);
        while (l < node[i].l) sub(l++);

        ans[node[i].idx] = solve();
    }
    for (int i = 0; i < q; i++) cout << ans[i] << '\n';
    return 0;
}
