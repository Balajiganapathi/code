/* string coder = "Balajiganapathi S"; // Never give up!  */

//#define LOCAL
#ifdef LOCAL
//#   define TRACE
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
constexpr int mx_n = 300005, lg_mx = 21;
vi ch[mx_n];
int siz[mx_n], mx_siz[mx_n], tstart[mx_n], tend[mx_n], tim;
int par[mx_n][lg_mx];
int n, q;

void pre() {
    rep(i, 1, n) for(int c: ch[i]) par[c][0] = i;
    par[1][0] = 1;
    re(j, 1, lg_mx) {
        rep(i, 1, n) par[i][j] = par[par[i][j-1]][j-1];
    }

    rep(i, 1, n) fo(j, lg_mx) assert(par[i][j] > 0);
}

void dfs1(int x) {
    siz[x] = 1;
    mx_siz[x] = 0;

    tstart[x] = ++tim;
    for(int c: ch[x]) {
        dfs1(c);
        siz[x] += siz[c];
        mx_siz[x] = max(mx_siz[x], siz[c]);
    }
    tend[x] = ++tim;
}

vector<pi> add[mx_n];
vector<pi> del[mx_n];

bool isancestor(int a, int b) {
    return tstart[a] <= tstart[b] && tstart[b] <= tend[a];
}

bool isCentroidOf(int c, int x) {
    int tot = siz[x];
    return isancestor(x, c) && 2 * mx_siz[c] <= tot && 2 * (tot - siz[c]) <= tot;
}

int getHighest(int c) {
    int ans = c;
    for(int i = lg_mx - 1; i >= 0; --i) {
        if(siz[par[ans][i]] <= 2 * siz[c]) ans = par[ans][i];
    }
    if(!isCentroidOf(c, ans)) return -1;
    return ans;
}

int getLowest(int c) {
    int ans = c;
    if(isCentroidOf(c, c)) return c;
    for(int i = lg_mx - 1; i >= 0; --i) {
        if(2 * mx_siz[c] > siz[par[ans][i]]) ans = par[ans][i];
    }
    ans = par[ans][0];
    if(!isCentroidOf(c, ans)) return -1;
    return ans;
}

int fil[mx_n][lg_mx];
int centroid[mx_n];
void dfs2(int x) {
    int a = getHighest(x);
    int d = getLowest(x);

    if(a != -1 || d != -1) {
        if(a == -1) a = d;
        if(d == -1) d = a;
        trace(x, a, d);
        int cur = d;
        centroid[d] = centroid[a] = x;
        for(int i = lg_mx - 1; i >= 0; --i) if(isancestor(a, par[cur][i])) {
            fil[cur][i] = x;
            cur = par[cur][i];
        }
    }

    for(int c: ch[x]) dfs2(c);
    //trace(x, ch[x], siz[x], mx_siz[x], a, d, add[x], del[x]);
}

set<pi> cur;
void dfs3(int x) {

    sort(all(del[x]));
    int i = 0;
    for(int c: ch[x]) {
        dfs3(c);
        for(; i < si(del[x]) && del[x][i].fi < tstart[c]; ++i);
        for(; i < si(del[x]) && del[x][i].fi <= tend[c]; ++i) cur.erase(del[x][i]);
    }


    for(auto a: add[x]) cur.insert(a);
    assert(!cur.empty());
    centroid[x] = cur.begin()->se;
    for(auto d: del[x]) cur.erase(d);
    assert(isancestor(x, centroid[x]));
}

#ifdef CHECK
vi cch[mx_n];
vi cadj[mx_n];
int csiz[mx_n], cmidx[mx_n];

int cdfs1(int x, int p) {
    if(p != -1) cch[p].push_back(x);
    csiz[x] = 1; cmidx[x] = -1;
    for(int a: cadj[x]) if(a != p) {
        cdfs1(a, x);
        csiz[x] += csiz[a];
        if(cmidx[x] == -1 || csiz[cmidx[x]] < csiz[a]) cmidx[x] = a;
    }
}

void rootAt(int r) {
    fo(i, mx_n) cch[i].clear();
    ini(csiz, 0); ini(cmidx, 0);
    cdfs1(r, -1);
}

int solve(int r, int x) {
    if(isCentroidOf(x, r)) return x;
    return solve(r, cmidx[x]);
}

int brute(int r) {
    rootAt(r);
    return solve(r, r);
}


#endif

void calc() {
    for(int j = lg_mx - 1; j >= 0; --j) {
        rep(i, 1, n) if(fil[i][j]) {
            centroid[i] = fil[i][j];
            if(j) {
                fil[i][j-1] = fil[par[i][j-1]][j-1] = fil[i][j];
            }
        }
    }
}

int main() {
#ifdef TEST
    n = 300000; q = 300000;
#else
    scanf("%d %d", &n, &q);
#endif
    fo(i, n - 1) {
        int p;
#ifdef TEST
        p = rand() % (i + 1) + 1;
#else
        scanf("%d", &p);
#endif
        ch[p].push_back(i + 2);
#ifdef CHECK
        cadj[p].push_back(i + 2);
        cadj[i+2].push_back(p);
#endif
    }

    pre();
    dfs1(1);
    dfs2(1);
    //dfs3(1);
    calc();
    
    while(q--) {
        int x;
#ifdef TEST
        x = rand() % n + 1;
#else
        scanf("%d", &x);
#endif
        printf("%d\n", centroid[x]);
#ifdef CHECK
        int bans = brute(x);
        if(!isCentroidOf(centroid[x], x)) {
            assert(isCentroidOf(bans, x));
            trace(x, centroid[x], bans);
            assert(isCentroidOf(centroid[x], x));
        }
#endif
    }
    
	return 0;
}

