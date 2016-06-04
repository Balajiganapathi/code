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
constexpr int mx_n = 102;
constexpr int mx_k = 100005;

vi solve(int k) {
    vi dig;
    int base = 6;
    for(; k; k /= base) dig.push_back(k % base);
    reverse(all(dig));

    vi ret = {};
    fo(l, dig[0]) ret.push_back(dig[0] - l);
    re(i, 1, si(dig)) {
        int x = si(ret);
        int lis = i + 1;
        fo(j, base) ret.push_back(x + base - j);
        fo(l, dig[i]) {
            int x = si(ret);
            fo(m, lis) ret.insert(ret.begin(), x + lis - m);
        }
    }

    return ret;
}

tuple<vi, int> memo[mx_k];

tuple<vi, int> sol(int k) {
    if(k == 1) return mt(vi{1}, 1);
    tuple<vi, int> &ret = memo[k];
    if(gt(ret, 1) != 0) return ret;

    for(int i = 2; i <= 10 && i <= k; ++i) {
        vi v;
        int lis;
        tie(v, lis) = sol(k / i);
        int rem = k % i;
        ++lis;
        int len = si(v) + i;
        len += rem * lis;
        if(gt(ret, 1) == 0 || len < si(gt(ret, 0)) || (len == si(gt(ret, 0)) && lis < gt(ret, 1))) {
            vi nw = v;
            int x = si(nw);
            fo(j, i) nw.push_back(x + i - j);
            fo(l, rem) {
                int x = si(nw);
                fo(m, lis) nw.insert(nw.begin(), x + lis - m);
            }
            ret = mt(nw, lis);
            assert(si(nw) == len);
        }
    }
    
    return ret;
}

int main() {
    int t;
#ifdef TEST
    t = 100000;
    int _k = 1;
#else
    scanf("%d", &t);
#endif

    while(t--) {
        int k;
#ifdef TEST
        k = _k++;
#else
        scanf("%d", &k);
#endif
        vi ans = gt(sol(k), 0);

        cout << si(ans) << endl;
        fo(i, si(ans)) cout << ans[i] << " ";
        cout << endl;

#ifdef TEST
        pi dp[mx_n];
        assert(1 <= si(ans) && si(ans) <= 100);
        if(k <= 100) {
            dp[0] = {1, 1};
            int lis = 1;
            re(i, 1, si(ans)) {
                dp[i] = {1, 1};
                fo(j, i) if(ans[i] > ans[j]) {
                    int x = dp[j].fi + 1;
                    if(x == dp[i].fi) dp[i].se += dp[j].se;
                    else if(x > dp[i].fi) dp[i] = mp(dp[j].fi + 1, dp[j].se);
                }
                lis = max(lis, dp[i].fi);
            }
            int cnt = 0;
            fo(i, si(ans)) if(dp[i].fi == lis) cnt += dp[i].se;
            trace(cnt, k);
            assert(cnt == k);
        }
        trace(k);
#endif
    }
    
    
	return 0;
}

