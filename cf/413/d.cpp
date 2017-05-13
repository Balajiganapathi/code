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
constexpr int mx_n = 100005;
int n, e[mx_n];
int a, b, h, w;

pi ok[2][(1 << 20) + 100];

int tryIt(int cnt, int x, int y) {
    trace(cnt, x, y);
    int nn = n;
    if(cnt <= 1) {
        fo(mask, (1 << cnt)) {
            int cx = (x + w - 1) / w, cy = (y + h - 1) / h;
            fo(i, cnt) {
                if(is1(mask, i)) cx = (cx + e[i] - 1) / e[i];
                else cy = (cy + e[i] - 1) / e[i];
            }

            trace(mask, cx, cy);
            if(cx == 1 && cy == 1) return cnt;
        }

        return oo;
    }

    int n[2];
    n[0] = cnt / 2;
    n[1] = cnt - n[0];
    int add[] = {0, n[0]};

    trace(cnt, n[0], n[1]);
    fo(i, 2) {
        fo(mask, (1 << n[i])) {
            int mx = 1, my = 1;
            fo(j, n[i]) {
                if(is1(mask, j)) mx = min(1ll * oo, 1ll * mx * e[j + add[i]]);
                else my = min(1ll * oo, 1ll * my * e[j + add[i]]);
            }
            ok[i][mask] = mp(mx, my);
            trace(i, mask, ok[i][mask]);
        }
        sort(ok[i], ok[i] + (1 << n[i]));
    }

    fo(i, (1 << n[0])) {
        int cx = (x + ok[0][i].fi - 1) / ok[0][i].fi;
        int cy = (y + ok[0][i].se - 1) / ok[0][i].se;
        int nx = (cx + w - 1) / w;
        int ny = (cy + h - 1) / h;
        int idx = lower_bound(ok[1], ok[1] + (1 << n[1]), mp(nx, -oo)) - ok[1];
        trace(i, cx, cy, nx, ny, idx, ok[1][idx].se);
        if(idx < (1 << n[1]) && ny <= ok[1][idx].se) return cnt;
    }

    return oo;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> a >> b >> h >> w >> n;
    fo(i, n) cin >> e[i];
    sort(e, e + n);
    reverse(e, e + n);

    int ans = oo;
    rep(cnt, 0, min(n, 2 * 18 + 1)) {
        ans = min(ans, min(tryIt(cnt, a, b), tryIt(cnt, b, a)));
    }
    if(ans >= oo) ans = -1;

    cout << ans << endl;

	return 0;
}

