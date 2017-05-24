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
constexpr int mx_n = 1003;
int g[mx_n][mx_n], n, m;
ll k;

int ans[mx_n][mx_n], vis[mx_n][mx_n];
int dcnt, opt;

void dfs(int i, int j) {
    if(i < 0 || i >= n || j < 0 || j >= m) return;
    if(g[i][j] < opt || dcnt == 0) return;
    if(vis[i][j]) return;

    ans[i][j] = opt;
    --dcnt;
    vis[i][j] = 1;
    fo(d, 4) {
        int ni = i + dx[d], nj = j + dy[d];
        dfs(ni, nj);
    }

}
void printFor(int i, int j) {
    cout << "YES" << endl;
    ini(ans, 0);
    opt = g[i][j];
    dcnt = k / opt;

    dfs(i, j);

    fo(i, n) {
        fo(j, m) cout << ans[i][j] << " ";
        cout << endl;
    }
}

int par[mx_n * mx_n], maxSize, sz[mx_n * mx_n];

void init() {
    fo(i, n  * m) par[i] = i, sz[i] = 1;
    maxSize = 1;
}

int find(int x) {
    if(x == par[x]) return x;
    return par[x] = find(par[x]);
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if(x == y) return;
    if(rand() % 2) {
        par[x] = y;
        sz[y] += sz[x];
    } else {
        par[y] = x;
        sz[x] += sz[y];
    }
    maxSize = max(maxSize, sz[find(x)]);
}

void mergePoint(int i, int j) {
    fo(d, 4) {
        int ni = i + dx[d], nj = j + dy[d];
        if(ni >= 0 && ni < n && nj >= 0 && nj < m && g[ni][nj] >= g[i][j]) {
            merge(i * m + j, ni * m + nj);
        }
    }
}


int main() {
    vector<pi> pts;
    cin >> n >> m >> k;
    fo(i, n) fo(j, m) {
        cin >> g[i][j];
        pts.emplace_back(i, j);
    }

    sort(all(pts), [](auto a, auto b) -> bool { return g[a.fi][a.se] < g[b.fi][b.se]; });
    init();
    opt = -1;
    for(int i = si(pts) - 1; i >= 0; --i) {
        int x = g[pts[i].fi][pts[i].se];
        mergePoint(pts[i].fi, pts[i].se);
        if(x > 0 && k % x == 0 && k / x <= maxSize) {
            printFor(pts[i].fi, pts[i].se);
            break;
        }
    }
    if(opt == -1) cout << "NO" << endl;

    
	return 0;
}

