/* string coder = "Balajiganapathi S"; // Never give up!  */

//#define LOCAL
#ifdef LOCAL
#   define TRACE
//#   define TEST
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
constexpr int mod[2] = {1000000007, 1000000009};

/* code */
constexpr int mx_n = 1003;

int c[2][mx_n], e[2][mx_n];
void pre() {
    fo(mi, 2) {
        c[mi][0] = 1;
        c[mi][1] = 1;
        e[mi][1] = 1;
    }

    re(i, 2, mx_n) {
        for(int j = 0; j <= i-1; ++j) {
            fo(mi, 2) {
                c[mi][i] = (c[mi][i] + 1ll * c[mi][j] * c[mi][i-1-j] % mod[mi]) % mod[mi];
                e[mi][i] = (e[mi][i] + 1ll * c[mi][j] * e[mi][i-1-j] % mod[mi]) % mod[mi];
                e[mi][i] = (e[mi][i] + 1ll * e[mi][j] * c[mi][i-1-j] % mod[mi]) % mod[mi];
            }
        }
        //trace(i, c[0][i], e[0][i]);
    }
}

int solve(ll n, int mod) {
    --n;
    ll a = n, b = n + 1;
    if(a % 2 == 0) a /= 2;
    else b /= 2;
    ll n2 = 2 * n - 1;

    ll g = __gcd(a, n2);
    a /= g; n2 /= g;
    g = __gcd(b, n2);
    b /= g; n2 /= g;

    a %= mod; b %= mod;
    int P = 1ll * a * b % mod;
    int Q = n2 % mod;
    trace(n, n2, P, Q);
    return 1ll * P * modpow(Q, mod - 2, mod) % mod;
}

pair<int, int> solve(ll n) {
    return mp(solve(n, mod[0]), solve(n, mod[1]));
}
int main() {
    pre();

    int t;
    cin >> t;
    while(t--) {
        ll n;
#ifdef TEST
        n = (100 - t % 100) % 100 + 1;
#else
        cin >> n;
#endif
        pi ans = solve(n);
#ifdef TEST
        vi tmp;
        fo(mi, 2) {
            int cur = 1ll * e[mi][n-1] * modpow(c[mi][n-1], mod[mi] - 2, mod[mi]) % mod[mi];
            tmp.push_back(cur);
        }
        pi chk(tmp[0], tmp[1]);
        if(chk != ans) {
            trace(n, chk, ans);
        }
#endif
        cout << ans.fi << " " << ans.se << '\n';
    }
    
	return 0;
}

