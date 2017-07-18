/* string coder = "Balajiganapathi S"; // Never give up!  */

//#define LOCAL
#ifdef LOCAL
#   define TRACE
#   define TEST
#   define CHECK
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
constexpr int di[] = {-2, -2, -1, -1, 1, 1, 2, 2};
constexpr int dj[] = {-1, 1, -2, 2, -2, 2, -1, 1};
constexpr auto PI  = 3.14159265358979323846L;
constexpr auto oo  = numeric_limits<int>::max() / 2 - 2;
constexpr auto eps = 1e-6;
constexpr auto mod = 1000000007;

/* code */
constexpr int mx_n = 55, mx_mask = (1 << 12) + 100;
int dp[mx_mask][mx_n];
int n, m;

void resolve(int cells[2][3], int mask) {
    fo(i, 2 * n) {
        cells[i/n][i%n] = mask % 2;
        mask /= 2;
    }
}

int getmask(int cells[2][3]) {
    int mask = 0;
    for(int j = 1; j >= 0; --j) for(int i = n - 1; i >= 0; --i) {
        mask = mask * 4 + cells[j][i];
    }

    assert(mask < mx_mask);
    return mask;
}

void initial(int cells[2][3], int col[3]) {
    fo(i, n) col[i] = 0;
    fo(j, 2) {
        fo(i, n) if(cells[j][i] & 1) {
            fo(d, 8) {
                int ni = i + di[d], nj = j + dj[d];
                if(nj == 2 && ni >= 0 && ni < n) {
                    col[ni] |= 2;
                }
            }
        }
    }
}

bool isok(int col[3]) {
    fo(i, n) if(col[i] == 0) return false;
    return true;
}


bool fill_back(int cells[2][3], int ncells[2][3], int ncol[3]) {
    fo(j, 2) fo(i, n) ncells[j][i] = cells[j][i];
    fo(i, n) if(ncol[i] == 1) {
        fo(d, 8) {
            int ni = i + di[d], nj = 2 + dj[d];
            if(nj >= 0 && nj < 2 && ni >= 0 && ni < n) {
                if(cells[nj][ni] & 1) return false;
                ncells[nj][ni] |= 2;
            }
        }
    }
    if(!isok(ncells[0])) return false;
    fo(i, n) ncells[0][i] = ncells[1][i];
    fo(i, n) ncells[1][i] = ncol[i];

    return true;
}

int solve(int mask, int j) {
    int cells[2][3];
    resolve(cells, mask);
    assert(getmask(cells) == mask);
    trace(mask, j);
#ifdef TRACE
    fo(i, n) {
        fo(j, 2) {
            cerr << cells[j][i];
        }
        cerr << endl;
    }
#endif
    int &ret = dp[mask][j];
    if(ret != -1) return ret;

    if(j == m) {
        trace(mask);
        if(!isok(cells[0])) ret = oo;
        else if(!isok(cells[1])) ret = oo;
        else ret = 0;
    } else {

        ret = oo;

        int col[3];
        initial(cells, col);
        fo(cur, (1 << n)) {
            int ncol[3], ncells[2][3];
            fo(i, n) ncol[i] = col[i];
            fo(i, n) if(is1(cur, i)) {
                ncol[i] |= 1;
            }
            if(fill_back(cells, ncells, ncol)) {
                ret = min(ret, __builtin_popcount(cur) + solve(getmask(ncells), j + 1));
            }
        }
    }

    trace(mask, j, ret);
    return ret;
}

int solve() {
    int cells[2][3];
    fo(j, 2) fo(i, n) cells[j][i] = 2;
    return solve(getmask(cells), 0);
}

int brute() {
    assert(n * m <= 26);
    int cells[mx_n][mx_n];
    int ans = oo;
    fo(mask, (1 << n * m)) {
        bool ok = true;
        if(__builtin_popcount(mask) > ans) continue;
        ini(cells, 0);
        fo(j, m) {
            fo(i, n) if(is1(mask, (i * m + j))) {
                cells[i][j] |= 1;
                fo(d, 8) {
                    int ni = i + di[d], nj = j + dj[d];
                    if(0 <= ni && ni < n && 0 <= nj && nj < m) cells[ni][nj] |= 2;
                }
                if(j >= 3 && cells[i][j-3] == 0) {ok = false; break;}
            }
            if(!ok) break;
        }
        if(ok) fo(i, n) fo(j, m) if(cells[i][j] == 0) ok = false;
        if(ok) ans = min(ans, __builtin_popcount(mask));
    }

    return ans;
}

int main() {
    int t;
#ifdef TEST
    t = 100;
#else
    cin >> t;
#endif
    while(t--) {
#ifdef TEST
        n = rand() % 3 + 1;
        int lm = 26 / n;
        m = rand() % lm + 1;
#else 
        cin >> n >> m;
#endif
        ini(dp, -1);
        int ans = solve();
        cout << ans << endl;
#ifdef CHECK
        int bans = brute();
        if(ans != bans) {
            trace(n, m, bans, ans);
            assert(ans == bans);
        }
#endif
    }
    
    
	return 0;
}

