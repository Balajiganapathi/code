

//#define LOCAL
#ifdef LOCAL
#   define TRACE
#   define CHECK
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
constexpr int mx_c = 100000;
vector<tuple<int, int, int>> ans;
int B, offset;
vi grid, carry, adigs, bdigs, ansdigs;

// <memory manager

int mm_inuse[mx_c];
queue<int> mm_free;
void mm_init() {
    ini(mm_inuse, 0);
    while(!mm_free.empty()) mm_free.front();
    fo(i, offset) mm_inuse[i] = 1;
    fo(i, mx_c) if(!mm_inuse[i]) mm_free.push(i);
}

int mm_get() {
    assert(!mm_free.empty());
    int x = mm_free.front(); mm_free.pop();
    assert(mm_inuse[x] == 0);
    mm_inuse[x] = 1;
    return x;
}

void mm_release(int x) {
    if(!mm_inuse[x]) return;
    mm_inuse[x] = 0;
    mm_free.push(x);
}

// memory manager>

// c = F(a, b)
int f(int c, int a, int b) {
    ans.emplace_back(a, b, c);
}

// ++a
void op_self_inc(int a) {
    f(a, 1, a);
}

// --a
void op_self_dec(int a) {
    fo(i, B - 1) op_self_inc(a);
}

// a = 0
void op_make0(int a) {
    f(a, 0, 0);
}

void release(int x) {
    //op_make0(x);
    //mm_release(x);
}

// a = (bool)a
void op_self_bool(int a) {
    f(a, a, 0);
}

// a = (bool)b
void op_bool(int a, int b) {
    f(a, b, 0);
}

// a = !a
void op_self_inv(int a) {
    op_self_bool(a);
    op_self_dec(a);
    op_self_bool(a);
}

// a = b;
void op_copy(int a, int b) {
    f(a, 0, b);
}

// a = (b == 0? 1: 0)
void op_is0(int a, int b) {
    op_copy(a, b);
    op_self_bool(a);
    op_self_inv(a);
}

// a += b, b = [0, 1];
void op_inc_if(int a, int bit) {
    f(a, bit, a);
}

// c = (a == b? 1: 0)
void op_eq(int c, int a, int b) {
    int r1 = mm_get();
    op_copy(r1, a);
    fo(i, (B - b) % B) op_self_inc(r1);
    op_is0(c, r1);
    release(r1);
}

// a = (a == b)
void op_self_eq(int a, int b) {
    fo(i, (B - b) % B) op_self_inc(a);
    op_self_bool(a);
    op_self_inv(a);
}

// a &= b
void op_self_and(int a, int b) {
    op_self_bool(a);
    op_self_bool(b);
    op_inc_if(a, b);
    op_self_eq(a, 2);
}

// a |= b
void op_self_or(int a, int b) {
    op_self_bool(a);
    op_self_bool(b);
    op_inc_if(a, b);
    op_self_bool(a);
}

// TODO: make grids B - 1;
void get_grid() {
    fo(i, B * B) grid.push_back(mm_get());
}

// c = (a >= b);
// given b >= 1
void op_ge(int c, int a, int b) {
    int r1 = mm_get(), r2 = mm_get(), r3 = mm_get();

    op_is0(r1, a);
    op_eq(r2, a, 1);
    op_eq(r3, b, 1);

    f(c, a, b);
    op_self_bool(c);

    op_self_and(r3, r2);

    op_self_inv(r1);
    op_self_inv(r2);
    op_self_and(r1, r2);

    op_self_and(c, r1);
    op_self_or(c, r3);

    release(r1); release(r2); release(r3);
}

void op_unary(int d1, int d2, int i, int j) {
    int gi = grid[i * B + j];
    int r1 = mm_get();
    op_ge(r1, d1, i+1);
    op_ge(gi, d2, j+1);
    op_self_and(gi, r1);
    release(r1);
}

void fill_grid(int d1, int d2) {
    fo(i, B - 1) fo(j, B - 1) {
        op_unary(d1, d2, i, j);
    }
}

void release_grid() {
    for(int x: grid) release(x);
    grid.clear();
}

void check_carry(int a, int b, int c) {
    int r1 = mm_get();

    op_eq(r1, a, B - 1);
    op_self_and(r1, b);
    op_self_or(c, r1);

    release(r1);;
}

void add_bit(int a, int b) {
    op_inc_if(a, b);
}

void partial_add(int ansi, int bit, int next_carry) {
    check_carry(ansi, bit, next_carry);
    add_bit(ansi, bit);
}

void add_to_ans(int s, int b) {
    for(int x: carry) op_make0(x);
    partial_add(ansdigs[s], b, carry[s]);
    re(i, s+1, 4) {
        partial_add(ansdigs[i], carry[i-1], carry[i]);
    }
}

void add_grid(int start) {
    for(int x: grid) add_to_ans(start, x);
}

void op_mult(int d1, int d2) {
    int from = d1 + d2;
    get_grid();
    trace(d1, d2, grid);
    fill_grid(adigs[d1], bdigs[d2]);
    add_grid(from);
    release_grid();
}

void init() {
    offset = B + 2 + 2 + 4;
    mm_init();
    adigs.clear();
    fo(i, 2) adigs.push_back(B + 1-i);
    bdigs.clear();
    fo(i, 2) bdigs.push_back(B + 2 + 1-i);
    ansdigs.clear();
    fo(i, 4) ansdigs.push_back(B + 2 + 2 + 3-i);
    carry.clear();
    fo(i, 4) carry.push_back(mm_get());
    grid.clear();
}

void solve() {
    init();
    trace(adigs, bdigs, ansdigs, carry);
    fo(i, 2) fo(j, 2) {
        op_mult(i, j);
    }
}

int F(int a, int b) {
    if(a == 0) return b;
    if(a == 1) return (b+1) % B;
    return (a >= b? 1: 0);
}

int cell[mx_c];

void F(int a, int b, int c) {
    cell[c] = F(cell[a], cell[b]);
}

void check(int n1, int n2) {
    int na = n1 * n2;
    trace(n1, n2, na);
    ini(cell, 0);
    fo(i, B) cell[i] = i;
    cell[B] = n1 / B;
    cell[B+1] = n1 % B;
    cell[B+2] = n2 / B;
    cell[B+3] = n2 % B;

    for(auto cur: ans) {
        F(gt(cur, 0), gt(cur, 1), gt(cur, 2));
    }

    int sa = 0;
    fo(i, 4) sa = sa * B + cell[B + 2 + 2 + i];
    if(sa != na) {
        trace(n1, n2, na, sa);
        fo(i, 100) {
            cout << cell[i];
            if(i % 10 == 9) cout << " ";
        }
        cout << endl;
        assert(sa == na);
    }
}

void check() {
    trace("checking");
    fo(n1, B * B) fo(n2, B * B) {
        check(n1, n2);
    }
}

int main() {
    cin >> B;
    solve();

    fo(i, B) {
        fo(j, B) cout << F(i, j) << " ";
        cout << endl;
    }
    cout << si(ans) << endl;
    for(auto cur: ans) cout << gt(cur, 0) << " " << gt(cur, 1) << " " << gt(cur, 2) << endl;
#ifdef CHECK
    check();
#endif
    
	return 0;
}

