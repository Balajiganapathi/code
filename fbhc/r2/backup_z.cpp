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
constexpr int mx = 800005;

int bitL[mx], bitR[mx];

int n, m;

/*
int read(int bit[mx], int idx){
    int sum = 0;
    while (idx > 0){
        sum += tree[idx];
        if(sum >= mod) sum -= mod;
        idx -= (idx & -idx);
    }
    return sum;
}

void update(int bit[mx], int idx ,int val){
    while (idx <= MaxVal){
        tree[idx] += val;
        if(tree[idx] >= mod) tree[idx] -= mod;
        idx += (idx & -idx);
    }
}

int getLeft(int from) {
    return read(bitL, from);
}

int getRight(int from) {
    return read(n - from + 1);
}

void putLeft(int at, int val) {
    update(bitL, at, val);
}

void putRight(int at, int val) {
    update(bitR, at, val);
}
*/

// 0 - prev, 1 - cur, 2 - next
int hit[mx][3];
int w[mx], z[mx], d[mx], s[mx];

using T = int;
constexpr int N = 2;
int mat[mx][N][N];

void matCopy(int res[N][N], int mat[N][N]) {
    fo(i, N) fo(j, N) res[i][j] = mat[i][j];
}

void mult(int res[N][N], int mat1[N][N], int mat2[N][N]) {
    static int tmp[N][N];
    fo(i, N) fo(j, N) {
        tmp[i][j] = 0;
        fo(k, N) {
            tmp[i][j] += 1ll * mat1[i][k] * mat2[k][j] % mod;
            if(tmp[i][j] >= mod) tmp[i][j] -= mod;
        }
    }

    matCopy(res, tmp);
}



int att(int i, int j) {
    if(i <= 0 || i > n) return 0;
    int idx = j - i + 1;
    return hit[i][idx];
}


int seg[3 * mx][N][N];

void build(int i, int a, int b) {
    if(a == b) {
        matCopy(seg[i], mat[a]);
        return;
    }
    int m = (a + b) / 2;
    int l = 2 * i + 1, r = 2 * i + 2;
    build(l, a, m);
    build(r, m + 1, b);
    mult(seg[i], seg[r], seg[l]);
}

void update(int i, int a, int b, int q) {
    if(q < a || q > b) return;
    if(a == b) {
        matCopy(seg[i], mat[q]);
        return;
    }
    int m = (a + b) / 2;
    int l = 2 * i + 1, r = 2 * i + 2;
    update(l, a, m, q);
    update(r, m + 1, b, q);
    mult(seg[i], seg[r], seg[l]);
}

void input() {
    cin >> n >> m;
    ll w1, aw, bw, d1, ad, bd, s1, as, bs;
    cin >> w1 >> aw >> bw >> d1 >> ad >> bd >> s1 >> as >> bs;
    w[1] = w1;
    d[1] = d1;
    s[1] = s1;
    rep(i, 2, m) {
        w[i] = (aw * w[i-1] + bw) % n + 1;
        d[i] = (ad * d[i-1] + bd) % 3;
        s[i] = (as * s[i-1] + bs) % 1000000000 + 1;
    }
    rep(i, 1, m) {
        z[i] = max(1, min(n, w[i] + d[i] - 1));
        //trace(i, w[i], z[i], s[i]);
    }


    ini(hit, 0);
    rep(i, 1, n) {
        ++hit[i][1];
        mat[i][0][0] = att(i, i);
        mat[i][0][1] = 1ll * att(i, i - 1) * att(i - 1, i) % mod;
        mat[i][1][0] = 1;
        mat[i][1][1] = 0;
        /*
        trace(i);
        fo(j, N) {
            fo(k, N) {
                cerr << mat[i][j][k] << " ";
            }
            cerr << endl;
        }
        */
    }
    build(0, 1, n);
    
}

int dp[mx];
int brute() {
    dp[0] = 1;
    rep(i, 1, n) {
        dp[i] = 0;
        if(i - 2 >= 0) dp[i] += 1ll * att(i, i - 1) * att(i - 1, i) % mod * dp[i-2] % mod;
        if(dp[i] >= mod) dp[i] -= mod;
        dp[i] += 1ll * att(i, i) * dp[i-1] % mod;
        if(dp[i] >= mod) dp[i] -= mod;
    }
    return dp[n];
}

int brute1(int i, int diff) {

    trace(i, diff);
    if(diff <= 0) {
        mat[i][0][0] = att(i, i);
        mat[i][0][1] = 1ll * att(i, i - 1) * att(i - 1, i) % mod;
        mat[i][1][0] = 1;
        mat[i][1][1] = 0;
    } else {
        ++i;
        mat[i][0][0] = att(i, i);
        mat[i][0][1] = 1ll * att(i, i - 1) * att(i - 1, i) % mod;
        mat[i][1][0] = 1;
        mat[i][1][1] = 0;
    }

    rep(i, 1, n) {
        trace(i);
        fo(j, N) {
            fo(k, N) {
                cerr << mat[i][j][k] << " ";
            }
            cerr << endl;
        }
    }
    

    T res[N][N] = {0};
    fo(i, N) res[i][i] = 1;

    rep(i, 1, n) mult(res, mat[i], res);
    fo(j, N) {
        fo(k, N) {
            cerr << res[j][k] << " ";
        }
        cerr << endl;
    }


    return res[0][0];
}


int change(int i, int diff) {

    //trace(i, diff);
    if(diff <= 0) {
        mat[i][0][0] = att(i, i);
        mat[i][0][1] = 1ll * att(i, i - 1) * att(i - 1, i) % mod;
        mat[i][1][0] = 1;
        mat[i][1][1] = 0;
    } else {
        ++i;
        mat[i][0][0] = att(i, i);
        mat[i][0][1] = 1ll * att(i, i - 1) * att(i - 1, i) % mod;
        mat[i][1][0] = 1;
        mat[i][1][1] = 0;
    }
    update(0, 1, n, i);

    return seg[0][0][0];
}



int solve() {
    int ret = 0;
    //brute();

    rep(i, 1, m) {
        int diff = z[i] - w[i];
        int idx = diff + 1;
        hit[w[i]][idx] += s[i];
        if(hit[w[i]][idx] >= mod) hit[w[i]][idx] -= mod;
        //int cur = brute();
        brute();
        int cur = change(w[i], diff);
        //trace(i, w[i], s[i], idx, dp[n], hit[w[i]][idx], cur);
        ret += cur;
        if(ret >= mod) ret -= mod;
    }

    return ret;
}

int main() {
    int t;
    cin >> t;
    rep(kase, 1, t) {
        ini(bitL, 0);
        ini(bitR, 0);
        input();
        
        int ans = solve();

        cout << "Case #" << kase << ": " << ans << endl;

    }
    
    
	return 0;
}

