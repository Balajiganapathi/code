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
constexpr int mx_n = 15;
constexpr int mx_deg = (1 << (mx_n)) + 1;
int a[mx_n], n;

int ans_d;
int ans[mx_deg];

int fact[mx_deg], ifact[mx_deg];

int inv2, inv3;
void pre() {
    fact[0] = ifact[0] = fact[1] = ifact[1] = 1;
    re(i, 2, mx_deg) ifact[i] = (mod - 1ll * (mod/i) * ifact[mod % i] % mod);
    int ci;
    re(i, 2, mx_deg) {
        fact[i] = 1ll * fact[i-1] * i % mod;
        ifact[i] = 1ll * ifact[i] * ifact[i-1] % mod;
    }
    inv2 = modpow(2, mod - 2, mod);
    inv3 = modpow(3, mod - 2, mod);
}

inline int comb(int n, int k) {
    //assert(n < mx_deg && k < mx_deg);
    return 1ll * fact[n] * ifact[k] % mod * ifact[n-k] % mod;
}

/*-------------------------------------------------------------------------------------------------------------------------------------*/
/*<modint>*/
// ASUMES mod is PRIME
template<int mod>
class modint {
    static_assert(mod > 0, "mod must be a positive value");
    static_assert(1ll * (mod - 1) + (mod - 1) == (mod - 1) + (mod - 1), "addition of 2 modints must fit in int");

private:
    int val;

public:
    constexpr modint(): val(0) { }

    modint(const int &_val): val(_val) {
        val %= mod;
        if(val < 0) val += mod;
    }

    modint(const modint<mod> &m): val(m.val) { }

    modint<mod> operator +(modint<mod> m) const {
        modint<mod> ret;
        ret.val = val + m.val;
        if(ret.val >= mod) ret.val -= mod;

        return ret;
    }

    modint<mod> operator *(modint<mod> m) const { 
        modint<mod> ret;
        ret.val = 1ll * val * m.val % mod;

        return ret;
    }

    modint<mod> operator -(modint<mod> m) const { return *this + m.negate(); }
    modint<mod> operator /(modint<mod> m) const { return *this * m.inverse(); }
    modint<mod>& operator +=(const modint<mod>& m) { return *this = *this + m; }
    modint<mod>& operator -=(const modint<mod>& m) { return *this = *this - m; }
    modint<mod>& operator *=(const modint<mod>& m) { return *this = *this * m; }

    bool operator ==(modint<mod> m) const { return val == m.val; }
    bool operator !=(modint<mod> m) const { return val != m.val; }
    bool operator <(modint<mod> m) const { return val < m.val; }
    bool operator >(modint<mod> m) const { return val > m.val; }

    modint<mod> negate() const { return modint<mod>(-val); }

    modint<mod> inverse() const {
        //assert(__gcd(val, mod) == 1);
        return pow(mod - 2);
    }

    template<typename T> // to support both int and ll
    modint<mod> pow(T p) const {
        modint<mod> ret(1), cur(*this);
        for(; p; p /= 2) {
            if(p & 1) ret = ret * cur;
            cur = cur * cur;
        }

        return ret;
    }

    int value() const { return val; }
};

template<int mod>
ostream& operator <<(ostream& os, const modint<mod> m) { // print a modint
    return os << m.value();
}

template<int mod>
istream& operator >>(istream& is, volatile modint<mod> &m) { // input a modint
    int x;
    is >> x;
    m = modint<mod>(x);
    return is;
}
/*</modint>*/
/*-------------------------------------------------------------------------------------------------------------------------------------*/

int coeffX;
class Coeff {
public:
    int a, b; // a + b * root(coeffX)
    Coeff(): a(0), b(0) {}
    Coeff(int a): a(a), b(0) {}
    Coeff(int a, int b): a(a), b(b) {}
    Coeff(const Coeff& rhs): a(rhs.a), b(rhs.b) {}

    const Coeff& operator=(const Coeff& rhs) {
        a = rhs.a;
        b = rhs.b;
        return *this;
    }

    Coeff& operator += (const Coeff& rhs);
    Coeff& operator -= (const Coeff& rhs);
    Coeff& operator *= (const Coeff& rhs);
    Coeff& operator *= (int rhs);

