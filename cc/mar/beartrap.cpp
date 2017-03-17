/* string coder = "Balajiganapathi S"; // Never give up!  */

//#define LOCAL
#ifdef LOCAL
#   define TRACE
#   define TEST
//#   define NDEBUG
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
constexpr int dx[] = {-1, 0, 1, 0, 1, -1};
constexpr int dy[] = {0, -1, 0, 1, -1, 1};
constexpr auto PI  = 3.14159265358979323846L;
constexpr auto oo  = numeric_limits<int>::max() / 2 - 2;
constexpr auto eps = 1e-6;
constexpr auto mod = 1000000007;

/* code */
constexpr int mx = -1, mx_cells = 1150;
int m;
constexpr int N = 20;

bool isvalid(int r, int c) {
    return abs(r) < N && abs(c) < N;
}

int tot;
pi crev[mx_cells];
set<pi> cells;
vi adj[mx_cells];
map<pi, int> idx;
int isBorder[mx_cells];
vi border;
int vis[mx_cells], mark;
int dist[mx_cells][mx_cells];

class State {
public:
    bool catMove;
    int cat;
    bitset<mx_cells> blocked;

    int rem() const {
        return m - blocked.count();
    }

    void blockCell(int m) {
        assert(!catMove);
        assert(cat != m);
        assert(blocked[m] == 0);
        blocked[m] = 1;
        catMove = true;
    }

    void catTo(int m) {
        assert(catMove);
        assert(blocked[m] == 0);
        assert(find(all(adj[cat]), m) != adj[cat].end());
        cat = m;
        catMove = false;
    }

    bool winning;
    void dfs(int x) {
        if(winning == false || vis[x] == mark || blocked[x]) return;
        if(isBorder[x]) {
            winning = false;
            return;
        }
        vis[x] = mark;
        for(int y: adj[x]) {
            dfs(y);
            if(!winning) return;
        }
    }

    bool hasWon() {
        if(isBorder[cat]) return false;
        ++mark;
        winning = true;
        dfs(cat);
        return winning;
    }

    bool hasLost() {
        if(isBorder[cat] || blocked.count() >= m) return true;
        int boa, bla;
        boa = bla = 0;
        for(int a: adj[cat]) {
            if(!blocked[a]) {
                ++bla;
                if(isBorder[a]) ++boa;
            }
        }

        if(boa > 1) return true;
        if(bla > rem()+1) return true;
        return false;
    }

    void calcDist(int start) const {
        fo(i, tot) dist[start][i] = oo;
        //if(blocked[start]) return;
        queue<int> q;
        q.push(start);
        dist[start][start] = 0;
        while(!q.empty()) {
            auto cur = q.front(); q.pop();
            for(int a: adj[cur]) if(!blocked[a] && dist[start][a] == oo) {
                dist[start][a] = dist[start][cur] + 1;
                q.push(a);
            }
        }
    }

    vi getCatMoves() {
        assert(catMove);
        calcDist(cat);
        for(int a: adj[cat]) if(!blocked[a]) calcDist(a);

        vi nearest;
        int minDist = oo;
        for(int b: border) if(!blocked[b]) {
            if(dist[cat][b] < minDist) {
                minDist = dist[cat][b];
                nearest.clear();
            }
            if(dist[cat][b] == minDist) nearest.push_back(b);
        }

        vector<pi> v;
        for(int a: adj[cat]) if(!blocked[a]) {
            for(int b: nearest) {
                if(dist[cat][b] == dist[a][b] + 1) {
                    int ac = 0;
                    for(int aa: adj[a]) if(!blocked[aa]) ++ac;
                    v.push_back(mp(-ac, a));
                    break;
                }
            }
        }

        vi catMoves;
        sort(all(v));
        for(auto x: v) catMoves.push_back(x.se);

        return catMoves;
    }

    bool operator ==(const State &s) const {
        return s.cat == cat &&
            s.blocked == blocked &&
            s.catMove == catMove;
    }
} global;

namespace std {
  template <>
  struct hash<State> {
    size_t operator()(const State& s) const {
        size_t hcat = hash<int>()(s.cat);
        size_t hblocked = hash<bitset<mx_cells>>()(s.blocked);
        //for(int x: s.blocked) hblocked ^= hash<int>()(x);
        size_t hmove = hash<bool>()(s.catMove);

        return hcat ^ hblocked ^ hmove;
    }
  };
}

vi getNearest(const State &s) {
    int minDist = oo;
    vi nearest;
    for(int i: border) if(!s.blocked[i]) {
        if(dist[s.cat][i] < minDist) {
            minDist = dist[s.cat][i];
            nearest.clear();
        }
        if(dist[s.cat][i] == minDist) nearest.push_back(i);
    }

    return nearest;
}

