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
constexpr int mx_n = 1003, mx_k = 1003, mx_m = 100 * 1003;
int w[mx_n], n, m, k;
int wt[mx_n][mx_n];
vector<pi> adj[mx_n];

bool isCity(int x) {
    return w[x] > 0;
}

bool hasTrack(int u, int v) {
    return wt[u][v] > 0 && wt[u][v] < oo;
}

class DSU {
public:
    int par[mx_n];
    DSU() {
        fo(i, n) par[i] = i;
    }

    int find(int x) {
        if(x == par[x]) return x;
        return par[x] = find(par[x]);
    }

    void merge(int a, int b) {
        a = find(a); b = find(b);
        if(a == b) return;
        if(rand() % 2) par[a] = b;
        else par[b] = a;
    }

};

class Edge {
public:
    int u, v, c;
    int we;

    bool operator <(const Edge &e) const {
        if(c != e.c) c < e.c;
        return we < e.we;
    }

    bool connectsACity() {
        return isCity(u) || isCity(v);
    }
} e[mx_m];

class Solution {
public:
    set<int> junctions;
    vector<pi> tracks;

    bool connected() const {
        DSU dsu;

        for(auto t: tracks) {
            dsu.merge(t.fi, t.se);
        }
        //return true;
        int comp = dsu.find(*junctions.begin());
        for(int c: junctions) {
            if(dsu.find(c) != comp) return false;
        }
        fo(i, n) {
            if(dsu.find(i) == comp) continue;
            if(dsu.find(i) != i) return false;
        }

        return true;

    }

    bool valid() const {
        if(junctions.empty()) return false;

        for(auto t: tracks) if(!hasTrack(t.fi, t.se)) return false;

        if(!connected()) return false;

        return true;
    }

    int score() const {
        assert(valid());
        int ret = 0;

        for(int c: junctions) if(isCity(c)) ret += w[c];
        for(auto t: tracks) ret -= wt[t.fi][t.se];

        return ret;
    }

    void addTrack(int u, int v) {
        assert(hasTrack(u, v));
        junctions.insert(u);
        junctions.insert(v);
        //trace(u, v, hasTrack(u, v));
        tracks.emplace_back(u, v);
    }
} best;
int bscore;

int rand(int a, int b) {
    return rand() % (b - a + 1) + a;
}

#ifdef TEST
int _t = 0;
int _lo[] = {100, 250, 500};
int _hi[] = {250, 500, 1000};
ll _tot = 0;
#endif
void input() {
#ifdef TEST
    srand(_t);
    n = 1000;
    m = min(n * (n - 1) / 2, rand(5 * n, 100 * n));
    int tt = _t % 3;
    k = min(n, rand(_lo[tt], _hi[tt]));
    int cm = 0;
    set<pi> done;
    while(cm < m) {
        int a = rand(0, n - 1);
        int b = rand(0, n - 1);
        if(done.count({a, b})) continue;
        assert(!done.count({b, a}));
        int c = rand(1, 1000);
        e[cm].u = a; e[cm].v = b; e[cm].c = c;
        e[cm].we = 0;
        ++cm;
        done.insert({a, b});
        done.insert({b, a});
    }
    vi v;
    fo(i, n) v.push_back(i);
    random_shuffle(all(v));
    ini(w, 0);
    fo(i, k) w[v[i]] = rand(1, 10000);

#else
    cin >> n >> m >> k;
    assert(n == 1000);
    assert(m <= 100 * n);
    //assert(100 <= k && k <= n);
    fo(i, n) cin >> w[i];
    fo(i, m) {
        cin >> e[i].u >> e[i].v >> e[i].c;
        --e[i].u; --e[i].v;
    }
    int kk = 0;
    fo(i, n) if(isCity(i)) ++kk;
    //assert(kk == k);
#endif
    trace(n, m, k);
}

void pre() {
    bscore = -oo;
    best = Solution();
    fo(i, n) adj[i].clear();
    fo(i, n) fo(j, n) {
        wt[i][j] = ((i == j)? 0: oo);
    }
    fo(i, m) {
        int u = e[i].u, v = e[i].v, c = e[i].c;
        wt[u][v] = wt[v][u] = c;
        adj[u].emplace_back(c, v);
        adj[v].emplace_back(c, u);
    }
}

vi sadj[mx_n];
int exclude[mx_n], mark;
Solution trimmed;

int dfs(int x, int p) {
    int score = w[x];

    for(int nxt: sadj[x]) if(nxt != p) {
        int cur = dfs(nxt, x) - wt[x][nxt];
        if(cur < 0) {
            exclude[nxt] = mark;
        } else {
            score += cur;
        }
    }

    return score;
}

void dfs2(int x, int p) {
    for(int nxt: sadj[x]) if(nxt != p && exclude[nxt] != mark) {
        trimmed.addTrack(x, nxt);
        dfs2(nxt, x);
    }
}