    Coeff operator + (const Coeff& rhs) const { Coeff res(*this); res += rhs; return res; }
    Coeff operator - (const Coeff& rhs) const { Coeff res(*this); res -= rhs; return res; }
    Coeff operator * (const Coeff& rhs) const { Coeff res(*this); res *= rhs; return res; }
    bool operator == (const Coeff& rhs) const { return a == rhs.a && b == rhs.b; }

    void halfNeg() {b = (mod - b);}
};

Coeff& Coeff::operator += (const Coeff& rhs) {
    a += rhs.a;
    if(a >= mod) a -= mod;
    b += rhs.b;
    if(b >= mod) b -= mod;
    return *this;
}

Coeff& Coeff::operator -= (const Coeff& rhs) {
    int ta = (rhs.a? (mod - rhs.a): 0), tb = (rhs.b? (mod - rhs.b): 0);

    a += ta;
    if(a >= mod) a -= mod;
    b += tb;
    if(b >= mod) b -= mod;
    return *this;
}

Coeff& Coeff::operator *= (const Coeff& rhs) {
    int ta = a, tb = b;
    a = (1ll * ta * rhs.a + 1ll * tb * rhs.b % mod * coeffX) % mod;
    b = (1ll * ta * rhs.b + 1ll * tb * rhs.a) % mod;
    return *this;
}

Coeff& Coeff::operator *= (int rhs) {
    a = 1ll * a * rhs % mod;
    b = 1ll * b * rhs % mod;
    return *this;
}

ostream &operator <<(ostream &o, const Coeff &v) { // print a Coeff
    if(v.a && v.b) {
        o << "(" << v.a << "+";
        if(v.b != 1) o << v.b;
        o << "s(" << coeffX << "))";
    } else {
        if(v.b) {
            if(v.b != 1) o << v.b;
            o << "s(" << coeffX << ")";
        } else if(v.a != 1) {
            o << v.a;
        }
    }
    return o;
}

template<typename T>
class Polynomial {
public:
    vector<T> coeffs;
    Polynomial() {}
    Polynomial(int d): coeffs(d+1) {}
    Polynomial(const Polynomial<T>& p) noexcept: coeffs(p.coeffs) {}
    Polynomial(Polynomial<T>&& p) noexcept: coeffs(move(p.coeffs)) {}
    Polynomial(initializer_list<T> lst) {
        for(auto& x: lst) coeffs.push_back(x);
        if(si(coeffs) == 0) coeffs.resize(1);
    }
    Polynomial operator+ (const Polynomial& rhs) const;
    Polynomial operator* (const Polynomial& rhs) const;
    Polynomial operator* (const T& rhs) const;
    Polynomial operator* (int rhs) const;
    Polynomial operator- (const Polynomial& rhs) const;

    Polynomial& operator+= (const Polynomial& rhs);
    Polynomial& operator-= (const Polynomial& rhs);
    Polynomial& operator+= (const T& rhs);
    Polynomial& operator*= (const T& rhs);

    Polynomial modX(int m) const;
    Polynomial mulX(int m) const;
    Polynomial divX(int m) const;

    Polynomial substitute(const Polynomial& P) const;
    Polynomial pow(int p) const;
    tuple<Polynomial<modint<mod>>, Polynomial<modint<mod>>> split() const;
    bool hasOddZero() const;
    Polynomial inflateSq(int sx) const;
    Polynomial deflate() const;
    Polynomial square() const;
    void selfMulX(int m);

    Polynomial& operator=(const Polynomial& rhs) {
        coeffs = rhs.coeffs;
        return *this;
    }
    
    Polynomial& operator=(const Polynomial&& rhs) {
        coeffs = move(rhs.coeffs);
        return *this;
    }

    T& operator[] (size_t idx) {return coeffs[idx]; }

    int maxDegree() const { return int(coeffs.size()) - 1; }
};

template<typename T>
Polynomial<T> Polynomial<T>::operator+ (const Polynomial<T>& rhs) const {
    int d1 = maxDegree(), d2 = rhs.maxDegree();
    int d = max(d1, d2);
    Polynomial res(d);

    rep(i, 0, min(d1, d2)) {
        res.coeffs[i] += coeffs[i];
        res.coeffs[i] += rhs.coeffs[i];
    }


    rep(i, min(d1, d2)+1, d) {
        if(i <= d1) res.coeffs[i] += coeffs[i];
        if(i <= d2) res.coeffs[i] += rhs.coeffs[i];
    }

    return res;
}

