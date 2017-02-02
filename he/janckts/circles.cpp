/* string coder = "Balajiganapathi S"; // Never give up!  */

//#define LOCAL
#ifdef LOCAL
#   define TRACE
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
constexpr auto oo  = 1000000000;
constexpr auto eps = 1e-6;
constexpr auto mod = 1000000007;


/*-------------------------------------------------------------------------------------------------------------------------------------*/
/*<shapes>*/
/*ref: emaxx, tc tutorials and wikipedia*/
/*WARNING: UNTESTED*/
/*Requires PI and eps constants*/

using coord_t = int;
using length_t = double; // Assumes double or long double, uses eps constant
using angle_t = double; // Assumes double or long double, uses eps constant

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
    length_t sqDist(const point &p) const { 
        length_t dx = length_t(x) - p.x;
        length_t dy = length_t(y) - p.y;
        return dx * dx + dy * dy;
    }

    length_t dist() const { return sqrt(sqDist()); }
    length_t sqDist() const { return length_t(x) * x + length_t(y) * y; }
    pair<length_t, angle_t> toPolar() const { return make_pair(dist(), atan2(y, x)); }

    bool operator ==(const point &p) const { return equals(x, p.x) && equals(y, p.y); }
    bool operator !=(const point &p) const { return !equals(x, p.x) || !equals(y, p.y); }
    bool operator < (const point &p) const { return x < p.x - eps || (equals(x, p.x) && y < p.y - eps); }
};

constexpr point origin(0, 0);

pair<double, double> fromPolar(length_t l, angle_t a) { return mp(l * cos(a), l * sin(a)); }
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

    bool intersects(const circle &cir) const { return cir.center.dist(center) <= cir.radius + radius + eps; }
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
ostream& operator<<(ostream& os, const circle& c) { return os << "<" << c.center << "-> " << c.radius << ">"; }

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
constexpr int mx_n = 1003;
int n;
length_t score;
bool found = false;

class Item {
    static constexpr double w1 = -20, w2 = 10, w3 = 50, w4 = 200;
    static constexpr double wsum = w1 + w2 + w3 + w4;
    public:
    int r, w, idx;

    double score() const {
        double v1 = r, v2 = w, v3 = 1.0 * w / (2 * r), v4 = 1.0 * w / (PI * r * r);
        return (w1 * v1 + w2 * v2 + w3 * v3 + w4 * v4) / wsum;
    }
} items[mx_n];


class Solution {
    public:
    circle circles[mx_n];

    length_t score() const {
        length_t num = 0, den = 0;
        fo(i, n) {
            num += items[i].w;
            den += items[i].w * circles[i].center.dist();
        }

        return 1000 * num / den * 100000;
    }

    bool valid() const {
        fo(i, n) re(j, i + 1, n) if(circles[i].center.dist(circles[j].center) < circles[i].radius + circles[j].radius - eps) {
            trace(i, j, circles[i], circles[j]);
            return false;
        }
        return true;
    }
} best;

void consider(const Solution &s) {
    if(!s.valid()) return;
    length_t sc = s.score();
    trace(sc, score);
    if(!found || sc > score + eps) {
        score = sc;
        best = s;
        found = true;
    }
}

int randRange(int a, int b) {
    return rand() % (b - a + 1) + a;
}

class IOrderer {
    public:
    virtual vector<Item> order() = 0;
};

class IPlacer {
    public:
    virtual vector<circle> _place(vector<Item>) = 0;

    Solution place(vector<Item> items) {
        vector<circle> cirs = _place(items);
        //trace(cirs);
        Solution sol;
        fo(i, n) {
            sol.circles[items[i].idx] = cirs[i];
        }
        return sol;
    }
};

class RandomOrderer: public IOrderer {
    public:
        vector<Item> order() {
            vector<Item> it(items, items + n);
            random_shuffle(all(it));
            return it;
        }
};

