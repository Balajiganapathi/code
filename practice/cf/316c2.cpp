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

struct MinCostFlow {
    MinCostFlow(int _n,int _s,int _t) : n(_n), s(_s), t(_t), fl(0), cost(0) {
        first.resize(n,-1);
        dist.resize(n);
        prev.resize(n);
        a.reserve(8*n);
    };
    struct Edge {
        Edge(int _to,int _cap,int _cost,int _next) : to(_to), cap(_cap), cost(_cost), next(_next) {};
        int to,next,cap,cost;
    };
    void addEdge(int u,int v,int cap,int cost) {
        a.push_back(Edge(v,cap,cost,first[u])); first[u]=a.size()-1;
        a.push_back(Edge(u,0,-cost,first[v])); first[v]=a.size()-1;
    }
    bool augment() {
        dist.assign(n,inf);
        dist[s]=0;
        priority_queue < pair <int,int> > q; q.push(make_pair(0,s));
        while(q.size()) {
            if (dist[t]!=inf) break;
            pair <int,int> top=q.top(); q.pop();
            if (dist[top.second]!=-top.first) continue;
            int u=top.second;
            for(int e=first[u];e!=-1;e=a[e].next) {
                int v=a[e].to,ndist=-top.first+a[e].cost;
                if (a[e].cap>0&&dist[v]>ndist) {
                    dist[v]=ndist;
                    q.push(make_pair(-ndist,v));
                    prev[v]=e;
                }
            }
        }
        return dist[t]!=inf;
    }
    pair <int,int> flow() {
        while(augment()) {
            int cur=t,size=inf;
            while(cur!=s) {
                int e=prev[cur];
                size=min(size,a[e].cap);
                cur=a[e^1].to;
            }
            fl+=size; cost+=(dist[t])*size;
//          if (cost>=0) break;
            cur=t;
            while(cur!=s) {
                int e=prev[cur];
                a[e].cap-=size;
                a[e^1].cap+=size;
                cur=a[e^1].to;
            }
        }
        return make_pair(fl,cost);
    }
    int n,s,t,fl,cost;
    static const int inf=1000000009;
    vector <int> first,prev,dist;
    vector <Edge> a;
};

int n, m;
int sock[82][82];

int calc(pi a, pi b) {
    return min((a.fi != b.fi) + (a.se != b.se), (a.fi != b.se) + (a.se != b.fi));
}

int main() {
    cin.sync_with_stdio(false);
    cin >> n >> m;

    fo(i, n) fo(j, m) {
        cin >> sock[i][j];
    }

    int tot = n * m + 2;
    int src = tot - 2, sink = tot - 1;
    MinCostFlow flow(tot, src, sink);

    int half = n * m / 2;
    fo(i, half) flow.addEdge(src, i, 1, 0);

    fo(i, n) fo(j, m) {
        int idx = (i * m + j);
        vector<tuple<int, int>> adj;
        fo(d, 4) {
            int ni = i + dx[d], nj = j + dy[d];
            if(ni < 0 || ni >= n || nj < 0 || nj >= m) continue;
            adj.push_back(mt(ni * m + nj, sock[i][j] != sock[ni][nj]));
        }

        if((i + j) % 2 == 0) {
            for(auto entry: adj) flow.addEdge(idx / 2, gt(entry, 0) / 2 + half, 1, gt(entry, 1));
        } else {
            for(auto entry: adj) flow.addEdge(gt(entry, 0) / 2, idx / 2 + half, 1, gt(entry, 1));
        }
    }


    fo(i, half) flow.addEdge(i + half, sink, 1, 0);


    auto ret = flow.flow();
    trace(ret);
    auto displ = ret.se;
    cout << displ << endl;
    
    
	return 0;
}

