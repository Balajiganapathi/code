/* string coder = "Balajiganapathi S"; // Never give up!  */
#pragma comment(linker, "/STACK: 200000000")
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

template <class T> inline void hash_combine(std::size_t& seed, const T& v) {
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}

namespace std {
    template<>
    class hash<pi> {
        public:
        size_t operator()(const pi &s) const {
            size_t h = 0;
            hash_combine(h, s.fi);
            hash_combine(h, s.se);
            return h;
        }
    };
}



/* code */
constexpr int mx_n = 2000106;
int n;
int a[mx_n], b[mx_n];
int nxta[mx_n], nxtb[mx_n];
int ca[mx_n], cb[mx_n];
int tmp[mx_n];

void input() {
    ini(a, -1); ini(b, -1);
    cin >> n;
    trace(n);
    int ka;
    cin >> a[1] >> ka;
    int idx = 2;
    fo(i, ka) {
        int ra, la;
        cin >> ra >> la;
        fo(j, la) {
            cin >> tmp[j];
        }
        fo(k, ra) {
            fo(j, la) {
                a[idx] = a[idx-1] + tmp[j];
                ++idx;
            }
        }

    }

    int kb;
    cin >> b[1] >> kb;
    idx = 2;
    fo(i, kb) {
        int rb, lb;
        cin >> rb >> lb;
        fo(j, lb) {
            cin >> tmp[j];
        }
        fo(k, rb) {
            fo(j, lb) {
                b[idx] = b[idx-1] + tmp[j];
                ++idx;
            }
        }    
    }

    //rep(i, 1, n) trace(i, a[i], b[i]);
}

constexpr int mx_f = 4 * mx_n;
int fact[mx_f], ifact[mx_f];
void pre() {
    fact[0] = 1;
    re(i, 1, mx_f)  {
        fact[i] = 1ll * fact[i-1] * i % mod;
    }
    fo(i, mx_f) ifact[i] = modpow(fact[i], mod - 2, mod);
}

void init() {
    ini(ca, 0); ini(cb, 0);
    ini(nxta, 0); ini(nxtb, 0);
    nxta[n+1] = nxtb[n+1] = n+1;
    for(int i = n; i >= 1; --i) {
        nxta[i] = nxtb[i] = i;
        if(i + 1 <= n) {
            if(a[i] == a[i+1]) {
                ca[i] = 1 + ca[i+2];
                nxta[i] = nxta[i+2];
            }
            if(b[i] == b[i+1]) {
                cb[i] = 1 + cb[i+2];
                nxtb[i] = nxtb[i+2];
            }
        }
        if(i + 3 <= n) {
            if(a[i] == a[i+2] && a[i+1] == a[i+3]) {
                ca[i] = 1 + ca[i+4];
                nxta[i] = nxta[i+4];
            }
            if(b[i] == b[i+2] && b[i+1] == b[i+3]) {
                cb[i] = 1 + cb[i+4];
                nxtb[i] = nxtb[i+4];
            }
        }
    }
}

int comp(int n, int k) {
    return 1ll * fact[n] * ifact[k] % mod * ifact[n-k] % mod;
}

map<pi, int> dp;

int solve(int i, int j) {
    if(i == n + 1 && j == n + 1) return 1;
    pi idx(i, j);
    if(dp.count(idx)) return dp[idx];
    int &ret = dp[idx];
    ret = 0;

    if(ca[i] > 0 || cb[j] > 0) {
        ret = 1ll * solve(nxta[i], nxtb[j]) * comp(ca[i] + cb[j], ca[i]) % mod;
        //trace(i, j, ca[i], cb[j], nxta[i], nxtb[j], comp(ca[i] + cb[j], ca[i]), ret);
        return ret;
    }

    if(a[i] == b[j]) {
        ret = solve(i + 1, j + 1);
        return ret;
    }

    // XYX / Y
    if(a[i] == a[i+2] && a[i+1] == b[j]) {
        ret = (ret + 2ll * solve(i + 3, j + 1)) % mod;
        //trace("xyx/y", i, j, ret);
    }

    // XY / YX
    if(a[i] == b[j+1] && b[j] == a[i+1]) {
        ret = (ret + 2ll * solve(i + 2, j + 2)) % mod;
        //trace("xy/xy", i, j, ret);
    }

    // Y / XYX
    if(b[j] == b[j+2] && a[i] == b[j+1]) {
        ret = (ret + 2ll * solve(i + 1, j + 3)) % mod;
        //trace("y/xyx", i, j, ret);
    }

    //trace(i, j, ret);
    return ret;
}

int main() {
    int t;
    pre();
    cin >> t;
    rep(kase, 1, t) {
        input();
        init();
        dp.clear();
        int ans = solve(1, 1);

        cout << "Case #" << kase << ": " << ans << endl;

    }
    
    
	return 0;
}

