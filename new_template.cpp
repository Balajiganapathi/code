/* string coder = "Balajiganapathi S"; // Never give up!  */

#include<bits/stdc++.h>

//#define LOCAL
#ifdef LOCAL
#   define TRACE
#   define TEST
#   define CHECK
#else
#   define NDEBUG
#endif

using namespace std;

/* type shortcuts */
using vi  = vector<int>;
using ll  = long long;
using ull = unsigned long long;
using pii = tuple<int, int>;
using vpi = vector<pii>;
using ld  = long double;

/* shortcut macros */
/* tuples */
#define mt          make_tuple
#define gt(t,i)     get<i>(t)
#define fi(t)       gt(t,0)
#define se(t)       gt(t,1)
/* loops */
#define rep(i,s,e)  for(decltype(e)i=s;i<=e;++i)
#define re(i,s,e)   for(decltype(e)i=s;i<e;++i)
#define fo(i,e)     re(i,0,e)
#define rrep(i,e,s) for(decltype(e)i=e;i>=s;--i)
#define rre(i,e,s)  for(decltype(e)i=e-1;i>s;--i)
#define rfo(i,e)    rre(i,e,0)
/* containers */
#define si(c)       (int(c.size()))
#define all(c)      c.begin(), c.end()
/* bit */
#define is1(x,b)    ((c>>b)&1)

/* trace macro */
#ifdef TRACE
#   define trace(v...)  {cerr << __func__ << "::" << __LINE__ << ": " ;_dt(#v, v);}
#else
#   define trace(...)
#endif

