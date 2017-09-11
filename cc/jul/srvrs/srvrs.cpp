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
constexpr int mx_n = 500005;

int n, q;
class CPU {
public:
    int s, c;
    int x, y, p;
    CPU() {}
    CPU(int s, int c, int x, int y, int p): s(s), c(c), x(x), y(y), p(p) {}
    bool operator <(const CPU &cpu) const {
        if(p != cpu.p) return p < cpu.p;
        return s < cpu.s || (s == cpu.s && c < cpu.c);
    }

    bool operator ==(const CPU &cpu) const {
        return s == cpu.s && c == cpu.c;
    }

    double score(int sx, int sy) const {
        double dx = (sx - x), dy = (sy - y);
        return  sqrt(dx * dx + dy * dy) + p;
    }

} all_cpus[mx_n];

list<CPU> at[mx_n];

class Bester {
public:
    double best;
    CPU bcpu;
    int x, y;
    int quota;
    Bester(int x, int y, int q): x(x), y(y), best(-1), quota(q) {}
    void submit(const CPU cpu) {
        double cur = cpu.score(x, y);
        if(best < -eps || best > cur) {
            best = cur;
            bcpu = cpu;
        }
    }
};

class ISelector {
    public:
    virtual void select(Bester &bester) = 0;
    virtual void init() = 0;
    virtual void remove(CPU cpu) = 0;
    virtual void add(CPU cpu) = 0;
};

class FirstSelector: public ISelector {
    set<CPU> cpus;
    public:
    void select(Bester &bester) {
         bester.submit(*cpus.begin());
    }
    
    void init() {
        fo(i, n) cpus.insert(all_cpus[i]);
    }

    void add(CPU cpu) {
        cpus.insert(cpu);
    }

    void remove(CPU cpu) {
        cpus.erase(cpu);
    }

};

class RandomWeightComparator {
public:
    bool operator()(const CPU &cpu1, const CPU &cpu2) const {
        int w1 = cpu1.s * oo + cpu1.c, w2 = cpu2.s * oo + cpu2.c;
        return w1 < w2;
    }
};

class RandomSelector: public ISelector {
    set<CPU, RandomWeightComparator> cpus;
    public:
    void select(Bester &bester) {
        auto it = cpus.begin();
        int till = min(bester.quota, min(10, si(cpus)));
        for(int i = 0; i < till && it != cpus.end(); ++i, ++it) bester.submit(*it);
        bester.quota -= till;
    }
    
    void init() {
        fo(i, n) cpus.insert(all_cpus[i]);
    }

    void add(CPU cpu) {
        cpus.insert(cpu);
    }

    void remove(CPU cpu) {
        cpus.erase(cpu);
    }
};

class ProcessTimeSelector: public ISelector {
    set<CPU> cpus;
    public:
    void select(Bester &bester) {
        auto it = cpus.begin();
        int till = max(1, min(3 * bester.quota/4, min(20, si(cpus))));
        for(int i = 0; i < till && it != cpus.end(); ++i, ++it) bester.submit(*it);
        bester.quota -= till;
    }
    
    void init() {
        fo(i, n) cpus.insert(all_cpus[i]);
    }

    void add(CPU cpu) {
        cpus.insert(cpu);
    }

    void remove(CPU cpu) {
        cpus.erase(cpu);
    }
};

class XAxisNearestSelector: public ISelector {
    map<int, set<CPU>> atx;
    public:
    void select(Bester &bester) {
        trace(bester.x);
        auto it = atx.lower_bound(bester.x);
        if(it != atx.end()) bester.submit(*(it->se.begin()));
    }
    
    void init() {
        fo(i, n) {
            atx[all_cpus[i].x].insert(all_cpus[i]);
        }
    }

    void add(CPU cpu) {
        atx[cpu.x].insert(cpu);
    }

    void remove(CPU cpu) {
        atx[cpu.x].erase(cpu);
        if(atx[cpu.x].empty()) atx.erase(cpu.x);
    }
};

class YAxisNearestSelector: public ISelector {
    map<int, set<CPU>> aty;
    public:
    void select(Bester &bester) {
        trace(bester.y);
        auto it = aty.lower_bound(bester.y);
        if(it != aty.end()) bester.submit(*(it->se.begin()));
    }
    
