/* string coder = "Balajiganapathi S"; // Never give up!  */

//#define LOCAL
#ifdef LOCAL
//#   define TRACE
#   define TEST
//#   define CHECK
#   define NDEBUG
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
constexpr int mx_nb = 1000, mx_bs = 1000;

int n;
int ed[mx_n][3];
ll dist[mx_n];


ll brute() {
    ll ans = 0;

    fo(i, n) {
        fo(j, n) dist[j] = oo;
        dist[i] = 0;
        for(int j = i - 1; j >= 0; --j) {
            rep(k, 1, 3) if(j + k <= i) {
                dist[j] = min(dist[j], dist[j+k] + ed[j][k-1]);
            }
            ans += dist[j];
        }
    }

    return ans;
}

bool subtask1() {
    return n <= 1000;
}

bool subtask2() {
    fo(i, n - 2) if(ed[i][1] != ed[i][0] + ed[i+1][0]) return false;
    fo(i, n - 3) if(ed[i][2] != ed[i][0] + ed[i+1][0] + ed[i+2][0]) return false;
    return true;
}

bool subtask3() {
    fo(i, n - 3) if(ed[i][2] != ed[i][0] + ed[i+1][0] + ed[i+2][0]) return false;
    return true;
}

void change(int diff, ll &tot, int i, int j) {
    int before = i + 1;
    int after = n - i - 1 - j;
    trace(diff, tot, i, j, before, after, ed[i][j]);
    tot += 1ll * diff * after * before * ed[i][j];
}

class Graph {
    public:
    int n;
    set<int> vertices;
    vector<tuple<int, int, int>> edges;
    map<int, int> idx;
    vector<vector<pi>> adj;
    vector<vector<pi>> radj;
    vector<vi> dfrom, dto;

    void init(int _n) {
        n = _n;
        adj.resize(n);
        radj.resize(n);
        dfrom.resize(n);
        dto.resize(n);
    }

    void addEdge(int a, int b, int w) {
        edges.emplace_back(a, b, w);
        vertices.insert(a);
        vertices.insert(b);
    }

    void normalize() {
        if(vertices.empty()) return;
        //trace(vertices);
        int i = 0;
        for(int x: vertices) idx[x] = i++;
        trace(idx);
        trace(edges);
        for(auto e: edges) {
            //trace(e, gt(e, 0), idx[gt(e, 0)], gt(e, 1), idx[gt(e, 1)]);
            adj[idx[gt(e, 0)]].emplace_back(idx[gt(e, 1)], gt(e, 2));
            radj[idx[gt(e, 1)]].emplace_back(idx[gt(e, 0)], gt(e, 2));
        }

        vertices.clear();
        edges.clear();
    }

    void calcFrom(int from) {
        normalize();
        assert(idx.find(from) != idx.end());
        from = idx[from];
        dfrom[from] = vi(n, oo);
        dfrom[from][from] = 0;
        re(i, from, n) {
            for(auto e: radj[i]) dfrom[from][i] = min(dfrom[from][i], e.se + dfrom[from][e.fi]);
        }
        trace(from, dfrom[from]);
    }

    void calcTo(int to) {
        normalize();
        assert(idx.find(to) != idx.end());
        to = idx[to];
        dto[to] = vi(n, oo);
        dto[to][to] = 0;
        for(int i = to; i >= 0; --i) {
            for(auto e: adj[i]) dto[to][i] = min(dto[to][i], e.se + dto[to][e.fi]);
        }
        trace(to, dto[to]);
    }

    int dist(int a, int b) {
        assert(idx.find(a) != idx.end());
        assert(idx.find(b) != idx.end());
        a = idx[a]; b = idx[b];
        if(!dfrom[a].empty()) return dfrom[a][b];
        if(!dto[b].empty()) return dto[b][a];
        assert(0);
    }

    ll sumDist(int f, int s) {
        assert(idx.find(f) != idx.end());
        assert(idx.find(s) != idx.end());
        f = idx[f];
        s = idx[s];
        ll ret = accumulate(dfrom[f].begin() + s, dfrom[f].end(), 0ll);
        trace(f, ret);
        return ret;
    }
};

class Block {
public:
    int s, e;
    int ns;
    Graph g;
    vector<pair<ll, ll>> d;
    ll d2sum;

