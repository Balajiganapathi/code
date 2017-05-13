/* string coder = "Balajiganapathi S"; // Never give up!  */

//#define LOCAL
#ifdef LOCAL
#   define TRACE
#   define TEST
#   define CHECK
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
ostream &operator <<(ostream &o, multiset<T> s) { // print a set
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
constexpr int mx = -1;

string av[2];
int n;

string overall;

string solve(string s, int mask) {
    int cnt = __builtin_popcount(mask);
    if(cnt == n) return s;

    string ret;
    if(cnt % 2 == 0) {
        fo(i, n) if(!is1(mask, i)) {
            fo(j, n) if(s[j] == '?') {
                s[j] = overall[i];
                string cur = solve(s, mask | (1 << i));
                if(ret == "" || cur < ret) ret = cur;
                s[j] = '?';
            }
        }
    } else {
        re(i, n, 2 * n) if(!is1(mask, i)) {
            fo(j, n) if(s[j] == '?') {
                s[j] = overall[i];
                string cur = solve(s, mask | (1 << i));
                if(ret == "" || cur > ret) ret = cur;
                s[j] = '?';
            }
        }
    }

    //trace(s, mask, ret);
    return ret;
}

string brute() {
    overall = av[0] + av[1];
    
    string ans = solve(string(n, '?'), 0);
    return ans;
}

int main() {
#ifdef TEST
    int t = 100;
    while(t--) {
    n = rand() % 5 + 1;
    fo(j, 2) {
        av[j] = "";
        fo(i, n) av[j] += char(rand() % 4 + 'a');
    }
#else
    cin >> av[0] >> av[1];
#endif
    n = si(av[0]);
    fo(j, 2) sort(all(av[j]));
    int start[2] = {0, 0}, end[2] = {n - 1, n - 1};
    int rem0 = (n + 1) / 2, rem1 = n / 2;

    string ans(n, '?');
    int as = 0, ae = n - 1;
    string rev;
    fo(i, n) {
        char play;
        trace(i);
        if(i % 2 == 0) { // Oleg
            if(av[0][start[0]] < av[1][end[1]]) {
                ans[as++] = av[0][start[0]];
                ++start[0];
            } else {
                ans[ae--] = av[0][start[0] + rem0-1];
            }
            --rem0;
        } else {
            if(av[1][end[1]] > av[0][start[0]]) {
                ans[as++] = av[1][end[1]];
                --end[1];
            } else {
                trace(as, ae, end[1], rem1, av[1][end[1] - rem1 + 1]);
                ans[ae--] = av[1][end[1] - rem1 + 1];
            }
            --rem1;
        }
    }

#ifdef CHECK
    string bans = brute();
    if(bans != ans) {
        trace(av[0], av[1], bans, ans);
        assert(ans == bans);
    }
#endif

    cout << ans << endl;
#ifdef TEST
    }
#endif
    
    
	return 0;
}

