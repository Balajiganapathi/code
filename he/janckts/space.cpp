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
constexpr int mx_n = 21, mx_t = 101;

int n, m, t;
int zvis[2][mx_n], zidx[2][mx_n];

class State {
public:
    int cnt[mx_n], cur, tokens;
    State() {
        ini(cnt, 0); cur = 0; tokens = 0;
    }

    State(const State &s) {
        fo(i, n) cnt[i] = s.cnt[i];
        cur = s.cur;
        tokens = s.tokens;
    }

    void addTokens(int i, int t) {
        tokens -= t;
        cnt[zidx[1][i]] += t;
    }

    void remTokens(int i, int t) {
        tokens += t;
        cnt[zidx[1][i]] -= t;
    }

    int getTokens(int i) {
        return cnt[zidx[1][i]];
    }

    bool operator <(const State &s) const {
        if(cur != s.cur) return cur < s.cur;
        if(tokens != s.tokens) return tokens < s.tokens;
        fo(i, n) if(cnt[i] != s.cnt[i]) return cnt[i] < s.cnt[i];
        return false;
    }

    bool operator ==(const State &s) const {
        if(cur != s.cur) return false;
        if(tokens != s.tokens) return false;
        fo(i, n) if(cnt[i] != s.cnt[i]) return false;
        return true;
    }

    int totTokens() {
        int tot = tokens;
        fo(i, n) tot += cnt[i];
        return tot;
    }
};


template <class T> inline void hash_combine(std::size_t& seed, const T& v) {
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}

namespace std {
    template<>
    class hash<State> {
        public:
        size_t operator()(const State &s) const {
            size_t h = 0;
            hash_combine(h, s.cur);
            hash_combine(h, s.tokens);
            fo(i, n) hash_combine(h, s.cnt[i]);

            return h;
        }
    };
}

ostream& operator<<(ostream& os, const State &s) {
    os << "cnt[";
    fo(i, n) os << s.cnt[i] << " ";
    os << "] @" << s.cur << " +" << s.tokens;
    return os;
}

class Door {
public:
    int u, v;
    int cost, cap;

    bool operator <(const Door &d) const {
        if(cost != d.cost) return cost < d.cost;
        return cap > d.cap;
    }
};

ostream& operator<<(ostream& os, const Door &d) {
    os << d.u << " <-> " << d.v << " -" << d.cost << " [" << d.cap << "]";
    return os;
}

vector<Door> doors[mx_n], zdoors[mx_n];
vector<Door> doorsFor[(1 << mx_n)];
int ans;
int evals;

void explore(State s);
void go(State s, int mask) {
    //trace(s, mask, doorsFor[mask]);
    for(const Door &d: doorsFor[mask]) {
        //if(d.cost > s.tokens) break;
        if(d.cost > s.tokens) continue;
        State nxt(s);
        nxt.tokens = min(nxt.tokens - d.cost, d.cap);
        assert(nxt.totTokens() < s.totTokens());
        nxt.cur = d.v;
        explore(nxt);
    }
}

unordered_set<State> vis;
void explore(State s) {
    //trace(s);
    if(vis.find(s) != vis.end()) return;
    vis.insert(s);
    ++evals;
    int cur = (is1(zvis[1][n-1], s.cur)? s.tokens: 0) + s.getTokens(n - 1);
    if(cur > ans) {
        trace(s);
        ans = max(ans, cur);
    }
    if(s.totTokens() <= ans) return;

    int ctokens = s.tokens;
    rep(keep, 0, ctokens) {
        s.addTokens(s.cur, keep);
        int mask = zvis[1][s.cur];

        go(s, mask);

        s.remTokens(s.cur, keep);
    }

    ctokens = s.getTokens(s.cur);
    rep(take, 0, ctokens) {
        s.remTokens(s.cur, take);

        go(s, zvis[1][s.cur]);

        s.addTokens(s.cur, take);
    }

    int ttokens = s.tokens;
    s.addTokens(s.cur, ttokens);

    fo(ni, n) if(is1(zvis[0][s.cur], ni)) {
        ctokens = s.getTokens(ni);
        rep(take, 0, ctokens) {
            s.remTokens(ni, take);

            go(s, zvis[1][ni]);

            s.addTokens(ni, take);
        }
    }

    s.remTokens(s.cur, ttokens);
}

int dfs_vis[mx_n];
int dfs_mask;

void dfs(int x, int t) {
    if(dfs_vis[x]) return;
    dfs_vis[x] = 1;
    dfs_mask |= (1 << x);
    for(const Door& d: zdoors[x]) {
        if(d.cap == 0 && t != 0) continue;
        if(d.cap > 0 && t != 1) continue;
        dfs(d.v, t);
    }
}

vector<Door> minimizeDoors(const vector<Door> &ds) {
    vector<Door> at[mx_n];
    vector<Door> ret;
    for(const Door& d: ds) at[d.v].push_back(d);
    fo(i, n) if(si(at[i])) {
        sort(all(at[i]));
        int max_cap = -oo;
        for(const Door &d: at[i]) {
            if(d.cap > max_cap) {
                ret.push_back(d);
                max_cap = d.cap;
            }
        }
    }
    sort(all(ret));

    return ret;
}

void pre() {
    fo(t, 2) {
        fo(i, n) if(!dfs_vis[i]) {
            dfs_mask = 0;
            dfs(i, t);
            fo(j, n) if(is1(dfs_mask, j)) {
                zvis[t][j] = dfs_mask;
            }
        }
        if(!t) ini(dfs_vis, 0);
    }

    fo(t, 2) fo(i, n) {
        zidx[t][i] = __builtin_ffs(zvis[t][i]) - 1;
        if(t == 1) zvis[0][i] |= zvis[1][i];
        //trace(t, i, zvis[t][i], zidx[t][i]);
    }

    fo(mask, (1 << n)) {
        fo(i, n) if(is1(mask, i)) {
            for(const Door &d: doors[i]) {
                if(is1(mask, d.v)) continue;
                doorsFor[mask].push_back(d);
            }
        }
        doorsFor[mask] = minimizeDoors(doorsFor[mask]);
    }

}

int main() {
    scanf("%d%d%d", &n, &m, &t);
    fo(i, m) {
        Door d;
        scanf("%d%d%d%d", &d.u, &d.v, &d.cost, &d.cap);
        --d.u; --d.v;
        //trace(d.u, d.v);
        assert(d.u < n && d.v < n);
        if(d.cost > 0) {
            doors[d.u].push_back(d);
            swap(d.u, d.v);
            doors[d.u].push_back(d);
        } else {
            zdoors[d.u].push_back(d);
            swap(d.u, d.v);
            zdoors[d.u].push_back(d);
        }
    }
    pre();
    ans = -1;

    State s;

    s.tokens = t;
    s.cur = 0;

    explore(s);
    printf("%d\n", ans);
    
    cerr << "Evals: " << evals << endl;
	return 0;
}

