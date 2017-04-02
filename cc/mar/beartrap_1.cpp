/* string coder = "Balajiganapathi S"; // Never give up!  */

//#define LOCAL
#ifdef LOCAL
#   define TRACE
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
constexpr int dx[] = {-1, 0, 1, 0, 1, -1};
constexpr int dy[] = {0, -1, 0, 1, -1, 1};
constexpr auto PI  = 3.14159265358979323846L;
constexpr auto oo  = numeric_limits<int>::max() / 2 - 2;
constexpr auto eps = 1e-6;
constexpr auto mod = 1000000007;

/* code */
constexpr int mx = -1, mx_cells = 1530;
int m;
constexpr int N = 20;

class Cell {
public:
    int r, c;
    Cell(): r(0), c(0) {}
    Cell(int _r, int _c): r(_r), c(_c){}

    bool operator <(const Cell &cell) const {
        return r < cell.r || (r == cell.r && c < cell.c);
    }
};

set<int> borderCells;
int tot;
map<Cell, int> idx;
Cell crev[mx_cells];
int isBorder[mx_cells], blocked[mx_cells];
int dist[mx_cells][mx_cells];
int cdist[mx_cells][mx_cells];
int bdist[mx_cells];

bool isvalid(int r, int c) {
    return abs(r) < N && abs(c) < N;
}

set<Cell> cells;
set<pair<Cell, int>> vis;
vi adj[mx_cells];
int badj[mx_cells];
vi imp;

void calcDist(int s) {
    queue<int> q;
    fo(i, mx_cells) dist[s][i] = oo;
    dist[s][s] = 0;
    q.push(s);
    while(!q.empty()) {
        int cur = q.front(); q.pop();
        for(int nxt:adj[cur]) if(!blocked[nxt]) {
            if(dist[s][nxt] > dist[s][cur] + 1) {
                dist[s][nxt] = dist[s][cur] + 1;
                q.push(nxt);
            }
        }
    }}

void pre() {
    rep(r, -(N-1), N-1) {
        int a, b;
        if(r <= 0) {
            a = -N - r + 1;
            b = N;
        } else {
            a = -N + 1;
            b = N - r;
        }

        re(c, a, b) cells.insert(Cell(r, c));
    }
    for(auto c: cells) {
        idx[c] = tot++;
        crev[idx[c]] = c;
    }
    tot = si(idx);
    for(auto c: cells) {
        fo(d, 6) {
            Cell nxt(c.r + dx[d], c.c + dy[d]);
            if(!cells.count(nxt)) {
                isBorder[idx[c]] = 1;
                borderCells.insert(idx[c]);
            } else {
                adj[idx[c]].push_back(idx[nxt]);
            }
        }
    }

    fo(c, tot) {
        for(auto n: adj[c]) if(isBorder[n]) ++badj[c];
    }

    trace(si(idx), si(borderCells));
#ifdef TRACE
    for(auto c: cells) cerr << "(" << c.r << " " << c.c << ") "; cerr << endl;
#endif

    fo(i, tot) calcDist(i);
    int origin = idx[Cell(0,0)];
    fo(c, tot) if(badj[c] >= 3 || isBorder[c]) imp.push_back(c);
}

int cat;

void calcCatDist(int s) {
    fo(i, mx_cells) cdist[s][i] = oo;
    cdist[s][s] = 0;
    queue<int> q;
    q.push(s);
    while(!q.empty()) {
        int cur = q.front(); q.pop();
        for(int nxt:adj[cur]) if(!blocked[nxt]) {
            if(cdist[s][nxt] > cdist[s][cur] + 1) {
                cdist[s][nxt] = cdist[s][cur] + 1;
                q.push(nxt);
            }
        }
    }
}

bool shouldUse(int nxt, int cur) {
    if(nxt == -1) return true;
    //if(isBorder[cur] != isBorder[nxt]) {
        //if(isBorder[cur]) return cdist[cat][cur] < 3 * cdist[cat][nxt];
        //return cdist[cat][nxt] < 3 * cdist[cat][cur];
    //}
    if(bdist[cur] != bdist[nxt]) return bdist[cur] < bdist[nxt];
    if(isBorder[cur] != isBorder[nxt]) return isBorder[cur] > isBorder[nxt];
    if(badj[cur] != badj[nxt]) return badj[cur] > badj[nxt];
    if(cdist[cat][cur] != cdist[cat][nxt]) return cdist[cat][cur] < cdist[cat][nxt];
    return false;
}

vi getCatMoves() {
    calcCatDist(cat);
    for(int d: adj[cat]) if(!blocked[d]) calcCatDist(d);

    int cnxt = -1;
    vi cmoves;
    for(int b: borderCells) {
        if(cnxt == -1 || cdist[cat][b] < cdist[cat][cnxt]) {
            cnxt = b;
            cmoves.clear();
        }
        if(cdist[cat][b] == cdist[cat][cnxt]) cmoves.push_back(b);
    }

    if(si(cmoves) == 0) return cmoves;
    set<int> ret;
    for(int b: cmoves) {
        for(int ca: adj[cat]) if(!blocked[ca] && cdist[cat][b] == cdist[ca][b] + 1) ret.insert(ca);
    }

    return vi(all(ret));
}

void play() {
#ifdef TEST
    cout << "clear()" << endl;
#endif
    srand(time(NULL));
    cat = idx[Cell(0, 0)];
    ini(blocked, 0);
    string move;
    while(1) {
        trace(cat);
        assert(!isBorder[cat]);
#ifdef TEST
        vi cmoves = getCatMoves();
        if(si(cmoves) == 0) return;
        cat = cmoves[rand() % si(cmoves)];
        cout << "cat(" << crev[cat].r << "," << crev[cat].c << ")" << endl;
#else
        cin >> move;
        if(move == "WIN") return;
        int r, c;
        cin >> r >> c;
        cat = idx[Cell(r, c)];
#endif
        trace(cat);

                int nxt = -1;
        vi pos;
        set<int> consider;
        //consider.insert(all(imp));
        //vi ncmoves = getCatMoves();
        //consider.insert(all(ncmoves));
        fo(i, tot) if(!blocked[i] && i != cat && (badj[i] == 3 || cdist[cat][i] == 5 || (isBorder[i] && cdist[cat][i] <= 5))) consider.insert(i);
        for(int a: adj[cat]) consider.insert(a);

        for(int i: consider) calcCatDist(i);
        for(int i: consider) {
            bdist[i] = oo;
            for(int b: borderCells) if(!blocked[b]) bdist[i] = min(bdist[i], cdist[i][b]);
        }

        for(int b: consider) if(!blocked[b] && cat != b) {
            if(nxt == -1 || shouldUse(nxt, b)) {
                nxt = b;
                pos.clear();
            }
            if(!shouldUse(b, nxt) && !shouldUse(nxt, b)) pos.push_back(b);
        }
        nxt = pos[rand() % si(pos)];
        assert(nxt != -1 && !blocked[nxt] && nxt != cat);
        trace(nxt, dist[nxt][cat]);
        Cell nx = crev[nxt];
#ifdef TEST
        cout << "block(" << nx.r << "," << nx.c << ")" << endl;
#else
        cout << "BLOCK " << nx.r << " " << nx.c << '\n';
        fflush(stdout);
#endif
        
        blocked[nxt] = 1;
    }
}

int main() {
    pre();
    int t;
#ifdef TEST
    t = 10, m = 500;
#else
    cin >> t >> m;
#endif
    while(t--) {
        play();
    }
    
	return 0;
}

