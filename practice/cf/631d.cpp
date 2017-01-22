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
constexpr auto oo  = RAND_MAX / 2 - 2;
constexpr auto eps = 1e-6;
constexpr auto mod = 1000000007;

/* code */
constexpr int mx = -1;
using block = pair<int, ll>;
vector<block> s, t;

bool isprime(int n) {
    if(n % 2 == 0) return n == 2;
    for(int i = 3; i * i <= n; i += 2) if(n % i == 0) return true;
    return false;
}

constexpr int nhash = 2;
int modd[nhash], base[nhash], baseinv[nhash];
int cbase[nhash][256];

int getRand() {
    return 1ll * rand() % rand() % INT_MAX;
}

void preHash() {
    fo(i, nhash) {
        do {
            modd[i] = getRand();
            base[i] = getRand();
        } while(min(base[i], modd[i]) <= oo || base[i] >= modd[i] || __gcd(base[i], modd[i]) != 1 || !isprime(modd[i]));
        baseinv[i] = modpow(base[i], modd[i] - 2, modd[i]);
        fo(c, 256) {
            do {
                cbase[i][c] = getRand() % base[i] + 1;
            } while(cbase[i][c] <= 1 || cbase[i][c] >= base[i] || __gcd(cbase[i][c], base[i]) != 1);
        }
    }

}

int getHash(block b) {
    ll tmp = (b.se ^ b.fi ^ (b.se >> 32));
    int cur = 0;
    for(; tmp > 0; tmp >>= 8) cur ^= cbase[0][tmp % 256];

    return cur % 256;
}

class Hash {
    public:
    int len;
    int cur_hash[nhash];
    Hash() {
        if(modd[0] == 0) preHash();
        len = 0;
        fo(i, nhash) cur_hash[i] = 0;
    }

    void addCharToEnd(int c) {
        c %= 256;
        ++len;
        fo(i, nhash) {
            trace(i, c, cur_hash[i], base[i], cbase[i][c], modpow(base[i], len - 1, modd[i]));
            cur_hash[i] = (1ll * cur_hash[i] * base[i] + cbase[i][c]) % modd[i];
        }
    }

    void addCharAtStart(int c) {
        c %= 256;
        ++len;
        fo(i, nhash) {
            trace(i, c, cur_hash[i], base[i], cbase[i][c], modpow(base[i], len - 1, modd[i]));
            cur_hash[i] = (cur_hash[i] + 1ll * cbase[i][c] * modpow(base[i], len - 1, modd[i])) % modd[i];
        }
    }

    void remCharFromEnd(int c) {
        assert(len > 0);
        c %= 256;
        fo(i, nhash) {
            cur_hash[i] = 1ll * (cur_hash[i] - cbase[i][c] + modd[i]) % modd[i] * baseinv[i] % modd[i];
        }
        --len;
    }

    void remCharFromStart(int c) {
        assert(len > 0);
        c %= 256;
        fo(i, nhash) {
            trace(i, c, cur_hash[i], base[i], cbase[i][c], modpow(base[i], len - 1, modd[i]));
            cur_hash[i] = (cur_hash[i] - 1ll * cbase[i][c] * modpow(base[i], len - 1, modd[i]) % modd[i] + modd[i]) % modd[i];
        }
        --len;
    }

    bool operator ==(const Hash &h) const {
        if(len != h.len) return false;
        fo(i, nhash) if(cur_hash[i] != h.cur_hash[i]) return false;
        return true;
    }

};


vector<block> input(int len) {
    vector<block> ans;
    string str;
    int prev = -1;
    ll cnt = 0;
    fo(i, len) {
        cin >> str;
        char c = str[si(str) - 1];
        str = str.substr(0, si(str) - 2);
        ll ccnt = atoi(str.c_str());
        if(prev == c) {
            cnt += ccnt;
        } else {
            if(prev != -1) ans.push_back(mp(prev, cnt));
            prev = c;
            cnt = ccnt;
        }
    }
    ans.push_back(mp(prev, cnt));

    return ans;
}

int main() {
    srand(time(NULL));
    int n, m;
    cin >> n >> m;
    s = input(n);
    t = input(m);

    ll ans = 0;
    n = si(s), m = si(t);
    if(m <= 2) {
        fo(i, n - m + 1) {
            if(t[0].fi == s[i].fi && t[0].se <= s[i].se && t[m-1].fi == s[i+m-1].fi && t[m-1].se <= s[i+m-1].se) {
                if(m == 1) {
                    trace(i, t[i], s[i]);
                    ans += s[i].se - t[0].se + 1;
                } else {
                    ans += 1;
                }
            }
        }
    } else {
        Hash thash, shash;
        re(i, 1, m - 1) {
            thash.addCharToEnd(getHash(t[i]));
            if(i < n) shash.addCharToEnd(getHash(s[i]));
        }
        trace(thash.len, thash.cur_hash[0], thash.cur_hash[1]);
        trace(shash.len, shash.cur_hash[0], shash.cur_hash[1]);
        re(i, m - 1, n) {
            trace(i, shash.len, shash.cur_hash[0], shash.cur_hash[1]);
            if(shash == thash && s[i-m+1].fi == t[0].fi && s[i].fi == t[m-1].fi && s[i-m+1].se >= t[0].se && s[i].se >= t[m-1].se) {
                ++ans;
            }
            shash.remCharFromStart(getHash(s[i-m+2]));
            trace(i, shash.len, shash.cur_hash[0], shash.cur_hash[1]);
            shash.addCharToEnd(getHash(s[i]));
        }
    }
    cout << ans << endl;
    
    
    
	return 0;
}

