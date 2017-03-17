/* string coder = "Balajiganapathi S"; // Never give up!  */

//#define LOCAL
#ifdef LOCAL
//#   define TRACE
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
constexpr int mx_n = 3 * 1000008;
int O[mx_n], R[mx_n], n;
int center_dist[mx_n];
vector<pi> adj[mx_n];

void input() {
    cin >> n;
    int a, b, c, d;
    cin >> O[0] >> a >> b >> c >> d;
    trace(n, O[0], a, b, c, d);
    re(i, 1, n) {
        O[i] = (1ll * a * O[i-1] + b) % c + d;
    }
    cin >> R[0] >> a >> b >> c >> d;
    trace(n, R[0], a, b, c, d);
    re(i, 1, n) {
        R[i] = (1ll * a * R[i-1] + b) % c + d;
    }
}

void calc_center() {
    fo(i, n) center_dist[i] = oo;
    center_dist[n] = 0;
    set<pi> q;
    q.insert({0,n});
    while(!q.empty()) {
        auto cur = *q.begin(); q.erase(q.begin());
        int i = cur.se;
        if(center_dist[i] < cur.fi) continue;
        for(auto ne: adj[i]) {
            auto nxt = mp(ne.se + cur.fi, ne.fi);
            if(center_dist[nxt.se] > nxt.fi) {
                center_dist[nxt.se] = nxt.fi;
                q.insert(nxt);
            }
        }
    }
}

ll cdist1[mx_n], tot_dist;
int cr[mx_n];
int ccdist1[mx_n];

void init() {
    fo(i, mx_n) {
        adj[i].clear();
    }
    tot_dist = 0;
    fo(i, n) {
        int j = (i+1) % n;
        adj[i].push_back({j, O[i]});
        adj[j].push_back({i, O[i]});
        adj[n].push_back({i, R[i]});
        adj[i].push_back({n, R[i]});
    }
    calc_center();
    fo(i, n) {
        tot_dist += O[i];
    }

    ll cur = 0, ccur = 0;
    int rcur = 0;
    fo(i, 2 * n) {
        cdist1[i] = cur;

        ccdist1[i] = ccur;
        cur += O[i%n];
        ccur = (cur + ccur) % mod;

        rcur += center_dist[i%n];
        if(rcur >= mod) rcur -= mod;
        cr[i] = rcur;
        trace(i, cdist1[i], ccdist1[i], cr[i]);
    }
    trace(tot_dist);
}

ll dist1(int a, int b) {
    return cdist1[b] - cdist1[a];
}

ll dist2(int a, int b) {
    return center_dist[a%n] + center_dist[b%n];
}

ll dist3(int a, int b) {
    return tot_dist - dist1(a, b);
}

int calc1(int x, int t) {
    x %= n; t %= n;
    int ans;
    if(x > t) {
        ans = calc1(x, n - 1) + calc1(0, t);
        //trace(x, t, ans);
        if(ans >= mod) ans -= mod;
        ans = (1ll * (dist1(x, n - 1) + O[n-1]) % mod * (t+1) + ans) % mod;
        //trace(x, t, ans);
    } else {
        ans = (ccdist1[t] - ccdist1[x] + mod) % mod;
        ans = (ans - 1ll * (t - x) * cdist1[x] % mod + mod) % mod;
    }
    return ans;
}

int calc2(int x, int t1, int t2) {
    int ans = (cr[t2] - cr[t1] + mod) % mod;
    ans = (ans + 1ll * (t2 - t1) * center_dist[x%n]) % mod;
    return ans;
}

int calc3(int x, int t) {
    int ans = (calc1(x, x + n - 1) + mod - calc1(x, t)) % mod;
    //trace(x, t, calc1(x, t), calc1(x, x + n - 1));
    //trace(ans);
    ans = (1ll * (x + n - 1 - t) * tot_dist % mod + mod - ans) % mod;
    return ans;
}

int calc(int x) {
    int t1, t2;
    int lo = x, hi = x + n - 1;
    while(lo < hi) {
        //trace(lo, hi);
        int m = (lo + hi + 1) / 2;
        trace(x, m, dist1(x, m), dist2(x, m), dist3(x, m));
        if(dist1(x, m) < min(dist2(x, m), dist3(x, m))) lo = m;
        else hi = m - 1;
    }
    t1 = lo;
    hi = x + n - 1;
    //trace(lo, hi);
    while(lo < hi) {
        int m = (lo + hi + 1) / 2;
        //trace(lo, hi, m, dist1(x, m), dist2(x, m), dist3(x, m));
        if(dist2(x, m) < dist3(x, m)) lo = m;
        else hi = m - 1;
    }

    t2 = lo;
    trace(x, t1, t2);
    trace(calc1(x, t1), calc2(x, t1, t2), calc3(x, t2));
    int ans = 0;
    ans = calc1(x, t1);
    ans += calc2(x, t1, t2);
    if(ans >= mod) ans -= mod;
    ans += calc3(x, t2);
    if(ans >= mod) ans -= mod;
    ans = (ans + 2ll * center_dist[x]) % mod;
    trace(x, ans);

    return ans;
}

int solve() {
    int ans = 0;

    fo(i, n) {
        ans += calc(i);
        if(ans >= mod) ans -= mod;
    }

    trace(ans);
    ans = 1ll *  ans * modpow(2, mod - 2, mod) % mod;

    return ans;
}

int main() {
    int t;
    cin >> t;
    rep(kase, 1, t) {
        input();
        init();
        int ans = solve();

        cout << "Case #" << kase << ": " << ans << endl;

    }
    
    
	return 0;
}

