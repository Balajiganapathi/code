/* string coder = "Balajiganapathi S"; // Never give up!  */

//#define LOCAL
#ifdef LOCAL
#   define TRACE
#   define TEST
#   define CHECK
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
constexpr int mx_n = 200005;
int n, m;
ll a[mx_n],  at[mx_n], in[mx_n];
int par[mx_n], skip[mx_n];


void init() {
    rep(i, 1, n) {
        par[i] = skip[i] = i;
    }
}

int find(int x) {
    if(par[x] == x) return x;
    return par[x] = find(par[x]);
}

void merge(int x, int y) {
    x = find(x); y = find(y);
    int mxy = max(skip[x], skip[y]);
    if(rand() % 2) {
        par[x] = y;
        skip[y] = mxy;
    } else {
        par[y] = x;
        skip[x] = mxy;
    }
}

ll brute(int k) {
    ll overflow = 0;
    ll cur = 0;
    rep(i, 1, k) {
        ll in = at[i] + overflow;
        cur = min(in, a[i]);
        overflow = in - cur;
        trace(i, at[i], a[i], in, cur, overflow);
    }

    return cur;
}

void put(int i, ll x) {
    while(x > 0 && i <= n) {
        trace(i, x, in[i], a[i], find(i), skip[find(i)]);
        if(in[i] == a[i]) {
            i = skip[find(i)] + 1;
            continue;
        }
        if(in[i] + x < a[i]) {
            in[i] += x;
            x = 0;
            continue;
        }
        int req = min(a[i] - in[i], x);
        in[i] += req;
        assert(in[i] == a[i]);

        if(i + 1 <= n && a[i+1] == in[i+1]) {
            merge(i, i + 1);
        }
        if(i - 1 >= 1 && a[i-1] == in[i-1]) {
            merge(i - 1, i);
        }

        x -= req;
        ++i;
    }
}

int main() {
#ifndef TEST
    cin >> n;
    rep(i, 1, n) {
        cin >> a[i];
    }
#else
    n = 10;
    rep(i, 1, n) a[i] = rand() % 10 + 1;
#endif
    
    init();
#ifndef TEST
    cin >> m;
#else
    m = 1000;
#endif

    while(m--) {
        int t;
#ifndef TEST
        cin >> t;
#else
        t = rand() % 2 + 1;
#endif
        if(t == 1) {
            int p, x;
#ifndef TEST
            cin >> p >> x;
#else
            p = rand() % n + 1;
            x = rand() % 10 + 1;
#endif
            trace(p, x);
            at[p] += x;
            put(p, x);
        } else {
            int k;
#ifndef TEST
            cin >> k;
#else
            k = rand() % n + 1;
#endif
            trace(k);
            ll ans = in[k];
#ifdef CHECK
            ll bans = brute(k);
            if(bans != ans) {
                trace(k,  bans, ans);
                assert(bans == ans);
            }
#endif
            cout << ans << '\n';
        }
    }
    
    
	return 0;
}

