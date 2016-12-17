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
constexpr int mx_n = 100005;
constexpr int mx_q = 50004;
int sn;

class Query {
    public:
    int x, y, i;
    int sx;
    Query()  {}
    Query(int _x, int _y, int _i): x(_x), y(_y), i(_i), sx(x / sn) {}
    bool operator <(const Query &q) const {
        if(sx != q.sx) return sx < q.sx;
        return y < q.y;
    }
};

int a[mx_n], n;
int q;
Query queries[mx_q];
int fans[mx_q];

int present[mx_n];
int ans;

void add(int x) {
    if(x == -1) return;
    trace(x, a[x]);
    x = a[x];
    present[x] = 1;
    if(present[x-1] && present[x+1]) --ans;
    if(!present[x-1] && !present[x+1]) ++ans;
    assert(ans >= 0 && ans <= n);
}

void rem(int x) {
    if(x == -1) return;
    trace(x, a[x]);
    x = a[x];
    present[x] = 0;
    if(present[x-1] && present[x+1]) ++ans;
    if(!present[x-1] && !present[x+1]) --ans;
    assert(ans >= 0 && ans <= n);
}

int bpre[mx_n];
int brute(int x, int y) {
    ini(bpre, 0);
    rep(i, x, y) bpre[a[i]] = 1;
    int ret = 0;
    int prev = 0;
    rep(i, 1, n) {
        if(bpre[i] == 1 && prev == 0) ++ret;
        prev = bpre[i];
    }

    return ret;
}

int main() {
    int x, y;
#ifdef TEST
    n = 1000; q = 1000;
    sn = sqrt(n) + 1;
    fo(i, n) a[i] = i + 1;
    random_shuffle(a, a + n);
    trace(n, q);
    fo(i, q) {
        int rx = rand(), ry = rand();
        int x = rx % n + 1; 
        int y = ry % n + 1;
        if(x > y) swap(x, y);
        trace(x, y);
        queries[i] = Query(x-1, y-1, i);
    }
#else
    scanf("%d %d", &n, &q);
    sn = sqrt(n) + 1;
    fo(i, n) scanf("%d", a + i);
    fo(i, q) {
        scanf("%d%d", &x, &y);
        queries[i] = Query(x-1, y-1, i);
    }
#endif
    sort(queries, queries + q);
    int ci = -1, cj = -1;

    fo(i, q) {
        x = queries[i].x;
        y = queries[i].y;
        trace(x, y);

        while(ci > x) add(--ci);
        while(cj < y) add(++cj);
        while(ci < x) rem(ci++);
        while(cj > y) rem(cj--);

        fans[queries[i].i] = ans;
#ifdef TEST
        int bans = brute(x, y);
        if(ans != bans) {
            trace(x, y);
            trace(ans, bans);
            assert(ans == bans);
        }
#endif
    }

    fo(i, q) printf("%d\n", fans[i]);
    
    
	return 0;
}