    void init() {
        ns = e - s + 1;
        g.init(ns);
        rep(i, s, e) {
            if(i + 1 <= e) g.addEdge(i, i + 1, ed[i][0]);
            if(i + 2 <= e) g.addEdge(i, i + 2, ed[i][1]);
        }
        rep(i, s, e) g.calcFrom(i);
        trace("OK");
        rep(j, s, e) {
            d.emplace_back(g.dist(s + 0, j) - g.dist(s + 1, j), 0);
        }
        sort(all(d));
        ll cs = 0;
        fo(i, si(d)) {
            d[i].se = cs;
            cs += d[i].fi;
        }
        d.emplace_back(oo, cs);
        trace(d);
        d2sum = g.sumDist(s + 1, s);
    }

    int dist(int a, int b) {
        return g.dist(a, b);
    }


    ll solveFrom(int i) {
        trace(i);
        return g.sumDist(i, i);
    }

    ll solve(ll c1, ll c2) {
        int till = lower_bound(all(d), mp(1ll * c2 - c1, 1ll * -oo)) - d.begin();
        ll ret = d2sum + d[till].se;
        ret += 1ll * till * c1;
        ret += 1ll * (ns - till) * c2;

        return ret;
    }

    void disp() {
        trace(s, e, ns, d2sum);
        trace(d);
    }

} blocks[mx_nb];
int nb, bs, bidx[mx_n];
Graph global;

void init() {
    bs = max(int(sqrt(n) * 6), 4);
    nb = max(1, n / bs - 1);
    trace(nb, bs);
    int bi = 0;
    blocks[bi] = Block();
    fo(i, n) {
        if(i % bs == bs - 1) {
            if(++bi == nb) {
                bi = nb - 1;
            } else {
                blocks[bi] = Block();
                blocks[bi].s = i;
            }
        }
        blocks[bi].e = i;
        bidx[i] = bi;
        trace(i, bidx[i]);
    }

    fo(i, nb) {
        blocks[i].init();
    }

    global = Graph();
    global.init(4 * nb);
    fo(i, nb) {
        fo(i1, 2) fo(i2, 2) {
            int a = blocks[i].s + i1, b = blocks[i].e - i2;
            global.addEdge(a, b, blocks[i].dist(a, b));
        }
        fo(i1, 2) {
            int a = blocks[i].e - i1;
            fo(j, 2) if(a + j + 1 < n) global.addEdge(a, a + j + 1, ed[a][j]);
        }
    }

    fo(i, nb) {
        fo(j, 2) {
            global.calcFrom(blocks[i].s + j);
            global.calcFrom(blocks[i].e - j);
        }
    }

    fo(i, nb) {
        trace(i);
        blocks[i].disp();
    }
}

ll solveFrom(int f, int b) {
    int bf = bidx[f];
    ll c1 = min(blocks[bf].g.dist(f, blocks[bf].e - 1) + global.dist(blocks[bf].e - 1, blocks[b].s), 
                blocks[bf].g.dist(f, blocks[bf].e) + global.dist(blocks[bf].e, blocks[b].s));
    ll c2 = min(blocks[bf].g.dist(f, blocks[bf].e - 1) + global.dist(blocks[bf].e - 1, blocks[b].s + 1), 
                blocks[bf].g.dist(f, blocks[bf].e) + global.dist(blocks[bf].e, blocks[b].s + 1));

    ll ret = blocks[b].solve(c1, c2);
    trace(f, b, c1, c2, ret);
    return ret;
}

ll solve2() {
    init();
    ll ret = 0;
    fo(i, n) {
        ret += blocks[bidx[i]].solveFrom(i);
        re(b, bidx[i] + 1, nb) {
            ret += solveFrom(i, b);
        }
    }

    return ret;
}

ll solve() {
    ll ret = 0;
#ifndef LOCAL
    if(subtask1()) {
        ret = brute();
    } else
#endif
    if(subtask2()) {
        fo(i, n - 1) change(1, ret, i, 0);
    } else if(subtask3()) {
        ret = solve2();
    } else if(subtask1()) {
        ret = brute();
    }


    return ret;
}

int main() {
    int t;
#ifdef TEST
    t = 3;
#else
    cin >> t;
#endif
    while(t--) {
#ifdef TEST
        n = rand() % 100000 + 1;
        fo(j, 3) fo(i, n - j - 1) ed[i][j] = rand() % 10 + 1;
        fo(i, n - 3) ed[i][2] = ed[i][0] + ed[i+1][0] + ed[i+2][0];
#else
        cin >> n;
        fo(j, 3) {
            fo(i, n - j - 1) cin >> ed[i][j];
        }
#endif

        ll ans = solve();

        cout << ans << endl;
#ifdef CHECK
        ll bans = brute();
        trace(ans, bans);
        assert(ans == bans);
#endif
        
    }
    
    
	return 0;
}

