/* string coder = "Balajiganapathi S"; // Never give up!  */

//#define LOCAL
#ifdef LOCAL
#   define TRACE
#   define TEST
#else
#   define NDEBUG
#   define FAST
#endif

#include<bits/stdc++.h>

using namespace std;

/* aliases */
using vi  = vector<int>;
using pi  = pair<int, int>;
using ll  = long long int;
using ld  = long double;

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
    //assert(p >= 0);
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
        //trace(buffer);
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
constexpr int mx_n = 15;
constexpr int mx_deg = (1 << (mx_n)) + 1;
int a[mx_n], n;

int ans_d;

int fact[mx_deg], ifact[mx_deg];
int inv2, inv3;

inline int comb(int n, int k) {
    return 1ll * fact[n] * ifact[k] % mod * ifact[n-k] % mod;
}

inline void mod_add(int &a, int b) {
    a += b;
    if(a >= mod) a -= mod;
}

inline void mod_sub(int &a, int b) {
    a += (mod-b);
    if(a >= mod) a -= mod;
}

inline void mod_mul(int &a, int b) {
    a = 1ll * a * b % mod;
}

void pre() {
    fact[0] = ifact[0] = fact[1] = ifact[1] = 1;
    re(i, 2, mx_deg) ifact[i] = (mod - 1ll * (mod/i) * ifact[mod % i] % mod);
    inv2 = ifact[2];
    inv3 = ifact[3];
    re(i, 2, mx_deg) {
        fact[i] = 1ll * fact[i-1] * i % mod;
        ifact[i] = 1ll * ifact[i] * ifact[i-1] % mod;
    }
}

class Poly {
public:
    vector<int> coeffs;
    Poly() {}
    Poly(int d): coeffs(d+1) {}
    Poly(const Poly & p) noexcept: coeffs(p.coeffs) {}
    //Poly(Poly && p) noexcept: coeffs(move(p.coeffs)) {}
    Poly(initializer_list<int>  lst) {
        for(auto& x: lst) coeffs.push_back(x);
        if(si(coeffs) == 0) coeffs.resize(1);
    }
    Poly operator+ (const Poly& rhs) const;
    Poly operator* (const Poly& rhs) const;
    Poly operator* (int rhs) const;
    Poly operator- (const Poly& rhs) const;

    Poly& operator+= (const Poly& rhs);
    Poly& operator-= (const Poly& rhs);
    Poly& operator+= (const int rhs);
    Poly& operator*= (const int rhs);

    bool operator== (const Poly&rhs) const;

    Poly modX(int m) const;
    Poly mulX(int m) const;
    Poly divX(int m) const;

    Poly square() const { return (*this) * (*this); };
    void selfMulX(int m);

    Poly& operator=(const Poly& rhs) {
        coeffs = rhs.coeffs;
        return *this;
    }
    
    /*
    Poly& operator=(const Poly&& rhs) {
        coeffs = move(rhs.coeffs);
        return *this;
    }
    */

    int& operator[] (size_t idx) {return coeffs[idx]; }

    int maxDegree() const { return int(coeffs.size()) - 1; }
};

Poly Poly::operator+ (const Poly& rhs) const {
    Poly res(*this);
    res += rhs;
    return res;
}

Poly Poly::operator- (const Poly& rhs) const {
    Poly res(*this);
    res -= rhs;
    return res;
}

