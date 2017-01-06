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
constexpr int mx_n = (1 << 7) + 10;

vi adj[mx_n];
int height[mx_n], h, n;
int known[mx_n], queried[mx_n];
int par[mx_n];
bool done;

void proc() {
    fo(iter, h + 1) {
        rep(x, 1, n) {
            if(height[x] == 1) {
                cout << "! " << x << endl;
                done = true;
                return;
            }
            if(si(adj[x]) == 1) {
                height[x] = h;
                par[x] = adj[x][0];
                height[par[x]] = h - 1;
                known[x] = 1; queried[x] = (si(adj[par[x]]) > 0);
            } else if(si(adj[x]) == 2) {
                height[x] = 1;
                cout << "! " << x << endl;
                done = true;
                return;
            } else {
                known[x] = 0;
                queried[x] = 0;
                for(int y: adj[x]) {
                    if(height[y] != -1) {
                        ++known[x];
                    }
                    if(si(adj[y])) {
                        ++queried[x];
                    }
                }
                int up, down;
                up = down = 0;
                if(known[x] == si(adj[x]) - 1) {
                    int found = -1;
                    for(int y: adj[x]) {
                        if(height[y] != -1) {
                            if(height[y] < height[x]) ++up;
                            else ++down;
                        } else {
                            found = y;
                        }
                    }
                    if(!up) {
                        height[found] = height[x] - 1;
                        par[x] = found;
                    } else {
                        height[found] = height[x] + 1;
                        par[found] = x;
                    }
                }
            }
        }
    }
}

void query(int x) {
    if(done) return;
    if(!si(adj[x])) {
        cout << "? " << x << endl;
        int k, y;
        cin >> k;
        if(!k) exit(0);
        fo(i, k) {
            cin >> y;
            adj[x].push_back(y);
        }
    }
    proc();
}

pi find_deepest(int p, int x) {
    pi nxt(0, x);
    if(si(adj[x])) return nxt;
    for(int y: adj[x]) if(y != p) {
        auto z = find_deepest(x, y);
        nxt = max(nxt, mp(1 + z.fi, z.se));
    }
    return nxt;
}

void solve() {
    while(!done) {
        proc();
        int s = -1;
        rep(i, 1, n) {
            if(par[i] != -1 || height[i] == -1) continue;
            
            if(s == -1) s = i;
            else if(make_tuple(height[i], -known[i], -queried[i]) < make_tuple(height[s], -known[s], -queried[s])) s = i;
        }
        trace(s);
        if(s == -1) {
            query(rand() % n + 1);
            continue;
        }
        int mnxt = -oo;
        vi prob = {};
        if(si(adj[s]) == 0) {
            mnxt = 0;
            prob.push_back(s);
        }
        for(int y: adj[s]) if(!queried[y]) {
            pi z = find_deepest(s, y);
            ++z.fi;
            if(si(adj[z.se]) != 0) continue;
            if(z.fi > mnxt) {
                mnxt = z.fi;
                prob.clear();
            }
            if(z.fi == mnxt) {
                prob.push_back(z.se);
            }
            
        }
        trace(prob);
        int idx = rand() % n + 1;
        if(mnxt > -oo) idx = prob[rand() % si(prob)];
        trace(idx);
        query(idx);
        //trace(done);
    }
}

int main() {
    srand(time(NULL));
    int t;
    cin >> t;
    while(t--) {
        cin >> h;
        if(!h) return 0;
        n = (1 << h) - 1;
        rep(i, 0, n) {
            height[i] = -1;
            adj[i].clear();
            par[i] = -1;
        }
        done = false;

        solve();
    }
    
    
	return 0;
}

