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
constexpr int mx = -1;
vector<tuple<int, int, int>> ans;

int b;
void f(int c0, int c1, int c2) {
    ans.emplace_back(c0, c1, c2);
}

void op_copy(int c0, int c1) {
    f(0, c0, c1);
}

void op_inc(int c0, int c1) {
    f(0, c0, c1);
}

void op_dec(int c0, int c1) {
    op_inc(c0, c1);
    fo(i, b - 2) op_inc(c1, c1);
}

void op_bool(int c0, int c1) {
    f(c0, 0, c1);
}

void op_inc_if(int b, int c0, int c1) {
    f(b, c0, c1);
}

void op_inv(int c0, int c1) {
    op_dec(c0, c1);
    f(c1, 0, c1);
}

void op_is0(int c0, int c1) {
    op_inv(c0, c1);
}

void op_is1(int c0, int c1) {
    op_dec(c0, c1);
    op_is0(c1, c1);
}

void op_isb1(int c0, int c1) {
    op_copy(c0, c1);
    op_inc(c1);
    op_is0(c1, c1);
}

void op_make0(int c0) {
    f(b - 1, c0, c0);
    op_dec(c0, c0);
}

void op_or(int a, int b, int c2) {
    assert(a != c2 && b != c2);
    op_make0(c2);
    op_inc_if(a, c2, c2);
    op_inc_if(b, c2, c2);
    op_bool(c2, c2);
}

void op_and(int a, int b, int c2, int ia, int ib) {
    set<int> s;
    s.insert(a); s.insert(b); s.insert(c2); s.insert(ia); s.insert(ib);
    assert(si(s) == 5 || (si(s) == 4 && a == b));
    op_inv(a, ia);
    op_inv(b, ib);
    op_or(ia, ib, c2);
    op_inv(c2, c2);
}

void op_cmp(int a, int b, int c2, int isa1, int isb0, int isb1, int tf, int ta, int tb) {
    op_is1(a, isa1);
    op_is0(b, isb0);
    op_is1(b, isb1);
    op_or(isb1, isb0, ta);
    op_copy(ta, isb1);
    op_and(isa1, isb1, tf, ta, tb);
    op_copy(tf, isb1);

    f(a, b, tf);
    op_bool(tf, tf);

    op_inv(isa1, isa1);
    op_and(isa1, tf, isb0, ta, tb);
    op_copy(isb0, isa1);

    op_or(isa1, isb1, c2);
}

int ptr;
int get_next() {
    return ptr++;
}
int offset;
array<int, 2> ad;
array<int, 2> bd;
array<int, 4> ansd;
int cd[4];

void fill_grid(int d1, int d2, const vi &grid) {
    fo(i, b) fo(j, b) {
    }
}

void check_carry(int a, int b, int c) {
}

// b += a + pc, c = carry(a, b)
void partial_add(int a, int b, int pc, int nc) {
    op_make0(nc);
    check_carry(b, a, nc);
    op_inc_if(a, b, b);
    check_carry(b, pc, nc);
    op_inc_if(pc, b, b);
}

void inc_bit(int b, int from) {
    op_make0(ansd[from]);
    for(int i = from; i < 4; ++i) {
        partial_add(b, ansd[i], cd[i-1], cd[i]);
    }
}

void init() {
    offset = b + 2 + 2 + 4;
    ptr = offset;
    ad = {b + 1, b};
    bd = {b + 3, b + 2};
    ansd = {b + 4 + 3, b + 4 + 2, b + 4 + 1, b + 4 + 0};
    fo(i, 4) cd[0] = get_next();
}

void solve() {
    init();
    vi grid;
    fo(i, b) fo(j, b) grid.push_back(get_next());

    fo(i, 2) fo(j, 2) {
        int from = i + j;
        fill_grid(ad[i], bd[j], grid);
        for(int x: grid) inc_bit(x, from);
    }
}

int main() {
    cin >> b;
    solve();

    cout << si(ans) << '\n';
    for(auto cur: ans) cout << gt(cur, 0) << " " << gt(cur, 1) << " " << gt(cur, 2) << '\n';
    
	return 0;
}

