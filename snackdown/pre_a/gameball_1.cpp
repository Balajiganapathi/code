/* string coder = "Balajiganapathi S"; // Never give up!  */

//#define LOCAL
#ifdef LOCAL
#   define TRACE
//#   define GEN
#   define TEST
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
constexpr int di[] = {-1, 0, 1, 0, 1, 1, -1, -1};
constexpr int dj[] = {0, -1, 0, 1, 1, -1, 1, -1};
constexpr auto PI  = 3.14159265358979323846L;
constexpr auto oo  = numeric_limits<int>::max() / 2 - 2;
constexpr auto eps = 1e-6;
constexpr auto mod = 1000000007;

/* code */
constexpr int mx_n = 11;
constexpr int mx_mask = 20;
#define prev adsfasdfdsa
int n, m;
char grid[mx_n][mx_n];
int dp[(1 << mx_mask)];

int id(int x, int y) {
    return x * m + y;
}

class Move {
public:
    int t;
    int x1, y1, x2, y2;
    Move() {}
    Move(int _t, int _x1, int _y1, int _x2, int _y2): t(_t), x1(_x1), y1(_y1), x2(_x2), y2(_y2) {}
    int apply(int cmask) {
        cmask ^= (1 << id(x1, y1));
        cmask ^= (1 << id(x2, y2));
        if(t == 2) {
            cmask ^= (1 << id((x1 + x2)/2, (y1 + y2)/2));
        }

        return cmask;
    }
};

Move prev[(1 << mx_mask)];

void disp(int mask) {
    fo(i, n) {
        fo(j, m) {
            if(is1(mask, id(i, j))) cout << '*';
            else cout << '.';
        }
        cout << endl;
    }
}

class State {
public:
    int mask, d;
    State(int _m, int _d): mask(_m), d(_d) {}
    bool operator <(const State &s) const {
        return d > s.d;
    }
};

int solve(int smask) {
    fo(i, (1 << (n * m))) dp[i] = oo;

    priority_queue<State> pq;
    pq.push(State(smask, 0));
    int cret = oo;

    while(!pq.empty()) {
        auto cur = pq.top(); pq.pop();
        int mask = cur.mask, d = cur.d;
        if(dp[mask] < d) continue;

        fo(i, n) fo(j, m) {
            int idx = id(i, j);
            if(is1(mask, idx)) continue;
            fo(d, 4) {
                int ni = i + di[d], nj = j + dj[d];
                if(ni < 0 || ni >= n || nj < 0 || nj >= m) continue;
                int nidx = id(ni, nj);
                
                if(is1(mask, nidx)) {
                    int nmask = (mask ^ (1 << nidx) ^ (1 << idx));
                    trace(mask, idx, nidx, d + 1, dp[nmask], nmask);
                    if(dp[nmask] > d + 1) {
                        dp[nmask] = d + 1;
                        prev[nmask] = Move(1, ni, nj, i, j);
                        pq.push(State(nmask, d + 1));
                    }

                    int pi = ni + di[d], pj = nj + dj[d];
                    if(pi < 0 || pi >= n || pj < 0 || pj >= m) continue;
                    int pidx = id(pi, pj);
                    if(is1(mask, pidx)) {
                        int nmask = (mask ^ (1 << idx) ^ (1 << pidx) ^ (1 << nidx));
                        trace(mask, idx, nidx, pidx, d + 1, dp[nmask], nmask);

                        if(dp[nmask] > d + 1) {
                            dp[nmask] = d + 1;
                            prev[nmask] = Move(2, pi, pj, i, j);
                            pq.push(State(nmask, d + 1));
                        }
                    }

                }
            }
        }
    }

    fo(i, n) fo(j, m) {
        int mask = 1 << id(i, j);
        if(dp[mask] >= oo) continue;
        return mask;
    }
    return -1;
}

void solve() {
    ini(dp, -1);
    int cmask = 0;
    fo(i, n) fo(j, m) if(grid[i][j] == '*') cmask |= (1 << id(i, j));
    disp(cmask);
    int amask = solve(cmask);
    trace(cmask, amask, dp[cmask]);
    if(amask == -1) {
        cout << -1 << endl;
        return;
    }

    int ans = dp[amask];
    vector<Move> moves;
    disp(amask);
    fo(i, ans) {
        trace(amask, dp[amask]);
        trace(prev[amask].t, id(prev[amask].x1, prev[amask].y1), id(prev[amask].x2, prev[amask].y2));
        moves.push_back(prev[amask]);
        amask = moves.back().apply(amask);
    disp(amask);
    }
    reverse(all(moves));

    cout << ans << endl;
    disp(cmask);
    fo(i, ans) {
        Move cm = moves[i];
        cout << cm.t << " " << cm.x1 << " " << cm.y1 << " " << cm.x2 << " " << cm.y2 << endl;
        cmask = cm.apply(cmask);
        disp(cmask);
    }
}

int main() {
    int t;
#ifndef GEN
    cin >> t;
#else
    t = 100;
    int cmask, cn, cm, ei, ej, tot = 1;
    cn = cm = 1; ei = ej = 0;
#endif
    while(t--) {
#ifndef GEN
        cin >> n >> m;
        fo(i, n) cin >> grid[i];
#else
        n = cn; m = cm;
        fo(i, n) fo(j, m) grid[i][j] = '*';
        grid[ei][ej] = '.';
        if(++ej == cm) {++ei; ej = 0; }
        if(ei == cn) {++cm; ei = ej = 0;}
        if(cn * cm > tot) {cm = 1; ++cn;}
        if(cn * cm > tot) {++tot;}
        if(tot > 20) {
            cn = cm = 1;
            tot = 1;
        }
#endif

#ifdef TEST
        solve();
#endif
    }

    
    
	return 0;
}

