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
constexpr int mx_n = 1000006;

ll a;

bitset<mx_n> notprime;
vi primes;
unordered_map<ll, int> simplePowers;
unordered_map<ll, vector<ll>> possible;
vector<vector<ll>> parts;
set<ll> divisors;
vector<ll> divs;
map<ll, int> inv;

bool isPrime(ll n) {
    if(n <= 1) return false;
    for(int i = 0; i < si(primes) && 1ll * primes[i] * primes[i] <= n; ++i) 
        if(n % primes[i] == 0) return false;

    return true;
}

ll getPrimeRoot(ll n) {
    auto it = simplePowers.find(n);
    if(it != simplePowers.end()) return it->se;
    return isPrime(n)? n: 0;
}

void proc(ll n) {
    divisors.insert(n);
    ll rn = getPrimeRoot(n-1);
    trace(n, rn);
    if(rn) possible[rn].push_back(n);
}


void pre() {
    notprime.reset();
    notprime[0] = notprime[1] = 1;
    for(int i = 2; i * i < mx_n; ++i) if(!notprime[i]) {
        for(int j = i * i; j < mx_n; j += i) notprime[j] = 1;
    }

    fo(i, mx_n) if(!notprime[i]) {
        primes.push_back(i);
        for(ll j = i; j <= a; j *= i) simplePowers[j] = i;
    }

    for(ll i = 1; i * i <= a; ++i) if(a % i == 0) {
        ll j = a / i;
        proc(i); proc(j);
    }

    for(auto entry: possible) {
        auto ls = entry.se;
        sort(all(ls)); ls.resize(unique(all(ls)) - ls.begin());
        parts.push_back(ls);
    }
    possible.clear();

    divs = vector<ll>(all(divisors));
    fo(i, si(divs)) inv[divs[i]] = i;

    trace(parts);
    trace(si(divs));
}


int cache[2][10004];

int solve(int idx, int d) {
    assert(d < 10004);
    if(idx == si(parts)) return d == si(divs) - 1;
    int &ret = cache[idx&1][d];
    if(ret != -1) return ret;
    ret = solve(idx + 1, d);

    ll dv = divs[d];
    for(ll nxt: parts[idx]) {
        if(nxt <= a / dv) {
            ll nw = dv * nxt;
            if(a % nw == 0) ret += solve(idx + 1, inv[nw]);
        } else {
            break;
        }
    }

    return ret;
}

int main() {
    cin >> a;
    pre();

    ini(cache, -1);
    for(int i = si(parts); i >= 0; --i) {
        ini(cache[i&1], -1);
        fo(j, si(divs)) solve(i, j);
    }

    cout << solve(0, 0) << endl;
    
	return 0;
}

