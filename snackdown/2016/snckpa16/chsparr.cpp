/* string coder = "Balajiganapathi S"; // Never give up!  */

//#define LOCAL
#ifdef LOCAL
#   define TRACE
//#   define TEST
#   define SPEED
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

/*-------------------------------------------------------------------------------------------------------------------------------------*/
/*<modint>*/
// ASUMES mod is PRIME
template<int mod>
class modint {
    static_assert(mod > 0, "mod must be a positive value");
    static_assert(1ll * (mod - 1) + (mod - 1) == (mod - 1) + (mod - 1), "addition of 2 modints must fit in int");

private:
    int val;

public:
    constexpr modint(): val(0) { }

    modint(const int &_val): val(_val) {
        if(val < 0) {
            val %= mod;
            if(val < 0) val += mod;
        } else if(val >= mod) {
            val %= mod;
        }
    }

    modint(const modint<mod> &m): val(m.val) { }

    modint<mod> operator +(modint<mod> m) const {
        modint<mod> ret;
        ret.val = val + m.val;
        if(ret.val >= mod) ret.val -= mod;

        return ret;
    }

    modint<mod> operator *(modint<mod> m) const { 
        modint<mod> ret;
        ret.val = 1ll * val * m.val % mod;

        return ret;
    }

    modint<mod> operator -(modint<mod> m) const { return *this + m.negate(); }
    modint<mod> operator /(modint<mod> m) const { return *this * m.inverse(); }

    bool operator ==(modint<mod> m) const { return val == m.val; }
    bool operator !=(modint<mod> m) const { return val != m.val; }
    bool operator <(modint<mod> m) const { return val < m.val; }
    bool operator >(modint<mod> m) const { return val > m.val; }

    modint<mod> negate() const { return modint<mod>(-val); }

    modint<mod> inverse() const {
        assert(__gcd(val, mod) == 1);
        return pow(mod - 2);
    }

    template<typename T> // to support both int and ll
    modint<mod> pow(T p) const {
        modint<mod> ret(1), cur(*this);
        for(; p; p /= 2) {
            if(p & 1) ret = ret * cur;
            cur = cur * cur;
        }

        return ret;
    }

    int value() const { return val; }
};

template<int mod>
ostream& operator <<(ostream& os, const modint<mod> m) { // print a modint
    return os << m.value();
}

template<int mod>
istream& operator >>(istream& is, volatile modint<mod> &m) { // input a modint
    int x;
    is >> x;
    m = modint<mod>(x);
    return is;
}
/*</modint>*/
/*-------------------------------------------------------------------------------------------------------------------------------------*/



/* code */
constexpr int mx_n = 100005;
int n, a[mx_n];
int m;
ll x, y;

ll randll() {
    return 1ll * rand() * rand();
}

modint<mod> getAt(ll a, ll b, ll idx, int m) {
    modint<mod> ret;
    if(m == 0) {
        return a;
    } else {
        if(is1(idx, m - 1)) ret = getAt(a + b, b, idx - (1ll << (m-1)), m - 1);
        else ret = getAt(a, a + b, idx, m - 1);
    }

    //trace(a, b, idx, m, ret);
    return ret;
}

modint<mod> getAt(ll i, int m) {
    if(m == 0) {
        return a[i];
    }
    ll ri = (i >> m);
    ll idx = i - (ri << m);
    auto ret = getAt(a[ri], a[ri+1], idx, m);
    //trace(i, m, ret);

    return ret;
}

modint<mod> get(ll x, int m) {
    if(m == 0) {
        modint<mod> ret = 0;
        rep(i, 0, x) ret = ret + a[i];
        //trace(x, m, ret);
        return ret;
    }

    auto ret = get(x / 2, m - 1) * 3 - getAt(0, m - 1);
    //trace(x, m, 1, ret);
    if(x % 2 == 0) {
        auto sub = getAt(x / 2, m - 1);
        ret = ret - sub;
        //trace(x, m, x % 2, sub, ret);
    } else {
        auto add = getAt(x / 2 + 1, m - 1);
        ret = ret + add;
        //trace(x, m, x % 2, add, ret);
    }

    //trace(x, m, ret);

    return ret;
}

modint<mod> get(ll x, ll y, int m) {
    auto ret = get(y, m);
    if(x) ret = ret - get(x - 1, m);

    return ret;
}

int brute();
int solve() {
    return get(x, y, m).value();
}

int brute() {
    vi cur;
    fo(i, n) cur.push_back(a[i]);

    fo(k, m) {
        vi nxt;
        nxt.push_back(cur[0]);
        re(i, 1, si(cur)) {
            nxt.push_back((cur[i-1] + cur[i]) % mod);
            nxt.push_back(cur[i]);
        }
        cur = nxt;
    }

    int ret = 0;
    rep(i, x, y) {
        ret += cur[i];
        if(ret >= mod) ret -= mod;
        //auto tmp = getAt(i, m);
        //trace(i, tmp, cur[i]);
        //assert(tmp.value() == cur[i]);
    }

    return ret;
}

int main() {
    int t;
#ifdef SPEED
    t = 10;
#else
    cin >> t;
#endif
    while(t--) {
#ifdef SPEED
        n = 100000, m = 30;
        ll len = n;
        fo(k, m) len = 2 * len - 1;
        trace(len);
        x = randll() % len + 1;
        y = randll() % len + 1;
        if(x > y) swap(x, y);
        fo(i, n) a[i] = rand() % 1000 + 1;
        //vi inp(a, a + n);
        //trace(inp);
#else
        cin >> n >> m >> x >> y;
        fo(i, n) cin >> a[i];
#endif
        a[n] = 0;
        --x; --y;
        int ans = solve();
        cout << ans << endl;
#ifdef TEST
        int bans = brute();
        if(bans != ans) {
            trace(n, m, x, y, ans, bans);
            assert(ans == bans);
        }
#endif
    }
    
    
	return 0;
}

