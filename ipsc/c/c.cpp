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
constexpr auto oo  = numeric_limits<int>::max() / 2 - 2;
constexpr auto eps = 1e-6;
constexpr auto mod = 1000000009;

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
        if(val < 0) {
            val %= mod;
            if(val < 0) val += mod;
        } else if(val >= mod) {
            val %= mod;
        }
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


/* code */
constexpr int mx_n = 100005;
int a[mx_n], n;
modint<mod> fact[mx_n], cnt[mx_n];
int vis[mx_n];


int brute(int n) {
    vi pos;
    fo(i, n) pos.push_back(i);
    trace(pos);
    int ans1 = oo, ans2 = 0;
    do {
        vi cur;
        fo(i, n - 1) cur.push_back(i+1);
        cur.push_back(0);
        int cur1 = 0;
        for(int i: pos) {
            //trace(cur);
            if(cur[i] != i) {
                ++cur1;
                int with = find(all(cur), i) - cur.begin();
                swap(cur[i], cur[with]);
            }
        }

        //trace(pos, cur1);
        if(cur1 < ans1) {
            ans1 = cur1;
            ans2 = 0;
        }
        if(cur1 == ans1) {
            ++ans2;
        }
    } while(next_permutation(all(pos)));

    if(si(pos) > 1) ans2 /= 2;
    else ans1 = 0,ans2 = 1;

    trace(n, cnt[n], ans1, ans2);
    assert(ans1 == n - 1);
    assert(ans2 == cnt[n].value());
    return ans2;
}

map<pair<int, vi>, int> ways;
set<vi> instack;
int brute(vi v, int d) {
    pair<int, vi> idx(d, v);
    if(ways.count(idx)) return ways[idx];
    int &ans = ways[idx];
    bool ok = true;
    fo(i, si(v)) {
        if(v[i] != i) {
            ok = false;
            break;
        }
    }
    if(ok) return ans = 1;
    if(d == 0) return ans=0;

    ans = 0;
    fo(i, si(v)) if(v[i] != i) re(j, i + 1, si(v)) if(v[j] != j) {
        swap(v[i], v[j]);
        if(!instack.count(v)) {
            instack.insert(v);
            ans += brute(v, d - 1);
            instack.erase(v);
        }
        swap(v[i], v[j]);
    }

    //trace(v, d, ans);

    return ans;
}

void pre() {
    fact[0] = 1;
    re(i, 1, mx_n) {
        fact[i] = fact[i-1] * i;
    }
    re(i, 2, mx_n) {
        modint<mod> num(i);
        cnt[i] = num.pow(i - 2);
    }
    /*
    re(i, 2, 9) {
        vi tmp;
        fo(j, i-1) tmp.push_back(j+1);
        tmp.push_back(0);
        trace(i, brute(tmp, i - 1));
    }
    */
}

int main() {
    int t;
#ifdef TEST
    ifstream fin("c1.correct");
#endif
    cin >> t;
    pre();
    while(t--) {
        cin >> n;
        fo(i, n) {
            cin >> a[i];
            --a[i];
        }

        int moves = 0;
        vi cycles;
        modint<mod> ans = 1;
        ini(vis, 0);
        fo(i, n) if(!vis[i]) {
            int cur = i;
            int tot = 0;
            for(; !vis[cur]; cur = a[cur]) {
                vis[cur] = 1;
                ++tot;
            }
            if(tot > 1) {
                cycles.push_back(tot);
                moves += (tot - 1);
                ans = ans / fact[tot - 1];
            }
        }

        ans = ans * fact[moves];
        trace(n, vi(a, a + n), cycles, moves, ans);
        for(int c: cycles) {
            ans = ans * cnt[c];
        }
        trace(ans);
        cout << ans << endl;
#ifdef TEST
        vi v(a, a + n);
        int bans;
        fin >> bans;
        if(ans != bans) {
            trace(n, moves, cycles);
            trace(v);
            trace(n, ans, bans);
            assert(ans == bans);
        }
#endif

    }
    
	return 0;
}

