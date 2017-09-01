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
constexpr int mx_n = 200005;
string s, t;
int n, m, k;
int ti[mx_n], te[mx_n];
bool matches[mx_n];

void setBit(unsigned int a[mx_n], int idx, int v) {
    a[idx/32] |= (v << (31 - idx % 32));
}

void shift(unsigned int a[mx_n], int n) {
    unsigned int cb = 0;
    for(int i = n - 1; i >= 0; --i) {
        int tb = (a[i] >> 31);
        a[i] = ((a[i] << 1) | cb);
    }
}

bool eq(unsigned int a[mx_n], unsigned int b[mx_n], int n) {
    trace(n);
    fo(i, (n+31) / 32) {
        //trace(a[i], b[i]);
        if((a[i] & b[i]) != a[i]) return false;
    }
    return true;
}

void copyIt(unsigned int a[mx_n], unsigned int b[mx_n], int n) {
    fo(i, (n+31) / 32) a[i] = b[i];
    if(n % 32 != 0) {
        b[n/32] = ((a[n/32] >> (31 - n%32)) << (31 - n%32));
    }
}

unsigned bs[mx_n], bt[mx_n], cs[mx_n];
int main() {
    cin >> n >> m >> k >> s >> t;
    char chars[] = "AGCT";

    trace(n, m, k, s, t);
    fo(i, n - m + 1) matches[i] = true;
    fo(ci, 4) {
        ini(bs, 0); ini(bt, 0); ini(cs, 0);
        ini(ti, 0); ini(te, 0);
        char c = chars[ci];
        fo(i, m) if(t[i] == c) {
            setBit(bt, i, 1);
        }
        //fo(i, (m+31) / 32) trace(i, bt[i]);
        fo(i, n) if(s[i] == c) {
            ++ti[max(0, i - k)];
            ++te[min(n, i + k + 1)];
        }
        int cur = 0;
        fo(i, n) {
            cur += ti[i];
            if(cur > 0) setBit(bs, i, 1);
            cur -= te[i];
        }
        //fo(i, (n+31) / 32) trace(i, bs[i]);

        copyIt(cs, bs, m);
        //fo(i, (m+31) / 32) trace(i, cs[i]);

        fo(i, n - m + 1) {
            //trace(ci, i, matches[i]);
            if(matches[i] && !eq(bt, cs, m)) matches[i] = false;
            trace(ci, i, matches[i]);
            shift(cs, m);
            setBit(cs, i + m, bs[i]);
        }
    }

    int ans = 0;
    fo(i, n) if(matches[i]) ++ans;
    cout << ans << endl;
    
	return 0;
}

