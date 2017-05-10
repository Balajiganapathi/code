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
constexpr auto oo  = numeric_limits<ll>::max() / 2 - 2;
constexpr auto eps = 1E-9L;
constexpr auto mod = 1000000007;

/* code */
constexpr int mx_n = 100005, mx_m = 100005, mx_p = 102;

int n, m, p, d[mx_n], h[mx_m], t[mx_m];
ll cd[mx_n];
ll req[mx_n], cr[mx_n];

class Fraction {
public:
    ll n, d;
    Fraction(ll _n, ll _d) {
        n = _n; d = _d;
    }

    bool operator <(const Fraction &f) const {
        return 1.0L * n / d < 1.0L * f.n / f.d - eps;
    }

    bool operator <=(const Fraction &f) const {
        return 1.0L * n / d <= 1.0L * f.n / f.d + eps;
    }

    bool operator ==(const Fraction &f) const {
        return n == f.n && d == f.d;
    }
};

class Line {
public:
    ll m, c;
    Line(ll _m, ll _c) {
        m = _m; c = _c;
        if(c >= oo) c = oo;
    }

    Fraction intX(const Line &l) const {
        return Fraction(l.c - c, m - l.m);
    }

    ll eval(ll x) {
        if(c >= oo) return oo;
        return m * x + c;
    }
};

bool canRemove(const Line &l1, const Line &l2, const Line &l) {
    return l.intX(l1) <= l1.intX(l2);
}

class ConvexHullOpti {
public:
    deque<pair<Fraction, Line>> hull;

    void add(const Line &l) {
        assert(hull.empty() || hull.back().se.m >= l.m);
        if(si(hull) < 1) {
            hull.emplace_back(Fraction(oo, 1), l);
            return;
        }

        while(si(hull) > 2 && canRemove(hull[si(hull) - 2].se, hull.back().se, l)) {
            hull.pop_back();
        }

        hull.back().fi = hull.back().se.intX(l);
        //while(si(hull) >= 2 && hull.back().fi == hull[si(hull) - 2].fi) hull.pop_back();
        hull.emplace_back(Fraction(oo, 1), l);
    }
};

ll dp[2][mx_n];
int c = 0;

void solveRow() {
    ConvexHullOpti opti;
    rep(i, 0, m) if(dp[1-c][i] < oo) {
        //trace(i, dp[1-c][i]);
        opti.add(Line(-i, dp[1-c][i] + cr[i]));
    }
    //fo(i, si(opti.hull)) trace(i, opti.hull[i].fi.n, opti.hull[i].fi.d, opti.hull[i].se.m, opti.hull[i].se.c);
    dp[c][0] = 0;
    int idx = 0;
    rep(i, 1, m) {
        ll x = req[i-1];
        while(idx + 1 < si(opti.hull) && 1.0L * x * opti.hull[idx].fi.d > opti.hull[idx].fi.n - eps) {
            ++idx;
        }
        dp[c][i] = opti.hull[idx].se.eval(x) + x * i - cr[i];
        //dp[c][i] = oo;
        ll cdp = oo;
        fo(j, i) cdp = min(cdp, dp[1-c][j] + 1ll * (i-j) * req[i-1] - (cr[i] - cr[j]));
        //trace(i, cdp, dp[c][i], req[i-1]);
        assert(cdp == dp[c][i]);
        //fo(j, i) dp[c][i] = min(dp[c][i], dp[1-c][j] + 1ll * (i-j) * req[i]);
    }
}

ll solve() {
    fo(i, m+1) dp[0][i] = oo;
    dp[0][0] = 0;
    rep(k, 1, p) {
        c = 1 - c;
        solveRow();
    }
    return dp[c][m];
}

int main() {
#ifndef TEST
    cin >> n >> m >> p;
    re(i, 1, n) cin >> d[i];
    fo(i, m) {
        cin >> h[i] >> t[i];
        --h[i];
    }
#else
    n = 1000; m = 20000; p = 20;
    re(i, 1, n) d[i] = rand() % 10000 + 1;
    fo(i, m) {
        h[i] = rand() % n;
        t[i] = rand() % 10000000000 + 1;
    }
#endif
    re(i, 1, n) cd[i] = cd[i-1] + d[i];
    fo(i, m) req[i] = max(0ll, 1ll * t[i] - cd[h[i]]);
    sort(req, req + m);
    fo(i, m) trace(i, req[i]);
    rep(i, 1, m) cr[i] = cr[i-1] + req[i-1];

    ll ans = solve();

    cout << ans << '\n';
    
	return 0;
}

