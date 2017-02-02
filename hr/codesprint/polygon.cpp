/* string coder = "Balajiganapathi S"; // Never give up!  */

//#define LOCAL
#ifdef LOCAL
#   define TRACE
#   define TEST
#else
//#   define NDEBUG
//#   define FAST
#endif

#include<bits/stdc++.h>

using namespace std;

/* aliases */
using vi  = vector<int>;
using pi  = pair<int, int>;
using ll  = long long int;

/* shortcut macros */
#define mp              make_pair
#define fi              first
#define se              second
#define mt              make_tuple
#define gt(t, i)        get<i>(t)
#define all(x)          (x).begin(), (x).end()
#define ini(a, v)       memset(a, v, sizeof(a))
#define rep(i, s, n)    for(int i = (s), _##i = (n); i <= _##i; ++i)
#define re(i, s, n)     rep(i, (s), (n) - 1)
#define fo(i, n)        re(i, 0, n)
#define si(x)           (int((x).size()))
#define is1(mask,i)     (((mask) >> i) & 1)

/* trace macro */
#ifdef TRACE
#   define trace(v...)  {cerr << __func__ << ":" << __LINE__ << ": " ;_dt(#v, v);}
#else
#   define trace(...)
#endif

#ifdef TRACE
pi _gp(string s) {
    pi r(0, si(s) - 1);
    int p = 0, s1 = 0, s2 = 0, start = 1;
    fo(i, si(s)) {
        int x = (s1 | s2);
        if(s[i] == ' ' && start) {
            ++r.fi;
        } else {
            start = 0;
            if(s[i] == ',' && !p && !x) {
                r.se = i - 1;
                return r;
            }
            if(x && s[i] == '\\') ++i;
            else if(!x && s[i] == '(') ++p;
            else if(!x && s[i] == ')') --p;
            else if(!s2 && s[i] == '\'') s1 ^= 1;
            else if(!s1 && s[i] == '"') s2 ^= 1;
        }
    }
    return r;
}

template<typename H> void _dt(string u, H&& v) {
    pi p = _gp(u);
    cerr << u.substr(p.fi, p.se - p.fi + 1) << " = " << forward<H>(v) << " |" << endl;
}

template<typename H, typename ...T> void _dt(string u, H&& v, T&&... r) {
    pi p = _gp(u);
    cerr << u.substr(p.fi, p.se - p.fi + 1) << " = " << forward<H>(v) << " | ";
    _dt(u.substr(p.se + 2), forward<T>(r)...);
}

template<typename T> 
ostream &operator <<(ostream &o, vector<T> v) { // print a vector
    o << "[";
    fo(i, si(v) - 1) o << v[i] << ", ";
    if(si(v)) o << v.back();
    o << "]";
    return o;
}

template<typename T1, typename T2> 
ostream &operator <<(ostream &o, map<T1, T2> m) { // print a map
    o << "{";
    for(auto &p: m) {
        o << " (" << p.fi << " -> " << p.se << ")";
    }
    o << " }";
    return o;
}

template<typename T> 
ostream &operator <<(ostream &o, set<T> s) { // print a set
    o << "{";
    bool first = true;
    for(auto &entry: s) {
        if(!first) o << ", ";
         
        o << entry;
        first = false;
    }
    o << "}";
    return o;
}

template <size_t n, typename... T>
typename enable_if<(n >= sizeof...(T))>::type
    print_tuple(ostream&, const tuple<T...>&) {} 

template <size_t n, typename... T>
typename enable_if<(n < sizeof...(T))>::type
    print_tuple(ostream& os, const tuple<T...>& tup) {
    if (n != 0)
        os << ", ";
    os << get<n>(tup);
    print_tuple<n+1>(os, tup);
}

template <typename... T>
ostream& operator<<(ostream& os, const tuple<T...>& tup) { // print a tuple
    os << "("; print_tuple<0>(os, tup); return os << ")"; } template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { // print a pair
    return os << "(" << p.fi << ", " << p.se << ")";
}
#endif
    
