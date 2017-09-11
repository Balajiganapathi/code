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
constexpr int mx_n = 102;
int n, a[mx_n];
ll k;

int brute() {
    int ans = 0;
    rep(d, 1, 1000000) {
        ll cur = 0;
        fo(i, n) {
            cur += (d - a[i] % d) % d;
        }
        //trace(d, cur, cur <= k);
        if(cur <= k) ans = d;
    }

    return ans;
}

ll csum[mx_n];
ll calc(ll d) {
    if(d > a[n-1]) return (d * n - csum[n-1]);
    ll ans = 0;
    for(int i = n - 1; i >= 0; --i) {
        ans += (d - a[i] % d) % d;
    }
    return ans;
}

int main() {
#ifdef TEST
    n = 100; k = 1000000;
    n = 1; k = 100000000000L;
    fo(i, n) {
        //int x = 1000000000, y = 900000000;
        int x = 100, y = 90;
        a[i] = rand() % (y-x+1) + x;
    }
#else
    cin >> n >> k;
    fo(i, n) {
        cin >> a[i];
    }
#endif
    
    /*
    rep(x, 1, 100) {
        rep(i, 1, x+1) {
            cout << (x % i) << " ";
        }
        cout << endl;
    }
    */

    sort(a, a + n);
    fo(i, n) {
        csum[i] = (i == 0? 0: csum[i-1]) + a[i];
    }
    ll ans = 1;
    vi trials;
    fo(i, n) {
        for(int d = 1; (d-1) * (d-1) <= a[i]; ++d) {
            trials.push_back(a[i] / d + 1);
        }
    }

    for(int d = 1; (d-1) * (d-1) <= a[n-1]; ++d) trials.push_back(d);

    sort(all(trials));
    trials.resize(unique(all(trials)) - trials.begin());
    reverse(all(trials));
    trace(si(trials));
    //trace(t);

    ll lo = 1;
    ll hi = 2 * (k + a[n-1]);
    for(int d: trials) {
        lo = d;
        if(calc(d) <= k) break;
        hi = d;
    }


    trace(lo, hi);
#ifdef LOCAL
    /*
    ll lst = calc(lo);
    rep(ch, lo, hi) {
        ll cur = calc(ch);
        assert(lst <= cur);
        lst = cur;
    }
    */
#endif

    while(lo < hi) {
        ll m = (lo + hi + 1) / 2;
        if(calc(m) <= k) lo = m;
        else hi = m - 1;
    }
    trace(lo, calc(lo), k);
    
    if(calc(lo) <= k) ans = max(ans, lo);

    assert(calc(ans) <= k);
    cout << ans << endl;
#ifdef LOCAL
    int bans = brute();
    trace(bans, calc(bans), calc(bans + 1));
#endif
    
	return 0;
}

