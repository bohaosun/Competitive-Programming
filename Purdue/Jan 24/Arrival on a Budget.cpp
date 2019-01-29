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

struct BigInteger {
    static const int BASE = 100000000;
    static const int WIDTH = 8;
    vector<int> s;

    BigInteger& clean(){ while(!s.back() && s.size() > 1) s.pop_back(); return *this; }
    BigInteger(long long num = 0) { *this = num; }
    BigInteger operator = (long long num) {
        s.clear();
        do {
            s.push_back(num % BASE);
            num /= BASE;
        } while(num > 0);
        return *this;
    }
    BigInteger operator = (const string& str) {
        s.clear();
        int x, len = (str.length() - 1)/WIDTH + 1;
        for(int i = 0; i < len; i++) {
            int end = str.length() - i*WIDTH;
            int start = max(end-WIDTH, 0);
            sscanf(str.substr(start, end - start).c_str(), "%d", &x);
            s.push_back(x);
        }
        return *this;
    }

    bool operator < (const BigInteger& b) const {
        if(s.size() != b.s.size()) return s.size() < b.s.size();
        for(int i = s.size() - 1; i >= 0; i--)
            if(s[i] != b.s[i]) return s[i] < b.s[i];
        return false;
    }
    bool operator > (const BigInteger& b) const { return b < *this; }
    bool operator <= (const BigInteger& b) const { return !(b < *this); }
    bool operator >= (const BigInteger& b) const { return !(*this < b); }
    bool operator != (const BigInteger& b) const { return b < *this || b > *this; }
    bool operator == (const BigInteger& b) const { return !(b < *this) && !(b > *this); }

    BigInteger operator + (const BigInteger& b) const {
        BigInteger c;
        c.s.clear();
        for(int i = 0, g = 0; ; i++) {
            if(g == 0 && i >= s.size() && i >= b.s.size()) break;
            int x = g;
            if(i < s.size()) x += s[i];
            if(i < b.s.size()) x += b.s[i];
            c.s.push_back(x % BASE);
            g = x / BASE;
        }
        return c.clean();
    }
    BigInteger operator - (const BigInteger& b) const {
        BigInteger c;
        c.s.clear();
        assert(b <= *this);
        for(int i = 0, g = 0; ; i++) {
            if(g == 0 && i >= s.size() && i >= b.s.size()) break;
            int x = g + s[i];
            if(i < b.s.size()) x -= b.s[i];
            if(x < 0) { g = -1; x += BASE; } else g = 0;
            c.s.push_back(x);
        }
        return c.clean();
    }
    BigInteger operator * (const BigInteger& b) const {
        BigInteger c;
        c.s.clear();
        vector<long long> v(s.size()+b.s.size(), 0);
        //v.clear();
        long long g = 0;
        for(int i = 0; i < s.size(); i++)
            for(int j = 0; j < b.s.size(); j++)
                v[i+j] += (long long)s[i]*b.s[j];
        for(int i = 0; ; i++) {
            if(i >= v.size() && g == 0) break;
            long long x = v[i] + g;
            c.s.push_back(x % BASE);
            g = x / BASE;
        }
        return c.clean();
    }
    BigInteger operator / (const BigInteger& b) const {
        assert(b > 0);
        if(*this < b) return 0;
        BigInteger c = *this;
        BigInteger m;
        m.s.clear();
        for(int i = s.size()-1; i >= 0; i--) {
            m = m*BASE + s[i];
            c.s[i] = bsearch(b, m);
            m = m - b*c.s[i];
        }
        return c.clean();
    }
    BigInteger operator % (const BigInteger& b) const {
        assert(b > 0);
        if(*this <= b) return *this;
        BigInteger c = *this;
        BigInteger m;
        m.s.clear();
        for(int i = s.size()-1; i >= 0; i--) {
            m = m*BASE + s[i];
            c.s[i] = bsearch(b, m);
            m = m - b*c.s[i];
        }
        return m;
    }
    int bsearch(const BigInteger& b, const BigInteger& m) const{
        int L = 0, R = BASE-1, x;
        while (1) {
            x = (L+R)>>1;
            if (b*x<=m) { if(b*(x+1)>m) return x; else L = x; }
            else R = x;
        }
    }
    BigInteger& operator += (const BigInteger& b) {*this = *this + b; return *this;}
    BigInteger& operator -= (const BigInteger& b) {*this = *this - b; return *this;}
    BigInteger& operator *= (const BigInteger& b) {*this = *this * b; return *this;}
    BigInteger& operator /= (const BigInteger& b) {*this = *this / b; return *this;}
    BigInteger& operator %= (const BigInteger& b) {*this = *this % b; return *this;}
};

ostream& operator << (ostream &out, const BigInteger& x) {
    out << x.s.back();
    for(int i = x.s.size()-2; i >= 0; i--) {
        char buf[20];
        sprintf(buf, "%08d", x.s[i]);
        for(int j = 0; j < strlen(buf); j++) out << buf[j];
    }
    return out;
}
istream& operator >> (istream &in, BigInteger& x) {
    string s;
    if(!(in >> s)) return in;
    x = s;
    return in;
}

const int N = 11234;

char s[N];
LL dp[N];

int main() {
    scanf("%s", s + 1);
    int n = strlen(s + 1);

    dp[0] = dp[1] = 1;
    for (int i = 2; i <= n; i++) {
        dp[i] = 0;
        if (s[i] != '0') dp[i] += dp[i - 1];

        int num = (s[i - 1] - '0') * 10 + s[i] - '0';
        if (10 <= num && num <= 26) dp[i] += dp[i - 2];
    }
    cout << dp[n] << '\n';
    return 0;
}