template<typename T>
Polynomial<T> Polynomial<T>::operator- (const Polynomial<T>& rhs) const {
    int d1 = maxDegree(), d2 = rhs.maxDegree();
    int d = max(d1, d2);
    Polynomial<T> res(d);

    rep(i, 0, min(d1, d2)) {
        res.coeffs[i] += coeffs[i];
        res.coeffs[i] -= rhs.coeffs[i];
    }

    rep(i, min(d1, d2)+1, d) {
        if(i <= d1) res.coeffs[i] += coeffs[i];
        if(i <= d2) res.coeffs[i] -= rhs.coeffs[i];
    }

    return res;
}

template<typename T>
Polynomial<T> Polynomial<T>::operator* (const Polynomial<T>& rhs) const {
    int d1 = maxDegree(), d2 = rhs.maxDegree();
    int m = max(d1, d2);

    if(1ll * d1 * d2 <= 2000) {
        Polynomial<T> res(d1 + d2);
        rep(i, 0, d1) rep(j, 0, d2) {
            res.coeffs[i+j] += coeffs[i] * rhs.coeffs[j];
        }

        return res;
    } else if(true) {
        m = (m + 1) / 2;
        Polynomial<T> x1(divX(m)), x0(modX(m));
        Polynomial<T> y1(rhs.divX(m)), y0(rhs.modX(m));

        Polynomial<T> z1((x1 + x0) * (y1 + y0));
        x1 = x1 * y1;
        x0 = x0 * y0;
        z1 -= x1;
        z1 -= x0;

        x1.selfMulX(2 * m);
        z1.selfMulX(m);
        //z1.selfMulX(m);
        //x1 = x1.mulX(2 * m);
        x1 += z1;
        x1 += x0;

        return x1;
    } else {
            int bi = (m + 2) / 3;
            trace(d1, d2, bi);
            Polynomial<T> m0 = modX(bi);
            Polynomial<T> m1 = divX(bi).modX(bi);
            Polynomial<T> m2 = divX(2 * bi);

            Polynomial<T> pf = m0 + m2;
            Polynomial<T> p0 = m0;
            Polynomial<T> p1 = pf + m1;
            Polynomial<T> p1d = pf - m1;
            Polynomial<T> p2d = (p1d + m2) * 2 - m0;
            Polynomial<T> poo = m2;

            m0 = rhs.modX(bi);
            m1 = rhs.divX(bi).modX(bi);
            m2 = rhs.divX(2 * bi);
            Polynomial<T> qf = m0 + m2;
            //Polynomial<T> q0 = n0;
            p0 = p0 * m0;
            //Polynomial<T> q1 = qf + n1;
            p1 = p1 * (qf + m1);
            Polynomial<T> q1d = qf - m1;
            p1d = p1d * q1d;
            //Polynomial<T> q2d = (q1d + n2) * 2 - n0;
            p2d = p2d * ((q1d + m2) * 2 - m0);
            //Polynomial<T> qoo = n2;
            poo = poo * m2;


            Polynomial<T> res0 = p0;
            Polynomial<T> res4 = poo;
            Polynomial<T> res3 = (p2d - p1) * inv3;
            Polynomial<T> res1 = (p1 - p1d) * inv2;
            Polynomial<T> res2 = p1d - p0;
            res3 = (res2 - res3) * inv2 + poo * 2;
            res2 += res1 - res4;
            res1 -= res3;

            return res4.mulX(4 * bi) + res3.mulX(3 * bi) + res2.mulX(2 * bi) + res1.mulX(bi) + res0;
        }

}

template<typename T>
Polynomial<T> Polynomial<T>::square() const {
    int d = maxDegree();
    int m = d;

    if(1ll * d * d <= 2000) {
        Polynomial<T> res(2 * d);
        rep(i, 0, d) rep(j, 0, d) {
            res.coeffs[i+j] += coeffs[i] * coeffs[j];
        }

        return res;
    } else if(true) {
        m = (m + 1) / 2;
        Polynomial<T> x1(divX(m)), x0(modX(m));

        Polynomial<T> z1((x1 + x0).square());
        x1 = x1.square();
        x0 = x0.square();
        z1 -= x1;
        z1 -= x0;

        x1.selfMulX(2 * m);
        z1.selfMulX(m);
        x1 += z1;
        x1 += x0;

        return x1;
    }
}



