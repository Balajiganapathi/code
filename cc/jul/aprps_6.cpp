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
    assert(n < mx_deg && k < mx_deg);
    return 1ll * fact[n] * ifact[k] % mod * ifact[n-k] % mod;
}


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

class Polynomial {
    vector<Coeff> coeffs;
public:
    Polynomial() {}
    Polynomial(int d): coeffs(d+1) {}
    Polynomial(const Polynomial& p) noexcept: coeffs(p.coeffs) {}
    Polynomial(const Polynomial&& p) noexcept: coeffs(move(p.coeffs)) {}
    Polynomial(initializer_list<Coeff> lst) {
        for(auto& x: lst) coeffs.push_back(x);
        if(si(coeffs) == 0) coeffs.resize(1);
    }
    Polynomial operator+ (const Polynomial& rhs) const;
    Polynomial operator* (const Polynomial& rhs) const;
    Polynomial operator* (const Coeff& rhs) const;
    Polynomial operator* (int rhs) const;
    Polynomial operator- (const Polynomial& rhs) const;

    Polynomial& operator+= (const Polynomial& rhs);
    Polynomial& operator-= (const Polynomial& rhs);
    Polynomial& operator+= (const Coeff& rhs);
    Polynomial& operator*= (const Coeff& rhs);

    Polynomial modX(int m) const;
    Polynomial mulX(int m) const;
    Polynomial divX(int m) const;

    Polynomial substitute(const Polynomial& P) const;
    Polynomial pow(int p) const;
    tuple<Polynomial, Polynomial> split() const;
    bool hasOddZero() const;
    Polynomial inflateSq(int sx) const;

    const Polynomial& operator=(const Polynomial& rhs) {
        coeffs = rhs.coeffs;
        return *this;
    }
    Coeff& operator[] (size_t idx) {return coeffs[idx]; }

    int maxDegree() const { return int(coeffs.size()) - 1; }
};


