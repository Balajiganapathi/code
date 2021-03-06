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
constexpr int mx_mask = (1 << 2), mx_dist = 45;

int dp[mx_dist][mx_dist][mx_dist][mx_mask][mx_mask][mx_mask];
int d[3], md[3], td[3];

int solve(int d1, int d2, int d3, int m1, int m2, int m3) {
    assert(max(d1, max(d2, d3)) < mx_dist);
    int &ret = dp[d1+2][d2+2][d3+2][m1][m2][m3];
    if(ret != -1) return ret;
    if(d1 == d2 || d2 == d3 || d1 == d3) return ret = -oo;
    int d[] = {d1, d2, d3};
    int m[] = {m1, m2, m3};
    int holding[3] = {-1, -1, -1};
    int held[3] = {-1, -1, -1};

    fo(i, 3) if(d[i] <= 0) {
        held[i] = abs(d[i]);
        holding[held[i]] = i;
    }

    fo(j, 3) {
        fo(i, 3) if(held[i] != -1 && d[held[i]] >= 1) {
            d[i] = d[held[i]];
        }
    }
    fo(i, 3) assert(d[i] > 0);


    ret = max(d[0], max(d[1], d[2]));

    // Move
    fo(i, 3) if(!is1(m[i], 0) && holding[i] == -1 && held[i] == -1) {
        m[i] ^= 1;
        int nd[] = {d1, d2, d3};
        rep(dd, max(1, d[i] - md[i]), d[i] + md[i]) {
            nd[i] = dd;
            ret = max(ret, solve(nd[0], nd[1], nd[2], m[0], m[1], m[2]));
        }
        m[i] ^= 1;
    }

    // i lifts j
    fo(i, 3) if(!is1(m[i], 1) && holding[i] == -1 && held[i] == -1) fo(j, 3) if(i != j && held[j] == -1 && abs(d[i] - d[j]) <= 1) {
        m[i] ^= 2;
        int nd[] = {d1, d2, d3};
        nd[j] = -i;
        ret = max(ret, solve(nd[0], nd[1], nd[2], m[0], m[1], m[2]));
        m[i] ^= 2;
    }

    // i throws j
    fo(i, 3) if(holding[i] != -1) {
        int nd[] = {d1, d2, d3};
        rep(dd, max(1, d[i] - td[i]), d[i] + td[i]) {
            nd[holding[i]] = dd;
            ret = max(ret, solve(nd[0], nd[1], nd[2], m[0], m[1], m[2]));
        }
    }

    trace(d1, d2, d3, m1, m2, m3, ret);
    return ret;
}

int main() {
    fo(i, 3) cin >> d[i] >> md[i] >> td[i];
    ini(dp, -1);

    int ans = solve(d[0], d[1], d[2], 0, 0, 0);
    cout << ans << endl;
	return 0;
}

