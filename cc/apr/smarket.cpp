/* string coder = "Balajiganapathi S"; // Never give up!  */

//#define LOCAL
#ifdef LOCAL
//#   define TRACE
#   define TEST
//#   define CHECK
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

int n, q;
int a[mx_n];

class Block {
public:
    int l, r;
    int n;
    vi cnts;
    int lcnt, rcnt;
    int ans;
    Block() {}
    Block(int i) {
        l = i; r = i;
        n = 1;
        lcnt = rcnt = 1;
        trace(l, r, lcnt, rcnt);
    }

    Block(const Block &b, int k) {
        l = b.l; r = b.r; n = b.n;
        lcnt = b.lcnt; rcnt = b.rcnt;
        ans = b.cnts.end() - lower_bound(all(b.cnts), k);
        trace(b.cnts, l, r, n, lcnt, rcnt, ans);
    }

    Block(const Block &b1, const Block &b2, int k) {
        ans = 0;
        if(k == -1) {
            cnts = b1.cnts;
            for(int c: b2.cnts) cnts.push_back(c);
        } else {
            ans += b1.ans + b2.ans;
            ans += b1.cnts.end() - lower_bound(all(b1.cnts), k);
            ans += b2.cnts.end() - lower_bound(all(b2.cnts), k);
        }

        l = b1.l; r = b2.r;
        n = b1.n + b2.n;

        if(b1.allSame()) {
            if(b2.allSame()) {
                if(a[b1.r] == a[b2.l]) {
                    lcnt = rcnt = b1.lcnt + b2.lcnt;
                } else {
                    lcnt = b1.lcnt; rcnt = b2.rcnt;
                }
            } else {
                if(a[b1.r] == a[b2.l]) {
                    lcnt = b1.lcnt + b2.lcnt;
                    rcnt = b2.rcnt;
                } else {
                    lcnt = b1.lcnt;
                    rcnt = b2.rcnt;
                    cnts.push_back(b2.lcnt);
                }
            }
        } else {
            if(b2.allSame()) {
                if(a[b1.r] == a[b2.l]) {
                    lcnt = b1.lcnt;
                    rcnt = b1.rcnt + b2.lcnt;
                } else {
                    lcnt = b1.lcnt;
                    rcnt = b2.rcnt;
                    cnts.push_back(b1.rcnt);
                }
            } else {
                lcnt = b1.lcnt;
                rcnt = b2.rcnt;
                if(a[b1.r] == a[b2.l]) {
                    cnts.push_back(b1.rcnt + b2.lcnt);
                } else {
                    cnts.push_back(b1.rcnt);
                    cnts.push_back(b2.lcnt);
                }
            }
        }

        if(k == -1) {
            sort(all(cnts)); // merge + insert?
            trace(b1.l, b1.r, b2.l, b2.r, l, r, n, lcnt, rcnt, ans, cnts);
        } else {
            trace(b1.l, b1.r, b2.l, b2.r, l, r, n, lcnt, rcnt, ans);
            for(int c: cnts) if(c >= k) ++ans;
            cnts.clear();
        }
    }

    int getAns(int k) {
        if(lcnt >= k) ++ans;
        if(rcnt < n && rcnt >= k) ++ans;
        return ans;
    }

    bool allSame() const {
        return n == lcnt && lcnt == rcnt;
    }
    
};

Block seg[4 * mx_n];

void build(int i, int l, int r) {
    if(l == r) {
        seg[i] = Block(l);
        return;
    }
    int i1 = 2 * i + 1, i2 = 2 * i + 2;
    int m = (l + r) / 2;
    build(i1, l, m); build(i2, m + 1, r);
    seg[i] = Block(seg[i1], seg[i2], -1);
}

int ql, qr, qk;

Block get(int i, int l, int r) {
    if(ql <= l && r <= qr) {
        return Block(seg[i], qk);
    }
    int i1 = 2 * i + 1, i2 = 2 * i + 2;
    int m = (l + r) / 2;
    if(m < ql) return get(i2, m + 1, r);
    if(m + 1 > qr) return get(i1, l, m);
    return Block(get(i1, l, m), get(i2, m + 1, r), qk);
}

int solve() {
    Block b = get(1, 1, n);
    return b.getAns(qk);
}

int brute() {
    int ret = 0;
    int last = -1, lcnt = 0;
    rep(i, ql, qr) {
        if(a[i] != last) {
            if(lcnt >= qk) ++ret;
            last = a[i];
            lcnt = 1;
        } else {
            ++lcnt;
        }
    }
    if(lcnt >= qk) ++ret;

    return ret;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
#ifndef TEST
    cin >> t;
#else
    t = 3;
#endif
    while(t--) {
#ifndef TEST
        cin >> n >> q;
        rep(i, 1, n) cin >> a[i];
#else
        n = 100000;
        q = 100000;
        rep(i, 1, n) a[i] = rand() % 10 + 1;
#endif
#ifdef CHECK
        rep(i, 1, n) cerr << a[i] << " ";
        cerr << endl;
#endif
        build(1, 1, n);
        fo(i, q) {
#ifndef TEST
            cin >> ql >> qr >> qk;
#else
            ql = rand() % n + 1;
            qr = rand() % n + 1;
            qk = rand() % 10 + 1;
            if(qr < ql) swap(ql, qr);
#endif
            trace(ql, qr, qk);
            int ans = solve();
#ifdef CHECK
            int bans = brute();
            if(ans != bans) {
                trace(ans, bans);
                assert(ans == bans);
            }
#endif
            cout << ans << '\n';
        }
    }

    
	return 0;
}

