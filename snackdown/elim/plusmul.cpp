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
constexpr auto mod = 1000000007;

/* code */
constexpr int mx_n =  100005;
int p2[mx_n], fact[mx_n], inv[mx_n];
int a[mx_n], n;

void pre() {
    p2[0] = 1;
    re(i, 1, mx_n) p2[i] = 2ll * p2[i-1] % mod;
    re(i, 1, mx_n) inv[i] = modpow(i, mod - 2, mod);
}

int brute() {
    int ans = 0;
    rep(i, 1, n) {
        int rem = n - 1;
        if(i - 1 >= 1) --rem;
        if(i + 1 <= n) --rem;
        int cc = 0;
        rep(j, i, n) {
            int cur = 1ll * fact[j] * modpow(fact[i-1], mod - 2, mod) % mod * p2[rem] % mod;
            //trace(i, j, rem, cur);
            cc = (cc + cur) % mod;
            if(j + 1 < n) --rem;
        }
        //trace(i, cc);
        ans = (ans + cc) % mod;
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    pre();
    int t;
#ifndef TEST
    cin >> t;
#else
    t = 20;
#endif
    while(t--) {
        int cur = 0;
        int ans = 0;
#ifndef TEST
        cin >> n;
        rep(i, 1, n) cin >> a[i];
#else
        n = rand() % 1000 + 1;
        rep(i, 1, n) a[i] = rand() % 1000000000 + 1;
#endif
        fact[0] = 1;
        rep(i, 1, n) fact[i] = 1ll * fact[i-1] * a[i] % mod;

        int f = fact[n];
        for(int j = n; j >= 1; --j) {
            int rem = n - 1;
            if(j - 1 >= 1) --rem;
            if(j + 1 <= n) --rem;

            cur = (fact[j] + 1ll * (j == n-1? 1: inv[2]) * cur) % mod;
            //trace(j, rem, f, cur, 1ll * cur * p2[rem] % mod);
            f = 1ll * f * modpow(a[j], mod - 2, mod) % mod;
            int F = modpow(fact[j-1], mod - 2, mod);
            int add = 1ll * cur * p2[rem] % mod * F % mod;
            //int ar = rem - (n - j);
            //add = (add + 1ll * p2[ar] * fact[n] % mod * F) % mod;
            ans = (ans + add) % mod;
            //trace(j, rem, ar, add, ans);
        }

        cout << ans << '\n';
#ifdef TEST
        int bans = brute();
        if(ans != bans) {
            trace(n);
            fo(i, n) trace(i, a[i]);
            trace(ans, bans);
            assert(ans == bans);
        }
#endif
    }
    
    
	return 0;
}

