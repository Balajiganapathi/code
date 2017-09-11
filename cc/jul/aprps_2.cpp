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
constexpr int mx_n = 16;
constexpr int mx_deg = 2 * (1 << mx_n) + 1;
int a[mx_n], n;

int ans_d;
ld coef[mx_deg];

int generator (int p) {
	vector<int> fact;
	int phi = p-1,  n = phi;
	for (int i=2; i*i<=n; ++i)
		if (n % i == 0) {
			fact.push_back (i);
			while (n % i == 0)
				n /= i;
		}
	if (n > 1)
		fact.push_back (n);
 
	for (int res=2; res<=p; ++res) {
		bool ok = true;
		for (size_t i=0; i<fact.size() && ok; ++i)
			ok &= modpow (res, phi / fact[i], p) != 1;
		if (ok)  return res;
	}
	return -1;
}

class Term {
public:
    int cnt;
    vi expos;
    Term(int n) {
        expos = vi(n);
        cnt = 0;
    }

    bool operator <(const Term &t) const {
        return expos < t.expos;
    }
};
#ifdef TRACE
ostream &operator <<(ostream &o, Term t) { // print a Term
    return o << "(" << t.cnt << " * " << t.expos << ")";
}
#endif



vector<Term> cx[mx_deg];

vector<Term> fromMap(const map<vi, int> tms) {
    vector<Term> ret;
    for(auto entry: tms) if(entry.se != 0) {
        Term cur(n);
        cur.expos = entry.fi;
        cur.cnt = entry.se;
        ret.push_back(cur);
    }

    return ret;

}

vector<Term> add(const vector<Term> &a, const vector<Term> &b) {
    map<vi, int> tms;
    for(auto cur: a) tms[cur.expos] += cur.cnt;
    for(auto cur: b) tms[cur.expos] += cur.cnt;

    return fromMap(tms);
}

vector<Term> mult(const vector<Term> &a, const vector<Term> &b) {
    map<vi, int> tms;
    for(auto cur1: a) for(auto cur2: b) {
        Term cur(n);
        cur.cnt = cur1.cnt * cur2.cnt;
        fo(i, n) cur.expos[i] = cur1.expos[i] + cur2.expos[i];
        tms[cur.expos] += cur.cnt;
    }

    //trace(a, b, tms);
    return fromMap(tms);
}


#define dec adfasdfa
int g = 5;
int sq = (int) sqrt (mod + .0) + 1;
vector < pair<int,int> > dec (sq);

int gsqrt(int a) {
	if (a == 0) {
		return 0;
	}
 
	for (int i=1; i<=sq; ++i)
		dec[i-1] = make_pair (modpow (g, int (i * sq * 1ll * 2 % (mod - 1)), mod), i);
	sort (dec.begin(), dec.end());
	int any_ans = -1;
	for (int i=0; i<sq; ++i) {
		int my = int (modpow (g, int (i * 1ll * 2 % (mod - 1)), mod) * 1ll * a % mod);
		vector < pair<int,int> >::iterator it =
			lower_bound (dec.begin(), dec.end(), make_pair (my, 0));
		if (it != dec.end() && it->first == my) {
			any_ans = it->second * sq - i;
			break;
		}
	}
    trace(any_ans);

	if (any_ans == -1) {
		return 0;
	}
 
	int delta = (mod-1) / __gcd (2, mod-1);
    return (modpow (g, any_ans % delta, mod));
 
}

