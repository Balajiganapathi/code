/* string coder = "Balajiganapathi S"; // Never give up!  */

//#define LOCAL
#ifdef LOCAL
//#   define TRACE
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
constexpr int mx_n = 200005;
constexpr int mx_seg = 4 * mx_n + mx_n * 20;

int seg[mx_seg], sl[mx_seg], sr[mx_seg], scnt;

int init(int l, int r) {
    int idx = scnt++;
    if(l == r) {
        seg[idx] = 0;
        return idx;
    }
    int m = (l + r) / 2;
    sl[idx] = init(l, m);
    sr[idx] = init(m+1, r);
    return idx;
}

int add(int pidx, int l, int r, int q) {
    int idx = scnt++;
    assert(idx < mx_seg);
    if(l == r) {
        seg[idx] = 1;
        return idx;
    }
    int m = (l + r) / 2;
    sl[idx] = sl[pidx]; sr[idx] = sr[pidx];
    if(q <= m) sl[idx] = add(sl[pidx], l, m, q);
    else sr[idx] = add(sr[pidx], m+1, r, q);
    seg[idx] = seg[sl[idx]] + seg[sr[idx]];

    return idx;
}

int get(int idx, int l, int r, int ql, int qr) {
    if(r < ql || l > qr) return 0;
    if(ql <= l && r <= qr) return seg[idx];
    int m = (l+r) / 2;
    return get(sl[idx], l, m, ql, qr) + get(sr[idx], m+1, r, ql, qr);
}

int n, q;
int col[mx_n], persistent[mx_n];

ll bget(int x1, int y1, int x2, int y2) {
    int cnt = 0;
    rep(i, x1, x2) if(y1 <= col[i] && col[i] <= y2) ++cnt;
    ll ans =  1ll * cnt * (cnt - 1) / 2;
    trace(x1, y1, x2, y2, ans);
    return ans;
}

ll get(int x1, int y1, int x2, int y2) {
    if(y1 < 1) ++y1;
    if(y2 > n) --y2;
    if(x1 < 1) ++x1;
    if(x2 > n) --x2;
    if(x1 > x2 || y1 > y2) return 0;
    trace(x2, persistent[x2], get(persistent[x2], 1, n, y1, y2));
    trace(x1, persistent[x1-1], get(persistent[x1-1], 1, n, y1, y2));
    int cnt = get(persistent[x2], 1, n, y1, y2) - get(persistent[x1-1], 1, n, y1, y2);
    ll ans = 1ll * cnt * (cnt - 1) / 2;
#ifdef TEST
    int bans = bget(x1, y1, x2, y2);
    trace(x1, y1, x2, y2, cnt, ans, bans);
    assert(ans == bans);
#endif
    return ans;
}

ll solve(int l, int d, int r, int u) {
    ll tot = 1ll * n * (n - 1) / 2;
    ll outside = get(1, 1, d-1, n) + get(u+1, 1, n, n) + get(1, 1, l-1, n) + get(r+1, 1, n, n);
    outside -= get(1, 1, l - 1, d - 1) + get(1, u+1, l-1, n) + get(r+1, 1, n, d-1) + get(r+1, u+1, n, n);

    return tot - outside;
}

ll brute(int l, int d, int r, int u) {
    ll tot = 1ll * n * (n - 1) / 2;
    ll outside = bget(1, 1, d-1, n) + bget(u+1, 1, n, n) + bget(1, 1, l-1, n) + bget(r+1, 1, n, n);
    outside -= bget(1, 1, l - 1, d - 1) + bget(1, u+1, l-1, n) + bget(r+1, 1, n, d-1) + bget(r+1, u+1, n, n);

    return tot - outside;
}

void pre() {
    persistent[0] = init(1, n);
    rep(i, 1, n) {
        persistent[i] = add(persistent[i-1], 1, n, col[i]);
        trace(i, persistent[i]);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> q;
    ini(col, -1);
    rep(i, 1, n) {
        cin >> col[i];
    }
    pre();

    while(q--) {
        int l, d, r, u;
        cin >> l >> d >> r >> u;
        ll ans = solve(l, d, r, u);
#ifdef TEST
        ll bans = brute(l, d, r, u);
        trace(ans, bans);
        assert(bans == ans);
#endif
        cout << ans << endl;
    }
    
    
	return 0;
}

