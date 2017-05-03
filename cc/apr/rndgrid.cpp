/* string coder = "Balajiganapathi S"; // Never give up!  */

//#define LOCAL
#ifdef LOCAL
#   define TRACE
#   define TEST
//#   define CHECK
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
constexpr int mx_n = 1003, mx_l = 5003, off = 200;
constexpr int mx_b = 2 * off + 3;
string s;
int l, n;
string grid[mx_n];

int li, hi, lj, hj;

void move(int &i, int &j, char m) {
    if(m == 'R') ++j;
    else if(m == 'L') --j;
    else if(m == 'U') --i;
    else ++i;
}

void calc() {
    ll totw = 0, toth = 0;
    int trials = 1000;
    fo(t, trials) {
        int ci = 0, cj = 0;
        int i1, i2, j1, j2;
        i1 = i2 = j1 = j2 = 0;
        fo(j, 5000) {
            move(ci, cj, "DLRU"[rand() % 4]);
            i1 = min(i1, ci);
            i2 = max(i2, ci);
            j1 = min(j1, ci);
            j2 = max(j2, ci);
        }
        totw += j2 - j1 + 1;
        toth += i2 - i1 + 1;
    }

    trace(1.0 * totw / trials, 1.0 * toth / trials);
}

int g[mx_n][mx_n], gsum[mx_n][mx_n];
int reach[mx_b][mx_b], nxt[mx_n][mx_n], nxti[mx_n][mx_n];
vector<tuple<int, int, int>> moves;

void initSum() {
    rep(i, 1, n) rep(j, 1, n) {
        gsum[i][j] = g[i][j] + gsum[i][j-1] + gsum[i-1][j] - gsum[i-1][j-1];
    }
}

int getSum(int i1, int j1, int i2, int j2) {
    return gsum[i2][j2] - gsum[i2][j1-1] - gsum[i1-1][j2] + gsum[i1-1][j1-1];
}

void initSub() {
    int ci, cj;
    ci = 0, cj = 0;
    fo(i, mx_b) fo(j, mx_b) reach[i][j] = oo;
    reach[ci+off][cj+off] = 0;
    li = lj = 0; hi = hj = 0;
    fo(i, l) {
        assert(abs(ci) < off && abs(cj) < off);
        move(ci, cj, s[i]);
        li = min(li, ci);
        lj = min(lj, cj);
        hi = max(hi, ci);
        hj = max(hj, cj);
        reach[ci+off][cj+off] = min(reach[ci+off][cj+off], i);
    }

    moves.clear();
    fo(i, mx_b) fo(j, mx_b) if(reach[i][j] != oo) {
        moves.emplace_back(reach[i][j], i - off, j - off);
    }
    sort(all(moves));
    trace(li, lj, hi, hj);
}

void initGrid() {
    rep(i, 1, n) {
        int last = n + 1;
        nxt[i][last] = last;
        for(int j = n; j >= 0; --j) {
            if(g[i][j]) last = j;
            nxt[i][j] = last;
        }
    }

    rep(j, 1, n) nxti[n+1][j] = n+1;
    for(int i = n; i >= 1; --i) {
        rep(j, 1, n) {
            nxti[i][j] = nxti[i+1][j];
            if(nxt[i][j] <= n) nxti[i][j] = i;
        }
    }
}

void init() {
    fo(i, n) fo(j, n) g[i+1][j+1] = (grid[i][j] == '#')? 1: 0;
    initSum();
    initSub();
    initGrid();
}

bool isvalid(int i, int j) {
    return i >= 1 && i <= n && j >= 1 && j <= n && g[i][j] == 0;
}

int brute(int si, int sj) {
    int i = si, j = sj;
    if(g[i][j]) return 0;
    //trace("br", i, j);
    fo(k, l) {
        move(i, j, s[k]);
        if(!isvalid(i, j)) {
            //trace(i, j, reach[i-si+off][j-sj+off]);
            return k;
        }
    }

    return l;
}

int solve(int i, int j) {
    int i1 = i + li, j1 = j + lj, i2 = i + hi, j2 = j + hj;
    //if(i1 < 1 || i2 > n || j1 < 1 || j2 > n) return brute(i, j);

    int ocnt = getSum(i1, j1, i2, j2);
    int ans = l;
    //if(ocnt == 0) return l;
    if(isvalid(i1, j1) && isvalid(i2, j2) && (i2 - i1 + 1) + ocnt < si(moves) / 2) {
        //trace("obs", i, j);
    //if(false) {
        //trace(i1, i2, j1, j2);
        rep(ci, i1, i2) {
            for(int cj = nxt[ci][j1]; cj <= j2; cj = nxt[ci][cj+1]) {
                //trace(i1, i2, j1, j2, ci, cj, nxt[ci][cj+1]);
                ans = min(ans, reach[ci-i+off][cj-j+off]);
            }
        }
    } else {
        //return brute(i, j);
        //trace("moves", i, j);
        for(auto cur: moves) {
            int ci = gt(cur, 1) + i, cj = gt(cur, 2) + j;
            if(!isvalid(ci, cj)) {
                ans = gt(cur, 0);
                break;
            }
        }
    }
#ifdef CHECK
    int bans = brute(i, j);
    //trace(i, j, bans, ans);
    assert(ans == bans);
#endif

    return ans;
}


int brute() {
    int ret = 0;
    rep(i, 1, n) rep(j, 1, n) ret ^= brute(i, j);

    return ret;
}

int solve() {
    int ret = 0;
    rep(i, 1, n) rep(j, 1, n) ret ^= solve(i, j);

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
#ifndef TEST
    cin >> t;
#else
    int _t = 0;
    t = 3;
    double pr[t] = {0.001, 0.001, 0.001};
#endif

    while(t--) {
#ifndef TEST
        cin >> l >> n >> s;
        fo(i, n) cin >> grid[i];
#else
        l = 5000; n = 1000;
        fo(i, l) s += "LRDU"[rand() % 4];
        trace(pr[_t]);
        fo(i, n) {
            grid[i] = string(n, '.');
            fo(j, n) if(rand() % 1000000001 < 1000000000 * pr[_t]) grid[i][j] = '#';
        }
        _t++;
#endif
        init();
        int ans = solve();
#ifdef CHECK
        int bans = brute();
        if(ans != bans) {
            trace(ans, bans);
            assert(ans == bans);
        }
#endif

        cout << ans << '\n';
    }
    
	return 0;
}

