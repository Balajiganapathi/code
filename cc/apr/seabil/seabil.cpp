
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
constexpr int mx_n = 105, mx_m = 1003;
int n, m;

class Vec {
public:
    int vi, vj;
    Vec() {};
    Vec(int _vi, int _vj) {
        vi = _vi; vj = _vj;
    }

    void inv() {
        vi *= -1; vj *= -1;
    }
};

Vec dirs[] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
bool maindiag;

class Pos {
public:
    int i, j;

    Pos() {}

    Pos(int _i, int _j) {
        i = _i; j = _j;
    }

    bool operator <(const Pos &p) const {
        if(i == p.i) return j < p.j;
        return i < p.i;
    }

    void apply(const Vec &v) {
        i += v.vi; j += v.vj;
    }

    bool ispocket() const {
        return (i == 0 || i == n + 2) && (j == 0 || j == n + 2);
    }

    bool operator !=(const Pos &p) const {
        return i != p.i && j != p.j;
    }

    bool operator ==(const Pos &p) const {
        return i == p.i && j == p.j;
    }

    int distFromCenter() const {
        int di = (i - n/2), dj = (j - n/2);
        return di * di + dj * dj;
    }

    int distFrom(const Pos &p) const {
        int di = (i - p.i), dj = (j - p.j);
        return di * di + dj * dj;
    }

    bool isdiagonal() const {
        if(maindiag) return i == j;
        return i == j || i + j == n + 2;
    }

    bool neardiagonal() const {
        if(maindiag) return diff() <= 3;
        return min(diff(), diff1()) <= 3;
    }

    int distFromDiagonal() const {
        if(maindiag) return diff();
        return min(diff(), diff1());
    }

    int diff1() const {
        return min(abs(n + 2 - j - i), abs(n + 2 - i - j));
    }

    int diff() const {
        return abs(i - j);
    }

    bool nearEdge() const {
        int l = 10;
        return i <= l || (n + 2 - i) <= l || j <= l || (n + 2 - j) <= l;
    }

};

class Ball {
public:
    Pos p;
    int cost;
    int debt;
    bool present;
    ll tscore;

    bool isNeg() const {
        return cost < 0;
    }

    bool isLargeNeg() const {
        return cost <= -2;
    }

    bool isPos() const {
        return cost > 0;
    }

    bool isLargePos() const {
        return cost > 2;
    }

    void init() {
        p.i++;
        p.j++;
        present = true;
        debt = 0;
    }
    
    void replacing(Ball &b) {
        debt += b.debt;
        cost += b.cost;
        b.present = false;
    }

    int distFrom(const Ball& b) const {
        return p.distFrom(b.p);
    }
};

class Move {
public:
    Pos p;
    Vec v;
    int e;

    Move() {}

    Move(Pos _p, Vec _v, int _e) {
        p = _p; v = _v; e = _e;
    }
};

void checkHit(Pos &p, Vec &v) {
    if(p.ispocket()) return;
    if(p.i == 0) p.i = 2, v.vi = 1;
    if(p.i == n + 2) p.i = n, v.vi = -1;
    if(p.j == 0) p.j = 2, v.vj = 1;
    if(p.j == n + 2) p.j = n, v.vj = -1;
}

class Table {
public:
    Ball balls[mx_m];
    int at[mx_n][mx_n];
    int score;
    vector<Move> moves;

    void clear() {
        ini(at, -1);
        score = 0;
        moves.clear();
    }

    void move(int i, Vec v, int e) {
        assert(balls[i].present);
        move(Move(balls[i].p, v, e));
    }

    void move(Move move) {
        if(move.e == 0) return;
        --score;

        assert(si(moves) < 4 * m);
        assert(move.e > 0 && move.e <= 4 * n);
        assert(move.p.i >= 1 && move.p.i <= n + 1);
        assert(move.p.j >= 1 && move.p.j <= n + 1);
        assert(at[move.p.i][move.p.j] != -1);
        assert(-1 <= move.v.vi && move.v.vi <= 1);
        assert(-1 <= move.v.vj && move.v.vj <= 1);

        Pos c = move.p;
        Vec v = move.v;

        moves.push_back(move);
        int i = at[move.p.i][move.p.j];
        ++balls[i].debt;

        fo(ee, move.e) {
            at[c.i][c.j] = -1;
            c.apply(v);
            balls[i].p = c;

            if(c.ispocket()) {
                balls[i].present = false;
                score += balls[i].cost;
                break;
            }

            checkHit(c, v);

            balls[i].p = c;

            if(hasBall(c)) balls[i].replacing(getBall(c));

            at[c.i][c.j] = i;
        }
    }

