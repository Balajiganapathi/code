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
using ld  = long double;

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
constexpr long double eps = 1e-7;
constexpr auto mod = 1000000007;

/* code */
constexpr int mx_n = 102;

ld mtime[mx_n];
int n, e[mx_n], s[mx_n];
ll d[mx_n][mx_n];

class State {
public:
    ld t;
    int ci, ch;

    State(ld _t, int _ci) {
        t = _t; ci = _ci;
    }

    bool operator <(const State &s) const {
        if(t != s.t) return t < s.t;
        if(ci != s.ci) return ci < s.ci;
        return false;

    }
};

ld solve(int u, int v) {
    fo(i, n) d[i][i] = 0;
    fo(k, n) fo(i, n) fo(j, n) {
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    }
    fo(i, n) mtime[i] = oo;
    set<State> pq;
    pq.emplace(0, u);
    mtime[u] = 0;

    while(!pq.empty()) {
        auto cur = *pq.begin(); pq.erase(pq.begin());
        int i = cur.ci;
        //trace(cur.ci, cur.t, mtime[i]);
        if(i == v) return cur.t;
        if(mtime[i] < cur.t - eps) continue;

        fo(nxt, n) if(d[i][nxt] <= e[i]) {
            ld ntime = cur.t + 1.0 * d[i][nxt] / s[i];
            if(ntime < mtime[nxt] - eps) {
                //trace(nxt, d[i][nxt], ntime, mtime[nxt]);
                mtime[nxt] = ntime;
                pq.emplace(ntime, nxt);
                //trace(pq.empty());
            }
        }
        //trace(si(pq));
    }

    assert(0);
    return -1;
}


int main() {
    int _t;
    cin >> _t;
    rep(kase, 1, _t) {
        int q;
        cin >> n >> q;
        fo(i, n) cin >> e[i] >> s[i];
        fo(i, n) fo(j, n) {
            cin >> d[i][j];
            if(d[i][j] == -1) d[i][j] = oo;
        }
        cout << "Case #" << kase << ":";
        while(q--) {
            int u, v;
            cin >> u >> v;
            --u; --v;
            cout.precision(10);
            cout << " " << fixed << solve(u, v);
        }
        cout << endl;
    }
    
    
	return 0;
}

