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

vi adj[mx_n];
int n, b;
int dist[mx_n][mx_n];
int siz[mx_n], par[mx_n];

void dfs(int x, int p) {
    siz[x] = 1;
    par[x] = p;
    for(int y: adj[x]) if(y != p) {
        dfs(y, x);
        siz[x] += siz[y];
    }
}

bool iscentroid(int x) {
    int rem = n - 1;
    for(int y: adj[x]) if(y != par[x]) {
        if(siz[y] > n / 2) return false;
        rem -= siz[y];
    }

    return rem <= n / 2;
}

vi getCenters() {
    vi ret;
    int cd = oo;
    fo(i, n) {
        int cur = 0;
        fo(j, n) cur = max(cur, dist[i][j]);
        if(cur < cd) {
            cd = cur;
            ret.clear();
        }
        if(cur == cd) ret.push_back(i);
    }

    return ret;
}


int beauty() {
    fo(i, n) {
        fo(j, n) {
            dist[i][j] = (i == j? 0: oo);
        }
    }

    fo(i, n) {
        for(int x: adj[i]) dist[i][x] = dist[x][i] = 1;
    }

    fo(k, n) {
        fo(i, n) fo(j, n) dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    }

    vi centroids, centers;
    dfs(0, -1);
    fo(i, n) {
        if(iscentroid(i)) centroids.push_back(i);
    }
    centers = getCenters();

    int ans = 0;
    for(int i: centroids) for(int j: centers) {
        ans = max(ans, dist[i][j]);
    }

    return ans;
}

vector<pi> bans, ans;
int pars[mx_n];

bool isok() {
    fo(i, mx_n) adj[i].clear();
    re(i, 1, n) {
        adj[i].push_back(pars[i]);
        adj[pars[i]].push_back(i);
    }

    return beauty() == b;
}

bool isok(const vector<pi> &e) {
    fo(i, mx_n) adj[i].clear();
    for(auto cur: e) {
        adj[cur.fi].push_back(cur.se);
        adj[cur.se].push_back(cur.fi);
    }

    return beauty() == b;
}

void gen(int i) {
    if(i == n) {
        if(isok()) {
            re(i, 1, n) bans.emplace_back(i, pars[i]);
        }
        return;
    }
    for(pars[i] = 0; pars[i] < i; ++pars[i]) {
        gen(i+1);
        if(si(bans)) return;
    }
}
vector<pi> brute() {
    bans.clear();
    gen(1);
    return bans;
}

void solve() {
    ans.clear();
    if(n <= 2) {
        brute();
        ans = bans;
        return;
    }
    trace(n, b);
    if(2 * b > n / 2) return;
    trace(n, b);
    rep(i, 1, 2 * b) {
        ans.emplace_back(i - 1, i);
    }
    re(i, 2 * b + 1, n) ans.emplace_back(0, i);
}

int main() {
    int t;
    cin >> t;
    while(t--) {
        fo(i, mx_n) adj[i].clear();
        cin >> n >> b;
#ifdef TEST
        brute();
        trace(bans);
#endif
        solve();
        if(si(ans)) {
            cout << "YES" << endl;
            for(auto e: ans) cout << e.fi + 1 << " " << e.se + 1 << endl;
#ifdef TEST
            assert(isok(ans));
#endif
        } else {
#ifdef TEST
            assert(bans.empty());
#endif
            cout << "NO" << endl;
        }
    }
    
    
	return 0;
}

