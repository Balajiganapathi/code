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
constexpr int mx_n = 200005;
constexpr int mx_seg = 4 * mx_n;
int n, m, k;
int c[mx_n], n1, n2, a[mx_n], b[mx_n];
int ord[mx_n], rnk[mx_n];
int liked[mx_n];
vi by[4];
vector<ll> csum[4];

int cnt[mx_seg];
ll sum[mx_seg];

void build(int i, int a, int b) {
    if(a == b) {
        cnt[i] = 1;
        sum[i] = c[ord[a]];
        return;
    }
    int l = 2 * i + 1, r = 2 * i + 2;
    int m = (a + b) / 2;
    build(l, a, m);
    build(r, m + 1, b);
    cnt[i] = cnt[l] + cnt[r];
    sum[i] = sum[l] + sum[r];
}

void markIt(int i, int a, int b, int q, int mr) {
    if(a == b) {
        cnt[i] = mr;
        sum[i] = mr * c[ord[a]];
        return;
    }
    int l = 2 * i + 1, r = 2 * i + 2;
    int m = (a + b) / 2;
    if(q <= m) markIt(l, a, m, q, mr);
    else markIt(r, m + 1, b, q, mr);
    cnt[i] = cnt[l] + cnt[r];
    sum[i] = sum[l] + sum[r];
}

ll get(int i, int a, int b, int c) {
    trace(i, a, b, c, cnt[i]);
    if(cnt[i] == c) return sum[i];
    assert(cnt[i] >= c);
    if(c == 0 || a == b) return 0;

    int l = 2 * i + 1, r = 2 * i + 2;
    int m = (a + b) / 2;

    int fl = min(c, cnt[l]);
    ll s = get(l, a, m, fl);
    if(c - fl > 0) s += get(r, m + 1, b, c - fl);

    return s;
}

ll get(int c) {
    trace(c, cnt[1]);
    if(cnt[1] < c || c < 0) return oo;
    if(c == 0) return 0;
    return get(1, 1, n, c);
}

ll solve() {
    ll ans = oo;
    build(1, 1, n);
    trace(cnt[1]);

    // 0 both
    ll cur = 0;
    int lim = k;
    fo(i, 2) {
        int fmask = (1 << i);
        int till = min(si(by[fmask]), lim);

        ll c = 0;

        fo(j, till) {
            markIt(1, 1, n, rnk[by[fmask][j]], 0);
        }

        if(k != till) c = oo;
        else c = csum[fmask][till-1];
        cur += c;
    }

    if(cur < oo && 2 * k <= m) {
        cur += get(m - 2 * k);
        ans = min(ans, cur);
    }
    trace(ans);

    trace(lim);
    fo(i, si(by[3])) if(i <= m) {
        trace(cnt[1]);
        lim = max(0, lim-1);
        if(lim >= 0) {
            fo(i, 2) {
                int fmask = (1 << i);
                if(lim < si(by[fmask])) markIt(1, 1, n, rnk[by[fmask][lim]], 1);
            }
        }
        markIt(1, 1, n, rnk[by[3][i]], 0);
        if(2 * lim + i + 1 <= m && lim <= min(si(by[1]), si(by[2]))) {
            int r = m - (2 * lim + i + 1);
            ll cur = csum[3][i];
            trace(i, lim, csum[3][i], r, get(r));
            if(lim >= 1) {
                trace(csum[1][lim-1], csum[2][lim-1]);
                fo(i, 2) {
                    int fmask = (1 << i);
                    cur += csum[fmask][lim-1];
                }
            }
            cur += get(r);
            trace(get(r));
            ans = min(ans, cur);
            trace(i, lim, cur);
        }
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> k;
    rep(i, 1, n) cin >> c[i];
    rep(i, 1, n) ord[i] = i;
    sort(ord + 1, ord + 1 + n, [](int i, int j) -> bool {return c[i] < c[j];});
    rep(i, 1, n) rnk[ord[i]] = i;


    cin >> n1;
    fo(i, n1) cin >> a[i];
    cin >> n2;
    fo(i, n2) cin >> b[i];

    fo(i, n1) liked[a[i]] |= 1;
    fo(i, n2) liked[b[i]] |= 2;

    rep(i, 1, n) by[liked[i]].push_back(i);

    fo(i, 4) {
        trace(i, by[i]);
        sort(all(by[i]), [](int i, int j) -> bool {trace(i, j, c[i], c[j]); return c[i] < c[j];});
        trace(i, by[i]);
        for(int cur: by[i]) csum[i].push_back(c[cur]);
        partial_sum(all(csum[i]), csum[i].begin());
    }

    ll ans = solve();

    if(ans >= oo) ans = -1;
    cout << ans << endl;


	return 0;
}

