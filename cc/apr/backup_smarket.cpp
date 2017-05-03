/* string coder = "Balajiganapathi S"; // Never give up!  */

//#define LOCAL
#ifdef LOCAL
//#   define TRACE
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
constexpr int mx_n = 100005;

int bit[mx_n];
int n, q;
int a[mx_n];
int sn;
class Query {
public:
    int l, r, k, i;
    int b;

    bool operator <(const Query &q) const {
        if(b == q.b) return r < q.r;
        return b < q.b;
    }
} queries[mx_n];

int read(int idx) {
    int ret = 0;
    for(; idx > 0; idx -= (idx & -idx)) 
        ret += bit[idx];

    return ret;
}

void update(int idx, int add) {
    for(; idx < mx_n; idx += (idx & -idx))
        bit[idx] += add;
}


int l, r;
deque<int> qcnt;

void clear() {
    l = r = 1;
    qcnt.clear();
    qcnt.push_back(1);
    ini(bit, 0);
    update(1, 1);
}

vi ops;
int vis[mx_n], cnt[mx_n], mark;

void updateLater(int idx, int val) {
    if(vis[idx] != mark) {
        vis[idx] = mark;
        ops.push_back(idx);
    }
    cnt[idx] += val;
}

void flushOps() {
    for(int idx: ops) {
        update(idx, cnt[idx]);
        cnt[idx] = 0;
    }
    ops.clear();
}

void add(int i) {
    //trace(i, l, r, qcnt.front(), qcnt.back());
    if(i == l - 1) {
        if(a[i] == a[l]) {
            update(qcnt.front(), -1); 
            ++qcnt.front();
        } else {
            qcnt.push_front(1);
        }
        update(qcnt.front(), 1);
        --l;
    } else {
        if(a[i] == a[r]) {
            update(qcnt.back(), -1);
            ++qcnt.back();
        } else {
            qcnt.push_back(1);
        }
        update(qcnt.back(), 1);
        ++r;
    }
}

void rem(int i) {
    //trace(i, l, r, qcnt.front(), qcnt.back());
    assert(r > l);
    if(i == l) {
        update(qcnt.front(), -1); 
        if(--qcnt.front() == 0) qcnt.pop_front();
        else update(qcnt.front() ,1);
        ++l;
    } else {
        update(qcnt.back(), -1); 
        if(--qcnt.back() == 0) qcnt.pop_back();
        else update(qcnt.back() ,1);
        --r;
    }
}

int ans[mx_n];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
#ifndef TEST
    cin >> t;
#else
    t = 3;
#endif
    while(t--) {
#ifndef TEST
        cin >> n >> q;
        rep(i, 1, n) cin >> a[i];
#else
        n = 20000;
        q = 20000;
        rep(i, 1, n) a[i] = rand() % 10 + 1;
#endif
        sn = max(1, int(sqrt(n) / 2));
        fo(i, q) {
            queries[i].i = i;
#ifndef TEST
            cin >> queries[i].l >> queries[i].r >> queries[i].k;
#else
            queries[i].l = rand() % n + 1;
            queries[i].r = rand() % n + 1;
            queries[i].k = rand() % 10 + 1;
            if(queries[i].r < queries[i].l) swap(queries[i].l, queries[i].r);
#endif

            queries[i].b = l / sn;
        }

        sort(queries, queries + q);
        clear();
        fo(i, q) {
            ++mark;
            int nl = queries[i].l, nr = queries[i].r;
            trace(l, r, nl, nr);
            while(nl < l) add(l-1);
            while(nr > r) add(r+1);
            while(nl > l) rem(l);
            while(nr < r) rem(r);
            flushOps();
            ans[queries[i].i] = si(qcnt) - read(queries[i].k - 1);
            //trace(l, r, nl, nr, ans[queries[i].i], si(qcnt), read(queries[i].k));

        }

        fo(i, q) cout << ans[i] << '\n';
    }

    
	return 0;
}

