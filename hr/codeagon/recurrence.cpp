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
constexpr auto oo  = numeric_limits<int>::max() / 2 - 2;
constexpr auto eps = 1e-6;
constexpr auto mod = 1000000007;

/* code */
constexpr int bx_n = 1003, bx_d = 1003;

int T[bx_n][bx_d];
int T1[bx_n][bx_d];
int T2[bx_n][bx_d];

void prebrute() {
    re(i, 1, bx_d) T[0][i] = modpow(i, mod - 2, mod);
    re(n, 1, bx_n) re(d, 1, bx_d) {
        T[n][d] = 1ll * (n + 1) * modpow(T[n-1][d] + 1, mod - 2, mod) % mod;
    }
    re(d, 1, bx_d) {
        int cur = 1;
        fo(n, bx_n) {
            cur = 1ll * cur * T[n][d] % mod;
            T1[n][d] = cur;
        }
    }
    fo(n, bx_n) {
        int cur = 1;
        T2[n][0] = 1;
        re(d, 1, bx_d) {
            cur = 1ll * cur * T[n][d] % mod;
            T2[n][d] = cur;
        }
    }
}

constexpr int mx_n = 1000006;
int fact[mx_n];
class Expression {
    public:
    int x, y;
    constexpr Expression():x(0),y(0) {}
    Expression(int _x, int _y): x(_x), y(_y) {}

    int eval(ll d) {
        return (x * d + y) % mod;
    }
} a[mx_n], b[mx_n];

void pre() {
    a[0] = Expression(0, 1);
    b[0] = Expression(1, 0);
    re(i, 1, mx_n) {
        a[i] = Expression(1ll * (i + 1) * b[i-1].x % mod, 1ll * (i + 1) * b[i-1].y % mod);
        int x = a[i-1].x + b[i-1].x; if(x >= mod) x -= mod;
        int y = a[i-1].y + b[i-1].y; if(y >= mod) y -= mod;
        b[i] = Expression(x, y);
        //trace(i, a[i].x, a[i].y, b[i].x, b[i].y);
    }
    fact[0] = 1;
    re(i, 1, mx_n) fact[i] = 1ll * fact[i-1] * i % mod;
}

int brute1(int l, int r, int d) {
    return 1ll * T1[r][d] * modpow(T1[l-1][d], mod - 2, mod) % mod;
}

int get1(int n, ll d) {
    d %= mod;
    int num = fact[n+1];
    int den = b[n].eval(d);
    trace(n, d, b[n].x, b[n].y, num, den);
    return 1ll * num * modpow(den, mod - 2, mod) % mod;
}

int solve1(int l, int r, ll d) {
    return 1ll * get1(r, d) * modpow(get1(l - 1, d), mod - 2, mod) % mod;
}

int brute2(int n, int m, ll d) {
    int d1 = d, d2 = m + d;
    return 1ll * T2[n][d2] * modpow(T2[n][d1-1], mod - 2, mod) % mod;
}

int solve2(int n, int m, ll d) {
    int k1 = d % mod, k2 = (d + m) % mod;
    int ret = 1;
    int ca = a[n].eval(k1), cb = b[n].eval(k1);
    int num = 1, den = 1;
    rep(k, k1, k2) {
        num = 1ll * num * ca % mod;
        den = 1ll * den * cb % mod;
        ca += a[n].x; if(ca >= mod) ca -= mod;
        cb += b[n].x; if(cb >= mod) cb -= mod;
    }
    ret = 1ll * num * modpow(den, mod - 2, mod) % mod;

    return ret;
}


int main() {
    std::ios::sync_with_stdio(false);
    int q;
    //prebrute();
    pre();
    cin >> q;
    while(q--) {
        int t, a, b;
        ll c;
        cin >> t >> a >> b >> c;
        int ans = 0;
        if(t == 1) ans = solve1(a, b, c);
        else ans = solve2(a, b, c);
        cout << ans << '\n';
    }
    
    
	return 0;
}

