/* string coder = "Balajiganapathi S"; // Never give up!  */

//#define LOCAL
#ifdef LOCAL
#   define TRACE
#   define TEST
//#   define CHECK
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
constexpr int mx_d = 10, mx_c = 20;
int a[mx_d];
int num[mx_c], dcnt;

ll C[mx_c][mx_c], rp[mx_d][mx_c];
ll fact[mx_c];

void pre() {
    fact[0] = 1;
    re(i, 1, mx_c) fact[i] = fact[i-1] * i;
    fo(i, mx_c) {
        C[i][0] = C[i][i] = 1;
        rep(j, 1, i - 1) C[i][j] = C[i-1][j-1] + C[i-1][j];
    }

    fo(i, mx_d) {
        rp[i][0] = 1;
        re(j, 1, mx_c) rp[i][j] = rp[i][j-1] * i;
    }
}

bool isok(ll n) {
    static int cnt[10];
    ini(cnt, 0);
    for(ll m = n; m > 0; m /= 10) ++cnt[m%10];
    fo(i, mx_d) if(a[i] == cnt[i]) return false;
    return true;
}

ll brute(ll n) {
    ll ret = 0;
    rep(i, 1, n) {
        if(isok(i)) ++ret;
    }

    return ret;
}

ll brute(ll l, ll r) {
    ll ret = 0;
    rep(i, l, r) ret += isok(i);
    return ret;
}

vi digs;
int amask[mx_c];
int acnt;

ll dp[mx_c][2][(1 << mx_c)];
int vis[mx_c][2][(1 << mx_c)], mark;


ll getRem(int rem, int mask) {
    int cnt[mx_d] = {0};
    int tot = 0;
    fo(i, acnt) if(!is1(mask, i)) {
        ++tot;
        ++cnt[amask[i]];
    }
    ll pos = fact[tot];
    fo(i, mx_d) {
        //trace(i, cnt[i]);
        pos /= fact[cnt[i]];
    }

    //trace(tot, rem, pos, si(digs));
    return C[rem][tot] * pos * rp[si(digs)][rem-tot];
}


ll solve(int i, int eq, int mask);

inline ll trySolve(int i, int eq, int mask, int d) {
    if(i == 0 && d == 0) return 0;
    if(eq && d > num[i]) return 0;
    else return solve(i + 1, (eq && num[i] == d), mask);
}

inline bool prune(int i, int eq, int mask) {
    ll arem = acnt - __builtin_popcount(mask);
    if(i + arem > dcnt) return true;

    return false;
}

ll solve(int i, int eq, int mask) {
    if(i == dcnt) {
        return (mask == (1 << acnt) - 1)? 1: 0;
    }
    if(prune(i, eq, mask)) return 0;
    ll &ret = dp[i][eq][mask];
    if(vis[i][eq][mask] == mark) return ret;
    vis[i][eq][mask] = mark;

    ret = 0;
    if(eq == 0)  return ret = getRem(dcnt - i, mask);

    // Use from amask
    int tried = 0;
    fo(j, acnt) if(!is1(mask, j) && !is1(tried, amask[j])) {
        ret += trySolve(i, eq, mask | (1 << j), amask[j]);
        tried |= (1 << amask[j]);
    }

    // Not from amask
    for(int d: digs) ret += trySolve(i, eq, mask, d);

    /*
    if(eq == 0) {
        //trace(i, eq, mask, acnt, ret, getRem(dcnt - i, mask));
        assert(ret == getRem(dcnt - i, mask));
    }
    */
    //trace(i, eq, mask, ret);
    return ret;
}

ll solveStart(int from) {
    if(from == 0) return solve(0, 1, 0);
    ll ret = 0;

    // Use from amask
    int tried = 0;
    fo(j, acnt) if(amask[j] > 0 && !is1(tried, amask[j])) {
        ret += solve(from + 1, 0, (1 << j));
        tried |= (1 << amask[j]);
    }

    // Not from amask
    for(int d: digs) if(d > 0) ret += solve(from + 1, 0, 0);

    //trace(from, ret);
    return ret;
}

ll solveFor(int mask, ll n) {
    digs.clear();

    acnt = 0;
    fo(i, mx_d) {
        if(is1(mask, i)) {
            if(acnt + a[i] > dcnt) return 0;
            fo(j, a[i]) amask[acnt++] = i;
        } else {
            digs.push_back(i);
        }
    }
    

    ++mark;
    //trace(mask, n, acnt, digs);
#ifdef TRACE
    //fo(i, acnt) cerr << amask[i];
    //cerr << endl;
#endif
    ll ret = 0;
    fo(i, dcnt) {
        ret += solveStart(i);
    }
    //trace(mask, n, ret);
    return ret;
}

ll solve(ll n) {
    if(n <= 100000) return brute(n);
    dcnt = 0;
    for(ll m = n; m > 0; m /= 10) num[dcnt++] = m % 10;
    reverse(num, num + dcnt);
    //trace(n, dcnt);

    ll ret = n;
    re(mask, 1, (1 << mx_d)) {
        ll sgn = (__builtin_popcount(mask) % 2? -1: 1);
        ret += sgn * solveFor(mask, n);
    }

#ifdef CHECK
    trace(n, ret, brute(n));
    assert(ret == brute(n));
#endif
    return ret;
}

ll solve(ll l, ll r) {
    return solve(r) - solve(l-1);
}


int main() {
    pre();
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
#ifndef TEST
    cin >> t;
#else
    t = 20;
#endif
    while(t--) {
        ll l, r;
#ifndef TEST
        cin >> l >> r;
        fo(i, mx_d) cin >> a[i];
#else
        l = 1ll * rand() * rand() % 1000000000000000000L + 1;
        r = 1ll * rand() * rand() % 1000000000000000000L + 1;
        //l = 1ll * rand() + 1;
        //r = 1ll * rand() + 1;
        if(l > r) swap(l, r);
        fo(i, mx_d) a[i] = rand() % 5;
#endif
        ll ans = solve(l, r);
#ifdef CHECK
        ll bans = brute(l, r);
        if(ans != bans) {
            trace(ans, bans);
            assert(ans == bans);
        }
#endif
        trace(l, r, ans);
        cout << ans << '\n';
    }
    
    
	return 0;
}

