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
vi adj[mx_n];
vi ch[mx_n];
int n;

constexpr int mx_h = 5;
int hbase[mx_h], hleaf[mx_h], hmod[mx_h], hbasepow[mx_h][mx_n], hbaseinv[mx_h][mx_n];
class Hash {
public:
    int hval[mx_h];

    bool operator <(const Hash &h) const {
        fo(i, mx_h) if(hval[i] != h.hval[i]) return hval[i] < h.hval[i];
        return false;
    }

    void add(Hash h, int pos) {
        fo(i, mx_h) {
            hval[i] = (hval[i] + 1ll * hbasepow[i][pos] * h.hval[i]) % hmod[i];
        }
    }

    void rem(Hash h, int pos) {
        fo(i, mx_h) {
            hval[i] = (hval[i] - 1ll * hbasepow[i][pos] * h.hval[i] % hmod[i] + hmod[i]) % hmod[i];
        }
    }
} h[mx_n];

bool ok(int n) {
    if(n <= 100) return false;
    for(int x = 2; x * x <= n; x += 2) if(n % x == 0) return false;
    return true;
}

void hash_init() {
    fo(i, mx_h) {
        do {
            hbase[i] = rand() % oo/2 + oo/2;
            hmod[i] =  rand() % oo/2 + oo/2;
            if(hmod[i] < hbase[i]) swap(hmod[i], hbase[i]);
        } while(!ok(hbase[i]));
        hbasepow[i][0] = 1;
        re(j, 1, mx_n) {
            hbasepow[i][j] = 1ll * hbasepow[i][j-1] * hbase[i] % hmod[i];
        }
        fo(j, mx_n) hbaseinv[i][j] = modpow(hbasepow[i][j], hmod[i] - 2, hmod[i]);
        hleaf[i] = rand() % hbase[i] / 2 + hbase[i] / 2;
    }
}

map<Hash, int> cnt;
int cur_dist, ans;

void add_node(Hash h) {
    if(++cnt[h] == 1) ++cur_dist;
}

void rem_node(Hash h) {
    if(--cnt[h] == 0) --cur_dist;
}


void dfs(int x, int p) {
    vector<Hash> chashes;
    for(int y: adj[x]) if(y != p) {
        ch[x].push_back(y);
        dfs(y, x);
        chashes.push_back(h[y]);
    }
    sort(all(chashes));
    if(si(chashes) == 0) {
        fo(i, mx_h) h[x].hval[i] = hleaf[i];
    }
    fo(i, si(chashes)) h[x].add(chashes[i], i);
    add_node(h[x]);
}

void solve(int x, Hash ph) {
    ans = max(ans, cur_dist);
    vector<pair<Hash, int>> chashes;
    for(int y: ch[x]) {
        chashes.push_back(mp(h[y], y));
    }
    sort(all(chashes));
    int siz = si(chashes);
    vector<Hash> hr(siz), hl(siz);

    Hash ch;
    fo(i, siz) {
        ch.add(chashes[i].fi, i);
        hl[i] = ch;
    }
    Hash ch2;
    for(int i = siz - 1; i >= 0; --i) {
        fo(j, mx_h) {
            ch2.hval[j] = (chashes[i].fi.hval[j] + 1ll * ch2.hval[j] * hbase[j]) % hmod[j];
        }
    }

    Hash cur_hash = h[x];
    fo(p, siz) {
        auto ch = chashes[p].fi;
        int i = chashes[p].se;
        Hash before = cur_hash;
        int idx = lower_bound(all(chashes), ph) - chashes.begin();
        Hash nhash;
        if(idx) nhash = hl[idx-1];
        if(idx < n) nhash.add(hl[idx+1], idx + 1);
        nhash.add(h[x], idx);
        int cp = p;
        if(idx < p) ++cp;
        nhash.rem(ch, cp);

        add_node(nhash);
        rem_node(before);

        solve(i, cur_hash);
        rem_node(nhash);
        add_node(before);

        cur_hash = before;
    }

}

int main() {
    hash_init();
    return 0;
    cin >> n;
    fo(i, n - 1) {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    dfs(1, 0);

    ans = 0;
    solve(1, Hash());
    cout << ans << endl;

    
    
	return 0;
}

