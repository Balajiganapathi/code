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
constexpr int mx_n = 16;
int n;
int dp[(1 << mx_n)][256];
int vis[(1 << mx_n)][256], mark;
char col[mx_n];
int r[mx_n], b[mx_n];
int order;
int rcnt[mx_n], bcnt[mx_n];
vi red, blue;

int get_rem(int rrem, int brem) {
    if(rrem <= 0 && brem <= 0) return 0;
    if(rrem > 0) return 2 * rrem;
    else 2 * brem + 1;
}

int solve(int mask, int rem) {
    if(mask == (1 << n) - 1) return 0;
    int &ans = dp[mask][rem];
    if(vis[mask][rem] == mark) return ans;
    vis[mask][rem] = mark;
    ans = 0;
    int idx = __builtin_popcount(mask);
    int brem = 0, rrem = 0;

    if(rem & 1) brem = rem / 2;
    else rrem = rem / 2;

    const vi &loop = (is1(order, idx)? blue: red);
    for(const int nxt: loop) if(!is1(mask, nxt)) {
        int nmask = mask | (1 << nxt);
        int save = max(r[nxt], b[nxt]) - max(max(r[nxt] - rrem - rcnt[idx], 0), max(b[nxt] - brem - bcnt[idx], 0));
        ans = max(ans, save + solve(nmask, get_rem(rrem - max(0, (save - rcnt[idx])), brem - max(0, (save - bcnt[idx])))));
    }

    trace(mask, rem, ans);
    return ans;
}

int solve() {
    int rr = 0, bb = 0;
    fo(i, n) {
        if(is1(order, i)) ++bb;
        else ++rr;
        rcnt[i] = rr; bcnt[i] = bb;
    }
    int sr = accumulate(r, r + n, 0), sb = accumulate(b, b + n, 0);
    ++mark;
    int saved = solve(0, 0);
    trace(order, sr, sb, saved, max(sr, sb) - saved);
    return max(sr, sb) - saved + n;
}

int main() {
    cin >> n;
    fo(i, n) {
        cin >> col[i] >> r[i] >> b[i];
        if(col[i] == 'R') red.push_back(i);
        else blue.push_back(i);
    }

    int ans = oo;
    fo(_order, (1 << n)) if(__builtin_popcount(_order) == si(blue)) {
        order = _order;
        ans = min(ans, solve());
    }

    cout << ans << endl;
    
	return 0;
}