class WeightedOrderer: public IOrderer {
    public:
        vector<Item> order() {
            vector<Item> it(items, items + n);
            sort(all(it), 
                    [](const Item &i1, const Item &i2) {
                        if(i1.w == i2.w) return i1.r < i2.r;
                        return i1.w > i2.w;
                    }
                );
            return it;
        }
};

class RadiusOrderer: public IOrderer {
    public:
        vector<Item> order() {
            vector<Item> it(items, items + n);
            sort(all(it), 
                    [](const Item &i1, const Item &i2) {
                        if(i1.r == i2.r) return i1.r > i2.r;
                        return i1.r < i2.r;
                    }
                );
            return it;
        }
};


class RatioOrderer: public IOrderer {
    public:
        vector<Item> order() {
            vector<Item> it(items, items + n);
            sort(all(it), 
                    [](const Item &i1, const Item &i2) {
                        return i1.w * i2.r > i2.w * i1.r;
                    }
                );
            return it;
        }
};

class AreaRatioOrderer: public IOrderer {
    public:
        vector<Item> order() {
            vector<Item> it(items, items + n);
            sort(all(it), 
                    [](const Item &i1, const Item &i2) {
                        return i1.w * i2.r * i2.r > i2.w * i1.r * i1.r;
                    }
                );
            return it;
        }
};

class AllTypeWeightedOrderer: public IOrderer {
    public:
        vector<Item> order() {
            vector<Item> it(items, items + n);
            sort(all(it), 
                    [](const Item &i1, const Item &i2) {
                        return i1.score() > i2.score();
                    }
                );
            return it;
        }
};



class RandomPlacer: public IPlacer {
    public:
        vector<circle> _place(vector<Item> items) {
            vector<circle> ret;
            fo(i, n) ret.push_back(circle(point(randRange(-2000000, 2000000), randRange(-2000000, 2000000)), items[i].r));
            //trace(ret);

            return ret;
        }
};

class LinearPlacer: public IPlacer {
    public:
        vector<circle> _place(vector<Item> items) {
            vector<circle> ret;
            int right_x = 0, left_x = 0;
            fo(i, n) {
                if(right_x <= abs(left_x)) {
                    ret.push_back(circle(point(right_x + items[i].r, 0), items[i].r));
                    right_x += 2 * items[i].r;
                } else {
                    ret.push_back(circle(point(left_x - items[i].r, 0), items[i].r));
                    left_x -= 2 * items[i].r;
                }
            }
            //trace(ret);
            return ret;
        }
};

class Simple2AxisPlacer: public IPlacer {
    public:
        vector<circle> _place(vector<Item> items) {
            vector<circle> ret;
            int rightx = items[0].r, leftx = items[0].r;
            int topy = items[0].r, bottomy = items[0].r;
            ret.push_back(circle(point(0, 0), items[0].r));
            re(i, 1, n) {
                int r = items[i].r;
                int minn = min(min(rightx, leftx), min(topy, bottomy));
                point p;
                if(rightx == minn) {
                    p = point(rightx + r, 0);
                    rightx += 2 * r;
                    topy = max(topy, r);
                    bottomy = max(bottomy, r);
                } else if(leftx == minn) {
                    p = point(-leftx - r, 0);
                    leftx += 2 * r;
                    topy = max(topy, r);
                    bottomy = max(bottomy, r);
                } else if(topy == minn) {
                    p = point(0, topy + r);
                    leftx = max(leftx, topy);
                    rightx = max(rightx, topy);
                    topy += 2 * r;
                } else {
                    p = point(0, -bottomy - r);
                    leftx = max(leftx, topy);
                    rightx = max(rightx, topy);
                    bottomy += 2 * r;
                }
                ret.push_back(circle(p, r));
                //trace(i, r, leftx, rightx, topy, bottomy);
            }

            //trace(ret);
            return ret;
        }
};

static constexpr int LEN = 512;
static constexpr int NUM = 1025;
static constexpr int OFFSET = 512;
vector<circle> blocks[NUM][NUM];
class CircleQuery {

