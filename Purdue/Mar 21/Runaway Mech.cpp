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
const double eps = 1e-10;
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
/**
 * The < here is theoretically not correct. But we can use this to remove duplicate points.
 */
bool operator < (const Point& a, const Point& b) {
    return dcmp(a.x - b.x) < 0 || (dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) < 0);
}
bool operator == (const Point& a, const Point& b) {
    return dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) == 0;
}
double Dot(Vector A, Vector B) { return A.x * B.x + A.y * B.y; }
double Length(Vector A) { return sqrt(Dot(A, A)); }
double Length2(Vector A) { return Dot(A, A); }
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

// The first line: P + v * t, the second line: Q + w * t
// Need to ensure they have unique intersection before applying "GetLineIntersection". (iff cross(v, w) != 0)
// t1 = cross(w, u) / cross(v, w); t2 = cross(v, u) / cross(v, w);
double getLineIntersection(Point P, Vector v, Point Q, Vector w) {
    Vector u = P - Q;
    if (dcmp(Cross(v, w)) == 0) return -1;
    double t = Cross(w, u) / Cross(v, w);
    return t;
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
    if (p == a1 || p == a2) return true;  // At the extremes
    return dcmp(Cross(a1 - p, a2 - p)) == 0 && dcmp(Dot(a1 - p, a2 - p)) < 0;
}
double polygonArea(vector<Point> &p) {  // size >= 3
    double area = 0;
    int n = p.size();
    assert(n >= 3);
    for (int i = 1; i < n - 1; i++) area += Cross(p[i] - p[0], p[i + 1] - p[0]);
    return area / 2;
}
bool segmentIntersection(Point a1, Point a2, Point b1, Point b2) {
    if (onSegment(a1, b1, b2) || onSegment(a2, b1, b2)) return true;
    if (onSegment(b1, a1, a2) || onSegment(b2, a1, a2)) return true;
    return segmentProperIntersection(a1, a2, b1, b2);
}

Point p[10];
Point st;
double slope;

int main() {
    cin >> st.x >> st.y;
    cin >> slope;
    Vector stv = { 1, slope };
    for (int i = 0; i < 4; i++) cin >> p[i].x >> p[i].y;

    double ans = 2e18;
    for (int i = 0; i < 4; i++) {
        Point p1 = p[i], p2 = p[(i + 1) % 4];
        double t = getLineIntersection(st, stv, p1, p2 - p1);
        if (t < 0) continue;
        Point cur = st + stv * t;
        if (!onSegment(cur, p1, p2)) continue;
        ans = min(ans, t);
    }

    cout << LL((st + stv * ans).x) << ' ' << LL((st + stv * ans).y) << '\n';
    return 0;
}