// this / X ^ m
template<typename T>
Polynomial<T> Polynomial<T>::divX(int m) const {
    int d = maxDegree();
    //assert(d >= m);
    //if(d < m) return Polynomial<T>(0);

    Polynomial<T> res(d - m);
    //rep(i, m, d) res.coeffs[i-m] = coeffs[i];
    memcpy(res.coeffs.data(), coeffs.data()+m, (d-m+1) * sizeof(T));
    return res;
}

// this % X ^ m
template<typename T>
Polynomial<T> Polynomial<T>::modX(int m) const {
    int d = maxDegree();
    //assert(m > 0 && d >= m);
    //if(d < m || m == 0) return *this;

    Polynomial<T> res(m-1);
    //rep(i, 0, m - 1) res.coeffs[i] = coeffs[i];
    memcpy(res.coeffs.data(), coeffs.data(), m * sizeof(T));
    return res;
}

// this * X ^ m
template<typename T>
Polynomial<T> Polynomial<T>::mulX(int m) const {
    int d = maxDegree();
    Polynomial<T> res(d+m);
    //rep(i, 0, d) res.coeffs[i+m] = coeffs[i];
    memcpy(res.coeffs.data()+m, coeffs.data(), (d+1) * sizeof(T));
    return res;
}

// this * X ^ m
template<typename T>
void Polynomial<T>::selfMulX(int m) {
    int d = maxDegree();
    coeffs.resize(d + m + 1);
    for(int i = d; i >= 0; --i) {
        coeffs[i+m] = coeffs[i];
        coeffs[i] = 0;
    }
}



template<typename T>
Polynomial<T> Polynomial<T>::operator* (const T& rhs) const {
    Polynomial<T> res(*this);
    int d = res.maxDegree();
    rep(i, 0, d) res.coeffs[i] *= rhs;
    return res;
}

template<typename T>
Polynomial<T> Polynomial<T>::operator* (int rhs) const {
    Polynomial<T> res(*this);
    int d = res.maxDegree();
    rep(i, 0, d) res.coeffs[i] *= rhs;
    return res;
}

// X -> P
template<typename T>
Polynomial<T> Polynomial<T>::substitute(const Polynomial<T>& P) const {
    int d = maxDegree();
    if(d == 0) return *this;

    if(d < 200 && P.maxDegree() == 1) {
        Polynomial<T> res({coeffs[d]});
        res.coeffs.resize(d+1);
        res.coeffs[0] = coeffs[d];

        int dd = 0;
        for(int i = d-1; i >= 0; --i) {
            ++dd;
            //res = res.mulX(1) + (res * P.coeffs[0]);

            res.coeffs[dd] = res.coeffs[dd-1];
            for(int j = dd-1; j  >= 1; --j) {
                res.coeffs[j] *= P.coeffs[0];
                res.coeffs[j] += res.coeffs[j-1];
            }
            res.coeffs[0] *= P.coeffs[0];
            res.coeffs[0] += coeffs[i];
        }
        return res;
    } else {
        int m = (d + 1) / 2;
        Polynomial<T> x1 = divX(m), x0 = modX(m);
        x1 = x1.substitute(P);
        x0 = x0.substitute(P);
        return P.pow(m) * x1 + x0;
    }
}

vi C[mx_deg];
template<typename T>
Polynomial<T> Polynomial<T>::pow(int p) const {
    //static map<pi, Polynomial<T>> cache;
    pi idx(coeffX, p);
    //auto it = cache.find(idx);
    //if(it != cache.end()) return it->se;
    if(C[p].empty()) {
        C[p].resize(p+1);
        rep(i, 0, p) C[p][i] = comb(p, i);
    }

    int d = maxDegree();;
    if(d == 1) {
        Polynomial<T> res(p);
        T cur(1);
        for(int i = p; i >= 0; --i) {
            res.coeffs[i] = cur * C[p][i];;
            cur *= coeffs[0];
        }
        return res;
    }
    Polynomial<T> tmp(*this);
    Polynomial<T> res({T(1)});
    for(; p > 0; p /= 2) {
        if(p & 1) res = res * tmp;
        tmp = tmp.square();
    }

    //return cache[idx] = res;
    return res;
}

