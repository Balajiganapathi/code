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
constexpr int mx_n = 100005;
constexpr int mx_a = 10, lg_n = 21;
int n, m, q;
vi at[mx_n], adj[mx_n];
vi ch[mx_n];
int par[mx_n], depth[mx_n], sz[mx_n];

class Block {
public:
    vi minv;
};

void dfs1(int x, int p, int d) {
    depth[x] = d;
    par[x] = p;
    sz[x] = 1;

    for(int y: adj[x]) if(y != p) {
        dfs1(y, x, d + 1);
        sz[x] += sz[y];
        ch[x].push_back(y);
    }
    trace(x, par[x], ch[x], sz[x], depth[x]);
}

int chNum, chHead[mx_n], chPos[mx_n], chIdx[mx_n], chSize[mx_n];
vi chNodes[mx_n];
vector<Block> chSeg[mx_n];

void hld(int x) {
    if(chHead[chNum] == -1) chHead[chNum] = x;
    chIdx[x] = chNum;
    chPos[x] = chSize[chNum];
    chNodes[chNum].push_back(x);
    ++chSize[chNum];

    int bi = -1;
    for(int y: ch[x]) if(bi == -1 || sz[y] > sz[bi]) bi = y;
    if(bi != -1) hld(bi);
    for(int y: ch[x]) if(y != bi) {
        ++chNum;
        hld(y);
    }
}
int up[mx_n][lg_n];

int lca(int u, int v) {
    if(depth[u] > depth[v]) swap(u, v);
    for(int j = lg_n - 1; j >= 0; --j) if(depth[up[v][j]] >= depth[u]) v = up[v][j];

    if(u == v) return v;

    for(int j = lg_n - 1; j >= 0; --j) if(up[v][j] != up[u][j]) {
        u = up[u][j];
        v = up[v][j];
    }

    assert(par[u] == par[v]);
    return par[u];
}

void initLCA() {
    rep(i, 1, n) up[i][0] = par[i];
    re(j, 1, lg_n) {
        rep(i, 1, n) up[i][j] = up[up[i][j-1]][j-1];
    }
}

int getLast(int u, int v) {
    for(int j = lg_n - 1; j >= 0; --j) if(depth[up[u][j]] > depth[v]) u = up[u][j];
    return u;
}

void add(list<Block *> &blocks, list<Block *> cur) {
    for(auto x: cur) blocks.push_back(x);
}

vi limit(vi v, int s) {
    if(si(v) > s) v.resize(s);
    return v;
}

list<Block *> get(int idx, int i, int a, int b, int qa, int qb) {
    assert(i < si(chSeg[idx]));
    if(a == qa && b == qb) {
        list<Block *> ret;
        ret.push_back(&chSeg[idx][i]);
        return ret;
    }
    int l = 2 * i + 1, r = 2 * i + 2;
    int m = (a + b) / 2;

    list<Block *> ret;
    if(qb <= m) {
        add(ret, get(idx, l, a, m, qa, qb));
    } else if(qa > m) {
        add(ret, get(idx, r, m + 1, b, qa, qb));
    } else {
        add(ret, get(idx, l, a, m, qa, m));
        add(ret, get(idx, r, m + 1, b, m + 1, qb));
    }

    return ret;
}

list<Block *> getBlocks(int chIdx, int a, int b) {
    trace(chIdx, a, b, chPos[a], chPos[b], par[a], par[b], depth[a], depth[b]);
    assert(chPos[b] <= chPos[a]);
    return get(chIdx, 0, 0, chSize[chIdx] - 1, chPos[b], chPos[a]);
}

list<Block *> solvePath(int u, int v) {
    list<Block *> ans;
    trace(u, v);

    while(1) {
        if(chIdx[u] == chIdx[v]) {
            trace(u, v);
            add(ans, getBlocks(chIdx[u], u, v));
            break;
        }

        trace(u, chHead[chIdx[u]]);
        add(ans, getBlocks(chIdx[u], u, chHead[chIdx[u]]));
        u = par[chHead[chIdx[u]]];
    }

    return ans;
}

vi getMin(const list<Block *> &blocks, int a) {
    vi ans;

    set<tuple<int, Block *, int>> pq;
    for(auto cur: blocks) if(si(cur->minv) > 0) {
        pq.emplace(cur->minv[0], cur, 0);
    }
    while(!pq.empty() && si(ans) < a) {
        int v, j;
        Block *cur;
        tie(v, cur, j) = *pq.begin(); pq.erase(pq.begin());
        ans.push_back(v);
        if(j + 1 < si(cur->minv)) pq.emplace(cur->minv[j+1], cur, j + 1);
    }

    trace(ans);
    return ans;
}

vi solveAll(int u, int v, int a) {
    trace(u, v);
    if(u == v) return limit(at[u], a);
    int l = lca(u, v);
    trace(u, l, v);
    list<Block *> blocks;
    if(l == u) {
        add(blocks, solvePath(v, l));
    } else if(l == v) {
        add(blocks, solvePath(u, l));
    } else {
        add(blocks, solvePath(u, l));
        add(blocks, solvePath(v, getLast(v, l)));
    }

    return getMin(blocks, a);
}

void solve(int u, int v, int a) {
    trace(u, v);
    vi ans = solveAll(u, v, a);
    cout << si(ans);
    for(int x: ans) cout << " " << x;
    cout << '\n';
}

void build(int idx, int i, int a, int b) {
    assert(i < si(chSeg[idx]));
    trace(idx, i, a, b);
    if(a == b) {
        int x = chNodes[idx][a];
        trace(x);
        chSeg[idx][i].minv = at[x];
        return;
    }
    int l = 2 * i + 1, r = 2 * i + 2;
    int m = (a + b) / 2;
    build(idx, l, a, m);
    build(idx, r, m + 1, b);

    list<Block *> v;
    v.push_back(&chSeg[idx][l]);
    v.push_back(&chSeg[idx][r]);

    chSeg[idx][i].minv = getMin(v, mx_a);
    trace(idx, i, a, b, chSeg[idx][i].minv);
}

void buildSeg(int x) {
    trace(x, chNodes[x]);
    int n = si(chNodes[x]);
    chSeg[x] = vector<Block>(4 * n);
    build(x, 0, 0, n - 1);
}

void init() {
    rep(i, 1, n) {
        sort(all(at[i]));
        at[i] = limit(at[i], mx_a); ;
        trace(i, at[i]);
    }
    dfs1(1, 1, 0);
    ini(chHead, -1);
    hld(1);
    ++chNum;
    trace(chNum);
    fo(i, chNum) buildSeg(i);

    initLCA();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> q;
    fo(i, n - 1) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    rep(i, 1, m) {
        int ci;
        cin >> ci;
        at[ci].push_back(i);
    }

    init();

    while(q--) {
        int u, v, a;
        cin >> u >> v >> a;
        solve(u, v, a);
    }
    
	return 0;
}

