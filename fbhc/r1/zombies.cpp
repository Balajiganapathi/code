/* string coder = "Balajiganapathi S"; // Never give up!  */

//#define LOCAL
#ifdef LOCAL
//#   define TRACE
#   define TEST
#else
#   define NDEBUG
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
constexpr auto eps = 9e-5;
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
    coord_t x, y;

    constexpr point(): x(0), y(0) {}
    constexpr point(const coord_t &_x, const coord_t &_y): x(_x), y(_y) {}
    constexpr point(const point &p): x(p.x), y(p.y) {}

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
    vector<point> intersection(const segment &s) const {
        vector<point> linePoints = intersection(line(s.a, s.b));
        vector<point> ret;
        for(const point &p: linePoints) if(s.contains(p)) ret.push_back(p);
        return ret;
    }

    bool contains(const point &p) const {
        return equals(radius, center.dist(p));
    }

    // TODO
    vector<point> intersection(const line &s) const {}
    vector<point> intersection(const circle &c) const {}
};

class polygon {
public:
    vector<point> points;

    polygon() {}
    polygon(const vector<point> &_points): points(_points) {}
    polygon(const polygon &pol): points(pol.points) {}

    length_t area() const {
        length_t ret = 0;
        for(int i = 1; i + 1 < si(points); ++i) {
            vec v1(points[i], points[0]);
            vec v2(points[i+1], points[0]);

            ret += (v1 ^ v2);
        }

        return fabs(ret) / 2;
    };

    // TODO
    bool intersects(const polygon &p) const {}
    bool contains(const point &p) const {}
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
polygon convexHull(vector<point> points) {
}

/*</shapes>*/
/*-------------------------------------------------------------------------------------------------------------------------------------*/



/* code */
constexpr int mx = 55;
point pts[mx];
int n, r;

int getMax(const vector<point> &v) {
    int j = 0;
    multiset<int> yInRange;
    int ans = 0;
    fo(i, si(v)) {
        while(j < si(v) && v[j].x - v[i].x <= r) {
            yInRange.insert(v[j].y);
            ++j;
        }
        auto it2 = yInRange.begin();
        int cnt = 0;
        for(auto it1 = yInRange.begin(); it1 != yInRange.end(); ++it1) {
            while(it2 != yInRange.end() && *it2 - *it1 <= r) {
                ++cnt;
                ++it2;
            }
            ans = max(ans, cnt);
            --cnt;
        }
        yInRange.erase(yInRange.find(v[i].y));
    }

    //trace(v, ans);
    return ans;
}

int solveForOne(int x) {
    vector<point> inside, outside;
    fo(i, n) {
        if(i == x) inside.push_back(pts[i]);
        else outside.push_back(pts[i]);
    }
    return 1 + getMax(outside);
}

int solveForTwo(int x, int y) {
    vector<point> inside, outside;
    segment seg(pts[x], pts[y]);
    circle cir(seg.midpoint(), seg.length() / 2);
    fo(i, n) {
        if(cir.contains(pts[i])) inside.push_back(pts[i]);
        else outside.push_back(pts[i]);
    }
    return getMax(inside) + getMax(outside);

}

int solveForThree(int x, int y, int z) {
    vector<point> inside, outside;
    segment seg(pts[x], pts[y]);
    if(seg.theLine.contains(pts[z])) return -oo;
    triangle tri(pts[x], pts[y], pts[z]);
    circle cir = tri.circumCircle();
    fo(i, n) {
        if(cir.contains(pts[i])) inside.push_back(pts[i]);
        else outside.push_back(pts[i]);
    }
    return getMax(inside) + getMax(outside);

}

int main() {
    int t;
#ifdef TEST
    t = 50;
#else
    cin >> t;
#endif
    rep(tt, 1, t) {
#ifdef TEST
        n = 50; r = 900000000;
        fo(i, n) pts[i] = point(rand() % 1000000000 + 1, rand() % 1000000000 + 1);
#else
        cin >> n >> r;
        fo(i, n) {
            coord_t x, y;
            cin >> x >> y;
            pts[i] = {x, y};
        }
#endif

        sort(pts, pts + n);
        int ans = 0;
        fo(i, n) {
            ans = max(ans, solveForOne(i));
            re(j, i + 1, n) {
                ans = max(ans, solveForTwo(i, j));
                re(k, j + 1, n) {
                    ans = max(ans, solveForThree(i, j, k));
                }
            }
        }

        cout << "Case #" << tt << ": " << ans << endl;

    }
    
    
	return 0;
}

