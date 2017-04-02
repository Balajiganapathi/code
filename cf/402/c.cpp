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
constexpr int mx_n = 300005;

// <HASH>
constexpr int nhash = 2;
int cbase[nhash][256], cpos[nhash][mx_n];

bool isprime(int n) {
    if(n % 2 == 0) return n == 2;
    for(int i = 3; i * i <= n; i += 2) if(n % i == 0) return true;
    return false;
}


int getRand() {
    return 11l * rand() * rand() % numeric_limits<int>::max();
}

void preHash() {
    srand(time(NULL));
    fo(i, nhash) {
        fo(c, 256) {
            cbase[i][c] = getRand();
        }
        fo(j, mx_n) {
            cpos[i][j] = getRand();
        }
    }

}
class Hash {
    public:
    int len;
    int cur_hash[nhash];
    Hash() {
        len = 0;
        fo(i, nhash) cur_hash[i] = 0;
    }

    void addCharToEnd(int c) {
        fo(i, nhash) {
            //trace(i, c, cur_hash[i], base[i], cbase[i][c], modpow(base[i], len - 1, modd[i]));
            cur_hash[i] += (cbase[i][c] ^ cpos[i][len]);
        }
        ++len;
    }

    bool operator ==(const Hash &h) const {
        if(len != h.len) return false;
        fo(i, nhash) if(cur_hash[i] != h.cur_hash[i]) return false;
        return true;
    }

    bool operator <(const Hash &h) const {
        if(len != h.len) return len < h.len;
        fo(i, nhash) if(cur_hash[i] != h.cur_hash[i]) return cur_hash[i] < h.cur_hash[i];
        return false;
    }

};

template<typename T> 
ostream &operator <<(ostream &o, const Hash &h) { // print a hash
    o << "<(" << h.len << ")";
    bool first = true;
    for(int i = 0; i < nhash; ++i) {
        if(!first) o << "; ";
         
        o << h.cur_hash[i];
        first = false;
    }
    o << ">";
    return o;
}
namespace std {
    template <>
    struct hash<Hash>
    {
        std::size_t operator()(const Hash& k) const
        {

            size_t h = 0;
            fo(i, nhash) {
                h = ((h << 1) ^ k.cur_hash[i]);
            }
            return h;

        }
    };
};

// </HASH>

vector<pi> nxt[mx_n];
unordered_set<Hash> pref[mx_n];
int reduce[mx_n];
int sz[mx_n];
int n;
int order[mx_n], depth[mx_n];;

void orit() {
    queue<pi> q;
    int cnt = 0;
    q.push(mp(1, 0));
    while(!q.empty()) {
        auto cur = q.front(); q.pop();
        order[cnt++] = cur.fi;
        depth[cur.fi] = cur.se;

        for(auto nx: nxt[cur.fi]) {
            q.push(mp(nx.fi, cur.se + 1));
        }
    }

    reverse(order, order + n);
}

void solve() {
    orit();
    fo(ii, n) {
        int x = order[ii];
        int d = depth[x];
        sz[x] = 1;

        for(auto nx: nxt[x]) {
            sz[x] += sz[nx.fi];
            pref[x].insert(all(pref[nx.fi]));
        }

        reduce[d] += sz[x] - si(pref[x]) - 1;;
        trace(x, d, reduce[d], sz[x], si(pref[x]));

        pref[x].clear();
        for(auto nx: nxt[x]) {
            for(Hash h: pref[nx.fi]) {
                h.addCharToEnd(nx.se);
                pref[x].insert(h);
            }
            pref[nx.fi].clear();
            Hash h;
            h.addCharToEnd(nx.se);
            pref[x].insert(h);
        }
    trace(x, d, si(pref[x]));
    }

}


int main() {
    cin.sync_with_stdio(false);
    preHash();
    cin >> n;
    fo(i, n - 1) {
        int u, v;
        char c;
        cin >> u >> v >> c;
        trace(u, v, c);
        nxt[u].push_back(mp(v, c));
    }

    solve();

    int ans1 = oo, ans2 = -1;
    fo(i, n) {
        int cur = n - reduce[i];
        if(cur < ans1) {
            ans1 = cur;
            ans2 = i + 1;
        }
    }

    cout << ans1 << endl << ans2 << endl;
    
    
	return 0;
}