    Ball& getBall(const Pos &p) {
        assert(at[p.i][p.j] != -1);
        assert(balls[at[p.i][p.j]].present);
        return balls[at[p.i][p.j]];
    }

    bool hasBall(const Pos &p) const {
        //if(p.i < 0 || p.i > n + 2 || p.j < 0 || p.j > n + 2) return false;
        return at[p.i][p.j] != -1 && balls[at[p.i][p.j]].present;
    }

    bool hasNeg() const {
        fo(i, m) if(balls[i].present && balls[i].isNeg()) return true;
        return false;
    }

    int remPos() const {
        int ret = 0;
        fo(i, m) if(balls[i].present && balls[i].isPos()) ++ret;
        return ret;
    }

    int getMinCost() const {
        int ret = oo;
        fo(i, m) ret = min(ret, balls[i].cost);
        return ret;
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


class State {
public:
    Pos cur;
    int vis, dist;
    Move prev;
    int ts;


    State() {}
    State(Pos _cur, int _vis, int _dist, Move _prev) {
        ts = 0;
        cur = _cur; vis = _vis; dist = _dist; prev = _prev;
    }

    bool operator <(const State &s) const {
        //if(dist != s.dist) return dist < s.dist;
        if(ts != s.ts) return ts > s.ts;
        //if(prev.e != s.prev.e) return prev.e > s.prev.e;
        return false;
    }
} states[mx_n][mx_n];
int mark;
int vis[mx_n][mx_n], vmark;

auto revcompare = [](const State &s1, const State &s2) { return s2 < s1;};

void addMoves(Table &table, Pos start) {
    stack<Move> moves;
    Pos cur = start;
    //trace(table.balls[table.at[start.i][start.j]].cost);
    while(1) {
        State &cstate = states[cur.i][cur.j];
        assert(cstate.vis == mark);
        if(cstate.dist == 0) break;
        moves.push(cstate.prev);
        cur = cstate.prev.p;
    }
    while(!moves.empty()) {
        table.move(moves.top());
        moves.pop();
    }
    //trace(start.i, start.j, si(moves), table.score);
}

int tries;
bool pocketBall(Table &table, const Pos &start, int lim) {
    ++mark;
    queue<State> q;
    states[start.i][start.j] = State(start, mark, 0, {start, {0,0}, 0});
    q.push(states[start.i][start.j]);
 
    assert(table.hasBall(start));
    while(!q.empty()) {
        auto s = q.front(); q.pop();
        auto cur = s.cur;
        //trace(start.i, start.j, cur.i, cur.j, finish(cur), skip(cur));
        if(cur.ispocket()) {
            addMoves(table, cur);
            return true;
        }
        if(s.dist >= lim) continue;

        vector<State> tmp;
        int ts = 0;
        fo(i, 8) {
            Pos p = cur;
            Vec v = dirs[i];
            ++vmark;
            rep(e, 1, 4 * n) {
                p.apply(v);
                checkHit(p, v);
 
                if(states[p.i][p.j].vis == mark) break;
                if(table.hasBall(p) && table.getBall(p).isNeg()) break;
                if(table.hasBall(p) && vis[p.i][p.j] != vmark) ts += 1; //table.getBall(p).cost;
                vis[p.i][p.j] = vmark;
 
                auto nxt = State(p, mark, states[cur.i][cur.j].dist + 1, Move(cur, dirs[i], e));
                nxt.ts = ts;

                tmp.push_back(nxt);
                if(p.ispocket()) break;
            }
        }

        sort(all(tmp));
        for(auto cur: tmp) {
            auto p = cur.cur;
            if(states[p.i][p.j].vis == mark) continue;
            states[p.i][p.j] = cur;
            q.push(cur);
        }

    }

    return false;
}

bool moveNeg(Table &table, const Pos &start, int lim) {
    ++mark;
    queue<State> q;
    states[start.i][start.j] = State(start, mark, 0, {start, {0,0}, 0});
    q.push(states[start.i][start.j]);
 
    assert(table.hasBall(start));
    while(!q.empty()) {
        auto s = q.front(); q.pop();
        auto cur = s.cur;
        //trace(start.i, start.j, cur.i, cur.j, finish(cur), skip(cur));
        if(((!table.hasBall(cur) || !table.getBall(cur).isPos())) && cur != start && !cur.neardiagonal()) {
            addMoves(table, cur);
            return true;
        }
        if(cur.ispocket()) {
            continue;
            //addMoves(table, cur);
            //return true;
        }
        if(states[cur.i][cur.j].dist >= lim) continue;
 
        vector<State> tmp;
        fo(i, 8) {
            Pos p = cur;
            Vec v = dirs[i];
            int ts = 0;
            ++vmark;
            rep(e, 1, 4 * n) {
                p.apply(v);
                checkHit(p, v);
 
                State nxt = State(p, mark, states[cur.i][cur.j].dist + 1, Move(cur, dirs[i], e));
                if(states[p.i][p.j].vis == mark) break;
                if(table.hasBall(p) && table.getBall(p).isPos()) break;
                if(p.ispocket()) break;

                if(table.hasBall(p) && vis[p.i][p.j] != vmark) ts += 1; //-table.getBall(p).cost;
                vis[p.i][p.j] = vmark;
 
                tmp.push_back(nxt);
            }
        }
        sort(all(tmp));
        for(auto cur: tmp) {
            auto p = cur.cur;
            if(states[p.i][p.j].vis == mark) continue;
            states[p.i][p.j] = cur;
            q.push(cur);
        }


    }

    return false;
}

bool movePos(Table &table, const Pos &start) {
    ++mark;
    queue<Pos> q;
    states[start.i][start.j] = State(start, mark, 0, {start, {0,0}, 0});
    q.push(start);
 
    assert(table.hasBall(start));
    while(!q.empty()) {
        auto cur = q.front(); q.pop();
        //trace(start.i, start.j, cur.i, cur.j, finish(cur), skip(cur));
        if(table.hasBall(cur) && cur != start && table.getBall(cur).isPos()) {
            addMoves(table, cur);
            return true;
        }
        if(cur.ispocket()) continue;
        if(states[cur.i][cur.j].dist >= 1) continue;
 
        fo(i, 8) {
            Pos p = cur;
            Vec v = dirs[i];
            rep(e, 1, 2 * n) {
                p.apply(v);
                if(p.ispocket()) break;
                checkHit(p, v);
 
                if(states[p.i][p.j].vis == mark) break;
                if(table.hasBall(p) && table.getBall(p).isNeg()) break;
 
                
                q.push(p);
 
                states[p.i][p.j] = State(p, mark, states[cur.i][cur.j].dist + 1, Move(cur, dirs[i], e));
            }
        }
    }

    return false;
}

bool moveToDiagonal(Table &table, const Pos &start, int lim) {
    ++mark;
    //priority_queue<State, deque<State>, decltype(revcompare)> q(revcompare);
    queue<State> q;
    states[start.i][start.j] = State(start, mark, 0, {start, {0,0}, 0});
    q.push(states[start.i][start.j]);
    int ldist = 0;
 
    assert(table.hasBall(start));
    while(!q.empty()) {
        auto s = q.front(); q.pop();
        //trace(start.i, start.j, cur.i, cur.j, finish(cur), skip(cur));
        auto cur = s.cur;
        //if(states[cur.i][cur.j] < s) continue;

        if(cur.isdiagonal() || cur.ispocket()) {
            addMoves(table, cur);
            return true;
        }
        if(s.dist >= lim) continue;
 
        vector<State> tmp;
        fo(i, 8) {
            Pos p = cur;
            Vec v = dirs[i];
            int ts = 0;
            ++vmark;
            rep(e, 1, 4 * n) {
                p.apply(v);
                checkHit(p, v);
 
                State nxt(p, mark, s.dist + 1, Move(cur, dirs[i], e));
                if(states[p.i][p.j].vis == mark) break;
                if(table.hasBall(p) && table.getBall(p).isNeg()) break;
 
                if(table.hasBall(p) && vis[p.i][p.j] != vmark) ts += 1; //table.getBall(p).cost;
                vis[p.i][p.j] = vmark;
                
                nxt.ts = ts;
                tmp.push_back(nxt);
                //q.push(nxt);
                //states[p.i][p.j] = nxt;
 
                if(p.ispocket()) break;
            }
        }

        sort(all(tmp));
        for(auto cur: tmp) {
            auto p = cur.cur;
            if(states[p.i][p.j].vis == mark) continue;
            states[p.i][p.j] = cur;
            q.push(cur);
        }
        /*
        if(!q.empty() && q.front().dist != ldist) {
            sort(all(q));
            ldist = q.front().dist;
        }
        */
    }

    return false;
}

void mergePos(Table &table, int cnt) {
    int scnt = 0;
    fo(i, m) if(table.balls[i].present && table.balls[i].isPos() && table.balls[i].debt == 0) {
        bool s = movePos(table, table.balls[i].p);
        scnt += s;
        if(--cnt == 0) break;
    }
    trace(scnt);
}

vi orderBalls(Table &table) {
    vi order;
    fo(i, m) order.push_back(i);

    fo(i, m) {
        Ball &ball = table.balls[i];
        ball.tscore = 100 * ball.p.distFromDiagonal();
    }

    sort(all(order), [table](int i, int j) -> bool {
            const Ball &b1 = table.balls[i], &b2 = table.balls[j];
            if(b1.tscore != b2.tscore) return b1.tscore > b2.tscore;
            //if(b1.cost != b2.cost) return b1.cost > b2.cost;
            return false;
        }
    );

    return order;
}

void clearDiagonal(Table &table) {
    fo(i, m) if(table.balls[i].present && table.balls[i].isNeg() && table.balls[i].p.isdiagonal()) {
        moveNeg(table, table.balls[i].p, min(3, -table.balls[i].cost));
    }
}

void moveToDiagonal(Table table) {
    clearDiagonal(table);
    bool done = false;
    vi order =  orderBalls(table);
    for(int i: order) if(table.balls[i].present && table.balls[i].isPos() && !table.balls[i].p.isdiagonal()) {
        bool done = false;
        rep(d, 1, 4) {
            if(!moveToDiagonal(table, table.balls[i].p, min(d, table.balls[i].cost))) {
                if(!pocketBall(table, table.balls[i].p, min(d, table.balls[i].cost))) {
                } else {
                    done = true;
                    break;
                }
            } else {
                done = true;
                break;
            }
        }
    }
    fo(i, n + 1) {
        if(table.hasBall({i, i}) && table.getBall({i,i}).isPos()) table.move(Move(Pos(i, i), Vec(1, 1), 4 * n));
        if(!maindiag && table.hasBall({i, n + 2 - i}) && table.getBall({i,n + 2 - i}).isPos()) table.move(Move(Pos(i, n + 2 - i), Vec(1, -1), 4 * n));
    }
    submit(table);
}

void moveViaDiagonal(Table table) {
    //if(m > 900 && table.getMinCost() < 0) mergePos(table, 10);
    maindiag = false;
    moveToDiagonal(table);
    maindiag = true;
    moveToDiagonal(table);
}

void pre() {
}


void init() {
    table.clear();
    best.clear();
    first = true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    pre();
    int t;
#ifndef TEST
    cin >> t;
#else
    t = 10;
    int tot = 0;
#endif
    while(t--) {
        init();
#ifndef TEST
        cin >> n >> m;
#else
        srand(t);
        n = 100; m = rand() % 501 + 500;
        int z1[] = {1, -3, 1, -100};
        int z2[] = {3, 3, 100, 100};
        int zi = rand() % 4;
        int vis[102][102] = {0};
#endif
        fo(i, m) {
#ifndef TEST
            cin >> table.balls[i].p.i >> table.balls[i].p.j >> table.balls[i].cost;
#else
            int ci, cj;
            do {
                ci = rand() %  (n + 1);
                cj = rand() %  (n + 1);
            } while(vis[ci][cj]);

            vis[ci][cj] = 1;
            table.balls[i].cost = rand() % (z2[zi] - z1[zi] + 1) + z1[zi];

            table.balls[i].p.i = ci; table.balls[i].p.j = cj;
#endif
            table.balls[i].init();
            table.at[table.balls[i].p.i][table.balls[i].p.j] = i;
        }

        moveViaDiagonal(table);

        cout << si(best.moves) << '\n';
        for(Move m: best.moves) {
            cout << m.p.i-1 << " " << m.p.j-1 << " " << m.v.vi << " " << m.v.vj << " " << m.e << '\n';
        }

#ifdef TEST
        trace(z1[zi], z2[zi], m, best.score, si(best.moves), best.remPos());
        tot += best.score;
#endif
    }

#ifdef TEST
    cerr << "Total score: " << tot << endl;
#endif
    
    
	return 0;
}

