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
constexpr int mx_n =  500005;
int c[mx_n];
int n;

class rect {
public:
    int x1, y1, x2, y2;
    int i;
    bool operator <(const rect &r) const {
        if(x1 == r.x1) return y1 < r.y1;
        return x1 < r.x1;
    }

} rects[mx_n];

class event {
public:
    int y;
    int typ, i;
    event(int _y, int _t, int _i): y(_y),typ(_t), i(_i) {}
    bool operator <(const event &e) const {
        if(y == e.y) return typ < e.typ;
        return y < e.y;
    }
};

vi adj[mx_n];

map<int, vector<event>> events_at;

void compute() {
    events_at.clear();
    fo(i, n) {
        events_at[rects[i].x1].push_back({rects[i].y1, 1, i});
        events_at[rects[i].x1].push_back({rects[i].y2, 0, i});
        events_at[rects[i].x2].push_back({rects[i].y1, 1, i});
        events_at[rects[i].x2].push_back({rects[i].y2, 0, i});
    }

    for(auto entry: events_at) {
        auto events = entry.se;
        sort(all(events));
        set<int> live;
        for(auto cur: events) {
            if(cur.typ == 1) {
                for(int idx: live) {
                    adj[idx].push_back(cur.i);
                    adj[cur.i].push_back(idx);
                }
                live.insert(cur.i);
            } else {
                live.erase(cur.i);
            }
        }
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    fo(i, n) {
        int x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        rects[i].x1 = min(x1, x2);
        rects[i].x2 = max(x1, x2);
        rects[i].y1 = min(y1, y2);
        rects[i].y2 = max(y1, y2);
        rects[i].i = i;
    }

    fo(k, 2) {
        compute();
        fo(i, n) {
            swap(rects[i].x1, rects[i].y1);
            swap(rects[i].x2, rects[i].y2);
        }
    }

    sort(rects, rects + n);


    ini(c, -1);
    fo(idx, n) {
        set<int> pos;
        fo(j, 4) pos.insert(j);
        int i = rects[idx].i;
        for(int j: adj[i]) pos.erase(c[j]);
        trace(idx, i, adj[i], pos);
        assert(si(pos) > 0);
        c[i] = *pos.begin();
    }


    cout << "YES\n";
    fo(i, n) cout << c[i] + 1 << "\n";
    
    
	return 0;
}