// DO NOT PANIC
#ifdef TRACE
pii _gp(string s) {
    pii r(0, si(s) - 1);
    int p = 0, s1 = 0, s2 = 0, start = 1;
    fo(i, si(s)) {
        int x = (s1 | s2);
        if(s[i] == ' ' && start) {
            ++fi(r);
        } else {
            start = 0;
            if(s[i] == ',' && !p && !x) {
                se(r) = i - 1;
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
    pii p = _gp(u);
    cerr << u.substr(fi(p), se(p) - fi(p) + 1) << " = " << forward<H>(v) << " |" << endl;
}

template<typename H, typename ...T> void _dt(string u, H&& v, T&&... r) {
    pii p = _gp(u);
    cerr << u.substr(fi(p), se(p) - fi(p) + 1) << " = " << forward<H>(v) << " | ";
    _dt(u.substr(se(p) + 2), forward<T>(r)...);
}

template<typename T> 
ostream &operator <<(ostream& o, vector<T> v) { // print a vector
    o << "[";
    fo(i, si(v) - 1) o << v[i] << ", ";
    if(!v.empty()) o << v.back();
    return o << "]";
}

template<typename T1, typename T2> 
ostream &operator <<(ostream& o, map<T1, T2> m) { // print a map
    o << "{";
    for(auto &p: m) o << " (" << p.fi << " -> " << p.se << ")";
    return o << " }";
}

template<typename T> 
ostream &operator <<(ostream& o, set<T> s) { // print a set
    o << "{";
    for(auto &entry: s) o << entry << ", ";
    if(!s.empty()) o << *s.rbegin();
    return o << "}";
}

template <size_t n, typename... T>
typename enable_if<(n >= sizeof...(T))>::type
    print_tuple(ostream&, tuple<T...>) {} 

template <size_t n, typename... T>
typename enable_if<(n < sizeof...(T))>::type
    print_tuple(ostream& os, tuple<T...> tup) {
    if (n != 0)
        os << ", ";
    os << get<n>(tup);
    print_tuple<n+1>(os, tup);
}

template <typename... T>
ostream& operator<<(ostream& os, tuple<T...> tup) { // print a tuple
    os << "("; print_tuple<0>(os, tup); return os << ")"; 
}
#endif

/* hash */
template <class T> inline void hash_combine(size_t& seed, T const& v) { seed ^= hash<T>()(v) + 0x9e3779b9 + (seed<<6) + (seed>>2); }

namespace {
    template <class Tuple, size_t Index = tuple_size<Tuple>::value - 1>
        struct HashValueImpl {
            static void apply(size_t& seed, Tuple const& tuple) {
                HashValueImpl<Tuple, Index-1>::apply(seed, tuple);
                hash_combine(seed, get<Index>(tuple));
            }
        };

    template <class Tuple> 
        struct HashValueImpl<Tuple,0> {
            static void apply(size_t& seed, Tuple const& tuple) { hash_combine(seed, get<0>(tuple)); }
        };
}

namespace std {
    template <typename ... TT>
        struct hash<tuple<TT...>> {
            size_t operator()(tuple<TT...> const& tt) const {                                              
                size_t seed = 0;                             
                HashValueImpl<tuple<TT...> >::apply(seed, tt);    
                return seed;                                 
            }                                              
        };
}

 
/* io */
class initio {
public:
    initio() {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);
        cout << setprecision(10) << fixed;
    }
} __initio;

template<typename H> void in(H& h) { cin >> h; }
template<typename H, typename ...T> void in(H& h, T&&... t) { cin >> h; in(forward<T>(t)...); }
template<typename H> ostream& out(H&& h) { return cout << forward<H>(h); }
template<typename H, typename ...T> ostream& out(H&& h, T&&... t) { cout << forward<H>(h) << ' '; return out(forward<T>(t)...); }
template<typename ...T> ostream& outl(T&&... t) { return out(forward<T>(t)..., '\n'); }

/* modulo */
template<class T> inline T madd(T a, T b, T mod) { T ret = a + b; if(ret >= mod) ret -= mod; return ret; }
template<class T> inline T msub(T a, T b, T mod) { T ret = a - b; if(ret < 0) ret += mod; return ret; }
template<class T1, class T2> inline T1 mmul(T1 a, T2 b, T1 mod) { return 1ll * a * b % mod;}

template<typename T1, typename T2, typename T3>
T1 modpow(T1 _a, T2 p, T3 mod) {
    assert(p >= 0);
    ll ret = 1, a = _a;

    for(; p > 0; p /= 2) {
        if(p & 1) ret = mmul(ret, a, mod);
        a = mmul(a, a, mod);
    }

    return ret;
}

template<class T> inline T minv(T a, T mod) { return modpow(a, mod - 2, mod); }
template<class T> inline T mdiv(T a, T b, T mod) { return mmul(a, minv(b, mod), mod); }

/* misc functions */
template<class T> bool umin(T& cmin, T cur) { if(cur < cmin) return (cur - cmin, true); else return false; }
template<class T> bool umax(T& cmin, T cur) { if(cur > cmin) return (cur - cmin, true); else return false; }

/* constants */
constexpr int dx[] = {-1, 0, 1, 0, 1, 1, -1, -1};
constexpr int dy[] = {0, -1, 0, 1, 1, -1, 1, -1};
constexpr auto PI  = 3.14159265358979323846L;
constexpr auto oo  = numeric_limits<int>::max() / 2 - 2;
constexpr auto eps = 1e-6;
constexpr auto mod = 1000000007;

/* code */
constexpr int mx = -1;

void pre() {
}

void init() {
}

int main() {
    pre();
    int a, b;
    string s;
    ld d1, d2;

    in(a, b, s, d1, d2);
    int n, nums[10];
    in(n);
    fo(i, n) in(nums[i]);
    vi v(nums, nums + 10);
    unordered_set<pii> sets;
    sets.emplace(1, 2);

    trace(a, b, s, d1, d2, v, set<pii>(all(sets)));
    umin(a, 100);
    umin(a, madd(a, modpow(a, 100, mod), mod));

    outl("YES") << "OK\n";
    out(a);
    out(b, s);
    outl(d1, d2);
    fo(i, n) out(nums[i], " ");
    outl();

    return 0;
}
