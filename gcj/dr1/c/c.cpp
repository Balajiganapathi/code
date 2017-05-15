/* string coder = "Balajiganapathi S"; // Never give up!  */

//#define LOCAL
#ifdef LOCAL
#   define TRACE
#   define TEST
#   include "todd_and_steven2.h"
#else
#   include "todd_and_steven.h"
#   define NDEBUG
//#   define FAST
#endif

#include<bits/stdc++.h>
#include<message.h>

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
constexpr auto eps = 1e-6;
constexpr auto mod = 1000000007;
constexpr int master = 0;

/* code */
constexpr int mx = -1;

int nodes, id;
int n0, n1, n;

int b1, b2, block;

tuple<int, int> calc(int i) {
    return mt(min(n, i * block), min(n, i * block + block));
}

void pre() {
    nodes = NumberOfNodes();
    id = MyNodeId();
    n0 = GetStevenLength();
    n1 = GetToddLength();
    n = n0 + n1;
    block = (n + nodes - 1) / nodes;
    tie(b1, b2) = calc(id);
}

bool ismaster() {
    return id == master;
}

ll odd(ll i1) {
    if(i1 >= n1) return oo;
    return GetToddValue(i1);
}


ll even(ll i0) {
    if(i0 >= n0) return oo;
    return GetStevenValue(i0);
}

int getLess0(ll x) {
    ll lo = 0, hi = n0;
    while(lo < hi) {
        trace(lo, hi);
        ll m = (lo + hi) / 2;
        if(even(m) >= x) hi = m;
        else lo = m + 1;
    }

    trace(x, lo);
    return lo;
}

int getLess1(ll x) {
    ll lo = 0, hi = n1;
    while(lo < hi) {
        trace(lo, hi);
        ll m = (lo + hi) / 2;
        trace(lo, hi, m, n1);
        if(odd(m) >= x) hi = m;
        else lo = m + 1;
    }

    trace(x, lo);
    return lo;
}

int getLess(ll x) {
    return getLess0(x) + getLess1(x);
}

tuple<int, int> getIth(int b) {
    ll lo = 0, hi = max(even(n0 - 1), odd(n1 - 1));
    while(lo < hi) {
        ll m = (lo + hi) / 2;
        trace(lo, hi, m, getLess(m));
        if(getLess(m) >= b) hi = m;
        else lo = m + 1;
    }
    trace(b, lo, getLess(lo));
    assert(getLess(lo) == b);
    return mt(getLess0(lo), getLess1(lo));
}

void proc() {
    if(b1 >= b2) {
        PutLL(master, 0);
        Send(master);
        return;
    }
    int i0, i1;
    ll c0, c1;
    trace(id, b1, b2);
    tie(i0, i1) = getIth(b1);
    c0 = even(i0);
    c1 = odd(i1);
    trace(b1, b2, i0, i1, c0, c1);
    

    ll ans = 0;
    re(i, b1, b2) {
        ll c;
        if(c0 < c1) {
            c = c0;
            ++i0;
            c0 = even(i0);
        } else {
            c = c1;
            ++i1;
            c1 = odd(i1);
        }
        trace(i, c);
        ans = (ans + (i ^ c)) % mod;
    }

    PutLL(master, ans);
    Send(master);
}

void collect() {
    ll ans = 0;
    fo(i, nodes) {
        Receive(i);
        ans += GetLL(i);
        ans %= mod;
    }

    cout << ans << endl;
}

int main() {
    pre();
    proc();
    if(ismaster()) collect();
    
    
	return 0;
}
