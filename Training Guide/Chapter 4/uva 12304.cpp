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

/**
 * Basic
 */
const double eps = 1e-6;
const double PI = acos(-1.0);

struct Point {
    double x, y;
    Point(double x = 0, double y = 0): x(x), y(y) {}
};
int dcmp(double x) {
    if (abs(x) < eps) return 0; else return x < 0 ? -1 : 1;
}
typedef Point Vector;
Vector operator + (Vector A, Vector B) { return Vector(A.x + B.x, A.y + B.y); }
Vector operator - (Vector A, Vector B) { return Vector(A.x - B.x, A.y - B.y); }
Vector operator * (Vector A, double p) { return Vector(A.x * p, A.y * p); }
Vector operator / (Vector A, double p) { return Vector(A.x / p, A.y / p); }
bool operator < (const Point& a, const Point& b) {
    return dcmp(a.x - b.x) < 0 || (dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) < 0);
}
bool operator == (const Point& a, const Point& b) {
    return dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) == 0;
}
double Dot(Vector A, Vector B) { return A.x * B.x + A.y * B.y; }
double Length(Vector A) { return sqrt(Dot(A, A)); }
double Angle(Vector A, Vector B) { return acos(Dot(A, B) / Length(A) / Length(B)); }  // In rad
double Cross(Vector A, Vector B) { return A.x * B.y - A.y * B.x; }
double Area2(Point A, Point B, Point C) { return Cross(B - A, C - A); }  // Divided by 2 to get triangle
Vector Rotate(Vector A, double rad) {
    return Vector(A.x * cos(rad) - A.y * sin(rad), A.x * sin(rad) + A.y * cos(rad));
}
Vector Norm(Vector A) {  // Norm with unit length, A != 0
    double L = Length(A);
    return Vector(-A.y / L, A.x / L);
}
struct Line {
    Point p;
    Vector v;
    Line(Point p, Vector v):p(p),v(v) { }
    Point point(double t) {
        return p + v * t;
    }
    Line move(double d) {
        return Line(p + Norm(v) * d, v);
    }
};

// The first line: P + v * t, the second line: Q + w * t
// Need to ensure they have unique intersection before applying "GetLineIntersection". (iff cross(v, w) != 0)
// t1 = cross(w, u) / cross(v, w); t2 = cross(v, u) / cross(v, w);
Point getLineIntersection(Point P, Vector v, Point Q, Vector w) {
    Vector u = P - Q;
    double t = Cross(w, u) / Cross(v, w);
    return P + v * t;
}
double distanceToLine(Point P, Point A, Point B) {  // Line: defined by A and B
    Vector v1 = B - A, v2 = P - A;
    return abs(Cross(v1, v2)) / Length(v1);
}
double distanceToSegment(Point P, Point A, Point B) {
    if (A == B) return Length(P - A);
    Vector v1 = B - A, v2 = P - A, v3 = P - B;
    if (dcmp(Dot(v1, v2)) < 0) return Length(v2);
    if (dcmp(Dot(v1, v3)) > 0) return Length(v3);
    return abs(Cross(v1, v2)) / Length(v1);
}
Point getLineProjection(Point P, Point A, Point B) {
    Vector v = B - A;
    return A + v * (Dot(v, P - A) / Dot(v, v));
}
bool segmentProperIntersection(Point a1, Point a2, Point b1, Point b2) {
    double c1 = Cross(a2 - a1, b1 - a1), c2 = Cross(a2 - a1, b2 - a1);
    double c3 = Cross(b2 - b1, a1 - b1), c4 = Cross(b2 - b1, a2 - b1);
    return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
}
bool onSegment(Point p, Point a1, Point a2) {  // segment defined by a1 and a2
    // if (p == a1 || p == a2) return true;  // At the extremes
    return dcmp(Cross(a1 - p, a2 - p)) == 0 && dcmp(Dot(a1 - p, a2 - p)) < 0;
}
double polygonArea(vector<Point> &p) {  // size >= 3
    double area = 0;
    int n = p.size();
    assert(n >= 3);
    for (int i = 1; i < n - 1; i++) area += Cross(p[i] - p[0], p[i + 1] - p[0]);
    return abs(area) / 2;
}

/**
 * Circles
 */

struct Circle {
    Point c;
    double r;
    Circle(Point c = Point(), double r = 0): c(c), r(r) {}
    Point point(double a) {
        return Point(c.x + cos(a) * r, c.y + sin(a) * r);
    }
};

// The line: P + t * v, P + v * t1 and P + v * t2 are intersections.
// return the number of intersections
// sol: all intersections. It's not cleared.
int getLineCircleIntersection(Point P, Vector v, Circle C, double &t1, double &t2, vector<Point> &sol) {
    double a = v.x, b = P.x - C.c.x, c = v.y, d = P.y - C.c.y;
    double e = a * a + c * c, f = 2 * (a * b + c * d), g = b * b + d * d - C.r * C.r;
    double delta = f * f - 4 * e * g;
    if (dcmp(delta) < 0) return 0;
    if (dcmp(delta) == 0) {
        t1 = t2 = -f / (2 * e);
        sol.push_back(P + v * t1);
        return 1;
    }
    t1 = (-f - sqrt(delta)) / (2 * e); sol.push_back(P + v * t1);
    t2 = (-f + sqrt(delta)) / (2 * e); sol.push_back(P + v * t2);
    return 2;
}

