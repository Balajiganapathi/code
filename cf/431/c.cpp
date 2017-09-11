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
constexpr auto oo  = numeric_limits<ll>::max() / 2 - 2;
constexpr auto eps = 1e-6;
constexpr auto mod = 1000000007;

/* code */
constexpr int mx_n = 101005, mx_ns = 680, mx_s = 170;
int a[mx_n], n;
int last[mx_n], p[mx_n];
int ns, s;
set<int> at[mx_n];
class Info {
public:
    int prev, i;
    ll csum;
    Info(): prev(0), i(-1), csum(0) {}
    Info(int prev, int i): prev(prev), i(i), csum(0) {}
    Info(int prev): prev(prev), i(-1), csum(0) {}
    bool operator <(const Info& info) const {
        return prev < info.prev;
    }
} bsum[mx_ns][mx_s];

void sumIt(int b) {
    ll cur = 0;
    for(int i = s - 1; i >= 0; --i) {
        cur += bsum[b][i].i - bsum[b][i].prev;
        bsum[b][i].csum = cur;
        trace(i, bsum[b][i].prev, bsum[b][i].i, bsum[b][i].csum);
    }
}

void initBlock(int b) {
    int l = b * s, r = b * s + s - 1;
    rep(i, l, r) {
        bsum[b][i-l].prev = p[i];
        bsum[b][i-l].i = i;
        bsum[b][i-l].csum = i - p[i];
    }
    sort(bsum[b], bsum[b] + s);
    sumIt(b);
}


ll brute(int l, int r, int ql) {
    ll ret = 0;
    rep(i, l, r) {
        trace(i, a[i], p[i]);
        if(p[i] >= ql) ret += i - p[i];
    }
    
    trace(l, r, ret);
    return ret;
}

ll solveBlock(int b, int ql, int qr) {
    int l = b * s, r = b * s + s - 1;
    ll ret = 0;
    if(ql <= l && r <= qr) {
        int till = lower_bound(bsum[b], bsum[b] + s, Info(ql)) - bsum[b];
        if(till < s) ret = bsum[b][till].csum;
        else ret = 0;
    } else { 
        ret = brute(max(l, ql), min(r, qr), ql);
    }
    trace(b, l, r, ql, qr, ret);

    return ret;
}

void init() {
    s = (int(sqrt(n)) + 1) / 2;
    ns = (n + s - 1) / s;
    if(n % ns != 0) n += (ns - n % ns);
    trace(n, ns, s);

    ini(last, -1);
    fo(i, n) {
        p[i] = last[a[i]];
        if(p[i] == -1) p[i] = i;
        last[a[i]] = i;
        at[a[i]].insert(i);
    }

    fo(i, ns) initBlock(i);
}

void changeBlock(int idx) {
    int b = idx / s;
    fo(i, s) if(bsum[b][i].i == idx) {
        bsum[b][i].prev = p[idx];
        break;
    }
    sort(bsum[b], bsum[b] + s);
    sumIt(b);
}

void change(int idx) {
    int x = a[idx];
    auto nxt = at[x].lower_bound(idx);
    if(nxt != at[x].end()) {
        p[*nxt] = idx;
        changeBlock(*nxt);
    }
    if(nxt != at[x].begin()) {
        --nxt;
        p[idx] = *nxt;
    } else {
        p[idx] = idx;
    }
    changeBlock(idx);
}

void change(int idx, int t) {
    int tmp = a[idx];
    at[tmp].erase(idx);
    auto also = at[tmp].lower_bound(idx);
    a[idx] = t;

    change(idx);
    if(also != at[tmp].end()) change(*also);
}

ll solve(int l, int r) {
    ll ret = 0;
    int bl = l / s, br = r / s;
    rep(b, bl, br) ret += solveBlock(b, l, r);
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, q, x, y;
    cin >> n >> m;
    fo(i, n) cin >> a[i];
    init();
    while(m--) {
        cin >> q >> x >> y;
        if(q == 1) {
            --x; 
            change(x, y);
        } else {
            --x; --y;
            cout << solve(x, y) << '\n';
        }
    }
    
    
	return 0;
}

