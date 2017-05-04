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
constexpr int mx_n = 300005, lg_n = 22;
int n;
vi adj[mx_n], ch[mx_n];
int sz[mx_n], par[mx_n], lvl[mx_n];
int at[mx_n], tim, till[mx_n];
int k;
int anc[mx_n][lg_n];
vi query;

int tree[mx_n];
int read(int idx){
    int sum = 0;
    while (idx > 0){
        sum += tree[idx];
        idx -= (idx & -idx);
    }
    return sum;
}

void update(int idx ,int val){
    while (idx < mx_n){
        tree[idx] += val;
        idx += (idx & -idx);
    }
}

void dfs(int x, int p, int d) {
    par[x] = p;
    lvl[x] = d;
    sz[x] = 1;
    at[x] = ++tim;
    for(int y: adj[x]) if(y != p) {
        sz[x] += sz[y];
        ch[x].push_back(y);
        dfs(y, x, d + 1);
    }
    till[x] = tim;
}

void add(int x) {
    update(at[x], 1);
}

void rem(int x) {
    update(at[x], -1);
}

int getAt(int x) {
    //trace(x, at[x], till[x]);
    return read(till[x]) - read(at[x] - 1);
}

int c[mx_n];

int cntat[mx_n];

int findNext(int x) {
    int cur = cntat[x] = getAt(x);;
    int cx = x;
    for(int j = lg_n - 1; j >= 0; --j) {
        int y = anc[cx][j];
        trace(y, getAt(y));
        if(getAt(y) == cur) cx = y;
    }

    trace(x, cx, getAt(x), getAt(cx));
    assert(getAt(x) == getAt(cx));
    cx = par[cx];
    assert(getAt(x) != getAt(cx));
    trace(x, cx, getAt(x));
    cntat[cx] = getAt(cx);
    return cx;
}

void solve() {
    set<pi> q;
    for(int x: query) {
        add(x);
        cntat[x] = getAt(x);
        q.emplace(cntat[x], x);
    }
    trace(k, query, si(q));

    vi cleanup;
    while(!q.empty()) {
        auto cur = *q.begin(); q.erase(q.begin());
        swap(cur.fi, cur.se);
        trace(cur, getAt(cur.fi), cntat[cur.fi]);
        if(cntat[cur.fi] != cur.se) continue;
        cleanup.push_back(cur.fi);
        int p = findNext(cur.fi);
            assert(p);
        c[cur.se] += lvl[cur.fi] - lvl[p];
        trace(cur, p, lvl[cur.fi] - lvl[p]);
        if(p != 1) {
            q.emplace(cntat[p], p);
        }
    }


    for(int x: cleanup) cntat[x] = 0;
    c[0] = n;
    c[k] = 1;
    rep(i, 1, k) c[0] -= c[i];
    fo(i, k + 1) cout << c[i] << " ";
    cout << '\n';
    for(int x: query) rem(x);
    fo(i, k + 1) c[i] = 0;
    query.clear();
}

void init() {
    rep(i, 1, n) {
        anc[i][0] = par[i];
    }
    anc[1][0] = 1;

    re(j, 1, lg_n) {
        rep(i, 1, n) anc[i][j] = anc[anc[i][j-1]][j-1];
    }
    trace(7, par[7], anc[7][0], anc[7][1]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    fo(i, n - 1) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 1, 0);
    init();
    int q;
    cin >> q;
    while(q--) {
        cin >> k;
        fo(i, k) {
            int x;
            cin >> x;
            query.push_back(x);
        }
        solve();
    }
    
    
	return 0;
}

