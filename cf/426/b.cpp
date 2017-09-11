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
constexpr int mx_n = 35003, mx_k = 55;
constexpr int mx_seg = 4 * mx_n;
int n, k, num[mx_n];

int dp[mx_n][mx_k];
int last[mx_n];
int seg[mx_seg], acc[mx_seg];

void init(int i, int a, int b, int k) {
    acc[i] = 0;
    if(a == b) {
        seg[i] = dp[a][k];
        return;
    }
    int m = (a + b) / 2;
    int l = 2 * i + 1, r = 2 * i + 2;
    init(l, a, m, k);
    init(r, m + 1, b, k);
    seg[i] = max(seg[l], seg[r]);
}

void update(int i, int a, int b, int qa, int qb) {
    if(b < qa || a > qb) return;
    if(qa <= a && b <= qb) {
        ++acc[i];
        ++seg[i];
        return;
    }

    int m = (a + b) / 2;
    int l = 2 * i + 1, r = 2 * i + 2;

    if(acc[i]) {
        acc[l] += acc[i]; seg[l] += acc[i];
        acc[r] += acc[i]; seg[r] += acc[i];
        acc[i] = 0;
    }

    update(l, a, m, qa, qb);
    update(r, m + 1, b, qa, qb);
    seg[i] = max(seg[l], seg[r]);
}

int get(int i, int a, int b, int qa, int qb) {
    if(b < qa || a > qb) return -oo;
    if(qa <= a && b <= qb) return seg[i];
    int m = (a + b) / 2;
    int l = 2 * i + 1, r = 2 * i + 2;

    if(acc[i]) {
        acc[l] += acc[i]; seg[l] += acc[i];
        acc[r] += acc[i]; seg[r] += acc[i];
        acc[i] = 0;
    }

    return max(get(l, a, m, qa, qb), get(r, m + 1, b, qa, qb));
}

int main() {
    cin >> n >> k;
    rep(i, 1, n) cin >> num[i];

    rep(i, 1, n) dp[0][i] = -oo;
    dp[0][0] = 0;

    rep(ki, 1, k) {
        init(0, 0, n, ki-1);
        ini(last, 0);
        dp[0][ki] = -oo;
        rep(i, 1, n) {
            dp[i][ki] = -oo;
            int l = last[num[i]];
            update(0, 0, n, l, i - 1);
            dp[i][ki] = get(0, 0, n, 0, i - 1);
            trace(ki, i, num[i], l, dp[i][ki]);
            if(dp[i][ki] < 0) dp[i][ki] = -oo;
            last[num[i]] = i;
        }
    }

    
    cout << dp[n][k] << endl;
    
	return 0;
}

