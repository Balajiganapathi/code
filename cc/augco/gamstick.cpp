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
#define j1 _adsfasdfasd

/* constants */
constexpr int di[] = {-1, 0, 1, 0, 1, 1, -1, -1};
constexpr int dj[] = {0, -1, 0, 1, 1, -1, 1, -1};
constexpr auto PI  = 3.14159265358979323846L;
constexpr auto oo  = numeric_limits<int>::max() / 2 - 2;
constexpr auto eps = 1e-6;
constexpr auto mod = 1000000007;

/* code */
constexpr int mx = -1;
ll n, i1, j1, i2, j2;

int solve(int i1, ll j1, int i2, ll j2) {
    ll m1, m2;
    if(n % 2 == 0) m1 = n/2, m2 = n/2+1;
    else m1 = m2 = n/2+1;
    trace(n, m1, m2);

    if(j1 == j2) return 0;

    ll d1 = 0, d2 = 0, bd1 = oo, bd2 = oo;
    vi res;
    if(j1 <= m1 && j2 <= m1) {
        d1 = m2 - j1, d2 = m2 - j2;
        bd1 = m1 - j1;
        bd2 = m1 - j2;
        trace(d1, d2, bd1, bd2);

        if(i1 == i2) {
            if(d1 <= bd2) res.push_back(1);
            else if(d2 <= bd1-1) res.push_back(2);
            else res.push_back(0);
        } else {
            if(d1  < bd2) res.push_back(1);
            else if(d2  < bd1-1) res.push_back(2);
            else res.push_back(0);
        }


    }

    if(j1 >= m2 && j2 >= m2) {
        d1 = j1 - m1, d2 = j2 - m1;
        bd1 = j1 - m2;
        bd2 = j2 - m2;
        trace(d1, d2, bd1, bd2);

        if(i1 == i2) {
            if(d1 <= bd2) res.push_back(1);
            else if(d2 <= bd1-1) res.push_back(2);
            else res.push_back(0);
        } else {
            if(d1  < bd2) res.push_back(1);
            else if(d2  < bd1-1) res.push_back(2);
            else res.push_back(0);
        }


    }

    if(j1 <= m1 && j2 >= m2) {
        trace("1");
        d1 = m2 - j1, d2 = j2 - m1;
        bd1 = m1 - j1;
        bd2 = j2 - m2;
        trace(d1, d2, bd1, bd2);

        if(i1 == i2) {
            if(d1 <= bd2) res.push_back(1);
            else if(d2 <= bd1-1) res.push_back(2);
            else res.push_back(0);
        } else {
            if(d1  < bd2) res.push_back(1);
            else if(d2  < bd1-1) res.push_back(2);
            else res.push_back(0);
        }


    }

    if(j2 <= m1 && j1 >= m2) {
        d1 = j1 - m1, d2 = m2 - j2;
        bd1 = j1 - m2;
        bd2 = m1 - j2;
        trace(d1, d2, bd1, bd2);

        if(i1 == i2) {
            if(d1 <= bd2) res.push_back(1);
            else if(d2 <= bd1-1) res.push_back(2);
            else res.push_back(0);
        } else {
            if(d1  < bd2) res.push_back(1);
            else if(d2  < bd1-1) res.push_back(2);
            else res.push_back(0);
        }


    }

    trace(res);
    if(count(all(res), 1)) return 1;
    if(count(all(res), 0)) return 0;
    if(si(res) > 0) return 2;


    return 0;
}

constexpr int bx_it = 15, bx_n = 6;
constexpr int bx_mask = 730 * 730;

int get(int grid[2][bx_n]) {
    int ret = 0;
    fo(i, 2) {
        //fo(j, n) cout << grid[i][j]; cout << endl;
    }
    for(int i = 2 * n - 1; i >= 0; --i) {
        int ni = i / n, nj = i % n;
        assert(grid[ni][nj] >= 0 && grid[ni][nj] < 3);
        ret = ret * 3 + grid[ni][nj];
    }

    return ret;
}

char state[bx_it][bx_mask][2][bx_n][2][bx_n];
int solve(int iter, int mask, int i1, int j1, int i2, int j2) {
    if(iter >= bx_it) return 0;
    //trace(iter, mask, i1, j1, i2, j2);
    assert(iter < bx_it);
    assert(mask >= 0 && mask < bx_mask);
    assert(i1 < 2 && i2 < 2 && j1 < bx_n && j2 < bx_n);
    char &ret = state[iter][mask][i1][j1][i2][j2];
    if(ret != -1) return ret;

    int p = (iter % 2 == 0? 1: 2);

    int tmp = mask;
    int grid[2][bx_n];
    int c[3] = {0};
    fo(i, 2 * n) {
        int ni = i / n, nj = i % n;
        grid[ni][nj] = tmp % 3;
        //trace(i, tmp % 3);
        ++c[grid[ni][nj]];
        tmp /= 3;
    }
    assert(get(grid) == mask);
    if(c[1] >= n+1) return ret = 1;
    if(c[2] >= n+1) return ret = 2;

    if(p == 1) {
        fo(d, 8) {
            int ni = i1 + di[d], nj = j1 + dj[d];
            if(ni < 0 || ni > 1 || nj < 0 || nj >= n || grid[ni][nj] == 3-p) continue;
            int tg = grid[ni][nj];
            grid[ni][nj] = p;
            int ns = solve(iter+1, get(grid), ni, nj, i2, j2);
            grid[ni][nj] = tg;

            if(ns == p) ret = p;
            else if(ret != p && ns == 0) ret = 0;
            else if(ret == -1) ret = ns;
        }
    } else {
        fo(d, 8) {
            int ni = i2 + di[d], nj = j2 + dj[d];
            if(ni < 0 || ni > 1 || nj < 0 || nj >= n || grid[ni][nj] == 3-p) continue;
            int tg = grid[ni][nj];
            grid[ni][nj] = p;
            int ns = solve(iter+1, get(grid), i1, j1, ni, nj);
            grid[ni][nj] = tg;

            if(ns == p) ret = p;
            else if(ret != p && ns == 0) ret = 0;
            else if(ret == -1) ret = ns;
        }
    }

    if(ret == -1) ret = 0;

    return ret;
}

int main() {
    string outcomes[] = {"Draw", "Miron", "Slava"};
    int t;

#ifndef TEST
    cin >> t;
#else
    t = 1000;
#endif
    while(t--) {
#ifndef TEST
        cin >> n >> i1 >> j1 >> i2 >> j2;
#else
        n = bx_n - rand() % 2;
        i1 = rand() % 2 + 1, j1 = rand() % n + 1;
        i2 = i1; j2 = j1;
        while(i1 == i2 && j1 == j2) {
            i2 = rand() % 2 + 1, j2 = rand() % n + 1;
        }
#endif

        int x = solve(i1, j1, i2, j2);
        cout << outcomes[solve(i1, j1, i2, j2)] << '\n';

#ifdef TEST
        ini(state, -1);
        int grid[2][bx_n] = {0};
        grid[i1-1][j1-1] = 1;
        grid[i2-1][j2-1] = 2;
        int bx = solve(0, get(grid), i1-1, j1-1, i2-1, j2-1);
        trace(n, i1, j1, i2, j2, x, bx);
        assert(bx == x);
#endif
    }
    
    
	return 0;
}

