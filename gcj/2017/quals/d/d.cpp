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
constexpr int mx_n = 202;
int n;
int b[mx_n][mx_n];
int ans[mx_n][mx_n];
int rowtaken[mx_n], coltaken[mx_n], d1taken[mx_n], d2taken[mx_n];

// Source: http://home.iitk.ac.in/~sshekh/codes/notebook.html#file5
//------------------------------------------------------------------
typedef vector<int> VI;
typedef vector<VI> VVI;

bool FindMatch(int i, const VVI &w, VI &mr, VI &mc, VI &seen) {
  for (int j = 0; j < w[i].size(); j++) {
    if (w[i][j] && !seen[j]) {
      seen[j] = true;
      if (mc[j] < 0 || FindMatch(mc[j], w, mr, mc, seen)) {
        mr[i] = j;
        mc[j] = i;
        return true;
      }
    }
  }
  return false;
}

int bpm(const VVI &w, VI &mr, VI &mc) {
  mr = VI(w.size(), -1);
  mc = VI(w[0].size(), -1);
  
  int ct = 0;
  for (int i = 0; i < w.size(); i++) {
    VI seen(w[0].size());
    if (FindMatch(i, w, mr, mc, seen)) ct++;
  }
  return ct;
}
//------------------------------------------------------------------

void solve() {
    ini(rowtaken, 0); ini(coltaken, 0); ini(d1taken, 0); ini(d2taken, 0);
    fo(i, n) fo(j, n) if(b[i][j] != 0) {
        int d1 = i + j, d2 = i - j + n-1;
        if((b[i][j] & 2) > 0) rowtaken[i] = coltaken[j] = 1;
        if((b[i][j] & 1) > 0) d1taken[d1] = d2taken[d2] = 1;
    }

    VVI m1w(n, VI(n, 0));
    VI m1r(n, 0), m1c(n, 0);
    VVI m2w(2 * mx_n, VI(2 * mx_n, 0));
    VI m2r(2 * mx_n, 0), m2c(2 * mx_n, 0);

    fo(i, n) fo(j, n) {
        int d1 = i + j, d2 = i - j + n-1;
        if(!rowtaken[i] && !coltaken[j]) m1w[i][j] = 1;
        if(!d1taken[d1] && !d2taken[d2]) m2w[d1][d2] = 1;
    }

    int b1 = bpm(m1w, m1r, m1c);
    int b2 = bpm(m2w, m2r, m2c);
    trace(b1, b2);

    fo(i, n) fo(j, n) {
        ans[i][j] = b[i][j];
        int d1 = i + j, d2 = i - j + n-1;
        if(m1r[i] == j) {
            assert(m1c[j] == i);
            ans[i][j] |= 2;
        }
        if(m2r[d1] == d2) {
            assert(m2c[d2] == d1);
            ans[i][j] |= 1;
        }
    }
}

void output() {
    int score = 0, cnt = 0;
    fo(i, n) fo(j, n) {
        if(ans[i][j] >= 1) ++score;
        if(ans[i][j] >= 3) ++score;
        if(ans[i][j] != b[i][j]) ++cnt;
    }

    cout << score << " " << cnt << endl;
    fo(i, n) fo(j, n) {
        if(ans[i][j] != b[i][j]) {
            assert(ans[i][j] > 0 && ans[i][j] > b[i][j]);
            cout << ".+xo"[ans[i][j]] << " " << (i+1) << " " << (j+1) << endl;
        }
    }
}

int main() {
    int _t;
    cin >> _t;
    rep(kase, 1, _t) {
        ini(b, 0);
        char mt;
        int m, r, c;
        cin >> n >> m;
        while(m--) {
            cin >> mt >> r >> c;
            --r; --c;
            //trace(r, c);
            if(mt == '+') b[r][c] = 1;
            else if(mt == 'x') b[r][c] = 2;
            else b[r][c] = 3;
            //trace(r, c, b[r][c]);
        }
        //trace(n);

        solve();

        cout << "Case #" << kase << ": ";
        output();
        /*
        fo(i, n) {
            fo(j, n) cerr << ".+xo"[b[i][j]];
            cerr << endl;
        }
        trace("-----");
        fo(i, n) {
            fo(j, n) cerr << ".+xo"[ans[i][j]];
            cerr << endl;
        }
        */
    }
    
    
	return 0;
}