/* util functions */
template<typename T1, typename T2, typename T3>
T1 modpow(T1 _a, T2 p, T3 mod) {
    assert(p >= 0);
    ll ret = 1, a = _a;

#ifndef FAST
    if(a < 0) {
        a %= mod;
        a += mod;
    } 

    if(a >= mod) {
        a %= mod;
    }
#endif

    for(; p > 0; p /= 2) {
        if(p & 1) ret = ret * a % mod;
        a = a * a % mod;
    }

    return ret;
}

#define x1 _asdfzx1
#define y1 _ysfdzy1

/* constants */
constexpr int dx[] = {-1, 0, 1, 0, 1, 1, -1, -1};
constexpr int dy[] = {0, -1, 0, 1, 1, -1, 1, -1};
constexpr auto PI  = 3.14159265358979323846L;
constexpr auto oo  = numeric_limits<int>::max() / 2 - 2;
constexpr auto eps = 1e-8;
constexpr auto mod = 1000000007;

/*-------------------------------------------------------------------------------------------------------------------------------------*/
/*<shapes>*/
/*ref: emaxx, tc tutorials and wikipedia*/
/*WARNING: UNTESTED*/
/*Requires PI and eps constants*/

using coord_t = long double;
using length_t = long double; // Assumes double or long double, uses eps constant
using angle_t = long double; // Assumes double or long double, uses eps constant

// utils
angle_t toDegrees(const angle_t &rad) { return rad * 180.0 / PI; }
angle_t toRadians(const angle_t &deg) { return deg * PI / 180.0; }
template<typename T> T det(T a, T b, T c, T d) { return a * d - b * c; }
template<typename T> T equals(T a, T b) { return fabs(a - b) <= eps; }
template<typename T> T iszero(T n) { return equals(n, T(0)); }

class point {
public:
    int idx;
    coord_t x, y;

    constexpr point(): x(0), y(0), idx(-1) {}
    constexpr point(const coord_t &_x, const coord_t &_y): x(_x), y(_y), idx(-1) {}
    constexpr point(const point &p): x(p.x), y(p.y), idx(p.idx) {}

    length_t dist(const point &p) const {
        length_t dx = length_t(x) - p.x;
        length_t dy = length_t(y) - p.y;
        return sqrt(dx * dx + dy * dy);
    }

    length_t dist() const { return sqrt(sqDist()); }
    length_t sqDist() const { return length_t(x) * x + length_t(y) * y; }
    pair<length_t, angle_t> toPolar() const { return make_pair(dist(), atan2(y, x)); }

    bool operator ==(const point &p) const { return equals(x, p.x) && equals(y, p.y); }
    bool operator !=(const point &p) const { return !equals(x, p.x) || !equals(y, p.y); }
    bool operator < (const point &p) const { return x < p.x - eps || (equals(x, p.x) && y < p.y - eps); }
};

constexpr point origin(0, 0);

point fromPolar(pair<length_t, angle_t> pol) { return point(pol.first * cos(pol.second), pol.first * sin(pol.second)); }
ostream& operator<<(ostream& os, const point& p) { return os << "(" << p.x << ", " << p.y << ")"; }

class vec {
public:
    coord_t x, y;

    constexpr vec(): x(0), y(0) { }
    constexpr vec(const coord_t &_x, const coord_t &_y): x(_x), y(_y) {}
    constexpr vec(const vec &v): x(v.x), y(v.y) {}
    vec(const point &from, const point &to) { x = to.x - from.x; y = to.y - from.y; }

    vec operator+(const vec &v) const { return vec(x + v.x, y + v.y); }
    vec operator-(const vec &v) const { return vec(x - v.x, y - v.y); }
    // Dot product
    length_t operator*(const vec &v) const { return length_t(x) * v.x - length_t(y) * v.y; }
    // Cross product
    length_t operator^(const vec &v) const { return length_t(x) * v.y - length_t(y) * v.x; }

    length_t length() const { return sqrt(length_t(x) * x + length_t(y) * y); }
    long double angleWith(const vec &v) const { 
        long double angle = acos((*this * v) / (length() * v.length())); 
        return angle;
    } // Angle in radians
};