Poly Poly::operator* (const Poly& rhs) const {
    int d1 = maxDegree(), d2 = rhs.maxDegree();
    int m = max(d1, d2);

    if(min(d1, d2) <= (1 << 7)) {
        Poly res(d1 + d2);
        rep(i, 0, d1) rep(j, 0, d2) {
            res.coeffs[i+j] = (res.coeffs[i+j] + 1ll * coeffs[i] * rhs.coeffs[j]) % mod;
        }

        //trace(*this, rhs, res);
        return res;
    } else {
        m = (min(d1, d2) + 1) / 2;
        Poly x1(divX(m)), x0(modX(m));
        Poly y1(rhs.divX(m)), y0(rhs.modX(m));

        Poly z1((x0 + x1) * (y0 + y1));
        x0 = x0 * y0;
        x1 = x1 * y1;

        int dx1 = x1.maxDegree();
        x0.coeffs.resize(dx1+1);
        //z1 -= x1;
        //z1 -= x0;
        assert(dx1 <= min(x0.maxDegree(), z1.maxDegree()));
        rep(i, 0, dx1) {
            mod_sub(z1.coeffs[i], x1.coeffs[i]);
            mod_sub(z1.coeffs[i], x0.coeffs[i]);
        }

        x1.selfMulX(2 * m);
        int dz1 = z1.maxDegree();

        //z1.selfMulX(m);
        //x1 += z1;
        //x1 += x0;
        x0.coeffs.resize(dz1+1);
        assert(dz1+m <= x1.maxDegree() && dz1 <= x0.maxDegree());
        rep(i, 0, dz1) {
            mod_add(x1.coeffs[i+m], z1.coeffs[i]);
            mod_add(x1.coeffs[i], x0.coeffs[i]);
        }

        return x1;
    } 
}


// this / X ^ m
Poly Poly::divX(int m) const {
    int d = maxDegree();
    assert(d >= m);
    if(d < m) return Poly(0);

    Poly res(d - m);
    //rep(i, m, d) res.coeffs[i-m] = coeffs[i];
    memcpy(res.coeffs.data(), coeffs.data()+m, (d-m+1) * sizeof(int));
    return res;
}

// this % X ^ m
Poly Poly::modX(int m) const {
    int d = maxDegree();
    assert(m > 0 && d >= m);
    if(d < m || m == 0) return *this;

    Poly res(m-1);
    //rep(i, 0, m - 1) res.coeffs[i] = coeffs[i];
    memcpy(res.coeffs.data(), coeffs.data(), m * sizeof(int));
    return res;
}

// this * X ^ m
Poly Poly::mulX(int m) const {
    int d = maxDegree();
    Poly res(d+m);
    //rep(i, 0, d) res.coeffs[i+m] = coeffs[i];
    memcpy(res.coeffs.data()+m, coeffs.data(), (d+1) * sizeof(int));
    return res;
}

// this * X ^ m
void Poly::selfMulX(int m) {
    int d = maxDegree();
    coeffs.resize(d + m + 1);
    for(int i = d; i >= 0; --i) {
        coeffs[i+m] = coeffs[i];
        coeffs[i] = 0;
    }
}

Poly Poly::operator* (int rhs) const {
    Poly res(*this);
    for(auto &cur: res.coeffs) mod_mul(cur, rhs);
    return res;
}

Poly& Poly::operator+= (const Poly& p) {
    int dp = p.maxDegree();
    if(maxDegree() < dp) coeffs.resize(dp+1);
    rep(i, 0, dp) mod_add(coeffs[i], p.coeffs[i]);
    return *this;
}

Poly& Poly::operator-= (const Poly& p) {
    int dp = p.maxDegree();
    if(maxDegree() < dp) coeffs.resize(dp+1);
    rep(i, 0, dp) mod_sub(coeffs[i], p.coeffs[i]);
    return *this;
}

Poly& Poly::operator+= (int c) {
    mod_add(coeffs[0], c);
    return *this;
}

Poly& Poly::operator*= (int c) {
    for(auto& cur: coeffs) mod_mul(cur, c);
    return *this;
}

bool Poly::operator== (const Poly&rhs) const {
    int d = maxDegree();
    if(d != rhs.maxDegree()) return false;
    rep(i, 0, d) if(coeffs[i] != rhs.coeffs[i]) return false;
    return true;
}

ostream &operator <<(ostream &o, const Poly &p) { // print a Poly
    int d = p.maxDegree();
    bool f = true;
    for(int i = d; i >= 0; --i) {
        auto cur = p.coeffs[i];
        if(!f) o << " + ";
        if(i == 0 || cur != 1) o << cur;
        if(i) {
            o << "X";
            if(i != 1) o << i;
        }
        f = false;
    }
    return o;
}

