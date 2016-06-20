/* string coder = "Balajiganapathi S"; // Never give up!  */

//#define LOCAL
#ifdef LOCAL
//#   define TRACE
#   define TEST
//#   define CHECK
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
constexpr auto eps = 1e-6;
constexpr auto mod = 1000000007;

/* code */
constexpr int mx_n = 100005;
int n, a[mx_n], b[mx_n];

class frac {
public:
    int a, b;
    frac(): a(0), b(1) {}
    frac(int x, int y): a(x), b(y) {}
    frac(const frac& f): a(f.a), b(f.b) {}

    bool operator <(const frac &f) const { return 1ll * a * f.b < 1ll * f.a * b; }
    bool operator ==(const frac &f) const { return a == f.a && b == f.b; }
};
ostream& operator<<(ostream& os, const frac &f) { // print a frac
    return os << f.a << "/" << f.b;
}

int ns, s;

class seg {
public:
    int n, f, t;
    vector<frac> fs;
    vector<ll> suma, sumb;
    ll sumb0;
    seg(int _f, int _t) {
        f = _f; t = _t;
        n = t - f + 1;
        trace(f, t, n);

        vector<pair<frac, int>> tmp;
        sumb0 = 0;
        rep(i, f, t) {
            if(a[i] == 0) {}
            else if(b[i] == 0) {sumb0 += a[i];}
            else {
                frac fr(a[i], b[i]);
                tmp.push_back(mp(fr, i));
            }
        }
        n = si(tmp);
        sort(all(tmp));
        suma = vector<ll>(n, 0);
        sumb = vector<ll>(n, 0);

        fs.reserve(n);
        ll ca = 0, cb = 0;
        for(int i = n - 1; i >= 0; --i) {
            fs.push_back(tmp[i].fi);
            int idx = tmp[i].se;
            ca += a[idx];
            cb += b[idx];
            suma[i] = ca;
            sumb[i] = cb;
        }
        reverse(all(fs));
        trace(fs);
        trace(suma);
        trace(sumb);
        trace(suma0, sumb0);
    }

    ll getSum(const frac &fr) const {
        int c = fr.b, d = fr.a;
        trace(suma, sumb0);
        //if(c == 0) return 0;
        if(d == 0) return ((si(suma) == 0? 0: suma[0]) + sumb0) * c;
        int idx = lower_bound(all(fs), fr) - fs.begin();
        trace(f, t, fr, idx);
        ll ans = 0;
        if(idx == si(fs)) ans = sumb0 * c;
        else ans = c * (sumb0 + suma[idx]) - d * sumb[idx];
        
#ifdef CHECK
        ll cans = ans;
        cans = getSum(f, t, c, d); trace(ans, cans);
        trace(fs);
        trace(suma);
        trace(sumb);
        trace(suma0, sumb0);
        assert(ans == cans);
#endif
        return ans;
    }

    ll getSum(int x, int y, int c, int d) const {
        ll ans = 0;
        for(int i = x; i <= y; ++i) ans += max(0ll, 1ll * c * a[i] - 1ll * d * b[i]);
        trace(x, y, c, d, ans);

        return ans;
    }

};

vector<seg> segs;

void pre() {
    s = sqrt(n) + 500;
    ns = (n + s - 1) / s;
    fo(i, ns) {
        int f = i * s, t = min(n - 1, i * s + s - 1);
        trace(i, f, t);
        segs.push_back(seg(f, t));
    }
    trace(n, ns, s);
}


ll brute(int l, int r, int c, int d) {
    ll ans = 0;
    rep(i, l, r) {
        ans += max(0ll, 1ll * a[i] * c - 1ll * b[i] * d);
    }

    return ans;
}

ll solve(int l, int r, int c, int d) {
    trace(n, ns, s);
    trace(s);
    int ls = l / s, rs = r / s;
    if(ls == rs) return segs[ls].getSum(l, r, c, d);
    ll ans = 0;
    int s1 = ls, s2 = rs;

    if(l != ls * s) {
        ans += segs[ls].getSum(l, ls * s + s - 1, c, d);
        ++s1;
    }
    if(r != rs * s + s - 1) {
        ans += segs[rs].getSum(rs * s, r, c, d);
        --s2;
    }

    trace(ls, rs);
    frac fr(d, c);
    rep(i, s1, s2) {
        trace(i);
        ans += segs[i].getSum(fr);
    }

    return ans;
}

int main() {
    int q;
#ifdef TEST
    n = 100000;
    fo(i, n) a[i] = rand() % 1000001;
    fo(i, n) b[i] = rand() % 1000001;
    q = 100000;
#else
    scanf("%d", &n);
    fo(i, n) scanf("%d", a + i);
    fo(i, n) scanf("%d", b + i);
    scanf("%d", &q);
#endif

    pre();
    while(q--) {
        int l, r, c, d;
#ifdef TEST
        //l = rand() % n; r = rand() % n;
        //if(l > r) swap(l, r);
        l = rand() % 10, r = n - 1 - rand() % 10;
        c = rand() % 1000001;
        d = rand() % 1000001;
#else
        scanf("%d %d %d %d", &l, &r, &c, &d);
        --l; --r;
#endif

        ll ans = solve(l, r, c, d);
        printf("%lld\n", ans);
#ifdef CHECK
        ll bans = brute(l, r, c, d);
        if(ans != bans) {
            trace(ans, bans);
            trace(l, r, c, d);
            rep(i, l, r) trace(i, a[i], b[i]);
            assert(ans == bans);
        }
#endif
        fflush(stdout);
    }

    
	return 0;
}

