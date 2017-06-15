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
constexpr int mx_m = 100005;
int n, k, m;
int head[mx_m][2], tail[mx_m][2];

int solve(vector<pi> &v) {
    int i1 = (n-k)/2 + 1;
    int i2 = i1 + k - 1;
    v.emplace_back(i2 + 1, 0);
    sort(all(v));
    int ans = 0;

    int cm = -oo;
    int ci = i1;
    int i = 0;
    while(i < si(v) && ci <= i2) {
        //trace(ci, cm, v[i]);
        if(ci < v[i].fi) {
            ci = cm+1;
            if(ci < v[i].fi) break;
            cm = -oo;
            ++ans;
            //trace(ci, cm, ans, v[i]);
            continue;
        } else {
            cm = max(cm, v[i].se);
        }
        ++i;
    }

    //trace(n, k, i1, i2, v, ci, ans);
    if(ci <= i2) return oo;
    return ans;
}

int main() {
    int t;
#ifndef TEST
    cin >> t;
#else
    t = 10;
#endif
    while(t--) {
#ifndef TEST
        cin >> n >> k >> m;
        fo(i, m) {
            fo(j, 2) cin >> head[i][j];
            fo(j, 2) cin >> tail[i][j];
        }
#else
        n = rand() % 1000000000 + 2;
        k = rand() % (n-2) + 1;
        m = rand() % 100000 + 1;
        trace(n, k, m);
        int ti1 = (n-k)/2 + 1;
        int ti2 = ti1 + k - 1;
        fo(i, m) {
            fo(j, 2) head[i][j] = rand() % n + 1;
            fo(j, 2) tail[i][j] = rand() % n + 1;
            if(1) {
                head[i][1] = head[i][0] + rand() % 1 + 1;
                tail[i][1] = tail[i][0] + rand() % 1 + 1;
            }
            if(rand() % 2) head[i][0] = head[i][1];
            else tail[i][0] = tail[i][1];
            bool tok = true;
            fo(j, 2) if(max(ti1, head[i][j]) > min(ti2, tail[i][j])) tok = false;
            if(!tok) {--i; continue;}
            trace(head[i][0], head[i][1], tail[i][0], tail[i][1]);
            
        }
#endif
        fo(i, m) fo(j, 2) if(head[i][j] > tail[i][j]) swap(head[i][j], tail[i][j]);

        int ans = 0;

        int i1 = (n-k)/2 + 1;
        int i2 = i1 + k - 1;
        fo(j, 2) {
            vector<pi> v;
            fo(i, m) if(max(i1, head[i][j]) <= min(i2, tail[i][j])) {
                //trace(j, i);
                v.emplace_back(head[i][j], tail[i][j]);
            }
            ans += solve(v);
        }
        if(ans >= oo) ans = -1;

        cout << ans << endl;
    }
    
    
	return 0;
}

