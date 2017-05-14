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
constexpr int mx_c = 55, mx_r = 5;
constexpr int mx_mask = (1 << mx_r);
string g[mx_r], ans[mx_r];
int r, c;
int dp[mx_c][mx_mask][mx_mask][mx_mask], opt[mx_c][mx_mask][mx_mask][mx_mask];
int optlaser[mx_c][mx_mask][mx_mask][mx_mask], optneed[mx_c][mx_mask][mx_mask][mx_mask], optbanned[mx_c][mx_mask][mx_mask][mx_mask];
int shooters[mx_c], walls[mx_c], hitmask[mx_r][mx_c], empty[mx_c];

void pre() {
    ini(shooters, 0); ini(walls, 0); ini(hitmask, 0); ini(empty, 0);
    fo(i, r) trace(i, g[i]);
    fo(j, c) {
        fo(i, r) {
            if(g[i][j] == '.') empty[j] |= (1 << i);
            else if(g[i][j] == '#') walls[j] |= (1 << i);
            else if(g[i][j] == '-' || g[i][j] == '|') shooters[j] |= (1 << i);
        }
        //trace(j, shooters[j], walls[j], empty[j]);
    }

    fo(i, r) fo(j, c) if(g[i][j] == '-' || g[i][j] == '|') {
        for(int ci = i - 1; ci >= 0 && g[ci][j] != '#'; --ci) hitmask[i][j] |= (1 << ci);
        for(int ci = i + 1; ci < r && g[ci][j] != '#'; ++ci) hitmask[i][j] |= (1 << ci);
        //trace(i, j, hitmask[i][j]);
    }
}

int solve(int j, int laser, int need, int banned) {
    if(j == c) return (need == 0? 1: 0);
    int &ret = dp[j][laser][need][banned];
    if(ret != -1) return ret;
    ret = 0;
    assert((need & banned) == 0);

    if((laser & shooters[j]) > 0) return ret = 0;
    if((need & walls[j]) > 0) return ret = 0;

    fo(mask, (1 << c)) {
        int lmask = (mask & shooters[j]);

        int vmask = (lmask ^ shooters[j]);

        if((need & vmask) > 0) continue;
        if((banned & lmask) > 0) continue;

        int claser = (laser ^ (laser & walls[j]));
        int nlaser = claser;
        //trace(is1(shooters[j], 3));
        fo(i, r) if(is1(shooters[j], i)) {
            if(is1(lmask, i)) {
                nlaser |= (1 << i);
            } else {
                //trace(i, j, hitmask[i][j]);
                claser |= hitmask[i][j];
            }
        }

        //trace(j, lmask, vmask, nlaser, claser, shooters[j]);
        if((claser & shooters[j]) > 0) continue;

        int done_need = (need & lmask);

        int nneed = (need ^ done_need) | (empty[j] ^ (empty[j] & claser));
        if((nneed & banned) > 0) continue;
        int nbanned = (banned ^ (banned & walls[j])) | shooters[j];

        if(solve(j + 1, nlaser, nneed, nbanned)) {
            ret = 1;
            opt[j][laser][need][banned] = lmask;
            optlaser[j][laser][need][banned] = nlaser;
            optneed[j][laser][need][banned] = nneed;
            optbanned[j][laser][need][banned] = nbanned;
            break;
        }
    }
    //trace(j, laser, need, banned, ret);
    //trace(opt[j][laser][need][banned], optlaser[j][laser][need][banned], optneed[j][laser][need][banned], optbanned[j][laser][need][banned]);

    return ret;
}

bool ok() {
    string gg[mx_r];
    fo(i, r) gg[i] = ans[i];
    fo(i, r) fo(j, c) {
        if(gg[i][j] == '-') {
            for(int cj = j - 1; cj >= 0; --cj) {
                if(gg[i][cj] == '.' || gg[i][cj] == '*') {gg[i][cj] = '*'; continue; }
                if(gg[i][cj] == '#') break;
                trace(i, j);
                return false;
            }
            for(int cj = j + 1; cj < c; ++cj) {
                if(gg[i][cj] == '.' || gg[i][cj] == '*') {gg[i][cj] = '*'; continue; }
                if(gg[i][cj] == '#') break;
                trace(i, j);
                return false;
            }
        } else if(gg[i][j] == '|') {
            for(int ci = i - 1; ci >= 0; --ci) {
                if(gg[ci][j] == '.' || gg[ci][j] == '*') {gg[ci][j] = '*'; continue; }
                if(gg[ci][j] == '#') break;
                trace(i, j);
                return false;
            }
            for(int ci = i + 1; ci < r; ++ci) {
                if(gg[ci][j] == '.' || gg[ci][j] == '*') {gg[ci][j] = '*'; continue; }
                if(gg[ci][j] == '#') break;
                trace(i, j);
                return false;
            }
        }
    }

    fo(i, r) fo(j, c) if(gg[i][j] == '.') {
        trace(i, j);
        return false;
    }

    return true;
}

void solve() {
    ini(dp, -1);
    if(!solve(0, 0, 0, 0)) {
        cout << "IMPOSSIBLE\n";
        return;
    } else {
        cout << "POSSIBLE\n";
    }

    fo(i, r) ans[i] = g[i];
    int laser = 0, need = 0, banned = 0;
    fo(j, c) {
        assert(dp[j][laser][need][banned]);
        int lmask = opt[j][laser][need][banned];
        fo(i, r) if(is1(shooters[j], i)) {
            if(is1(lmask, i)) ans[i][j] = '-';
            else ans[i][j] = '|';
        }
        int nlaser = optlaser[j][laser][need][banned];
        int nneed = optneed[j][laser][need][banned];
        int nbanned = optbanned[j][laser][need][banned];
        laser = nlaser; need = nneed; banned = nbanned;
    }

    fo(i, r) cout << ans[i] << endl;
    assert(ok());
}

int main() {
    int _t;
    cin >> _t;
    rep(kase, 1, _t) {
        cin >> r >> c;
        fo(i, r) cin >> g[i];
        pre();

        cout << "Case #" << kase << ": ";
        solve();
    }
    
    
	return 0;
}