template<typename T>
Polynomial<T>& Polynomial<T>::operator+= (const Polynomial<T>& p) {
    int dp = p.maxDegree();
    rep(i, 0, dp) coeffs[i] += p.coeffs[i];
    return *this;
}

template<typename T>
Polynomial<T>& Polynomial<T>::operator-= (const Polynomial<T>& p) {
    int dp = p.maxDegree();
    rep(i, 0, dp) coeffs[i] -= p.coeffs[i];
    return *this;
}

template<typename T>
Polynomial<T>& Polynomial<T>::operator+= (const T& c) {
    coeffs[0] += c;
    return *this;
}

template<typename T>
Polynomial<T>& Polynomial<T>::operator*= (const T& c) {
    for(auto& cur: coeffs) cur *= c;
    return *this;
}

template<>
tuple<Polynomial<modint<mod>>, Polynomial<modint<mod>>> Polynomial<Coeff>::split() const {
    int d = maxDegree();
    Polynomial<modint<mod>> r1(d/2), r2(d/2-1);
    for(int i = 0; i <= d; i += 2) {
        r1.coeffs[i/2] = coeffs[i].a;
    }
    for(int i = 1; i <= d; i += 2) {
        r2.coeffs[i/2] = coeffs[i].b;
    }
    return make_tuple(r1, r2);
}

template<typename T>
bool Polynomial<T>::hasOddZero() const {
    int d = maxDegree();
    for(int i = 1; i <= d; i += 2) if(coeffs[i].b != 0) return false;
    return true;
}

template<typename T>
Polynomial<T> Polynomial<T>::inflateSq(int sx) const {
    int d = maxDegree();
    Polynomial<T> res(2 * d + sx);
    rep(i, 0, d) res.coeffs[2*i + sx] = coeffs[i];
    return res;
}

template<typename T>
Polynomial<T> Polynomial<T>::deflate() const {
    int d = maxDegree();
    Polynomial<T> res(d / 2);
    for(int i = 0; i <= d; i += 2) res.coeffs[i/2] = coeffs[i];
    return res;
}

template <typename T>
ostream &operator <<(ostream &o, Polynomial<T> &p) { // print a Poly
    int d = p.maxDegree();
    bool f = true;
    for(int i = d; i >= 0; --i) {
        auto &cur = p[i];
        if(!f) o << " + ";
        o << cur;
        if(i) {
            o << "X";
            if(i != 1) o << i;
        }
        f = false;
    }
    return o;
}

Polynomial<modint<mod>> dp[mx_n];

Polynomial<Coeff> toCoeff(Polynomial<modint<mod>> p) {
    int pd = p.maxDegree();
    Polynomial<Coeff> res(pd);
    rep(i, 0, pd) res.coeffs[i].a = p.coeffs[i].value();
    return res;
}

template<typename T>
Polynomial<T> interleave(Polynomial<T> a, Polynomial<T> b) {
    int d1 = a.maxDegree();
    int d2 = b.maxDegree();
    Polynomial<T> res(max(d1 * 2, d2 * 2 + 2));
    rep(i, 0, d1) res.coeffs[2 * i] = a.coeffs[i];
    rep(i, 0, d2) res.coeffs[2 * i + 2] -= b.coeffs[i];

    return res;
}

void solve() {
    dp[0] = Polynomial<modint<mod>>({mod-a[0], 0, 1});
    trace(0, dp[0]);
    re(i, 1, n) {
        coeffX = a[i];
        trace(i, coeffX);

        Polynomial<Coeff> s1({Coeff(0, 1), Coeff(1)});

        Polynomial<modint<mod>> q1, q2;
        Polynomial<Coeff> p1 = toCoeff(dp[i-1]).substitute(s1);

        tie(q1, q2) = p1.split();
        
        dp[i] = interleave(q1.square(), q2.square() * coeffX);
        //dp[i] = (q1 * q1).inflateSq(0) - (q2 * q2 * coeffX).inflateSq(2);
    }
    ans_d = dp[n-1].maxDegree();
    rep(i, 0, ans_d) ans[i] = dp[n-1][i].value();
}

int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(nullptr);
    pre();
    int t;
    cin >> t;
    while(t--) {
        cin >> n;
        fo(i, n) cin >> a[i];
        solve();
        cout << ans_d << endl;
        rep(i, 0, ans_d) cout << ans[i] << " ";
        cout << endl;
    }
    
    
	return 0;
}