    void init() {
        fo(i, n) {
            aty[all_cpus[i].y].insert(all_cpus[i]);
        }
    }

    void add(CPU cpu) {
        aty[cpu.y].insert(cpu);
    }

    void remove(CPU cpu) {
        aty[cpu.y].erase(cpu);
        if(aty[cpu.y].empty()) aty.erase(cpu.y);
    }
};

class GridSelector: public ISelector {
    set<CPU> g[102][102];
    static constexpr int DIV = 1024;
    public:
    void select(Bester &bester) {
        int ni = bester.x/DIV, nj = bester.y/DIV;
        if(g[ni][nj].empty()) {
            fo(d, 8) {
                int ci = bester.x/DIV + dx[d];
                int cj = bester.y/DIV + dy[d];
                if(ci >= 0 && ci < 102 && cj >= 0 && cj < 102 && !g[ci][cj].empty()) {
                    ni = ci;
                    nj = cj;
                    break;
                }
            }
        }
        if(!g[ni][nj].empty()) {
            int till = max(1, min(si(g[ni][nj]), min(bester.quota, oo)));
            auto it = g[ni][nj].begin();
            for(int i = 0; i < till && it != g[ni][nj].end(); ++i, ++it) bester.submit(*it);
            bester.quota -= till;
        }
    }
    
    void init() {
        fo(i, n) {
            g[all_cpus[i].x/DIV][all_cpus[i].y/DIV].insert(all_cpus[i]);
        }
    }

    void add(CPU cpu) {
        g[cpu.x/DIV][cpu.y/DIV].insert(cpu);
    }

    void remove(CPU cpu) {
        g[cpu.x/DIV][cpu.y/DIV].erase(cpu);
    }
};

class LargeGridSelector: public ISelector {
    set<CPU> g[34][34];
    static constexpr int DIV = 32768;
    public:
    void select(Bester &bester) {
        fo(i, 34) fo(j, 34) {
            if(!g[i][j].empty()) {
                bester.submit(*g[i][j].begin());
            }
        }
    }
    
    void init() {
        fo(i, n) {
            g[all_cpus[i].x/DIV][all_cpus[i].y/DIV].insert(all_cpus[i]);
        }
    }

    void add(CPU cpu) {
        g[cpu.x/DIV][cpu.y/DIV].insert(cpu);
    }

    void remove(CPU cpu) {
        g[cpu.x/DIV][cpu.y/DIV].erase(cpu);
    }
};

vector<ISelector *> selectors;

void add(int t) {
    for(auto cur: selectors) for(auto cpu: at[t]) cur->add(cpu);
}

void init() {
    //selectors.push_back(new FirstSelector());
    selectors.push_back(new ProcessTimeSelector());
    //selectors.push_back(new XAxisNearestSelector());
    //selectors.push_back(new YAxisNearestSelector());
    selectors.push_back(new GridSelector());
    //selectors.push_back(new RandomSelector());
    //selectors.push_back(new LargeGridSelector());

    for(auto cur: selectors) cur->init();
}

int tot = 3000000, t;
CPU solve(int x, int y) {
    Bester bester(x, y, tot / (q - t + 1));
    for(auto cur: selectors) cur->select(bester);
    return bester.bcpu;
}

void remove(int t, CPU cpu) {
    if(t + cpu.p < mx_n) at[t+cpu.p].push_back(cpu);
    for(auto cur: selectors) cur->remove(cpu);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int _n;
    cin >> _n >> q;
    fo(i, _n) {
        int x, y, k, p;
        cin >> x >> y >> k;
        fo(j, k) {
            cin >> p;
            all_cpus[n++] = CPU(i + 1, j + 1, x, y, p);
        }
    }

    init();

    for(t = 1; t <= q; ++t) {
        add(t);
        int x, y;
        cout << "?" << endl;
        cin >> x >> y;
        auto cpu = solve(x, y);
        trace(cpu.s, cpu.c, cpu.p, t, t + cpu.p);
        remove(t, cpu);
        cout << "! " << cpu.s << " " << cpu.c << endl;
    }
    cout << "end" << endl;

    
    
	return 0;
}