vi genMoves(const State &s) {
    s.calcDist(s.cat);
    vi moves;
    vi nearest = getNearest(s);

    if(si(nearest) > 13) {
        int nac = -oo, na = -1;
        for(int a: adj[s.cat]) if(!s.blocked[a]) {
            s.calcDist(a);
            int cac = 0;
            for(int b: nearest) {
                if(dist[a][b] == dist[s.cat][b] - 1) {
                    ++cac;
                }
            }
            if(na == -1 || cac > nac) {
                nac = cac;
                na = a;
            }
        }
        moves.push_back(na);
    } else if(si(nearest) > 6) {
        int nbc = 0, nb = -1;
        for(int bc: nearest) {
            s.calcDist(bc);
            int cbc = 0;
            for(int bn: nearest) cbc = max(cbc, dist[bc][bn]);
            if(nb == -1 || cbc < nbc) {
                nbc = cbc;
                nb = bc;
            }
            //trace(bc, cbc);
        }
        //trace(nb, nbc);
        moves.push_back(nb);
    } else if(si(nearest) > 1) {
        int nbc = 0, nb = -1;
        for(int bc: nearest) {
            s.calcDist(bc);
            int cbc = 0;
            for(int a: adj[bc]) if(s.blocked[a]) ++cbc;
            if(nb == -1 || cbc < nbc) {
                nbc = cbc;
                nb = bc;
            }
            //trace(bc, cbc);
        }
        //trace(nb, nbc);
        moves.push_back(nb);
    } else {
        int nr = nearest.front();
        moves = nearest;
        s.calcDist(nr);
        if(s.rem() > 5) {
            fo(i, tot) if(s.cat != i && !s.blocked[i] && i != nr && (dist[nr][i] <= 3 && dist[s.cat][i] <= 3)) moves.push_back(i);
        } else if(s.rem() > 3) {
            fo(i, tot) if(s.cat != i && !s.blocked[i] && i != nr && (dist[nr][i] <= 3 && dist[s.cat][i] <= 1)) moves.push_back(i);
        } else {
            fo(i, tot) if(s.cat != i && !s.blocked[i] && i != nr) {
                //if(dist[nr][i] >= 2 && dist[nr][i] <= 3 && dist[s.cat][i] <= 3) moves.push_back(i);
                if(dist[nr][i] <= 2 || dist[s.cat][i] <= 1) moves.push_back(i);
            }
        }
    }
    random_shuffle(all(moves));
    //moves.resize(unique(all(moves)) - moves.begin());
    //trace(si(nearest), s.cat, si(moves), s.blocked.count(), moves);

    return moves;
}

int evals;

unordered_map<State, int> cache;

int play(State state) {
    if(cache.find(state) != cache.end()) {
        return cache[state];
    }
    int ret;
    if(++evals % 5001 == 0) {
        trace(evals);
        trace(state.catMove, state.cat, state.blocked.count());
    }
    //if(evals > 50) exit(0);

    if(state.hasWon()) {
        trace("WIN", state.catMove, state.cat, state.blocked.count());
        return oo;
    }

    if(state.hasLost()) {
        //trace("LOST", state.catMove, state.cat, isBorder[state.cat], state.blocked);
        return -oo;
    }

    if(state.catMove) {
        vi catMoves = state.getCatMoves();
        //random_shuffle(all(catMoves));
        //trace(catMoves);
        ret = oo;
        for(int nxt: catMoves) {
            State cur = state;
            cur.catTo(nxt);
            int mv = play(cur);
            if(mv == -oo) {
                ret = -oo;
                break;
            }
        }
    } else {
        ret = -oo;
        vi moves = genMoves(state);
        //trace(moves);
        for(auto nxt: moves) {
            State cur = state;
            cur.blockCell(nxt);
            int mv = play(cur);
            if(mv != -oo) {
                ret = nxt;
                break;
            }
        }
    }
    cache[state] = ret;
    return ret;
}

int getNextMove() {
    int nxt;
    vi moves = genMoves(global);
    if(si(moves) == 1) {
        nxt = moves.front();
        trace(si(getNearest(global)));
    } else {
        nxt = play(global);
    }
    return nxt;
}

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

        re(c, a, b) cells.insert(mp(r, c));
    }
    for(auto c: cells) {
        idx[c] = tot++;
        crev[idx[c]] = c;
    }
    tot = si(idx);
    for(auto c: cells) {
        fo(d, 6) {
            pi nxt(c.fi + dx[d], c.se + dy[d]);
            if(!cells.count(nxt)) {
                if(!isBorder[idx[c]]) {
                    isBorder[idx[c]] = 1;
                    border.push_back(idx[c]);
                }
            } else {
                adj[idx[c]].push_back(idx[nxt]);
            }
        }
    }
}

void play() {
#ifdef TEST
    cout << "clear()" << endl;
#endif
    global = State();
    global.catMove = true;
    global.cat = idx[mp(0, 0)];
    while(1) {
        int cat;
#ifdef TEST
        vi pos = global.getCatMoves();
        if(si(pos) == 0) return;
        assert(global.blocked.count() <= m);
        cat = pos[rand() % si(pos)];
        cout << "cat(" << crev[cat].fi << ", " << crev[cat].se << ")" << endl;
#else
        string move;
        cin >> move;
        if(move == "WIN") return;
        int r, c;
        cin >> r >> c;
        cat = idx[mp(r, c)];
#endif

        global.catTo(cat);

        int nxt = getNextMove();
        assert(nxt >= 0 && nxt < tot);
        pi nx = crev[nxt];
        global.blockCell(nxt);

#ifdef TEST
        cout << "block(" << crev[nxt].fi << ", " << crev[nxt].se << ")" << endl;
#else
        cout << "BLOCK " << crev[nxt].fi << " " << crev[nxt].se << endl;
#endif
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    pre();
    cache.reserve(1000000);
    trace(tot);
    int t;
#ifdef TEST
    t = 100, m = 20;
#else
    cin >> t >> m;
    m = min(m, 20);
#endif
    while(t--) {
        play();
    }
    
	return 0;
}