void solve() {
    fo(i, mx_deg) coef[i] = 0;
    ans_d = 0;
    
    int tot = (1 << (n-1));
    vector<ld> terms;
    fo(i, n) terms.push_back(sqrt(a[i]));
    vector<ld> roots;

    //trace(terms);

    fo(mask, (1 << (n-1))) {
        int d = tot - __builtin_popcount(mask);
        ld cur = terms[0];
        re(i, 1, n) {
            if(is1(mask, (i-1))) cur += terms[i];
            else cur += -terms[i];
            //while(cur < 0) cur += mod;
            //if(cur >= mod) cur -= mod;
        }
        //roots.push_back(fmod(cur * cur, mod));
        cur = fmod(cur, mod);
        roots.push_back(fmod(cur * cur, mod));
    }

    trace(tot, roots);

    fo(mask, (1 << tot)) {
        int bits = __builtin_popcount(mask);
        int d = 2 * (tot - bits);
        ld mul = (bits % 2 == 0? 1: -1);
        fo(i, tot) if(is1(mask, i)) {
            mul = fmod(mul * roots[i], mod);
        }
        ans_d = max(ans_d, d);
        coef[d] += mul;
    }
}

int dp[mx_n][mx_deg];

void check() {
    fo(i, mx_deg) cx[i].clear();
    vector<vector<Term>> roots;
    int tot = (1 << (n-1));
    fo(mask, tot) {
        int d = tot - __builtin_popcount(mask);
        vector<Term> cur;
        fo(i, n) {
            Term tmp(n);
            tmp.cnt = 1;
            tmp.expos[i] = 1;
            if(is1(mask, i)) tmp.cnt = -1;
            cur.push_back(tmp);
        }
        roots.push_back(mult(cur, cur));
    }
    //trace(roots);

    fo(mask, (1 << tot)) {
        int bits = __builtin_popcount(mask);
        int d = 2 * (tot - bits);
        vector<Term> mul;
        Term s(n);
        s.cnt = (bits % 2 == 0? 1: -1);
        mul.push_back(s);
        fo(i, tot) if(is1(mask, i)) mul = mult(mul, roots[i]);
        //trace(mask, mul);
        cx[d] = add(cx[d], mul);
    }
    fo(i, mx_deg) {
        for(auto& cur: cx[i]) {
            fo(j, n) {
                assert(cur.expos[j] % 2 == 0);
                cur.expos[j] /= 2;
            }
        }
    }

#ifdef TRACE
    for(int i = mx_deg - 1; i >= 0; --i) {
        if(!cx[i].empty()) {
            set<int> pattern;
            cerr << "X^" << i << "*";
            bool f = true;
            sort(cx[i].rbegin(), cx[i].rend());
            for(const auto& cur: cx[i]) if(cur.expos[0] > 0) {
                if(!f && cur.cnt > 0) cerr << "+";
                if(cur.cnt != 1) cerr << cur.cnt;
                pattern.insert(abs(cur.cnt));
                fo(i, n) if(cur.expos[i] != 0) {
                    cerr << "a" << i << "^" << cur.expos[i];
                }
                f = false;
            }
            cerr << endl;
            trace(pattern);
        }
    }
    cerr << "\n--------------------\n\n";
#endif
}

int convert(ld x) {
    if(x < -eps) return (mod - convert(-x)) % mod;
    return int(fmod(x, mod) + eps);
}

int ans[mx_deg];
void solve2() {
    check();
    fo(i, mx_deg) {
        ans[i] = 0;
        for(auto cur: cx[i]) {
            int term = (mod + cur.cnt) % mod;
            fo(j, n) term = 1ll * term * modpow(a[j], cur.expos[j], mod) % mod;
            ans[i] += term;
            if(ans[i] >= mod) ans[i] -= mod;
        }
        if(!cx[i].empty()) ans_d = i;
    }
}

int tdp[(1 << 6)][(1 << 6)][(1 << 6)][2];

int comb2(int n) {
    if(n < 2) return 0;
    return 1ll * n * (n-1) % mod * modpow(2, mod - 2, mod) % mod;
}

int getTimes(int pos, int neg, int d, int s) {
    if(pos < 0 || neg < 0) return 0;
    if(d == 0) return (s == 0? 1: mod-1);
    int &ret = tdp[pos][neg][d][s];
    if(ret != -1) return ret;
    ret = 0;

    // pos
    ret += 1ll * comb2(pos) * getTimes(pos - 2, neg, d - 1, s) % mod;
    if(ret >= mod) ret -= mod;
    ret += 1ll * comb2(neg) * getTimes(pos, neg - 2, d - 1, s) % mod;
    if(ret >= mod) ret -= mod;

    // neg
    ret += 1ll * pos * neg % mod * getTimes(pos - 1, neg - 1, d - 1, 1-s) % mod;
    if(ret >= mod) ret -= mod;

    return ret;
}

