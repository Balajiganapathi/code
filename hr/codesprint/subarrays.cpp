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
constexpr int mx_n = 200005, mx_a = 40, off = 40;
constexpr int mx_na = 2 * mx_a + 3;
constexpr int mx_sum = mx_a * (mx_a + 1) / 2 + 1;
constexpr int mx_li = mx_sum + off + 10;
int n, a[mx_n];

int lcov[mx_li];
int csum[mx_n];

/*
//int lca[mx_na];
//int lcsum[mx_li][mx_na];
pi brute() {
    int m = oo, g = -oo;
    int cnt = 0;
    rep(i, 1, n) {
        trace(i, a[i]);
        ini(lca, 0);
        int sum = 0;
        rep(j, i, n) {
            sum += a[j];
            int curlcs = a[j];
            re(p, -off, a[j]) {
                //trace(p, lca[p+off]);
                curlcs = max(curlcs, a[j] + lca[p+off]);
            }
            lca[a[j]+off] = max(lca[a[j]+off], curlcs);
            int lcsum = *max_element(lca, lca + mx_na);
            int cg = sum - lcsum;
            int cm = j - i + 1;
            trace(i, j, sum, lcsum, cg, cm);
            if(cg > g) {
                g = cg;
                m = cm;
                cnt = 1;
            } else if(cg == g && cm < m) {
                m = cm;
                cnt = 1;
            } else if(cg == g && cm == m) {
                ++cnt;
            }
        }
    }

    return mp(g, cnt);
}
*/


int seg[3 * mx_n];

void build(int i, int a, int b) {
    //assert(0 <= i && i < 2 * mx_n);
    if(a == b) {
        seg[i] = a;
        return;
    }
    int l = 2 * i, r = 2 * i + 1;
    int m = (a + b) / 2;
    build(l, a, m);
    build(r, m + 1, b);
    seg[i] = seg[r];
    if(csum[seg[l]] < csum[seg[r]]) seg[i] = seg[l];
    trace(i, a, b, seg[i]);
}

int query(int i, int a, int b, int qa, int qb) {
    //assert(0 <= i && i < 2 * mx_n);
    if(qa <= a && b <= qb) return seg[i];
    int l = 2 * i, r = 2 * i + 1;
    int m = (a + b) / 2;
    if(qb <= m) return query(l, a, m, qa, qb);
    if(qa > m) return query(r, m + 1, b, qa, qb);
    int lidx = query(l, a, m, qa, qb);
    int ridx = query(r, m + 1, b, qa, qb);
    int idx = ridx;
    if(csum[lidx] < csum[ridx]) idx = lidx;
    trace(i, a, b, qa, qb, idx);
    return idx;
}

int get_min(int a, int b) {
    assert(a <= b && 0 <= a && b <= n);
    int ans = b;
    ans = query(1, 0, n, a, b);

    return ans;
}

class Stats {
    static constexpr int mx_tree = mx_na + 2;
    public:
    int tree[mx_tree];

    int read(int idx){
        ++idx;
        int ret = -oo;
        while (idx > 0){
            ret = max(ret, tree[idx]);
            idx -= (idx & -idx);
        }
        return ret;
    }

    void update(int idx ,int val){
        ++idx;
        while (idx < mx_tree){
            tree[idx] = max(tree[idx], val);
            idx += (idx & -idx);
        }
    }

    public:
    void init() {
        fo(i, mx_tree) tree[i] = -oo;
    }

    void add(int i, int idx) {
        assert(i >= 0 && i < mx_na);
        update(i, idx);
    }

    int get(int till) {
        assert(till >= 0 && till < mx_na);
        int ans = read(till);
        return ans;
    }
    
} lcstats[mx_li];

pi solve() {
    int m = oo, g = -oo;
    int cnt = 0;
    fo(i, mx_li) {
        lcov[i] = -oo;
        lcstats[i].init();
    }
    rep(i, 1, n) csum[i] = csum[i-1] + a[i];
    build(1, 0, n);


    rep(i, 1, n) {
        int idx = a[i]+off;

        lcov[idx] = max(lcov[idx], i);
        //trace(i, a[i], idx, lcsum[idx][idx], lcov[idx]);
        if(a[i] > 0) {
            lcstats[idx].add(idx, i);
            for(int j = mx_sum + off - a[i]; j > off; --j) {
                assert(j < mx_li);
                int uidx = lcstats[j].get(idx-1);
                trace(i, a[i], j, uidx);
                if(uidx == -oo) continue;
                int nxt_idx = j + a[i];
                lcstats[nxt_idx].add(idx, uidx);
                lcov[nxt_idx] = max(lcov[nxt_idx], uidx);
            }
            //fo(i, mx_li) lcov[i] = lcstats[i].ov;

            int last = 0;
            for(int cl = mx_sum + off; cl > off; --cl) if(lcov[cl] > last) {
                trace(cl, last, lcov[cl]);
                int midx = get_min(last, lcov[cl] - 1);
                int cg = csum[i] - csum[midx] - cl + off;
                int cm = i - midx;
                //trace(i, cl, cg, cm, midx);

                if(cg > g) {
                    g = cg;
                    m = cm;
                    cnt = 1;
                } else if(cg == g && cm < m) {
                    m = cm;
                    cnt = 1;
                } else if(cg == g && cm == m) {
                    ++cnt;
                }
                last = lcov[cl];
            }
        } else {
            int cg = 0;
            int cm = 1;
            //trace(i, cl, cg, cm, midx);

            if(cg > g) {
                g = cg;
                m = cm;
                cnt = 1;
            } else if(cg == g && cm < m) {
                m = cm;
                cnt = 1;
            } else if(cg == g && cm == m) {
                ++cnt;
            }

        }
    }

    return mp(g, cnt);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    assert(n < mx_n);
    rep(i, 1, n) {
        cin >> a[i];
        assert(-mx_a <= a[i] && a[i] <= mx_a);
    }
    
    pi bans = solve();
    cout << bans.fi << " " << bans.se << endl;
    
	return 0;
}