ostream& operator<<(ostream& os, const vec& v) { return os << "->(" << v.x << ", " << v.y << ")"; }

class line {
public:
    point p, q;
    length_t a, b, c;

    constexpr line(): a(0), b(0), c(0) {}
    line(const point &_p, const point &_q): p(_p), q(_q) { init(); }
    line(const line &l): p(l.p), q(l.q) { init(); }
    line(const coord_t &x1, const coord_t &y1, const coord_t &x2, const coord_t &y2): p(x1, y1), q(x2, y2) { init();  }
    //line(const segment &s): a(s.a), b(s.b) {}

private:
    void init() {
        a = length_t(p.y) - q.y;
        b = length_t(q.x) - p.x;
        c = -a * p.x - b * p.y;

        length_t z = sqrt(a * a + b * b);
        a /= z; b /= z; c /= z;
        if(a < -eps && (equals(a, length_t(0)) && b < -eps)) {
            a *= -1; b *= -1; c *= -1;
        }
    }

public:
    bool parallel(const line &l) const { return iszero(det(a, b, l.a, l.b)); }

    point intersection(const line &l) const {
        assert(!parallel(l));
        length_t d = det(a, b, l.a, l.b);
        assert(!iszero(d));
        return point(det(c, b, l.c, l.b) / d, det(a, c, l.a, l.c) / d);
    }

    bool contains(const point &p) const { return iszero(a * p.x + b * p.y + c); }

    bool operator == (const line &l) const {
        return iszero(det(a, b, l.a, l.b)) && iszero(det(a, c, l.a, l.c)) && iszero(det(b, c, l.b, l.c));
    }
};

ostream& operator<<(ostream& os, const line& l) { return os << l.p << " <-> " << l.q; }

class segment {
public:
    point a, b;
    line theLine;

    constexpr segment() {}
    segment(const point &_a, const point &_b): a(_a), b(_b), theLine(_a, _b) { }
    segment(const segment &l): a(l.a), b(l.b), theLine(l.theLine) {}
    segment(const coord_t &x1, const coord_t &y1, const coord_t &x2, const coord_t &y2): a(x1, y1), b(x2, y2), theLine(x1, y1, x2, y2) {}

    length_t length() const { return a.dist(b); }

    bool intersects(const segment &s) const { 
        if(theLine.parallel(s.theLine)) return false;
        point p = theLine.intersection(s.theLine);
        return contains(p) && s.contains(p);
    }

    bool contains(const point &p) const { 
        if(!theLine.contains(p)) return false;
        if(!(min(a.x, b.x) - eps <= p.x && p.x <= max(a.x, b.x) + eps)) return false;
        if(!(min(a.y, b.y) - eps <= p.y && p.y <= max(a.y, b.y) + eps)) return false;
        return true;
    }

    // Assumes single point of intersection
    point intersection(const segment &s) const { assert(intersects(s)); return theLine.intersection(s.theLine); }

    point midpoint() const { return point((length_t(a.x) + b.x) / 2, (length_t(a.y) + b.y) / 2); }
    length_t dist(const point &c) {
        vec ba(b, a), ca(c, a), cb(c, b), ab(a, b), bc(b, c), ac(a, c);
        length_t dist = (ba ^ ca) / sqrt(ba * ba);
        if(cb * ba > eps) return sqrt(bc * bc);
        if(ca * ab > eps) return sqrt(ac * ac);
        return fabs(dist);
    }

    long double angleWith(const segment &s) const { // an endpoint must be common
        assert(intersects(s));
        point p = s.a;
        if(p != a && p != b) p = s.b;
        assert(p == a || p == b);
        assert(p == s.a || p == s.b);
        vec v1, v2;
        if(s.a == p) v1 = vec(s.a, s.b);
        else v1 = vec(s.b, s.a);

        if(a == p) v2 = vec(a, b);
        else v2 = vec(b, a);

        return v1.angleWith(v2);
    }
};