Solution trim(const Solution &s) {
    fo(i, n) sadj[i].clear();
    trimmed = Solution();
    for(auto e: s.tracks) {
        sadj[e.fi].push_back(e.se);
        sadj[e.se].push_back(e.fi);
    }

    int bi = -1;
    for(int i: s.junctions) {
        if(bi == -1 || w[i] > w[bi]) bi = i;
    }

    ++mark;
    dfs(bi, -1);
    dfs2(bi, -1);

    return trimmed;
}


void submit(const Solution &s) {
    int cur = s.score();
    if(cur > bscore) {
        bscore = cur;
        best = s;
    }
}

void output() {
    trace(bscore);
#ifdef TEST
    assert(best.valid());
    _tot += best.score();
#else
    cout << si(best.junctions) << " " << si(best.tracks) << endl;
    for(int c: best.junctions) cout << c + 1 << " "; cout << endl;
    for(auto t: best.tracks) cout << t.fi + 1 << " " << t.se + 1 << endl;
#endif
}

void trySingleCity() {
    fo(i, n) if(isCity(i)) {
        Solution s;
        s.junctions.insert(i);
        submit(s);
    }
}

void trySingleTrack() {
    fo(i, m) if(e[i].connectsACity()) {
        Solution s;
        s.addTrack(e[i].u, e[i].v);
        submit(s);
    }
}

void buildKruskal() {
    DSU dsu;
    Solution s;
    set<int> connectedCities;
    fo(i, m) {
        int a = e[i].u, b = e[i].v;
        if(dsu.find(a) != dsu.find(b)) {
            dsu.merge(a, b);
            s.addTrack(a, b);
            if(isCity(a)) connectedCities.insert(a);
            if(isCity(b)) connectedCities.insert(b);
        }
        if(si(connectedCities) == k && s.connected()) break;
        //if(rand() % 100 == 0 && s.connected()) submit(s);
    }
    submit(trim(s));
}

void tryKruskal() {
    for(int tries = 100; --tries > 0;) {
        fo(i, m) e[i].we = rand();
        sort(e, e + m);
        buildKruskal();
    }
}

class Candidate {
public:
    int c, u, v;
    Candidate(int _c, int _u, int _v) {
        c = _c; u = _u; v = _v;
    }

    bool operator <(const Candidate &can) const {
        if(c != can.c) return c < can.c;
        //int wu = w[u] - c, wcu = w[can.u] - can.c;
        //if(wu != wcu) return wu > wcu;
        return u < can.u;
    }
};

void buildPrim(int start) {
    Solution s;
    set<Candidate> edges;
    s.junctions.insert(start);
    for(auto nxt: adj[start]) edges.insert(Candidate(nxt.fi, nxt.se, start));
    while(!edges.empty()) {
        auto cur = *edges.begin();
        edges.erase(edges.begin());
        if(s.junctions.count(cur.u) == 0) {
            s.addTrack(cur.u, cur.v);
            //submit(s);
            for(auto nxt: adj[cur.u]) edges.insert(Candidate(nxt.fi, nxt.se, cur.u));
        }
    }
    submit(trim(s));
    //trace(start, si(s.junctions), s.score());
}


void multiPrim(const bitset<mx_n> start) {
    Solution s;
    set<int> comps;
    DSU dsu;
    set<Candidate> edges;
    fo(i, n) if(start[i]) {
        comps.insert(i);
        s.junctions.insert(i);
        for(auto nxt: adj[i]) edges.insert({nxt.fi, nxt.se, i});
    }
    trace(si(comps));

    while(!edges.empty()) {
        auto cur = *edges.begin();
        edges.erase(edges.begin());
        int cu = dsu.find(cur.u), cv = dsu.find(cur.v);
        if(cu != cv) {
            s.addTrack(cur.u, cur.v);
            dsu.merge(cu, cv);
            comps.erase(cu);
            comps.erase(cv);
            comps.insert(dsu.find(cu));
            if(si(comps) == 1) break;
            for(auto nxt: adj[cur.u]) edges.insert(Candidate(nxt.fi, nxt.se, cur.u));
        }
    }
    submit(trim(s));

}

void tryPrim() {
    buildPrim(0);

    fo(tries, 10) {
        bitset<mx_n> cit;
        fo(i, n) cit[i] = (rand() % 10001 <= w[i] + (w[i]? 1000: 0)? 1: 0);
        multiPrim(cit);
    }
}

int main() {
#ifdef TEST
    _t = 0;
    for(; _t < 12; ++_t) {
#endif
    input();
    pre();
    
    //trySingleCity();
    //trySingleTrack();
    tryKruskal();
    tryPrim();

    output();

#ifdef TEST
    }
    cerr << "Score: " << _tot << endl;
#endif

	return 0;
}

