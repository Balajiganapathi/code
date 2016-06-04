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

/* fast io */
class fastio {
public:

    int cur;
    char buffer[(1 << 10)];

    inline void gc() {
        cur = getchar_unlocked();
    }

    inline void pc(char c) {
        putchar_unlocked(c);
    }

    bool skip() {
        for(gc(); cur && cur <= ' '; gc());
        return cur;
    }

    template<typename T>
    fastio& operator >>(T &n) {
        n = 0;
        bool neg = false;
        if(skip()) {
            if(cur == '-') {
                neg = true;
                gc();
            }
            for(; cur != '\0' && isdigit(cur); gc()) n = 10 * n + cur - '0';
            if(neg) n *= -1;
        }
        return *this;
    }

    fastio& operator >>(double &n) {
        *this >> buffer;
        trace(buffer);
        sscanf(buffer, "%lf", &n);
        return *this;
    }

    fastio& operator >>(char &c) {
        skip();
        c = cur;
        return *this;
    }

    fastio& operator >>(char *str) {
        if(skip()) {
            for(; cur && cur > ' '; gc(), str++) *str = cur;
        }
        *str = 0;
        return *this;
    }

    fastio& operator <<(const char *str) {
        for(; *str; ++str) pc(*str);
        return *this;
    }

    fastio& operator <<(const char &c) {
        pc(c);
        return *this;
    }

    template<typename T>
    fastio& operator <<(T n) {
        int len = 0;
        if(n < 0) {
            pc('-');
            n *= -1;
        }
        if(n == 0) buffer[len++] = '0';
        for(; n > 0; n /= 10) {
            buffer[len++] = char('0' + n % 10);
        }
        for(int i = len - 1; i >= 0; --i) pc(buffer[i]);
        return *this;
    }
} io;

#define endl '\n'
#define cin io
#define cout io



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
constexpr int mx_n = 400005;
constexpr int mx_in = 1000006;
constexpr int mx_q = 100005;
int till[mx_n], n;
int nxt[mx_n];
int cnt[mx_n], nxtb[mx_n];
int rnk[mx_in], pres[mx_in];
constexpr int s = 1024;

void pre() {
    nxt[mx_n - 1] = oo;
    for(int i = mx_n - 2; i >= 1; --i) {
        nxt[i] = min(till[i], nxt[i+1]);
    }
    fo(i, 10) trace(i, till[i], nxt[i]);


    for(int i = mx_n - 2; i >= 1; --i) {
        int cb = i / s;
        if(nxt[i] == oo) {
            nxtb[i] = oo;
            cnt[i] = 0;
        } else {
            if((nxt[i] + 1) / s == cb) {
                nxtb[i] = nxtb[nxt[i] + 1];
                cnt[i] = 1 + cnt[nxt[i] + 1];
            } else {
                nxtb[i] = nxt[i];
                cnt[i] = 1;
            }
        }
    }
    fo(i, 10) trace(i, nxtb[i], cnt[i]);
}

int solve(int a, int b) {
    int ba = a / s, bb = b / s;
    int ret = 0;
    if(b - a + 1 <= s) {
        for(int cur = a; nxt[cur] <= b; cur = nxt[cur] + 1) ++ret;
        return ret;
    }

    int cur = a;
    for(cur = a; nxt[cur] / s == ba; cur = nxt[cur] + 1) ++ret;
    for(; nxtb[cur] / s < bb; cur = nxtb[cur] + 1) ret += cnt[cur];
    for(; nxt[cur] <= b; cur = nxt[cur] + 1) ++ret;

    return ret;
}

int brute(int a, int b) {
    int ret = 0;
    for(int cur = a; nxt[cur] <= b; cur = nxt[cur] + 1) ++ret;
    return ret;
}

int st[mx_q], en[mx_q], a[mx_q], b[mx_q];

int main() {
    int q;
    fo(i, mx_n) till[i] = oo;
#ifdef TEST
    n = q = 100000;
#else
    cin >> n >> q;
#endif
    int s, e;
    fo(i, n) {
#ifdef TEST
        s = rand() % 1000000 + 1;
        e = rand() % 1000000 + 1;
        if(s > e) swap(s, e);
        e = min(s + rand() % 10 + 1, e);
#else
        cin >> s >> e;
#endif
        st[i] = s; en[i] = e;
        pres[st[i]] = pres[en[i]] = 1;
    }

    fo(i, q) {
#ifdef TEST
        a[i] = rand() % 1000000 + 1;
        b[i] = rand() % 1000000 + 1;
        if(a[i] > b[i]) swap(a[i], b[i]);
#else
        cin >> a[i] >> b[i];
#endif
        pres[a[i]] = pres[b[i]] = 1;
    }
    int idx = 0;
    fo(x, mx_in) if(pres[x]) rnk[x] = ++idx;

    fo(i, n) {
        st[i] = rnk[st[i]]; en[i] = rnk[en[i]];
        till[st[i]] = min(till[st[i]], en[i]);
    }

    pre();

    fo(i, q) {
        a[i] = rnk[a[i]]; b[i] = rnk[b[i]];
        int ans = solve(a[i], b[i]);
        cout << ans << endl;
#ifdef TEST
        /*
        int bans = brute(a[i], b[i]);
        if(ans != bans) {
            trace(a[i], b[i], ans, bans);
            assert(ans == bans);
        }
        */
#endif
    }
	return 0;
}