ostream& operator<<(ostream& os, const segment& s) { return os << s.a << " - " << s.b; }

class circle {
public:
    point center;
    length_t radius;

    constexpr circle(): radius(0) {}
    constexpr circle(const point &_center, const length_t &_radius): center(_center), radius(_radius) {}
    length_t area() { return PI * radius * radius; }

    template<typename T> bool intersects(const T &shape) const { return shape.dist(center) <= radius + eps; }
    template<typename T> length_t dist(const T &shape) const { assert(!intersects(shape)); return shape.dist(center) - radius; }

    bool contains(const point &p) const {
        return equals(radius, center.dist(p));
    }
    /*
    vector<point> intersection(const segment &s) const {
        vector<point> linePoints = intersection(line(s.a, s.b));
        vector<point> ret;
        for(const point &p: linePoints) if(s.contains(p)) ret.push_back(p);
        return ret;
    }
    */


    // TODO
    //vector<point> intersection(const line &s) const {}
    //vector<point> intersection(const circle &c) const {}
};
ostream& operator<<(ostream& os, const circle& c) { return os << "{o(" << c.center << ", " << c.radius << ")}"; }

class polygon {
public:
    vector<point> points;

    polygon() {}
    polygon(const vector<point> &_points): points(_points) {}
    polygon(const polygon &pol): points(pol.points) {}

    length_t area() const {
        return fabs(signedArea());
    };

    length_t signedArea() const {
        length_t ret = 0;
        for(int i = 1; i + 1 < si(points); ++i) {
            vec v1(points[i], points[0]);
            vec v2(points[i+1], points[0]);

            ret += (v1 ^ v2);
        }

        return ret / 2;
    };

    point centroid() const {
        length_t cx = 0, cy = 0;
        fo(i, si(points) - 1) {
            cx += length_t(points[i].x + points[i+1].x) * (length_t(points[i].x) * points[i+1].y - length_t(points[i+i].x) * points[i].y);
            cy += length_t(points[i].y + points[i+1].y) * (length_t(points[i].y) * points[i+1].x - length_t(points[i+i].y) * points[i].x);
        }
        length_t A = signedArea();
        return point(cx / 6 / A, cy / 6 / A);
    }


    length_t perimeter() const {
        length_t ret = 0;

        fo(i, si(points) - 1) ret += points[i].dist(points[i+1]);
        ret += points.back().dist(points.front());

        return ret;
    }

    // TODO
    //bool intersects(const polygon &p) const {}
    //bool contains(const point &p) const {}
};

class triangle {
public:
    point a, b, c;
    constexpr triangle() {}
    triangle(const point &_a, const point &_b, const point &_c): a(_a), b(_b), c(_c) {}
    triangle(const coord_t &x1, const coord_t &y1, const coord_t &x2, const coord_t &y2, const coord_t &x3, const coord_t &y3)
        : a(x1, y1), b(x2, y2), c(x3, y3) {}

