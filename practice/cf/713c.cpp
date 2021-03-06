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
ostream &operator <<(ostream &o, multiset<T> s) { // print a set
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
constexpr int mx_n = 3003;

// N -> tot()
template<typename T>
class DynamicMedian {
public:
    multiset<T> small, large;
    ll small_sum, large_sum;
    int tot() { // O(1)
        return si(small) + si(large);
    }

    ll sum() {
        return small_sum + large_sum;
    }

    DynamicMedian() {
        init();
    }

    void init() { // O(N)
        small.clear();
        large.clear();
        small_sum = large_sum = 0;
    }

    T median() { // O(1)
        assert(tot() > 0);
        return *large.begin();
    }

    T maxElement()  { // O(1)
        assert(tot() > 0);
        return *large.rbegin();
    }

    T minElement() { // O(1)
        assert(tot() > 0);
        if(!small.empty()) return *small.begin();
        else return *large.begin();
    }

    void add(T x) { // O(lg N)
        if(tot() == 0 || x < median()) {
            small_sum += x;
            small.insert(x);
        } else {
            large_sum += x;
            large.insert(x);
        }
        reorder();
    }

    void remove(const T& x) { // O(lg N)
        if(x < median()) {
            assert(small.find(x) != small.end());
            small.erase(small.find(x));
            small_sum -= x;
        } else {
            assert(large.find(x) != large.end());
            large.erase(large.find(x));
            large_sum -= x;
        }
        reorder();
    }

    void reorder() { // O(lg N)
        while(si(large) < si(small)) {
            T x = *small.rbegin();
            small_sum -= x; large_sum += x;
            large.insert(x);
            small.erase(small.find(x));
        }

        while(si(large) > si(small) + 1) {
            T x = *large.begin();
            small_sum += x; large_sum -= x;
            small.insert(x);
            large.erase(large.begin());
        }
    }
};

int n;
ll a[mx_n], eq[mx_n][mx_n], dp[mx_n], big[mx_n][mx_n], sm[mx_n][mx_n];
ll bdp[mx_n];

int main() {
    cin >> n;
    rep(i, 1, n) cin >> a[i];

    rep(i, 1, n) {
        DynamicMedian<int> dm;
        ll sum = 0;
        rep(j, i, n) {
            int x = a[j] - (j - i);
            dm.add(x);
            sum += x;
            int m = dm.median();
            eq[i][j] = 1ll * si(dm.small) * m - dm.small_sum + dm.large_sum - 1ll * si(dm.large) * m;
            sm[i][j] = dm.median();
            big[i][j] = sm[i][j] + (j-i);
            trace(i, j, m, eq[i][j], sm[i][j], big[i][j]);
        }
    }

    dp[0] = 0;
    eq[0][0] = 0;
    bdp[0] = -oo;
    rep(i, 1, n) {
        dp[i] = oo;
        for(int j = i - 1; j >= 0; --j) if(bdp[j] < sm[j+1][i]) {
            ll cur = dp[j] + eq[j+1][i];
            if(cur < dp[i]) {
                dp[i] = cur;
                bdp[i] = sm[j+1][i] + (i - j - 1);
            }
        }
        trace(i, dp[i], bdp[i]);
    }

    cout << dp[n] << endl;

    
    
	return 0;
}