int fact[mx_deg], ifact[mx_deg];

void pre() {
    fact[0] = 1;
    re(i, 1, mx_deg) fact[i] = 1ll * fact[i-1] * i % mod;
    fo(i, mx_deg) ifact[i] = modpow(fact[i], mod - 2, mod);
}

int comb(int n, int k) {
    if(k > n || k < 0 || n < 0) return 0;
    assert(n < mx_deg && k < mx_deg);
    return 1ll * fact[n] * ifact[k] % mod * ifact[n-k] % mod;
}

int getTimes(int t, int d) {
    int pos = t/2, neg = t/2;
    int ret = 0;
    //trace(t, d);
    rep(p, 0, d) {
        int ways = 1ll * comb(pos, p) * comb(neg, d-p) % mod;
        if(p % 2 == 1) ways = (mod - ways) % mod;
        //trace(p, ways);
        ret += ways;
        if(ret >= mod) ret -= mod;
    }

    return ret;
}

void solve3() {
    solve2();

    ini(tdp, -1);
    ini(dp, 0);
    dp[n][0] = 1;
    for(int i = n - 1; i >= 0; --i) {
        trace(i);
        for(int j = 0; j <= (1 << n); j += 2) {
            trace(i, j);
            dp[i][j] = 0;
            if(j == 0) {
                dp[i][0] = 1;
                continue;
            }
            int ca = 1;
            for(int k = j; k >= 0; k -= 2) {
                trace(j, j-k, getTimes(j,j-k));
                dp[i][j] = (dp[i][j] + 1ll * ca * getTimes(j, j-k) % mod * dp[i+1][k]) % mod;
                ca = 1ll * ca * a[i] % mod;
            }
            trace(i, j, dp[i][j]);
        }
    }

    ans_d = (1 << n);
    for(int i = 0; i <= ans_d; i += 2) {
        trace(i, ans[i], dp[0][ans_d-i]);
        //assert(ans[i] == dp[0][ans_d-i]);
    }
}

int cdp[(1 << 6)][(1 << 6)][(1 << 6)];
int getCoeff(int mask, int i, int rem) {
    if(rem < 0)  return 0;
    if(rem == 0) {
        if(mask == 0) return 1;
        else return 0;
    }
    if(i == (1 << n)) return 0;

    int &ret = cdp[mask][i][rem];
    if(ret != -1) return ret;
    ret = 0;

    ret = getCoeff(mask, i + 1, rem);

    fo(j, n) {
        int s = 1;
        if(is1(i, j)) s = mod-1;
        if(is1(mask, j)) s = 1ll * s * a[j] % mod;
        ret += 1ll * s * getCoeff(mask ^ (1 << j), i + 1, rem - 1) % mod;
        if(ret >= mod) ret -= mod;
    }

    return ret;
}

void solve4() {
    solve2();
    ini(cdp, -1);
    ans_d = (1 << n);
    rep(i, 0, ans_d) {
        //trace(ans[i], getCoeff(0, 0, ans_d - i));
        ans[i] = getCoeff(0, 0, ans_d - i);
    }
}

int main() {
    //trace(generator(mod));
    trace(modpow(5, (1 << 20), 7340033));
    return 0;
    pre();
    int t;
    cin >> t;
    while(t--) {
        cin >> n;
        fo(i, n) cin >> a[i];
        solve4();
        cout << ans_d << endl;
        //rep(i, 0, ans_d) trace(i, coef[i], convert(coef[i]));
        //rep(i, 0, ans_d) cout << convert(coef[i]) % mod << " ";
        rep(i, 0, ans_d) cout << ans[i] << " ";
        cout << endl;
    }
    
    
	return 0;
}

