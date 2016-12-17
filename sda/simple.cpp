/* string coder = "Balajiganapathi S"; // Never give up!  */

//#define LOCAL
#ifdef LOCAL
#   define TRACE
#   define TEST
#else
//#   define NDEBUG
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
constexpr int mx_n = 100005, mx_c = 41;
constexpr int lg_n = 18;
constexpr int mx_m = 2 * mx_n;
int n, m, c;
int u[mx_m], v[mx_m], w[mx_m];
vi edge[mx_n];
int vis[mx_n];
int isArt[mx_n];

int adj(int e, int x) {
    if(u[e] == x) return v[e];
    return u[e];
}

int depth[mx_n], low[mx_n], npar[mx_n];
void bridge_dfs(int x, int up, int d) {
    vis[x] = 1;
    int childCount = 0;
    bool isA = false;
    for(int e: edge[x]) {
        int y = adj(e, x);
        if(!vis[y]) {
            npar[y] = x;
            bridge_dfs(y, e, d + 1);
            childCount++;
            if(low[y] >= depth[x]) isA = true;
            low[x] = min(low[x], low[y]);

        } else if(e != up) {
            low[x] = min(low[x], depth[y]);
        }
    }

    if((npar[x] != -1 && isA) || (npar[x] == -1 && childCount > 1)) {
        isArt[x] = 1;
    }
}

int comps;
int incomp[mx_n];
int par[mx_n][lg_n];
int lvl[mx_n];
ll cmask[mx_n], pcol[mx_n][lg_n];
void tree_dfs(int x, int c, int lc)  {
    trace(x, c, lc);
    if(vis[x]) return;
    vis[x] = 1;
    incomp[x] = c;
    lvl[c] = lc;
    for(int e: edge[x]) {
        int y = adj(e, x);
        if(vis[y]) continue;
        if(isbridge[e]) {
            trace(comps, c);
            par[comps][0] = c;
            pcol[comps][0] = (1ll << w[e]);
            trace(comps, par[comps][0]);
            tree_dfs(y, comps++, lc + 1);
        } else {
            cmask[c] |= (1ll << w[e]);
            tree_dfs(y, c, lc);
        }
    }
}

void pre_lca() {
    fo(i, n) pcol[i][0] |= cmask[i];
    re(j, 1, lg_n) {
        fo(i, comps) if(par[i][j-1] != -1) {
            par[i][j] = par[par[i][j-1]][j-1];
            pcol[i][j] = (pcol[i][j-1] | pcol[par[i][j-1]][j-1]);
        }
    }
}

int solve(int x, int y) {
    x = incomp[x]; y = incomp[y];
    ll mask = 0;
    if(lvl[x] > lvl[y]) swap(x, y);
    trace(x, y, lvl[x], lvl[y]);
    for(int i = lg_n - 1; i >= 0; --i) {
        int p = par[y][i];
        trace(i, y, lvl[y], p, lvl[p]);
        if(p != -1 && lvl[p] >= lvl[x]) {
            mask |= pcol[y][i];
            y = p;
        }
    }
    trace(x, y, lvl[x], lvl[y], mask);

    for(int i = lg_n - 1; i >= 0; --i) {
        if(par[x][i] != par[y][i]) {
            mask |= pcol[y][i];
            mask |= pcol[x][i];
            x = par[x][i];
            y = par[y][i];
        }
    }

    if(x != y) {
        mask |= pcol[x][0];
        mask |= pcol[y][0];
        x = par[x][0];
        y = par[y][0];
    }
    assert(x == y);
    mask |= cmask[x];

    trace(x, y, mask);
    return __builtin_popcount(mask);
}

void pre() {
    ini(vis, 0);
    fo(i, n) if(!vis[i]) bridge_dfs(i, -1, 0);
    ini(vis, 0);
    ini(par, -1);
    fo(i, n) if(!vis[i]) tree_dfs(i, comps++, 0);
    assert(comps <= n);
    pre_lca();
    trace(n, comps);
    fo(i, n) trace(i, incomp[i]);
    fo(i, comps) trace(i, par[i][0], pcol[i][0], lvl[i]);
}

int main() {
    scanf("%d %d %d", &n, &m, &c);
    fo(i, m) {
        scanf("%d%d%d", u + i, v + i, w + i);
        --u[i]; --v[i]; --w[i];
        edge[u[i]].push_back(i);
        edge[v[i]].push_back(i);
    }
    pre();
    int q, x, y;
    scanf("%d", &q);
    fo(i, q) {
        scanf("%d%d", &x, &y);
        --x; --y;
        printf("%d\n", solve(x, y));
    }

    return 0;
}

