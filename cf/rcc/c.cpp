/* string coder = "Balajiganapathi S"; // Never give up!  */

//#define LOCAL
#ifdef LOCAL
#   define TRACE
#   define TEST
#   define GEN
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
constexpr auto eps = 1e-6;
constexpr auto mod = 1000000007;

/*-------------------------------------------------------------------------------------------------------------------------------------*/
/*<shapes>*/
/*WARNING: UNTESTED*/
/*Requires PI and eps constants*/

using itype = long double;
using otype = long double; // Assumes double or long double, uses eps constant

class point {
public:
    itype x, y;

    constexpr point(): x(0), y(0) {}
    point(const itype &_x, const itype &_y): x(_x), y(_y) {}
    point(const point &p): x(p.x), y(p.y) {}

    otype dist(const point &p) const {
        otype dx = otype(x) - p.x;
        otype dy = otype(y) - p.y;
        return sqrt(dx * dx + dy * dy);
    }
};

ostream& operator<<(ostream& os, const point& p) { // print a point
    return os << "(" << p.x << ", " << p.y << ")";
}

otype toDegrees(const otype &rad) {
    return rad * 180.0 / PI;
}

otype toRadians(const otype &deg) {
    return deg * PI / 180.0;
}

class vec {
public:
    itype x, y;

    constexpr vec(): x(0), y(0) { }
    vec(const itype &_x, const itype &_y): x(_x), y(_y) {}
    vec(const vec &v): x(v.x), y(v.y) {}
    vec(const point &from, const point &to) {
        x = to.x - from.x;
        y = to.y - from.y;
    }

    vec operator+(const vec &v) const { return vec(x + v.x, y + v.y); }
    vec operator-(const vec &v) const { return vec(x - v.x, y - v.y); }
    // Dot product
    otype operator*(const vec &v) const { return otype(x) * v.x - otype(y) * v.y; }
    // Cross product
    otype operator^(const vec &v) const { return otype(x) * v.y - otype(y) * v.x; }

    otype length() const { return sqrt(otype(x) * x + otype(y) * y); }
    long double angleWith(const vec &v) const { 
        long double angle = acos((*this * v) / (length() * v.length())); 
        return angle;
    } // Angle in radians
};

ostream& operator<<(ostream& os, const vec& v) { // print a vec
    return os << "->(" << v.x << ", " << v.y << ")";
}

class line {
public:
    point a, b;
    vec v;
    otype la, lb, lc;

    constexpr line(): la(0), lb(0), lc(0) {}
    line(const point &_a, const point &_b): a(_a), b(_b) { init(); }
    line(const line &l): a(l.a), b(l.b) { init(); }
    line(const itype &x1, const itype &y1, const itype &x2, const itype &y2): a(x1, y1), b(x2, y2) { init();  }
    //line(const segment &s): a(s.a), b(s.b) {}

private:
    void init() {
        v = vec(a, b);
        la = otype(b.y) - a.y;
        lb = otype(a.x) - b.x;
        lc = la * a.x + lb * a.y;
    }

public:
    bool isParallelTo(const line &l) const { 
        otype det = la * l.lb - l.la * lb;
        return fabs(det) <= eps;
    }

    point intersection(const line &l) const {
        assert(!isParallelTo(l));
        otype det = la * l.lb - l.la * lb;
        assert(fabs(det) > eps);
        point p((l.lb * lc - lb * l.lc) / det, (la * l.lc - l.la * lc) / det);
        return p;
    }

    bool contains(const point &p) const {
        return true; // TODO
    }

    otype dist(const point &c) { 
        vec ba(b, a), ca(c, a);
        return (ba ^ ca) / sqrt(ba * ba);
    }
};

ostream& operator<<(ostream& os, const line& l) { // print a line
    return os << l.a << " <-> " << l.b;
}

class segment {
public:
    point a, b;
    line theLine;

    constexpr segment() {}
    segment(const point &_a, const point &_b): a(_a), b(_b), theLine(_a, _b) { }
    segment(const segment &l): a(l.a), b(l.b), theLine(l.theLine) {}
    segment(const itype &x1, const itype &y1, const itype &x2, const itype &y2): a(x1, y1), b(x2, y2), theLine(x1, y1, x2, y2) {}

    otype length() const { return a.dist(b); }

    bool intersects(const segment &s) const { 
        if(theLine.isParallelTo(s.theLine)) return false;
        point p = theLine.intersection(s.theLine);
        return contains(p) && s.contains(p);
    }

    bool contains(const point &p) const { 
        if(!theLine.contains(p)) return false;
        if(!(min(a.x, b.x) - eps <= p.x && p.x <= max(a.x, b.x) + eps)) return false;
        if(!(min(a.y, b.y) - eps <= p.y && p.y <= max(a.y, b.y) + eps)) return false;
        return true;
    }

    point intersection(const segment &s) const {
        assert(intersects(s));
        return theLine.intersection(s.theLine);
    }

    point midpoint() const { return point((otype(a.x) + b.x) / 2, (otype(a.y) + b.y) / 2); }
    otype dist(const point &c) {
        vec ba(b, a), ca(c, a), cb(c, b), ab(a, b), bc(b, c), ac(a, c);
        otype dist = (ba ^ ca) / sqrt(ba * ba);
        if(cb * ba > eps) return sqrt(bc * bc);
        if(ca * ab > eps) return sqrt(ac * ac);
        return fabs(dist);
    }

private:
    point getIntersectionPoint(const segment &s) const {
        return theLine.intersection(s.theLine);
    }
};

ostream& operator<<(ostream& os, const segment& s) { // print a seg
    return os << s.a << " - " << s.b;
}

class circle {
public:
    point center;
    itype radius;

