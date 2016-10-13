/* string coder = "Balajiganapathi S"; // Never give up!  */

//#define LOCAL
#ifdef LOCAL
#   define TRACE
#   define TEST
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
constexpr int mx_n = 200005;
constexpr int lg_n = 20;
int n, a[mx_n], b[mx_n];
int ma[mx_n][lg_n], mb[mx_n][lg_n];
int flog[mx_n];

void pre() {
    fo(i, n) {
        ma[i][0] = a[i];
        mb[i][0] = b[i];
    }

    re(j, 1, lg_n) {
        fo(i, n) {
            if(i + (1 << (j-1)) >= n) {
                ma[i][j] = ma[i][j-1];
                mb[i][j] = mb[i][j-1];
            } else {
                ma[i][j] = max(ma[i][j-1], ma[i + (1 << (j-1))][j-1]);
                mb[i][j] = min(mb[i][j-1], mb[i + (1 << (j-1))][j-1]);
            }
        }
    }

    flog[1] = 0;
    int cur = 0;
    re(i, 1, mx_n) {
        if((1 << (cur+1) < i)) ++cur;
        flog[i] = cur;
    }
}

int isequal(int i, int j) {
    int len = j - i + 1;
    int k = flog[len];
    return max(ma[i][k], ma[j - (1 << k) + 1][k]) == min(mb[i][k], mb[j - (1 << k) + 1][k]);
}

int main() {
#ifndef TEST
    scanf("%d", &n);
    fo(i, n) scanf("%d", a + i);
    fo(i, n) scanf("%d", b + i);
#else
    n = 20;
    fo(i, n) {
        a[i] = rand() % 2 + 1;
        b[i] = rand() % 2 + 1;
    }
#endif
    pre();

    ll ans = 0;
    fo(i, n) if(a[i] == b[i]) {
        int lo = 1, hi = n - i;
        while(lo < hi) {
            int mid = (lo + hi + 1) / 2;
            if(isequal(i, i + mid - 1)) lo = mid;
            else hi = mid - 1;
        }
        trace(i, i + lo - 1);
        ans += lo;
    }

#ifdef CHECK
    ll bans = 0;
    fo(i, n) {
        int aa = a[i], bb = b[i];
        re(j, i, n) {
            aa = max(aa, a[j]);
            bb = min(bb, b[j]);
            if(aa == bb) {
                trace(i, j);
                ++bans;
            }
        }
    }
    if(ans != bans) {
        trace(n);
        fo(i, n) cerr << a[i] << " "; cerr << endl;
        fo(i, n) cerr << b[i] << " "; cerr << endl;
        trace(ans, bans);
        assert(ans == bans);
    }
#endif

    cout << ans << endl;
    
	return 0;
}

