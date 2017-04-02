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
constexpr int mx_n = 200005, mx_k = 6;

vi adj[mx_n];
int n, k;
ll ans;

class Rem {
public:
    int sz;
    int cnt[mx_k];
    ll tot;

    void add(const Rem &r) {
        fo(i, k) cnt[i] += r.cnt[i];
        tot += r.tot;
    }

    void increment() {
        int tmp = cnt[0];
        re(i, 1, k) {
            swap(tmp, cnt[i]);
        }
        cnt[0] = tmp;
        tot += cnt[0];
    }

} val[mx_n];

void dfs(int x, int p) {
    vi ch;
    val[x].sz = 1;
    for(int nxt: adj[x]) if(nxt != p) {
        ch.push_back(nxt);
        dfs(nxt, x);
        val[x].sz += val[nxt].sz;
    }

    // x via c to descendants
    ll tsum = 0;
    ll from = 0;
    for(int c: ch) {
        val[c].increment();
        trace(c, val[c].sz, val[c].tot);
#ifdef TRACE
        fo(i, k) cerr << val[c].cnt[i] << " "; cerr << endl;
#endif
        from += val[c].tot + val[c].sz - val[c].cnt[0];
        tsum += 1ll * (val[x].sz - 1 - val[c].sz) * val[c].tot;
    }
    trace(x, ch, tsum, from);
    ans += from;

    //tsum *= tsum;
    //for(int c: ch) tsum -= 1ll * val[c].tot * val[c].tot;

    ans += tsum;
    trace(x, tsum);
    ll psum = 0;

    fo(k1, k) re(k2, k1, k) {
        ll s1 = 0, s2 = 0;
        ll pairs = 0;
        for(int c: ch) {
            s1 += val[c].cnt[k1];
            s2 += val[c].cnt[k2];
        }
        pairs += 1ll * s1 * s2;
        for(int c: ch) pairs -= 1ll * val[c].cnt[k1] * val[c].cnt[k2];
        if(k1 == k2) pairs /= 2;
        if(k1 + k2 != 0) psum += pairs;
        if(k1 + k2 > k) psum += pairs;
        trace(x, k1, k2, s1, s2, pairs);
    }
    ans += psum;
    trace(x, psum);


    for(int c: ch) val[x].add(val[c]);
    ++val[x].cnt[0];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    fo(i, n - 1) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1, -1);

    //ans /= 2;

    cout << ans << endl;
    
    
	return 0;
}

