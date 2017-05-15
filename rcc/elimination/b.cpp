/* string coder = "Balajiganapathi S"; // Never give up!  */

//#define LOCAL
#ifdef LOCAL
#   define TRACE
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
constexpr auto oo  = numeric_limits<ll>::max() / 100 - 2;
constexpr auto eps = 1e-6;
constexpr auto mod = 1000000007;

/* code */
constexpr int mx_n = 2103;
constexpr int mx_s = 5 * mx_n;
int n;
ll a, b, c;
int layout[mx_n][256];
ll dp[mx_n][mx_n];
string s;

bool instack[mx_n][2];

ll amin[mx_s],  prop[mx_s];

void build(int i, int a, int b, int di) {
    prop[i] = 0;
    if(a == b) {
        amin[i] = dp[di][a];
        return;
    }
    int l = 2 * i + 1, r = 2 * i + 2, m = (a + b) / 2;
    build(l, a, m, di);
    build(r, m + 1, b, di);
    amin[i] = min(amin[l], amin[r]);
}

void add(int i, int a, int b, int qa, int qb, ll s) {
    if(a == qa && b == qb) {
        prop[i] += s;
        amin[i] += s;
        return;
    }
    int l = 2 * i + 1, r = 2 * i + 2, m = (a + b) / 2;
    prop[l] += prop[i]; prop[r] += prop[i];
    amin[l] += prop[i]; amin[r] += prop[i];
    prop[i] = 0;
    amin[i] = min(amin[l],  amin[r]);

    if(qb <= m) {
        add(l, a, m, qa, qb, s);
    } else if(qa > m) {
        add(r, m + 1, b, qa, qb, s);
    } else {
        add(l, a, m, qa, m, s);
        add(r, m + 1, b, m + 1, qb, s);
    }
    amin[i] = min(amin[l],  amin[r]);
}

ll get(int i, int a, int b, int qa, int qb) {
    if(a == qa && b == qb) return amin[i];
    int l = 2 * i + 1, r = 2 * i + 2, m = (a + b) / 2;
    prop[l] += prop[i]; prop[r] += prop[i];
    amin[l] += prop[i]; amin[r] += prop[i];
    prop[i] = 0;
    amin[i] = min(amin[l],  amin[r]);

    if(qb <= m) {
        return get(i, a, m, qa, qb);
    } else if(qa > m) {
        return get(r, m + 1, b, qa, qb);
    } else {
        return min(get(l, a, m, qa, m),
            get(r, m + 1, b, m + 1, qb)
        );
    }

}

int main() {
#ifndef TEST
    cin >> n >> a >> b >> c;
    fo(i, n) {
        string cur;
        cin >> cur;
        for(char x: cur) layout[i][x] = 1;
    }
    cin >> s;
#else
    int m = 1000000000;
    n = 200; a = rand() % m + 1; b = rand() % m + 1; c = rand() % m + 1;
    if(b > a) swap(a, b);
    fo(i, n) rep(c, 'a', 'z') layout[i][c] = rand() % 10 == 0;
    fo(i, 200) s += rand() % 26 + 'a';
#endif
    ini(dp, -1);

    fo(j, n) dp[si(s)][j] = 0;
    for(int i = si(s) - 1; i >= 0; --i) {
        build(1, 0, n - 1, i + 1);
            //fo(jj, n) trace(jj, get(1, 0, n - 1, jj, jj));
        add(1, 0, n - 1, 0, 0, oo);
        assert(get(1, 0, n - 1, 0, 0) >= oo);
        re(j, 1, n) add(1, 0, n - 1, j, j, b * j);
            //fo(jj, n) trace(jj, get(1, 0, n - 1, jj, jj));

        fo(j, n) {
            dp[i][j] = oo;
            if(layout[j][s[i]]) {
                dp[i][j] = min(dp[i][j], c + dp[i+1][j]);
            } else {
                ll cur = c + (a-b) + get(1, 0, n - 1, 0, n - 1);
                trace(i, j, cur);
                dp[i][j] = min(dp[i][j], cur);
            }
            if(j + 1 < n) {
                add(1, 0, n - 1, 0, n - 1, -b);
                ll x = get(1, 0, n - 1, j, j);
                add(1, 0, n - 1, j, j, dp[i+1][j] + (n-1) * b - x);
                add(1, 0, n - 1, j + 1, j + 1, oo);
            }
        }
    }

    ll ans = dp[0][0];
    if(ans >= oo) ans = -1;
    cout << ans << endl;
    
    
	return 0;
}