Polynomial Polynomial::operator+ (const Polynomial& rhs) const {
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

Polynomial Polynomial::operator- (const Polynomial& rhs) const {
    int d1 = maxDegree(), d2 = rhs.maxDegree();
    int d = max(d1, d2);
    Polynomial res(d);

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

Polynomial Polynomial::operator* (const Polynomial& rhs) const {
    int d1 = maxDegree(), d2 = rhs.maxDegree();
    int m = (max(d1, d2) + 1) / 2;

    if(1ll * d1 * d2 <= 1000) {
        int d = d1 + d2;
        Polynomial res(d);
        rep(i, 0, d1) rep(j, 0, d2) {
            res.coeffs[i+j] += coeffs[i] * rhs.coeffs[j];
        }

        return res;
    } else if(m < (1 << 14)) {
        Polynomial x1(divX(m)), x0(modX(m));
        Polynomial y1(rhs.divX(m)), y0(rhs.modX(m));

        Polynomial z1((x1 + x0) * (y1 + y0));
        x1 = x1 * y1;
        x0 = x0 * y0;
        z1 -= x1;
        z1 -= x0;

        x1 = move(x1.mulX(2 * m));
        x1 += z1.mulX(m);
        x1 += x0;

        return x1;
    } else {
            int bi = (m + 2) / 3 + 1;
            trace(d1, d2, bi);
            Polynomial m0 = modX(bi);
            Polynomial m1 = divX(bi).modX(bi);
            Polynomial m2 = divX(2 * bi);

            Polynomial pf = m0 + m2;
            Polynomial p0 = m0;
            Polynomial p1 = pf + m1;
            Polynomial p1d = pf - m1;
            Polynomial p2d = (p1d + m2) * 2 - m0;
            Polynomial poo = m2;

            m0 = rhs.modX(bi);
            m1 = rhs.divX(bi).modX(bi);
            m2 = rhs.divX(2 * bi);
            Polynomial qf = m0 + m2;
            //Polynomial q0 = n0;
            p0 = p0 * m0;
            //Polynomial q1 = qf + n1;
            p1 = p1 * (qf + m1);
            Polynomial q1d = qf - m1;
            p1d = p1d * q1d;
            //Polynomial q2d = (q1d + n2) * 2 - n0;
            p2d = p2d * ((q1d + m2) * 2 - m0);
            //Polynomial qoo = n2;
            poo = poo * m2;


            Polynomial res0 = p0;
            Polynomial res4 = poo;
            Polynomial res3 = (p2d - p1) * inv3;
            Polynomial res1 = (p1 - p1d) * inv2;
            Polynomial res2 = p1d - p0;
            res3 = (res2 - res3) * inv2 + poo * 2;
            res2 += res1 - res4;
            res1 -= res3;

            return res4.mulX(4 * bi) + res3.mulX(3 * bi) + res2.mulX(2 * bi) + res1.mulX(bi) + res0;
        }

}

// this / X ^ m
Polynomial Polynomial::divX(int m) const {
    int d = maxDegree();
    if(d < m) return Polynomial({Coeff(0)});

    Polynomial res(d - m);
    //rep(i, m, d) res.coeffs[i-m] = coeffs[i];
    memcpy(res.coeffs.data(), coeffs.data()+m, (d-m+1) * sizeof(Coeff));
    return res;
}

// this % X ^ m
Polynomial Polynomial::modX(int m) const {
    int d = maxDegree();
    if(d < m) return *this;

    Polynomial res(m-1);
    //rep(i, 0, m - 1) res.coeffs[i] = coeffs[i];
    memcpy(res.coeffs.data(), coeffs.data(), m * sizeof(Coeff));
    return res;
}

// this * X ^ m
Polynomial Polynomial::mulX(int m) const {
    int d = maxDegree();
    Polynomial res(d+m);
    //rep(i, 0, d) res.coeffs[i+m] = coeffs[i];
    memcpy(res.coeffs.data()+m, coeffs.data(), (d+1) * sizeof(Coeff));
    return res;
}

Polynomial Polynomial::operator* (const Coeff& rhs) const {
    Polynomial res(*this);
    int d = res.maxDegree();
    rep(i, 0, d) res.coeffs[i] *= rhs;
    return res;
}

Polynomial Polynomial::operator* (int rhs) const {
    Polynomial res(*this);
    int d = res.maxDegree();
    rep(i, 0, d) res.coeffs[i] *= rhs;
    return res;
}

// X -> P
Polynomial Polynomial::substitute(const Polynomial& P) const {
    int d = maxDegree();

    if(d < 200) {
        Polynomial res({coeffs[d]});
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
        Polynomial x1 = divX(m), x0 = modX(m);
        x1 = x1.substitute(P);
        x0 = x0.substitute(P);
        return P.pow(m) * x1 + x0;
    }
}

vi C[mx_deg];
unordered_map<int, Polynomial> cache;
Polynomial Polynomial::pow(int p) const {
    auto it = cache.find(p);
    if(it != cache.end()) return it->se;
    if(C[p].empty()) {
        rep(i, 0, p) C[p].push_back(comb(p, i));
    }

    int d = maxDegree();;
    if(d == 1) {
        Polynomial res(p);
        Coeff cur(1);
        for(int i = p; i >= 0; --i) {
            res.coeffs[i] = cur * C[p][i];;
            cur *= coeffs[0];
        }
        return res;
    }
    Polynomial tmp(*this);
    Polynomial res({Coeff(1)});
    for(; p > 0; p /= 2) {
        if(p & 1) res = res * tmp;
        tmp = tmp * tmp;
    }

    return cache[p] = res;
}

Polynomial& Polynomial::operator+= (const Polynomial& p) {
    int dp = p.maxDegree();
    rep(i, 0, dp) coeffs[i] += p.coeffs[i];
    return *this;
}

Polynomial& Polynomial::operator-= (const Polynomial& p) {
    int dp = p.maxDegree();
    rep(i, 0, dp) coeffs[i] -= p.coeffs[i];
    return *this;
}

Polynomial& Polynomial::operator+= (const Coeff& c) {
    coeffs[0] += c;
    return *this;
}

Polynomial& Polynomial::operator*= (const Coeff& c) {
    for(auto& cur: coeffs) cur *= c;
    return *this;
}

tuple<Polynomial, Polynomial> Polynomial::split() const {
    int d = maxDegree();
    Polynomial r1(d/2), r2(d/2-1);
    for(int i = 0; i <= d; i += 2) {
        r1.coeffs[i/2] = Coeff(coeffs[i].a);
    }
    for(int i = 1; i <= d; i += 2) {
        assert(coeffs[i-1].b == 0);
        r2.coeffs[i/2] = Coeff(coeffs[i].b);
    }
    return make_tuple(r1, r2);
}

bool Polynomial::hasOddZero() const {
    int d = maxDegree();
    for(int i = 1; i <= d; i += 2) if(coeffs[i].b != 0) return false;
    return true;
}

Polynomial Polynomial::inflateSq(int sx) const {
    int d = maxDegree();
    Polynomial res(2 * d + sx);
    rep(i, 0, d) res.coeffs[2*i + sx] = coeffs[i];
    return res;
}

ostream &operator <<(ostream &o, Polynomial &p) { // print a Coeff
    int d = p.maxDegree();
    bool f = true;
    for(int i = d; i >= 0; --i) {
        auto &cur = p[i];
        if(cur.a || cur.b) {
            if(!f) o << " + ";
            o << cur;
            if(i) {
                o << "X";
                if(i != 1) o << i;
            }
            f = false;
        }
    }
    return o;
}

Polynomial dp[mx_n];

void solve() {
    dp[0] = Polynomial({mod-a[0], 0, 1});
    trace(0, dp[0]);
    re(i, 1, n) {
        coeffX = a[i];
        trace(i, coeffX);

        Polynomial s1({Coeff(0, 1), Coeff(1)});
        cache.clear();

        Polynomial p1 = dp[i-1].substitute(s1);
        Polynomial p2;

        tie(p1, p2) = p1.split();
        dp[i] = (p1 * p1).inflateSq(0) - (p2 * p2 * coeffX).inflateSq(2);
    }
    ans_d = dp[n-1].maxDegree();
    rep(i, 0, ans_d) ans[i] = dp[n-1][i].a;
}

int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(nullptr);
    pre();
    int t;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        fo(i, n) scanf("%d", a+i);
        solve();
        printf("%d\n", ans_d);
        rep(i, 0, ans_d) printf("%d ", ans[i]);
        printf("\n");
    }
    
    
	return 0;
}

