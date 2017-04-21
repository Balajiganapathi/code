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
constexpr int mx_n = 102, mx_m = 1003;
int n, m;

class Ball {
public:
    int i, j;
    int cost;
    bool present;

    bool isPocketed() {
        return !present && (i < 0 || i > n || j < 0 || j > n);
    }
};

class Move {
public:
    int i, j;
    int vi, vj, e;

    Move(int _i, int _j, int _vi, int _vj, int _e) {
        i = _i; j = _j; vi = _vi; vj = _vj; e = _e;
    }
};

void checkHit(int &ci, int &cj, int &vi, int &vj) {
    if(ci == -1) ci = 1, vi = 1;
    if(ci == n + 1) ci = n - 1, vi = -1;
    if(cj == -1) cj = 1, vj = 1;
    if(cj == n + 1) cj = n - 1, vj = -1;
}

bool ishole(int ci, int cj) {
    return (ci == -1 || ci == n + 1) && (cj == -1 || cj == n + 1);
}

class Table {
public:
    Ball balls[mx_m];
    int pos[mx_n][mx_n];
    int score;
    vector<Move> moves;

    void clear() {
        ini(pos, -1);
        score = 0;
        moves.clear();
    }

    void move(int i, int vi, int vj, int e) {
        if(e == 0) return;
        assert(balls[i].present);
        assert(si(moves) <= 4 * m);
        assert(e > 0 && e <= 4 * n);
        int ci = balls[i].i, cj = balls[i].j;
        moves.push_back(Move(ci, cj, vi, vj, e));
        fo(ee, e) {
            pos[ci][cj] = -1;
            ci += vi; cj += vj;
            balls[i].i = ci; balls[i].j = cj;
            if(ishole(ci, cj)) {
                balls[i].present = false;
                score += balls[i].cost;
                break;
            }

            checkHit(ci, cj, vi, vj);

            balls[i].i = ci; balls[i].j = cj;

            if(pos[ci][cj] != -1) {
                balls[i].cost += balls[pos[ci][cj]].cost;
                balls[pos[ci][cj]].present = false;
            }
            pos[ci][cj] = i;
        }
    }
} table;

Table best;
bool first;

void submit(const Table &t) {
    if(first || t.score > best.score) {
        first = false;
        best = t;
    }
    //trace(table.score);
}

void naive(Table table) {
    fo(i, m) if(table.balls[i].present && table.balls[i].cost > 0) {
        if(table.balls[i].present) table.move(i, -1, 0, table.balls[i].i); // move to (0, j);
        if(table.balls[i].present) table.move(i, 0, -1, table.balls[i].j); // Move to (0, 0);
        if(table.balls[i].present) table.move(i, -1, -1, 1); // move to (-1, -1);
    }
    //trace(table.score);
    submit(table);
}

void shootTo(Table table, int hi, int hj) {
    fo(i, m) if(table.balls[i].present && table.balls[i].cost > 0) {
        int ci = table.balls[i].i, cj = table.balls[i].j;
        int di, dj;
        di = (hi < ci? -1: 1);
        dj = (hj < cj? -1: 1);
        if(table.balls[i].present) table.move(i, di, 0, abs(hi - ci) - 1); // move to (0, j);
        if(table.balls[i].present) table.move(i, 0, dj, abs(hj - cj) - 1); // Move to (0, 0);
        if(table.balls[i].present) table.move(i, di, dj, 1); // move to (-1, -1);
    }
    //trace(table.score);
    submit(table);
}

int vis[mx_n][mx_n], pd[mx_n][mx_n], pe[mx_n][mx_n], dist[mx_n][mx_n];
pi prv[mx_n][mx_n];
int mark;
void startFrom(Table &table, int i1, int j1) {
    ++mark;
    queue<pi> q;
    vis[i1][j1] = mark;
    q.emplace(i1, j1);
    while(!q.empty()) {
        auto cur = q.front(); q.pop();
        fo(d, 8) {
            int vi = dx[d], vj = dy[d];
            int ci = i1, cj = j1;
            rep(e, 1, 4 * n) {
                ci += vi; cj += vj;
                if(ishole(ci, cj)) break;
                checkHit(ci, cj, vi, vj);

                if(vis[ci][cj] != mark) {
                    dist[ci][cj] = 1 + dist[cur.fi][cur.se];
                    prv[ci][cj] = mp(cur.fi, cur.se);
                    vis[ci][cj] = mark;
                    pd[ci][cj] = d;
                    pe[ci][cj] = e;
                    q.emplace(ci, cj);
                }
            }
        }
    }
}

void moveTo(Table &table, int i, int ti, int tj) {
    assert(vis[ti][tj] == mark);
    vector<Move> vm;
    int ci = ti, cj = tj;
    fo(j, dist[ti][tj]) {
        vm.push_back(Move(table.balls[i].i, table.balls[i].j, dx[pd[ci][cj]], dy[pd[ci][cj]], pe[ci][cj]));
        auto tmp = prv[ci][cj];
        ci = tmp.fi; cj = tmp.se;
    }
    reverse(all(vm));
    for(auto m: vm) table.move(i, m.vi, m.vj, m.e);
}


void mergeNegs(Table &table) {
    fo(i, m) if(table.balls[i].present && table.balls[i].cost < 0) {
        startFrom(table, table.balls[i].i, table.balls[i].j);
        rep(ci, 0, n) {
            rep(cj, 0, n) {
                if(vis[ci][cj] == mark && table.balls[table.pos[ci][cj]].cost < 0 && dist[ci][cj] <= 4) {
                    moveTo(table, i, ci, cj);
                    break;
                }
            }
            if(!table.balls[i].present) break;
        }
    }
}

void tryAllCorners(Table table) {
    shootTo(table, -1, -1);
    shootTo(table, -1, n + 1);
    shootTo(table, n + 1, -1);
    shootTo(table, n + 1, n + 1);

    mergeNegs(table);
    shootTo(table, -1, -1);
    shootTo(table, -1, n + 1);
    shootTo(table, n + 1, -1);
    shootTo(table, n + 1, n + 1);
}

int main() {
    int t;
#ifndef TEST
    cin >> t;
#else
    t = 10;
    int tot = 0;
#endif
    while(t--) {
        table.clear();
        best.clear();
        first = true;
#ifndef TEST
        cin >> n >> m;
#else
        n = 100; m = rand() % 501 + 500;
        int z1[] = {1, -3, 1, -100};
        int z2[] = {3, 3, 100, 100};
        int zi = rand() % 4;
        int vis[102][102] = {0};
#endif
        fo(i, m) {
#ifndef TEST
            cin >> table.balls[i].i >> table.balls[i].j >> table.balls[i].cost;
#else
            int ci, cj;
            do {
                ci = rand() %  (n + 1);
                cj = rand() %  (n + 1);
            } while(vis[ci][cj]);

            vis[ci][cj] = 1;
            table.balls[i].cost = rand() % (z2[zi] - z1[zi] + 1) + z1[zi];

            table.balls[i].i = ci; table.balls[i].j = cj;
#endif
            table.balls[i].present = true;
            table.pos[table.balls[i].i][table.balls[i].j] = i;
        }

        tryAllCorners(table);

        cout << si(best.moves) << '\n';
        for(Move m: best.moves) {
            cout << m.i << " " << m.j << " " << m.vi << " " << m.vj << " " << m.e << '\n';
        }

#ifdef TEST
        trace(best.score);
        tot += best.score;
#endif
    }

#ifdef TEST
    cerr << "Total score: " << tot << endl;
#endif
    
    
	return 0;
}