    constexpr circle(): radius(0) {}
    circle(const point &_center, const itype &_radius): center(_center), radius(_radius) {}
    otype area() { return PI * radius * radius; }

    // TODO
    bool intersects(const circle &c) const {
        otype dist = center.dist(c.center);
        return dist <= otype(radius) + c.radius + eps;
    }
    bool intersects(const segment &s) const {}
    bool contains(const point &p) const {}
    vector<point> intersection(const circle &c) const {}
    vector<point> intersection(const line &s) const {}
    vector<point> intersection(const segment &s) const {
        vector<point> linePoints = intersection(line(s.a, s.b));
        vector<point> ret;
        for(const point &p: linePoints) if(s.contains(p)) ret.push_back(p);
        return ret;
    }
};

class polygon {
public:
    vector<point> points;

    polygon() {}
    polygon(const vector<point> &_points): points(_points) {}
    polygon(const polygon &pol): points(pol.points) {}

    otype area() const {
        otype ret = 0;
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


class Triangle {
    // TODO
};


// TODO
polygon convexHull(vector<point> points) {
}

/*</shapes>*/
/*-------------------------------------------------------------------------------------------------------------------------------------*/

/* code */
constexpr int mx = -1;

int n, k;
list<pi> ans;

int pts(int x, int y) {
    return x * y + 2 * x + 2 * y + 1;
}

void check() {
    trace(si(ans));
    assert(si(ans) == n + 1);
    vector<pi> v(all(ans));
    int cnt = 0;
    fo(i, n) {
        assert((v[i].fi == v[i+1].fi) ^ (v[i].se == v[i+1].se));
        assert(1 <= v[i].fi && v[i].fi <= 3000);
        assert(1 <= v[i].se && v[i].se <= 3000);
    }
    assert(1 <= v[n].fi && v[n].fi <= 3000);
    assert(1 <= v[n].se && v[n].se <= 3000);
    fo(i, n) {
        segment s1(v[i].fi, v[i].se, v[i+1].fi, v[i+1].se);
        re(j, i + 3, n) {
            segment s2(v[j].fi, v[j].se, v[j+1].fi, v[j+1].se);
            if(s1.intersects(s2)) {
                //trace(s1, s2, s1.intersection(s2));
                ++cnt;
            }
        }
    }
    trace(cnt);
    assert(k == cnt);
}


int main() {
    int t;
#ifdef GEN
    t = 10000;
#else
    scanf("%d", &t);
#endif
    while(t--) {
        ans.clear();
#ifdef GEN
        n = rand() % 10 + 1;
        int n2 = n / 2;
        int tot = n2 * (n2 - 1) / 2;
        k = rand() % (tot + 1);
#else
        scanf("%d %d", &n, &k);
#endif
        if(n == 1) {
            ans.push_back(mp(1, 1));
            ans.push_back(mp(1, 3));
        } else if(n == 2) {
            ans.push_back(mp(1, 1));
            ans.push_back(mp(1, 3));
            ans.push_back(mp(4, 3));
        } else if(n == 3) {
            ans.push_back(mp(1, 1));
            ans.push_back(mp(1, 3));
            ans.push_back(mp(4, 3));
            ans.push_back(mp(4, 10));
        } else {
            int co = 3000;
            ans.push_back(mp(co / 2, co));
            ans.push_back(mp(co / 2, 1));
            ans.push_back(mp(co / 2 + 2, 1));
            ans.push_back(mp(co / 2 + 2, co - 10));

            int rem = n - 3;
            int remk = k;

            int y1 = 1, y2 = co - 10;
            int cx = co / 2 + 2, cy = co - 10;
            vi ver;
            ver.push_back(co / 2);
            int pos = 0;
            while(remk > 0) {
                if(pos == 0) {
                    if(remk >= si(ver)) {
                        remk -= si(ver);
                        ver.push_back(cx);
                        cx = ver[0] - 2;
                        ans.push_back(mp(cx, cy));
                    } else {
                        cx = ver[si(ver) - 1 - remk + 1] - 1;
                        ans.push_back(mp(cx, cy));
                        remk = 0;
                    }
                    --rem;
                    if(rem > 0 && remk > 0) {
                        y1 += 2;
                        cy = y1;
                        ans.push_back({cx, cy});
                        --rem;
                    }
                } else {
                    if(remk >= si(ver)) {
                        remk -= si(ver);
                        ver.insert(ver.begin(), cx);
                        cx = ver.back() + 2;
                        ans.push_back({cx, cy});
                    } else {
                        cx = ver[remk-1] + 1;
                        ans.push_back({cx, cy});
                        remk = 0;
                    }
                    --rem;
                    if(rem > 0 && remk > 0) {
                        y2 -= 2;
                        cy = y2;
                        ans.push_back({cx, cy});
                        --rem;
                    }
                }
                pos = (pos + 1) % 2;
            }

            cx = co / 2; cy = co;
            for(; rem > 0; )  {
                if(rem > 0) {
                    ++cx;
                    ans.insert(ans.begin(), mp(cx, cy));
                    --rem;
                }
                if(rem > 0) {
                    --cy;
                    ans.insert(ans.begin(), mp(cx, cy));
                    --rem;
                }
                if(rem > 0) {
                    ++cx;
                    ans.insert(ans.begin(), mp(cx, cy));
                    --rem;
                }
                if(rem > 0) {
                    ++cy;
                    ans.insert(ans.begin(), mp(cx, cy));
                    --rem;
                }
            }
        }
        for(auto pt: ans) {
            printf("%d %d\n", pt.fi, pt.se);
        }

#ifdef TEST
        check();
#endif 

    }
    
	return 0;
}

