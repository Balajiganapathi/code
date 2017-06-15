/* string coder = "Balajiganapathi S"; // Never give up!  */

//#define LOCAL
#ifdef LOCAL
//#   define TRACE
#   define GEN
//#   define TEST
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
constexpr int di[] = {-1, 0, 1, 0, 1, 1, -1, -1};
constexpr int dj[] = {0, -1, 0, 1, 1, -1, 1, -1};
constexpr auto PI  = 3.14159265358979323846L;
constexpr auto oo  = numeric_limits<int>::max() / 2 - 2;
constexpr auto eps = 1e-6;
constexpr auto mod = 1000000007;

/* code */
constexpr int mx_n = 12;
int n, m;
char grid[mx_n][mx_n];

int id(int x, int y) {
    return x * m + y;
}

class Move {
public:
    int t;
    int x1, y1, x2, y2;
    Move() {}
    Move(int _t, int _x1, int _y1, int _x2, int _y2): t(_t), x1(_x1), y1(_y1), x2(_x2), y2(_y2) {}
    ll apply(ll cmask) {
        assert(x1 >= 0 && x1 < n && y1 >= 0 && y1 < m);
        assert(x2 >= 0 && x2 < n && y2 >= 0 && y2 < m);
        trace(cmask, t, x1, y1, x2, y2);
        if(t == 1) assert(abs(x1 - x2) + abs(y1 - y2) == 1);
        else assert((y1 == y2 && abs(x1 - x2) == 2) || (x1 == x2 &&  abs(y1 - y2) == 2));
        assert(is1(cmask, id(x1, y1)));
        assert(!is1(cmask, id(x2, y2)));
        cmask ^= (1ll << id(x1, y1));
        cmask ^= (1ll << id(x2, y2));
        if(t == 2) {
            assert(is1(cmask, id((x1 + x2)/2, (y1 + y2)/2)));
            cmask ^= (1ll << id((x1 + x2)/2, (y1 + y2)/2));
        }

        assert(cmask >= 0);
        return cmask;
    }
};

void disp(ll mask) {
#ifdef TRACE
    fo(i, n) {
        fo(j, m) {
            if(is1(mask, id(i, j))) cout << '*';
            else cout << '.';
        }
        cout << endl;
    }
#endif
}

void dispGrid() {
#ifdef TRACE
    fo(i, n) cout << grid[i] << endl;
    cout << endl;
#endif
}


vector<Move> ans;

int vis[mx_n][mx_n], mark;
ll chmask;

int dfs(int i, int j, int ai, int aj) {
    if(i < 0 || i >= n || j < 0 || j >= m) return 0;
    if(vis[i][j] == mark) return 0;
    if(i == ai && j == aj) return 0;
    if(grid[i][j] == '*') return 1;

    vis[i][j] = mark;
    vi vd = {0,1,2,3};
    random_shuffle(all(vd));
    for(auto d: vd) {
        int ni = i + di[d], nj = j + dj[d];
        if(dfs(ni, nj, ai, aj)) {
            ans.push_back(Move(1, ni, nj, i, j));
            chmask = ans.back().apply(chmask);
            swap(grid[i][j], grid[ni][nj]);
            return 1;
        }
    }

    return 0;
}

int dfs(int i, int j) {
    if(i < 0 || i >= n || j < 0 || j >= m) return 0;
    if(vis[i][j] == mark) return 0;
    if(grid[i][j] == '.') return 1;
    vis[i][j] = mark;
    vi vd = {0,1,2,3};
    random_shuffle(all(vd));
    for(auto d: vd) {
        int ni = i + di[d], nj = j + dj[d];
        if(dfs(ni, nj)) {
            //trace(i, j, ni, nj);
            ans.push_back(Move(1, i, j, ni, nj));
            chmask = ans.back().apply(chmask);
            swap(grid[i][j], grid[ni][nj]);
            return 1;
        }
    }

    return 0;
}

void BringBall(int si, int sj, int ai, int aj) {
    ++mark;
    bool ok = dfs(si, sj, ai, aj);
    assert(ok);
    assert(grid[si][sj] == '*');
}

void MakeEmpty(int si, int sj) {
    ++mark;
    dfs(si, sj);
    if(grid[si][sj] != '.') {
        trace(si, sj);
        dispGrid();
        assert(grid[si][sj] == '.');
    }
}

int countBalls() {
    int cnt = 0;
    fo(i, n) fo(j, m) if(grid[i][j] == '*') ++cnt;
    return cnt;
}
void solve() {
    ans.clear();
    if(n < 3 && m < 3) {
        if(countBalls() == 1) cout << 0 << endl;
        else cout << -1 << endl;
        return;
    }
    ll cmask = 0;
    fo(i, n) fo(j, m) if(grid[i][j] == '*') cmask |= (1 << id(i, j));
    chmask = cmask;
    if(n >= 3) {
        while(countBalls() > 1) {
            BringBall(0, 0, -1, -1);
            BringBall(1, 0, 0, 0);
            MakeEmpty(2, 0);
            ans.push_back(Move(2, 0, 0, 2, 0));
            chmask = ans.back().apply(chmask);
            grid[0][0] = '.';
            grid[1][0] = '.';
            grid[2][0] = '*';
        }
    } else {
        while(countBalls() > 1) {
            BringBall(0, 0, -1, -1);
            BringBall(0, 1, 0, 0);
            MakeEmpty(0, 2);
            ans.push_back(Move(2, 0, 0, 0, 2));
            chmask = ans.back().apply(chmask);
            grid[0][0] = '.';
            grid[0][1] = '.';
            grid[0][2] = '*';
        }
    }

    trace(si(ans));
    cout << si(ans) << endl;
    assert(si(ans) <= 5000);
    disp(cmask);
    fo(i, si(ans)) {
        Move cm = ans[i];
        cout << cm.t << " " << cm.x1+1 << " " << cm.y1+1 << " " << cm.x2+1 << " " << cm.y2+1 << endl;
        cmask = cm.apply(cmask);
        disp(cmask);
    }
    assert(__builtin_popcount(cmask) == 1);
}

int main() {
    int t;
#ifndef GEN
    cin >> t;
#else
    t = 10000;
    int cmask, cn, cm, ei, ej, tot = 1;
    cn = cm = 1; ei = ej = 0;
#endif
    while(t--) {
#ifndef GEN
        cin >> n >> m;
        fo(i, n) cin >> grid[i];
#else
        do {
            n = rand() % 10 + 1;
            m = rand() % 10 + 1;
        } while(n * m >= 31 || n >= 3);
        int ei = rand() % n, ej = rand() % m;
        //int ei = n - 1, ej = m - 1;
        fo(i, n) fo(j, m) grid[i][j] = '*';
        grid[ei][ej] = '.';
#endif

        solve();
    }

    
    
	return 0;
}

