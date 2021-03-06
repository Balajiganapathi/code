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
constexpr int mx_n = 13, mx_k = 11, mx_full = 600005;
int m, n;
int k[mx_n], l[mx_n], a[mx_n][mx_k], c[mx_n][mx_k];

vector<pair<ll, ll>> gen(const vi &v, int idx) {
    vector<pair<ll, ll>> ret;
    if(idx >= si(v)) {
        ret.emplace_back(0ll, 0ll);
        return ret;
    }

    auto prev = gen(v, idx + 1);

    int i = v[idx];
    ll cur = 0;
    rep(j, l[i], k[i]) {
        vector<pair<ll, ll>> tmp;
        for(auto entry: prev) {
            tmp.emplace_back(entry.fi + cur, entry.se + a[i][j]);
        }
        sort(all(tmp));
        //trace(i, j, tmp);
        for(auto entry: tmp) ret.push_back(entry);
        cur += c[i][j];
    }

    return ret;
}

ll solve(vi v) {
    int n = si(v);
    int n1 = (n + 1) / 2;
    int n2 = n - n2;

    vi part1, part2;
    fo(i, n1) part1.push_back(v[i]);
    re(i, n1, n) part2.push_back(v[i]);
    //trace(part1, part2);
    vector<pair<ll, ll>> pos1 = gen(part1, 0);
    vector<pair<ll, ll>> pos2 = gen(part2, 0);

    sort(all(pos1));
    sort(all(pos2));
    ll cur = 0;
    fo(i, si(pos2)) {
        cur = max(cur, pos2[i].se);
        pos2[i].se = cur;
    }

    //trace(pos1);
    //trace(pos2);
    ll ans = 0;
    fo(i, si(pos1)) if(pos1[i].fi <= m) {
        ll r = m - pos1[i].fi;
        int idx = upper_bound(all(pos2), mp(r, oo)) - pos2.begin();
        if(idx > 0) {
            --idx;
            ll cur = pos1[i].se + pos2[idx].se;
            //trace(i, idx, pos1[i], pos2[idx], cur);
            assert(pos1[i].fi + pos2[idx].fi <= m);
            ans = max(ans, cur);
        }
    }

    //trace(v, ans);
    return ans;
}

ll genSolve(vi v, int i) {
    if(si(v) == 8) {
        return solve(v);
    }
    if(i >= n) return -oo;

    ll ret = genSolve(v, i + 1);
    v.push_back(i);
    ret = max(ret, genSolve(v, i + 1));

    return ret;
}

int main() {
    int t;
    cin >> t;
    rep(kase, 1, t) {
        cin >> m >> n;
        fo(i, n) {
            cin >> k[i] >> l[i];
            rep(j, 1, k[i]) cin >> a[i][j];
            rep(j, 1, k[i] - 1) cin >> c[i][j];
        }

        ll ans = genSolve(vi(), 0);
        cout << "Case #" << kase << ": " << ans << endl;

    }
    
    
	return 0;
}

