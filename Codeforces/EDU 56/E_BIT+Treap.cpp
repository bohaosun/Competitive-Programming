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
#define all(x) (x).begin(), (x).end()
#define uni(x) (x).erase(unique(all(x)), (x).end());
#define reset(x, y) memset(x, y, sizeof(x))
#define BUG(x) cerr << #x << " = " << (x) << endl
#define mp make_pair
using namespace std;

typedef long long LL;
typedef pair<int, int> pii;
typedef pair<LL, LL> pll;
// Head

#define rank rank1

const int N = 212345;

struct Node {
    Node *ch[2];                  
    int r;                        
    int v;                        
    int s;                        
    Node(int v): v(v) { ch[0] = ch[1] = NULL; r = rand(); s = 1; }
    int cmp(int x) const {
        if(x == v) return -1;
        return x < v ? 0 : 1;
    }
    void maintain() {
        s = 1;
        if(ch[0] != NULL) s += ch[0]->s;
        if(ch[1] != NULL) s += ch[1]->s;
    }
};

bool find(Node* o, int x) {
    while(o != NULL) {
        int d = o->cmp(x);
        if(d == -1) return true;
        else o = o->ch[d];
    }
    return false;
}

void rotate(Node* &o, int d) {  
    Node* k = o->ch[d ^ 1];
    o->ch[d ^ 1] = k->ch[d];
    k->ch[d] = o;
    o->maintain(); k->maintain();
    o = k;
}

void insert(Node* &o, int x) {  
    if(o == NULL) o = new Node(x);
    else {
        int d = o->cmp(x);      
        insert(o->ch[d], x);
        if(o->ch[d]->r > o->r) rotate(o, d ^ 1);
    }
    o->maintain();
}

void remove(Node* &o, int x) {   
    int d = o->cmp(x);
    if(d == -1) {
        if(o->ch[0] == NULL) o = o->ch[1];
        else if(o->ch[1] == NULL) o = o->ch[0];
        else {
            int d2 = (o->ch[0]->r > o->ch[1]->r ? 1 : 0);
            rotate(o, d2); remove(o->ch[d2], x);
        }
    } else remove(o->ch[d], x);
    if(o != NULL) o->maintain();
}

int kth(Node* o, int k) {   
    if(o == NULL || k <= 0 || k > o->s) return -1;
    int s = (o->ch[1] == NULL ? 0 : o->ch[1]->s);
    if(k == s + 1) return o->v;
    else if(k <= s) return kth(o->ch[1], k);
    else return kth(o->ch[0], k - s - 1);
}

int rank(Node* o, int x) {
    if (o == NULL) return 1;
    int s = (o->ch[1] == NULL ? 0 : o->ch[1]->s);
    if (x >= o->v) return rank(o->ch[1], x);
    else return rank(o->ch[0], x) + s + 1;
}

Node* root[N];
int n, q;
int a[N], b[N];

int lowbit(int x) { return x & (-x); }

void add(int pos, int val) {
    while (pos <= n) {
        insert(root[pos], val);
        pos += lowbit(pos);
    }
}

int sum(int pos, int val) {
    int ans = 0;
    while (pos) {
        ans += rank(root[pos], val);
        pos -= lowbit(pos);
    }
    return ans;
}

void rem(int pos, int val) {
    while (pos <= n) {
        remove(root[pos], val);
        pos += lowbit(pos);
    }
}

int main() {

    scanf("%d%d", &n, &q);

    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        a[x] = i;
    }
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        b[i] = a[x];
    }

    for (int i = 1; i <= n; i++) add(i, b[i]);

    while (q--) {
        int id;
        scanf("%d", &id);
        if (id == 1) {
            int la, ra, lb, rb;
            scanf("%d%d%d%d", &la, &ra, &lb, &rb);
            int ans = sum(rb, la - 1) - sum(lb - 1, la - 1);
            ans -= sum(rb, ra) - sum(lb - 1, ra);
            printf("%d\n", ans);
        } else {
            int x, y;
            scanf("%d%d", &x, &y);
            rem(x, b[x]);
            rem(y, b[y]);
            swap(b[x], b[y]);
            add(x, b[x]);
            add(y, b[y]);
        }
    }
    return 0;
}
