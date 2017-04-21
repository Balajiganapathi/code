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
constexpr int mx_n = 100005, lg_n = 19;
vi adj[mx_n], ch[mx_n];
int n;
int dp[mx_n], heavy[mx_n], omax[mx_n], cost[mx_n];
int depth[mx_n], hpend[mx_n];
multiset<int> costs[mx_n][lg_n];
deque<int> hpmax[mx_n];

int solve(int x);

void dfs(int x, int p, int d) {
    hpend[x] = x;
    depth[x] = d;
    for(int y: adj[x]) if(y != p) {
        dfs(y, x, d + 1);
        ch[x].push_back(y);
    }
    solve(x);
}

inline int sc(int h) {
    if(h == 0) return 0;
    return int(ceil(log(h) / log(2))) + 1;
}

int solve(int x) {
    int &ret = dp[x];
    if(ret != -1) return ret;
    int m = si(ch[x]);
    if(m == 0) return ret = 0;

    if(heavy[x] == -1) {
        int score = -oo;
        omax[x] = -oo;
        for(int y: ch[x]) {
            int cur = solve(y);
            if(cur > score) {
                heavy[x] = y;
                omax[x] = score;
                score = cur;
            } else if(cur > omax[x]) {
                omax[x] = cur;
            }
        }
    }

    int hx = heavy[x];

    hpend[x] = hpend[hx];

    ret = cost[depth[hpend[x]] - depth[x]];

    fo(i, lg_n) costs[x][i] = move(costs[hx][i]);
    hpmax[x] = move(hpmax[hx]);

    omax[x] += 1;
    hpmax[x].push_front(omax[x]);
    if(omax[x] >= 0) costs[x][0].insert(omax[x]);

    if(si(hpmax[x]) > 1 && hpmax[x][1] >= 0) {
        costs[x][0].erase(costs[x][0].find(hpmax[x][1]));
        costs[x][1].insert(hpmax[x][1]);
    }

    fo(i, lg_n) {
        int idx = (1 << i) + 1;
        if(idx < si(hpmax[x]) && hpmax[x][idx] >= 0) {
            costs[x][i+1].erase(costs[x][i+1].find(hpmax[x][idx]));
            costs[x][i+2].insert(hpmax[x][idx]);
        }
    }


    fo(i, lg_n) {
        if(!costs[x][i].empty()) ret = max(ret, i + *costs[x][i].rbegin());
    }

    //fo(i, si(hpmax[x])) ret = max(ret, sc(i) + hpmax[x][i]);

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    fo(i, mx_n) cost[i] = sc(i);
    int t;
#ifndef TEST
    cin >> t;
#else
    t = 10;
#endif

    while(t--) {
        fo(i, mx_n) {
            adj[i].clear(), ch[i].clear();
            hpmax[i].clear();
            fo(j, lg_n) costs[i][j].clear();
        }
#ifndef TEST
        cin >> n;
        fo(i, n - 1) {
            int a, b;
            cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
#else
        n = 100000;
        trace(n);
        fo(i, n - 1) {
            //int x = rand() % (i+1) + 1, y = i + 2;
            int x = i + 1, y = i + 2;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
#endif

        dfs(1, -1, 0);
        ini(dp, -1); ini(heavy, -1);
        int ans = solve(1);
        trace(ans);
        cout << ans << '\n';
    }
    
	return 0;
}