int coeffX;
class Result {
public:
    Poly a, b;
    Result(): a(0), b(0) {}
    Result(const Poly& a, const Poly& b): a(a), b(b) {}
    Result(const Result& r): a(r.a), b(r.b) {}
    //Result(const Result&& r): a(move(r.a)), b(move(r.b)) {}

    Result& operator= (const Result& r) { a = r.a; b = r.b; return *this; }
    Result& operator= (const Result&& r) { a = move(r.a); b = move(r.b); return *this;  }

    Result& operator+= (const Result& r) { a += r.a; b += r.b; return *this; }
    Result& operator-= (const Result& r) { a -= r.a; b -= r.b; return *this; }
    Result& operator*= (int x) { a *= x; b *= x; return *this; }


    Result operator+ (const Result& r) const { Result res(*this); return res += r;}
    Result operator- (const Result& r) const { Result res(*this); return res -= r;}
    Result operator* (int x) const { Result res(*this); return res *= x;; }
    Result operator* (const Result& r) const { Result res(*this); return res *= r;}

    Result& operator*= (const Result& r) { 
        Poly a2 = a * r.a, b2 = b * r.b;
        b = (a + b) * (r.a + r.b);
        b -= a2 + b2;
        a = a2 + (b2 * coeffX).mulX(1);
        /*
        auto ta = a * a + b * r.b * coeffX;
        auto tb = a * r.b + b * r.a;
        a = ta; b = tb;
        */
        return *this;
    }

};

ostream &operator <<(ostream &o, const Result &r) { // print a Result
    return o << "(" << r.a << " + (sq)" << r.b << ")";
}

#define prev adfsads
Result ans;


// (x + sqrt(coeffX)) ^ n
Result getPow(int n) {
    assert(n % 2 == 0);
    Result res(Poly(n/2), Poly(n/2));
    int cur = 1;
    for(int i = n/2-1; i >= 0; --i) {
        res.b.coeffs[i] = 1ll * comb(n, 2 * i + 1) * cur % mod;
        cur = 1ll * cur * coeffX % mod;
        res.a.coeffs[i] = 1ll * comb(n, 2 * i) * cur % mod;
    }
    res.a.coeffs[n/2] = 1;

    return res;
}

Result doSubs(Result r) {
    int d = r.a.maxDegree();
    if(d <= (1 << 6)) {
        Result res;
        rep(i, 0, d) {
            auto cur = getPow(2 * i) * r.a.coeffs[i];
            //trace(i, getPow(2 * i), r.a.coeffs[i], cur);
            res += cur;
        }
        return res;
    } else {
        int m = (d + 1) / 2;
        Result r1(r.a.divX(m), r.b.divX(m)), r2(r.a.modX(m), r.b.modX(m));
        //trace(m, r1, r2);
        r1 = doSubs(r1);
        r2 = doSubs(r2);
        //trace(getPow(2 * m), r1, r2);
        return getPow(2 * m) * r1 + r2;
    }
    //trace(r, res);
}

Result subs(Result& r) {
    r.b.coeffs.resize(r.a.coeffs.size());
    assert(r.a.maxDegree() == r.b.maxDegree());
    Result res = doSubs(r);
    res.b.coeffs.pop_back();
    //trace(res.a, res.b, res.a.square(), (res.b.square() * coeffX).mulX(1));
    res = Result(res.a.square() - (res.b.square() * coeffX).mulX(1), Poly(2 * r.a.maxDegree()));
    //trace(res);
    return res;
}

void solve() {
    sort(a, a + n); reverse(a, a + n); // This makes stuff faster; no idea why
    ans = Result(Poly({mod-a[0], 1}), Poly({0, 0}));
    trace(ans);
    re(i, 1, n) {
        coeffX = a[i];
        trace(i, coeffX);
        ans = subs(ans);
    }
    if(n <= 5) trace(ans);
}

int main() {
    pre();
    int t;
    cin >> t;
    while(t--) {
        cin >> n;
        fo(i, n) cin >> a[i];
        solve();
        cout << (1 << n) << endl;
        cout << ans.a.coeffs[0];
        rep(i, 1, (1 << (n-1))) cout << " 0 " << ans.a.coeffs[i];
        cout << endl;
    }
    
    
	return 0;
}