    circle circumCircle() const {
        length_t D = (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
        length_t x = a.sqDist() / 2 / D * (b.y - c.y) + b.sqDist() / 2 / D * (c.y - a.y) + c.sqDist() / 2 / D * (a.y - b.y);
        length_t y = a.sqDist() / 2 / D * (c.x - b.x) + b.sqDist() / 2 / D * (a.x - c.x) + c.sqDist() / 2 / D * (b.x - a.x);
        trace(a, b, c, D);
        point center(x, y);
        length_t radius = center.dist(a);
        trace(center, radius);
        trace(radius, center.dist(a), center.dist(b), center.dist(c));
        assert(equals(radius, center.dist(b)));
        assert(equals(radius, center.dist(c)));
        return circle(center, radius);
    }
};


// TODO
//polygon convexHull(vector<point> points) { }

/*</shapes>*/
/*-------------------------------------------------------------------------------------------------------------------------------------*/



/* code */
constexpr int mx_n = 1003;
using ld = long double;
length_t d;
int n;
point points[mx_n];

class Move {
public:
    int idx;
    point np;
    Move(int _idx, const point &_np): idx(_idx), np(_np) {
        assert(equals(points[idx].dist(np), d));
    };
};

class Solution {
public:
    polygon poly;
    vector<Move> moves;
    ld score() const {
        if(si(poly.points) == 0) return 0;
        ld p = poly.perimeter(), area = poly.area();
        return 4 * n * tan(PI / n) * area / p / p;
    }
} best;

void consider(const Solution &sol) {
    trace(sol.score());
    if(sol.score() > best.score()) best = sol;
}

void justSort(vector<point> pts) {
    sort(all(pts), [](const point &p1, const point &p2) { return p1.toPolar().se < p2.toPolar().se;});
    Solution sol;
    sol.poly = polygon(pts);
    consider(sol);
}

point centerOfPoints(const vector<point> &pts) {
    ld sx = 0, sy = 0;
    for(const point &p: pts) {
        sx += p.x;
        sy += p.y;
    }

    sx /= si(pts); sy /= si(pts);

    return point(sx, sy);
}

polygon sortPoints(vector<point> pts) {
    point center = centerOfPoints(pts);

    sort(all(pts), [center](const point &p1, const point &p2) { 
            point n1(p1.x - center.x, p1.y - center.y);
            point n2(p2.x - center.x, p2.y - center.y);
            return n1.toPolar().se < n2.toPolar().se;
        });

    return polygon(pts);
}

void sortWithCenter(vector<point> pts) {
    Solution sol;
    sol.poly = sortPoints(pts);
    trace(sol.poly.points);
    consider(sol);
}

point moveIt(point o, point p, length_t dist) {
    point op(p.x - o.x, p.y - o.y);
    auto opol = op.toPolar();
    auto np = fromPolar(mp(opol.fi + dist, opol.se));
    np = point(np.x + o.x, np.y + o.y);
    trace(o, p, opol, dist, p.dist(np), np);
    assert(equals(p.dist(np), fabs(dist)));
    return np;
}

void moveAround(circle c, const vector<point> &pts, Solution &sol) {
    trace(c);
    vector<point> newPts;
    fo(i, n) {
        length_t cp = c.center.dist(pts[i]);
        point  p = pts[i];
        length_t mdist = 0;
        rep(dir, -1, 1) {
            if(fabs(fabs(cp + dir * d) - c.radius) < fabs(fabs(cp + mdist) - c.radius)) {
                mdist = dir * d;
            }
        }
        if(!iszero(mdist)) {
            p = moveIt(c.center, pts[i], mdist);
            sol.moves.push_back(Move(pts[i].idx, p));
        }
        p.idx = i;
        newPts.push_back(p);
    }
    sol.poly = sortPoints(newPts);
}

void centeredCircle(point center, vector<point> pts) {
    length_t r = 0, max_dist = 0;
    for(const auto &p: pts) max_dist = max(max_dist, center.dist(p));
    trace(center, r, d, max_dist);


    r = max_dist / 2;
    int cnt = 100;
    do {
        vector<point> pot;
        trace(center, r);
        Solution sol;
        angle_t inc = 2 * PI / (n - 1);
        trace(inc);

        moveAround(circle(center, r), pts, sol);
        consider(sol);

        r = rand() % (int(ceil(2 * max_dist))) + 2;

    } while(cnt--);
}

point centroid(vector<point> pts) {
    return sortPoints(pts).centroid();
}

void solve() {
    vector<point> pts(points, points + n);
    sortWithCenter(pts);
    centeredCircle(centerOfPoints(pts), pts);
    centeredCircle(centroid(pts), pts);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> d;
    fo(i, n) {
        coord_t x, y;
        cin >> x >> y;
        points[i] = point(x, y);
        points[i].idx = i;
    }
    solve();
    
    cout.precision(8);
    cout << fixed;
    cout << si(best.moves) << endl;
    for(const Move& m: best.moves) {
        cout << m.idx + 1 << " " << m.np.x << " " << m.np.y << endl;
    }
    fo(i, n) cout << best.poly.points[i].idx + 1 << " ";
    cout << endl;
    
    
	return 0;
}

