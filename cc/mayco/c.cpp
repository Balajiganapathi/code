/* string coder = "Balajiganapathi S"; // Never give up!  */

//#define LOCAL
#ifdef LOCAL
//#   define TRACE
//#   define TEST
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
constexpr int mx_n = 1000003, mx_b = 65;
int ci[mx_b];
ll a[mx_n];
int q[mx_n], n, m;
int cmove, cb, idx[mx_n];
int msb[mx_n];
ll ans[mx_b * mx_n];

vi cur[2];
void rec(int b, int s, int e) {
    if(s > e) return;
    if(b >= 63) return;
    fo(j, 2) {
        cur[j].clear();
        cur[j].reserve(e-s+1);
    }
    int s1 = 0;
    rep(id, s, e) {
        int i = idx[id];
        if(msb[i] < b) ++s1;
        else if(is1(a[i], (msb[i]-b))) cur[1].push_back(i);
        else cur[0].push_back(i);
    }
    int c = s1;
    int m = -1;
    fo(j, 2) {
        //memcpy(idx+c, cur[j].data(), 4 * si(cur[j]));
        //c += si(cur[j]);
        fo(k, si(cur[j])) {
            int i = cur[j][k];
            ll tval = (a[i] >> (msb[i]-b));
            assert(tval >= 0);
            ans[--ci[b]] = tval;
            idx[c++] = i;
        }
        if(m == -1) m = c;
    }

    rec(b+1, s1, m-1);
    rec(b+1, m, e);
}

void proc() {
    fo(i, n) idx[i] = i;
    fo(i, n) {
        for(ll tmp = (a[i] >> 1); tmp > 0; tmp >>= 1) ++msb[i];
        //trace(i, msb[i]);
        ++ci[msb[i]];
    }
    int tc = 0, sofar = 0;
    for(int i = mx_b-1; i >= 0; --i) {
        sofar += ci[i];
        tc += sofar;
        ci[i] = tc;
        trace(i, ci[i], tc, sofar);
    }
    fo(i, n) ans[--ci[0]] = 1;

    ci[0] = n;
    rec(1, 0, n - 1);
    int ts = 0;
    fo(b, 63) {
        //trace(b, rem[b]);
        ts += ci[b];
    }
    trace(q[m-1], ci[0]+n);

    cb = 63;
    cmove = 0;
}

ll solve(int q) {
    return ans[q-1];
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef TEST
    cin >> n >> m;
    fo(i, n) cin >> a[i];
#else
    n = 1000000;
    m = 1000000;
    fo(i, n) {
        a[i] = (1llu << 63) - 1;
        assert(a[i] >= 0);
    }
    q[m-1] = 63 * n;
    fo(i, m-1) q[i] = rand() % (q[m-1] - 1) + 1;
    sort(q, q + m);
    cout << n << " " << m << endl;
    fo(i, n) cout << a[i] << " ";
    cout << endl;
    fo(i, m) cout << q[i] << endl;
    return 0;
#endif
    proc();

    fo(i, m) {
        int id;
#ifndef TEST
        cin >> id;
#else
        id = q[i];
#endif
        cout << ans[id-1] << '\n';
    }

    
    
	return 0;
}

