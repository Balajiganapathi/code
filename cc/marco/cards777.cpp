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
constexpr int mx = -1;

map<tuple<int, int, int>, double> cache;


double solve(int cr, int cb, int tr) {
    if(cr + cb == 0) return 0;
    if(cr < cb) {
        swap(cr, cb);
        tr = cr + cb - tr;
        return solve(cr, cb, tr);
    }

    int tb = cr + cb - tr;
    if(cr == 0) return tb;
    if(cb == 0) return tr;
    if(tr == 0) return cb;
    if(tb == 0) return cr;
    if(cr == cb) return cr;
    if(tr == tb) return tr;

    auto idx = mt(cr, cb, tr);
    auto it = cache.find(idx);
    if(it != cache.end()) return it->se;

    double &ret = cache[idx];
    ret = 0;

    double pr = 1.0 * cr / (cr + cb);
    double cur;
    if(tr > 0) {
        cur = pr * (1.0 + solve(cr - 1, cb, tr - 1));
        cur += (1 - pr) * solve(cr, cb - 1, tr - 1);
        ret = max(ret, cur);
    } else {
        cur = pr * solve(cr - 1, cb, tr);
        cur += (1 - pr) * (1.0 + solve(cr, cb - 1, tr));
        ret = max(ret, cur);
    }

    return ret;
}

double get(int cr, int cb, int tr) {
    if(cr == cb) return cr;
    int tb = cr + cb - tr;
    if(cr < cb) {
        swap(cr, cb);
        swap(tr, tb);
    }
    int nxt = min(cr - cb, tr);
    int posB = min(nxt, cb);

    double ret = 0;
    double prob = 1;
    fo(i, nxt) prob *= 1.0 * (cr - i) / (cr + cb - i);
    trace(cr, cb, tr);
    int lr = cr - nxt + 1;
    trace(nxt, posB, prob, lr);
    double cnt = 1;
    rep(nb, 0, posB) {
        int nr = nxt - nb;
        trace(nb, nr, cnt, prob, solve(cr - nr, cb - nb, tr - nxt));
        ret += cnt * prob * (nr + solve(cr - nr, cb - nb, tr - nxt));
        prob *= 1.0 * (cb - nb) / lr;
        cnt *= 1.0 * (nxt - nb) / (nb + 1);
        ++lr;
    }


    return ret;
}

int main() {
    int r, p, b;
    int t;
    cin >> t;
    while(t--) {
        cin >> r >> b >> p;
        printf("%.09lf\n", get(r, b, p));
    }
    
    
	return 0;
}