// Polar Angle of a vector
double polarAngle(Vector v) { return atan2(v.y, v.x); }

// Get two circles intersections, which are stored in sol.
// sol is not cleared.
int getCircleCircleIntersection(Circle C1, Circle C2, vector<Point> &sol) {
    double d = Length(C1.c - C2.c);
    if (dcmp(d) == 0) {
        if (dcmp(C1.r - C2.r) == 0) return -1;
        return 0;
    }
    if (dcmp(d - C1.r - C2.r) > 0) return 0;         // Seperated
    if (dcmp(abs(C1.r - C2.r) - d) > 0) return 0;    // Included

    double a = polarAngle(C2.c - C1.c);
    double da = acos((C1.r * C1.r + d * d - C2.r * C2.r) / (2 * C1.r * d));

    Point p1 = C1.point(a - da), p2 = C1.point(a + da);
    sol.push_back(p1);
    if (p1 == p2) return 1;
    sol.push_back(p2);
    return 2;
}

// The tangents of the circle C passing the point p
// The directional vectors are stored in sol.
// Return the number of tangents
int getTangents(Point p, Circle C, vector<Vector> &sol) {
    Vector u = C.c - p;
    double dist = Length(u);
    if (dcmp(dist - C.r) < 0) return 0;   // Included
    else if (dcmp(dist - C.r) == 0) {
        sol.push_back(Rotate(u, PI / 2));
        return 1;
    } else {
        double ang = asin(C.r / dist);
        sol.push_back(Rotate(u, ang));
        sol.push_back(Rotate(u, -ang));
        return 2;
    }
}

// The tangents of two circles
// a[i], b[i]: the i-th tangent point on circle A and B
// Return the number of tangents
int getTangents(Circle A, Circle B, Point *a, Point *b){
    int cnt = 0;        //存切点用
    if (dcmp(A.r - B.r) < 0) { swap(A, B); swap(a, b); }
    double d = sqrt((A.c.x - B.c.x) * (A.c.x - B.c.x) + (A.c.y - B.c.y) * (A.c.y - B.c.y));     // 圆心距
    double rdiff = A.r - B.r;                                                                   // 两圆半径差
    double rsum  = A.r + B.r;                                                                   // 两圆半径和
    if (dcmp(d - rdiff) < 0) return 0;                                                          // 1.内含

    double base = atan2(B.c.y - A.c.y, B.c.x - A.c.x);                                          // 向量AB的极角
    if (dcmp(d) == 0) return -1;                                                                // 2.重合

    if (dcmp(d - rdiff) == 0) {                                                                 // 3.内切
        a[cnt] = b[cnt] = A.point(base); cnt++;
        return 1;
    }
    double ang = acos((A.r - B.r) / d);
    a[cnt] = A.point(base + ang); b[cnt] = B.point(base + ang); cnt++;       // 4.相交（外切、外离的外公切线也在此求出）
    a[cnt] = A.point(base - ang); b[cnt] = B.point(base - ang); cnt++;       // 两条外公切线的切点
    if (dcmp(d - rsum) == 0) {                                               // 5.外切
        a[cnt] = b[cnt] = A.point(base);
        cnt++;
    } else if (dcmp(d - rsum) > 0) {                                         // 6.相离
        double ang = acos((A.r + B.r) / d);
        a[cnt] = A.point(base + ang); b[cnt] = B.point(base + ang + PI); cnt++;
        a[cnt] = A.point(base - ang); b[cnt] = B.point(base - ang + PI); cnt++;
    }
    return cnt;
}

/******************* Problem 1 **********************/

Circle CircumscribedCircle(Point A, Point B, Point C) {
    Point mid1 = A + (B - A) * 0.5, mid2 = B + (C - B) * 0.5;
    Vector v1 = Rotate(B - A, PI / 2), v2 = Rotate(C - B, PI / 2);
    Point intersect = getLineIntersection(mid1, v1, mid2, v2);
    return Circle(intersect, Length(intersect - A));
}

/******************* Problem 2 **********************/


Circle InscribedCircle(Point A, Point B, Point C) {
    if (dcmp(Cross(B - A, C - A)) < 0) swap(B, C);
    double deg1 = Angle(B - A, C - A) / 2, deg2 = Angle(C - B, A - B) / 2;
    Vector v1 = Rotate(B - A, deg1), v2 = Rotate(C - B, deg2);
    Point intersect = getLineIntersection(A, v1, B, v2);
    return Circle(intersect, distanceToLine(intersect, A, B));
}


/******************* Problem 3 **********************/


