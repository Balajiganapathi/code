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
constexpr int mx_n = 102;
int n;
int pb[mx_n][mx_n];

class Grid {
public:
    int b[mx_n][mx_n];

    bool operator<(const Grid &g) const {
        fo(i, n) fo(j, n) if(g.b[i][j] != b[i][j]) return b[i][j] < g.b[i][j];
        return false;
    }
};

int mx_score;
// 1 - +, 2 - x, 3 - o
class State {
public:
    int vrow[mx_n], vcol[mx_n], vdiag1[2 * mx_n], vdiag2[2 * mx_n];
    int row[mx_n], col[mx_n], diag1[2 * mx_n], diag2[2 * mx_n];
    Grid b;
    int played[mx_n][mx_n];
    int score;
    int cnt[4];

    State() {
        ini(row, 0); ini(col, 0); ini(vrow, 0); ini(vcol, 0);
        ini(diag1, 0); ini(diag2, 0); ini(vdiag1, 0); ini(vdiag2, 0);
        ini(b.b, 0); ini(played, 0);
        ini(cnt, 0);
        score = 0;
        cnt[0] = n * n;
    }

    bool canplay(int prev, int nxt) {
        if(prev == 0) return true;
        if(prev == nxt) return true;
        return ((prev == 1 || prev == 2) && nxt == 3);
    }

    void add(int r, int c, char  m) {
        int d1 = r + c, d2 = r - c + mx_n;
        b.b[r][c] = m;
        if(m == 1) {
            ++score;
            ++vrow[r];
            ++vcol[c];
        } else if(m == 2) {
            ++score;
            ++vdiag1[d1];
            ++vdiag2[d2];
        } else if(m == 3) {
            ++score;
            ++score;
        }
        if(m != 0) {
            ++row[r];
            ++col[c];
            ++diag1[d1];
            ++diag2[d2];
            ++cnt[m];
            --cnt[0];
        }
    }

    void rem(int r, int c) {
        int d1 = r + c, d2 = r - c + mx_n;
        int m = b.b[r][c];
        b.b[r][c] = 0;
        if(m == 1) {
            --score;
            --vrow[r];
            --vcol[c];
        } else if(m == 2) {
            --score;
            --vdiag1[d1];
            --vdiag2[d2];
        } else if(m == 3) {
            --score;
            --score;
        }


        if(m != 0) {
            --row[r];
            --col[c];
            --diag1[d1];
            --diag2[d2];
            --cnt[m];
            ++cnt[0];
        }
    }

    bool isvalid(int r, int c, int m) {
        if(!canplay(pb[r][c], m)) return false;
        if(b.b[r][c] != 0) return false;
        int d1 = r + c, d2 = r - c + mx_n;
        //trace(r, c, m, row[r], vrow[r], col[c], vcol[c], diag1[d1], vdiag1[d1], diag2[d2], vdiag2[d2]);
        if(m == 1) {
            if(diag1[d1] > vdiag1[d1]) return false;
            if(diag2[d2] > vdiag2[d2]) return false;
        } else if(m == 2) {
            if(row[r] > vrow[r]) return false;
            if(col[c] > vcol[c]) return false;
        } else if(m == 3) {
            if(row[r] > vrow[r]) return false;
            if(col[c] > vcol[c]) return false;
            if(diag1[d1] > vdiag1[d1]) return false;
            if(diag2[d2] > vdiag2[d2]) return false;
        }
        return true;
    }

    bool prune() {
        if(score + 2 * cnt[0] < mx_score) return true;
        if(score + cnt[0] + min(cnt[0], n - cnt[3]) < mx_score) return true;

        return false;
    }

};

void disp(const State &s) {
    fo(i, n) {
        fo(j, n) cerr << ".+xo"[s.b.b[i][j]];
        cerr << endl;
    }
    cerr << "Score: " << s.score << endl;
}

State ans;

void submit(const State &s) {
    if(s.score > mx_score) {
        mx_score = s.score;
        ans = s;
    }
}

void greedyFill(State s) {
    fo(i, n) fo(j, n) if(s.b.b[i][j] == 0) {
        rep(m, 1, 2) if(s.isvalid(i, j, m)) {
            s.add(i, j, m);
        }
    }
    submit(s);
}

set<Grid> cache;
void rec(State s) {
    //disp(s);
    if(cache.find(s.b) != cache.end()) return;
    cache.insert(s.b);
    if(s.prune()) return;
    submit(s);
    //greedyFill(s);

    fo(r, n) fo(c, n) if(!s.played[r][c]) {
        int prev = s.b.b[r][c];
        s.rem(r, c);
        s.played[r][c] = 1;
        for(int m = 3; m >= 1; --m) if(s.isvalid(r, c, m)) {
            //disp(s);
            s.add(r, c, m);
            rec(s);
            s.rem(r, c);
        }
        s.played[r][c] = 0;
        s.add(r, c, prev);
    }
}

void solve() {
    cache.clear();
    mx_score = 0;
    State s;
    fo(i, n) fo(j, n) s.add(i, j, pb[i][j]);
    rec(s);
}

void output() {
    int cnt = 0;
    fo(i, n) fo(j, n) {
        if(pb[i][j] != ans.b.b[i][j]) ++cnt;
    }

    cout << mx_score << " " << cnt << endl;
    fo(i, n) fo(j, n) {
        if(pb[i][j] != ans.b.b[i][j]) cout << "+xo"[ans.b.b[i][j]-1] << " " << i + 1 << " " << j + 1 << endl;
    }
}


int main() {
    int _t;
#ifndef TEST
    cin >> _t;
#else
    _t = 10;
#endif
    rep(kase, 1, _t) {
        ini(pb, 0);
        char mt;
        int m, r, c;
#ifndef TEST
        cin >> n >> m;
#else
        State inp;
        n = 4; m = 0;
#endif
        while(m--) {
#ifndef TEST
            cin >> mt >> r >> c;
            --r; --c;
#else
            int mm;
            do {
                r = rand() % n; c = rand() % n;
                mm = rand() % 3 + 1;
            } while(!inp.isvalid(r, c, mm));
            inp.add(r, c, mm);
            mt = ".+xo"[mm];
#endif
            //trace(r, c);
            if(mt == '+') pb[r][c] = 1;
            else if(mt == 'x') pb[r][c] = 2;
            else pb[r][c] = 3;
            //trace(r, c, pb[r][c]);
        }
        trace(n);

        solve();

        cout << "Case #" << kase << ": ";
        output();
        fo(i, n) {
            fo(j, n) cerr << ".+xo"[pb[i][j]];
            cerr << endl;
        }
        trace("-----");
        fo(i, n) {
            fo(j, n) cerr << ".+xo"[ans.b.b[i][j]];
            cerr << endl;
        }
    }
    
    
	return 0;
}

