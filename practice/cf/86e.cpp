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
constexpr int mx = (1 << 25) + 10;

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
    modint() { val = 0; }

    modint(const int &_val) {
        val = _val;
        if(val < 0) {
            val %= mod;
            if(val < 0) val += mod;
        } else if(val >= mod) {
            val %= mod;
        }
    }

    modint(const modint<mod> &m) { val = m.val; }

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

    bool operator ==(modint<mod> m) const { return val == m.val; }
    bool operator !=(modint<mod> m) const { return val != m.val; }
    bool operator <(modint<mod> m) const { return val < m.val; }
    bool operator >(modint<mod> m) const { return val > m.val; }

    modint<mod> negate() const { return modint<mod>(-val); }

    modint<mod> inverse() const {
        assert(__gcd(val, mod) == 1);
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
ostream& operator <<(ostream& os, modint<mod> m) { // print a modint
    return os << m.value();
}

template<int mod>
istream& operator >>(istream& is, modint<mod> &m) { // input a modint
    int x;
    is >> x;
    m = modint<mod>(x);
    return is;
}

/*-------------------------------------------------------------------------------------------------------------------------------------*/
/*<matrix>*/
template<typename T>
class matrix {
private:
    vector<vector<T>> val;
    int n, m;
public:
    constexpr matrix(): n(0), m(0) {}

    matrix(int _n, int _m): n(_n), m(_m) {
        assert(n > 0);
        assert(m > 0);
        val = vector<vector<T>>(n, vector<T>(m));
    }

    matrix(int _n): n(_n), m(_n) {
        assert(n > 0);
        assert(m > 0);
        val = vector<vector<T>>(n, vector<T>(m));
    }

    matrix(const initializer_list<initializer_list<T>> &_val) {
        n = _val.size();
        assert(n > 0);
        m = _val.begin()->size();
        assert(m > 0);
        val = vector<vector<T>>(n, vector<T>(m));

        int r = 0;
        for(const auto &row: _val) {
            int c = 0;
            assert(row.size() == m);
            for(const auto &entry: row) {
                val[r][c++] = entry;
            }
            ++r;
        }
    }

    int rows() const { return n; }
    int columns() const { return m; }

    void makeIdentity() {
        assert(n == m);
        for(int i = 0; i < n; ++i) for(int j = 0; j < m; ++j) {
            val[i][j] = (i == j? 1: 0);
        }
    }

    void fill(const T &x) {
        for(int i = 0; i < n; ++i) for(int j = 0; j < m; ++j) val[i][j] = x;
    }

    bool isIdentity() const {
        assert(n == m);
        for(int i = 0; i < n; ++i) for(int j = 0; j < m; ++j) {
            if(i == j && val[i][j] != 1) return false;
            if(i != j && val[i][j] != 0) return false;
        }
        return true;
    }

    matrix operator +(const matrix &mat) const {
        assert(n == mat.n && m == mat.m);
        matrix ret(*this);
        for(int i = 0; i < n; ++i) for(int j = 0; j < m; ++j) ret.val[i][j] = ret.val[i][j] + mat.val[i][j];
        return ret;
    }

    matrix operator -(const matrix &mat) const {
        assert(n == mat.n && m == mat.m);
        matrix ret(*this);
        for(int i = 0; i < n; ++i) for(int j = 0; j < m; ++j) ret.val[i][j] = ret.val[i][j] - mat.val[i][j];
        return ret;
    }

    matrix operator *(const matrix &mat) const {
        assert(m == mat.n);
        matrix ret(n, mat.m);
        for(int i = 0; i < n; ++i) for(int j = 0; j < mat.m; ++j) for(int k = 0; k < m; ++k) {
            ret.val[i][j] = ret.val[i][j] + val[i][k] * mat.val[k][j];
        }
        return ret;
    }

    template<typename N>
    matrix pow(N p) const {
        assert(n == m);
        matrix ret(n);
        ret.makeIdentity();
        matrix cur(*this);

        for(; p; p /= 2) {
            if(p & 1) ret = ret * cur;
            cur = cur * cur;
        }

        return ret;
    }

    T &operator()(int x, int y) { return val[x][y]; }

    matrix operator()(int x) { 
        matrix ret(1, m);
        for(int j = 0; j < m; ++j) ret(0, j) = val[x][j];
        return ret;
    }

};

template<typename T>
ostream& operator <<(ostream& os, matrix<T> mat) { // print a matrix
    os << '\n';
    for(int i = 0; i < mat.rows(); ++i) {
        for(int j = 0; j < mat.columns(); ++j) os << mat(i, j) << ' ';
        os << '\n';
    }
    return os;
}
/*</matrix>*/
/*-------------------------------------------------------------------------------------------------------------------------------------*/

template<int mx>
class Seive {
private:
    bitset<mx> notprime;
    vector<int> primes;
public:
    Seive() {
        notprime[0] = notprime[1] = 1;
        notprime[2] = 0;
        for(int i = 3; i * i < mx; ++i) if(!notprime[i]) {
            for(int j = i * i; j < mx; j += i) notprime[j] = 1;
        }

        primes.push_back(2);
        for(int i = 3; i < mx; i += 2) if(!notprime[i]) primes.push_back(i);
    }

    vector<int> &allPrimes() { return primes; }

    template<typename T>
    bool isprime(T n) {
        assert(n < T(mx) * mx);
        if(n < mx) return !notprime[n];
        for(T x: primes) {
            if(x * x > n) break;
            if(n % x == 0) return false;
        }

        return true;
    }
};

Seive<mx> seive;
int n;

matrix<modint<2>> gen() {
    matrix<modint<2>> ret(n, n);
    fo(i, n - 1) ret(i, i + 1) = 1;
    fo(j, n) ret(n - 1, j) = rand() % 2;
    return ret;
}

bool ok(const matrix<modint<2>> &mat) {
    ll p = (1ll << n) - 1;
    //trace(mat, p, mat.pow(p));
    if(mat.isIdentity() || !mat.pow(p).isIdentity()) return false;

    for(ll i = 3; i * i <= p; i += 2) if(p % i == 0) {
        if(seive.isprime(i) && mat.pow(p / i).isIdentity()) return false;
        if(seive.isprime(p / i) && mat.pow(i).isIdentity()) return false;
    }

    return true;
}

matrix<modint<2>> solve(int _n) {
    n = _n;
    matrix<modint<2>> ans(n);

    do {
        ans = gen();
    } while(!ok(ans));
    
    return ans(n - 1);
}

void pre() {
    cout << "{{{0}}, {{0}}";
    for(int i = 2; i <= 50; ++i) {
        matrix<modint<2>> cur = solve(i);
        cout << ", {{" << cur(0, 0);
        for(int j = 1; j < i; ++j) cout << ", " << cur(0, j);
        cout << "}}";
        trace(i);
    }
    cout << "}\n";
}

matrix<modint<2>> dp[] = 
{{{0}}, {{0}}, {{1, 1}}, {{1, 1, 0}}, {{1, 0, 0, 1}}, {{1, 1, 1, 0, 1}}, {{1, 1, 0, 1, 1, 0}}, {{1, 0, 1, 1, 1, 1, 1}}, {{1, 1, 1, 1, 1, 0, 1, 0}}, {{1, 0, 1, 0, 1, 0, 0, 0, 1}}, {{1, 0, 1, 1, 1, 1, 1, 1, 0, 1}}, {{1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1}}, {{1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0}}, {{1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1}}, {{1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0}}, {{1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1}}, {{1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1}}, {{1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0}}, {{1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1}}, {{1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0}}, {{1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0}}, {{1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1}}, {{1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0}}, {{1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1}}, {{1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0}}, {{1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1}}, {{1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}}, {{1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0}}, {{1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1}}, {{1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0}}, {{1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1}}, {{1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1}}, {{1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0}}, {{1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1}}, {{1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0}}, {{1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0}}, {{1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1}}, {{1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1}}, {{1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0}}, {{1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0}}, {{1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1}}, {{1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0}}, {{1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0}}, {{1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1}}, {{1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1}}, {{1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1}}, {{1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1}}, {{1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1}}, {{1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1}}, {{1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1}}, {{1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0}}};

int main() {
    pre();
    return 0;
    cin >> n;

    matrix<modint<2>> ans = dp[n];
    fo(i, n) cout << ans(0, n - 1 - i) << " ";
    cout << endl;
    fo(i, n - 1) cout << "0 ";
    cout << "1\n";

	return 0;
}