void TangentLineThroughPoint(Circle C, Point p, vector<double> &ans) {
    vector<Point> dir;
    getTangents(p, C, dir);
    for (int i = 0; i < dir.size(); i++) {
        double deg = atan2(dir[i].y, dir[i].x) * 180 / PI;
        if (dcmp(deg) < 0) deg += 360;
        if (dcmp(deg - 180) >= 0) deg -= 180;
        ans.pb(deg);
    }

    sort(all(ans));
    //uni(ans);
}

/******************* Problem 4 **********************/


void CircleThroughAPointAndTangentToALineWithRadius(Point p, Point A, Point B, double r, vector<Point> &ans) {
    Vector v = B - A;
    Vector vL = Norm(v);
    Point base1 = A + vL * r, base2 = A - vL * r;

    Circle C(p, r);
    double t1, t2;
    getLineCircleIntersection(base1, v, C, t1, t2, ans);
    getLineCircleIntersection(base2, v, C, t1, t2, ans);

    sort(all(ans));
}

/******************* Problem 5 **********************/


void CircleTangentToTwoLinesWithRadius(Point A1, Point A2, Point B1, Point B2, double r, vector<Point> &ans) {
    Vector v1 = A2 - A1, v2 = B2 - B1;
    Vector vL1 = Norm(v1), vL2 = Norm(v2);
    Point base[] = { A1 + vL1 * r, A1 - vL1 * r, B1 + vL2 * r, B1 - vL2 * r };
    for (int i = 0; i < 2; i++) {
        for (int j = 2; j < 4; j++) {
            ans.pb(getLineIntersection(base[i], v1, base[j], v2));
        }
    }
    sort(all(ans));
}

/******************* Problem 6 **********************/

void CircleTangentToTwoDisjointCirclesWithRadius(Circle C1, Circle C2, double r, vector<Point> &ans) {
    Circle A(C1.c, C1.r + r), B(C2.c, C2.r + r);
    getCircleCircleIntersection(A, B, ans);
    sort(all(ans));
}

string s;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed;
    cout.precision(6);

    while (cin >> s) {
        if (s == "CircumscribedCircle") {
            Point p[5];
            for (int i = 0; i < 3; i++) cin >> p[i].x >> p[i].y;
            Circle ans = CircumscribedCircle(p[0], p[1], p[2]);
            cout << '(' << ans.c.x << ',' << ans.c.y << ',' << ans.r << ")\n";
        } else if (s == "InscribedCircle") {
            Point p[5];
            for (int i = 0; i < 3; i++) cin >> p[i].x >> p[i].y;
            Circle ans = InscribedCircle(p[0], p[1], p[2]);
            cout << '(' << ans.c.x << ',' << ans.c.y << ',' << ans.r << ")\n";
        } else if (s == "TangentLineThroughPoint") {
            Point p;
            Circle C;
            cin >> C.c.x >> C.c.y >> C.r;
            cin >> p.x >> p.y;
            vector<double> ans;
            TangentLineThroughPoint(C, p, ans);
            if (ans.empty()) {
                cout << "[]\n";
                continue;
            }
            cout << '[';
            cout << ans[0];
            for (int i = 1; i < ans.size(); i++) cout << ',' << ans[i];
            cout << "]\n";
        } else if (s == "CircleThroughAPointAndTangentToALineWithRadius") {
            Point p[5];
            double r;
            for (int i = 0; i < 3; i++) cin >> p[i].x >> p[i].y;
            cin >> r;
            vector<Point> ans;
            CircleThroughAPointAndTangentToALineWithRadius(p[0], p[1], p[2], r, ans);
            if (ans.empty()) {
                cout << "[]\n";
                continue;
            }
            cout << '[';
            cout << '(' << ans[0].x << ',' << ans[0].y << ')';
            for (int i = 1; i < ans.size(); i++) cout << ",(" << ans[i].x << ',' << ans[i].y << ')';
            cout << "]\n";
        } else if (s == "CircleTangentToTwoLinesWithRadius") {
            Point p[5];
            double r;
            for (int i = 0; i < 4; i++) cin >> p[i].x >> p[i].y;
            cin >> r;
            vector<Point> ans;
            CircleTangentToTwoLinesWithRadius(p[0], p[1], p[2], p[3], r, ans);
            if (ans.empty()) {
                cout << "[]\n";
                continue;
            }
            cout << '[';
            cout << '(' << ans[0].x << ',' << ans[0].y << ')';
            for (int i = 1; i < ans.size(); i++) cout << ",(" << ans[i].x << ',' << ans[i].y << ')';
            cout << "]\n";
        } else {
            Circle C[2];
            double r;
            for (int i = 0; i < 2; i++) cin >> C[i].c.x >> C[i].c.y >> C[i].r;
            cin >> r;
            vector<Point> ans;
            CircleTangentToTwoDisjointCirclesWithRadius(C[0], C[1], r, ans);
            if (ans.empty()) {
                cout << "[]\n";
                continue;
            }
            cout << '[';
            cout << '(' << ans[0].x << ',' << ans[0].y << ')';
            for (int i = 1; i < ans.size(); i++) cout << ",(" << ans[i].x << ',' << ans[i].y << ')';
            cout << "]\n";
        }
    }
    return 0;
}