    public:
    CircleQuery() {
        fo(i, NUM) fo(j, NUM) blocks[i][j].clear();
    }
    void add(circle cir) {
            point p = cir.center;
            int r = cir.radius;
            int lx = (p.x - r) / LEN, hx = (p.x + r) / LEN;
            int ly = (p.y - r) / LEN, hy = (p.y + r) / LEN;
            //trace(cir, lx, hx, ly, hy);
            rep(x, lx + OFFSET, hx + OFFSET ) rep(y, ly + OFFSET, hy + OFFSET) {
                //trace(x, y);
                assert(x < NUM && y < NUM);
                blocks[x][y].push_back(cir);
            }
        }

        bool isin(point p, int r) {
            rep(x, (p.x - r) / LEN + OFFSET, (p.x + r) / LEN + OFFSET) rep(y, (p.y - r) / LEN + OFFSET, (p.y + r) / LEN + OFFSET) {
                //trace(x, y);
                assert(x < NUM && y < NUM);
                for(const circle &cir: blocks[x][y]) {
                    int dr = r + cir.radius;
                    if(cir.center.sqDist(p) < dr * dr) return true;
                }
            }
            return false;
        }
};

class NearestCirclePlacer: public IPlacer {
    public:
        vector<circle> _place(vector<Item> items) {
            CircleQuery cq;
            vector<circle> ret;

            angle_t inc = 2 * PI;
            if(n <= 200) inc /= 360;
            else if(n <= 400) inc /= 180;
            else if (n <= 900) inc /= 90;
            else inc /= 72;
            circle cir;

            fo(i, n) {
                int r = items[i].r;
                point p;
                length_t best = oo;
                fo(j, i) {
                    for(angle_t a = -PI; a < PI + eps; a += inc) {
                        auto tmp = fromPolar(ret[j].radius + r, a);
                        int x, y;
                        if(tmp.fi < 0) x = ret[j].center.x + int(floor(tmp.fi));
                        else x = ret[j].center.x + int(ceil(tmp.fi));
                        if(tmp.se < 0) y = ret[j].center.y + int(floor(tmp.se));
                        else y = ret[j].center.y + int(ceil(tmp.se));

                        point cur(x, y);

                        length_t cdist = cur.sqDist();
                        if(!cq.isin(cur, r) && cdist < best) {
                            p = cur;
                            best = cdist;
                        }
                    }
                }
                cir = circle(p, r);
                //trace(i, cir);
                assert(!cq.isin(cir.center, cir.radius));
                cq.add(cir);
                ret.push_back(cir);
            }
            //trace(ret);
            return ret;
        }
};



vector<IOrderer*> orderers;
vector<IPlacer*> placers;

void init() {
    //orderers.push_back(new RandomOrderer());
    if(n <= 500) orderers.push_back(new WeightedOrderer());
    if(n <= 600) orderers.push_back(new RadiusOrderer());
    if(n <= 700) orderers.push_back(new RatioOrderer());
    //if(n <= 700) orderers.push_back(new AreaRatioOrderer());
    orderers.push_back(new AllTypeWeightedOrderer());

    //placers.push_back(new RandomPlacer());
    //placers.push_back(new LinearPlacer());
    //placers.push_back(new Simple2AxisPlacer());
    placers.push_back(new NearestCirclePlacer());

    for(const auto &orderer: orderers) {
        vector<Item> it = orderer->order();
        for(const auto &placer: placers) {
            consider(placer->place(it));
        }
    }
}

void solve() {
    init();
}

int main() {
    scanf("%d", &n);
    fo(i, n) {
        items[i].idx = i;
        scanf("%d%d", &items[i].r, &items[i].w);
    }
    solve();
    fo(i, n) {
        printf("%d %d\n", best.circles[i].center.x, best.circles[i].center.y);
    }
    
    
	return 0;
}

