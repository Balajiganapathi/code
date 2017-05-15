/* string coder = "Balajiganapathi S"; // Never give up!  */

//#define LOCAL
#ifdef LOCAL
#   define TRACE
#   define TEST
#   include "weird_editor2.h"
#else
#   include "weird_editor.h"
#   define NDEBUG
//#   define FAST
#endif

#include<bits/stdc++.h>
#include<message.h>

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
constexpr int master = 0;

/* code */
constexpr int mx_nodes = 102, mx_d = 11;

int nodes, id;
int n;
int b1, b2, block;

tuple<int, int> calc(int i) {
    return mt(min(n, i * block), min(n, i * block + block));
}
void pre() {
    nodes = NumberOfNodes();
    id = MyNodeId();
    n = GetNumberLength();
    block = (n + nodes - 1) / nodes;
    tie(b1, b2) =  calc(id);
}

bool ismaster() {
    return id == master;
}



void proc() {
    int val[mx_d], midx[mx_d], mcnt[mx_d];
    fo(i, 10) midx[i] = -oo;
    ini(mcnt, 0);
    ini(val, 0);

    int md = -1;
    for(int i = b2 - 1; i >= b1; --i) {
        int d = GetDigit(i);
        if(d > md) {
            md = d;
            midx[md] = i;
        }
        if(d == md) {
            val[d] = (1ll * modpow(10, mcnt[d], mod) * d + val[d]) % mod;
            ++mcnt[d];
        }
        trace(id, i, d);
    }

    fo(i, 10) {
        trace(id, i, mcnt[i], val[i], midx[i]);
        PutInt(master, val[i]);
        PutInt(master, mcnt[i]);
        PutInt(master, midx[i]);
    }
    Send(master);
}


int val[mx_nodes][mx_d], cnt[mx_nodes][mx_d], idx[mx_nodes][mx_d];
void collect() {
    int ans = 0;
    fo(i, nodes) {
        Receive(i);
        fo(d, 10) {
            val[i][d] = GetInt(i);
            cnt[i][d] = GetInt(i);
            idx[i][d] = GetInt(i);
        }
    }

    int nzcnt = 0;
    int s = 0;
    for(int d = 9; d >= 1; --d) {
        int midx = 0;
        int c = 0;
        re(i, s, nodes) {
            midx = max(midx, idx[i][d]);
            ans = (1ll * ans * modpow(10, cnt[i][d], mod) + val[i][d]) % mod;
            nzcnt += cnt[i][d];
            if(cnt[i][d] > 0) c = 1;
        }
        trace(d, midx);
        if(c) {
            ++midx;
            s = midx / block;
        }
        trace(d, midx, s);
    }

    ans = 1ll * ans * modpow(10, n - nzcnt, mod) % mod;
    cout << ans << endl;
}

int main() {
    pre();
    proc();
    if(ismaster()) collect();
    
    
	return 0;
}

