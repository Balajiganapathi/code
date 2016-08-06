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
constexpr long double eps = 1e-9;
constexpr auto mod = 1000000007;

/* code */
constexpr int mx = -1;

int n, v1, v2, l, k;

long double dropAt(long double x) {
    long double ct = 0, cd = 0;
    int rem = n;
    long double ans = 0;
    while(rem > 0 && cd < l - eps) {
        long double till = min(1.0L * l, cd + x);
        long double t = max(0.0L, (till - cd))/ v2;
        rem -= k;
        ct += t;
        ans = max(ans, ct + (l - till) / v1);
        cd += t * v1;
        //trace(t, cur);
        t = max(0.0L, (till - cd)) / (v1 + v2);
        cd += t * v1;
        ct += t;
        //trace(t, cur);
        //trace(ans);
    }
    return ans;
}

long double firstDist(long double x) {
    long double ct = x / v2;
    long double cd = ct * v1;
    int rem = n - k;
    long double ans = ct + (l - x) / v1;
    long double dv = (v2 - v1);
    long double fi = x;

    long double t = max(0.0L, fi - cd) / (v1 + v2);
    cd += t * v1; fi += t * v1; fi = min(1.0L * l, fi); ct += t;

    while(rem > 0 && cd < l + eps) {
        long double till = min(1.0L * l, cd + (fi - cd) / dv * v2);
        long double t = max(0.0L, (till - cd))/ v2;
        rem -= k;
        ct += t;
        ans = max(ans, ct + (l - till) / v1);
        cd += t * v1;
        fi += t * v1; fi = min(1.0L * l, fi);
        //trace(t, cur);
        t = max(0.0L, (till - cd)) / (v1 + v2);
        cd += t * v1;
        fi += t * v1; fi = min(1.0L * l, fi);
        ct += t;
        //trace(t, cur);
        //trace(ans);
    }
    return ans;
}

int main() {
    cin >> n >> l >> v1 >> v2 >> k;

    int rem = n;
    long double ans = 0, cur = 0;
    long double lo = 0, hi = l;
    fo(iter, 10000) {
        long double m1 = (2 * lo + hi) / 3;
        long double m2 = (lo + 2 * hi) / 3;
        trace(m1, firstDist(m1), m2, firstDist(m2));
        if(firstDist(m1) < firstDist(m2)) {
            hi = m2;
        } else {
            lo = m1;
        }
    }

    ans = firstDist(lo);
        
    cout << fixed << setprecision(9) << ans << endl;
    
    
	return 0;
}

