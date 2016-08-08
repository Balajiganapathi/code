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
constexpr auto oo  = numeric_limits<ll>::max() / 2 - 2;
constexpr auto eps = 1e-6;
constexpr auto mod = 1000000007;

/* code */
constexpr int mx_n = 5003;

int a[mx_n], b[mx_n], c[mx_n], d[mx_n], n, s, e;
int x[mx_n];
ll dp[mx_n][3][3];

ll solve(int idx, int right_launcher, int right_lander) {
    if(idx == n) {
        return (right_launcher + right_lander == 0)? 0: oo;
    }
    ll &ret = dp[idx][right_launcher][right_lander];
    if(ret != -1) return ret;

    ret = oo;
    int nxt_launcher = 0, nxt_lander = 0;

    // i -> launcher, j -> lander
    // i = 0 -> launch left
    // i = 1 -> launch right
    // j = 0 -> land from left
    // j = 1 -> land from right

    ll costi = 0, costj = 0;
    fo(i, 3) {
        if((i == 2) ^ (idx == e)) continue;
        int lander_allowed = 1;
        int nxt_launcher = 0;

        if(i == 0) {
            if(right_lander == 0) continue;
            else lander_allowed = 0;
            costi = c[idx];
        } else if(i == 1) {
            nxt_launcher = 1;
            costi = d[idx];
        } else {
            costi = 0;
        }

        fo(j, 3) {
            if((j == 2) ^ (idx == s)) continue;
            int launcher_allowed = 1;
            int nxt_lander = 0;
            if(j == 0) {
                if(right_launcher == 0) continue;
                else launcher_allowed = 0;
                costj = a[idx];
            } else if(j == 1) {
                nxt_lander = 1;
                costj = b[idx];
            } else {
                costj = 0;
            }

            nxt_lander += ((right_lander>0) && lander_allowed);
            nxt_launcher += ((right_launcher>0) && launcher_allowed);


            ll cost = costi + costj;
            if(idx + 1 < n) cost += 1ll * (nxt_launcher + nxt_lander) * (x[idx+1] - x[idx]);
            ll tmp = cost + solve(idx + 1, nxt_launcher, nxt_lander);
            trace(idx, right_launcher, right_lander, i, j, costi, costj, cost);
            trace(nxt_launcher, nxt_lander, tmp);
            ret = min(ret, tmp);
        }
    }

    trace(idx, right_launcher, right_lander, ret);

    
    return ret;
}

int main() {
    scanf("%d %d %d", &n, &s, &e); --s; --e;
    fo(i, n) scanf("%d", x + i);
    fo(i, n) scanf("%d", a + i);
    fo(i, n) scanf("%d", b + i);
    fo(i, n) scanf("%d", c + i);
    fo(i, n) scanf("%d", d + i);

    ini(dp, -1);
    cout << solve(0, 0, 0) << endl;
    
	return 0;
}

