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
constexpr int mx_n = 5003;
int n, m;

// Number of vertices in given graph
constexpr int V = 2 * mx_n + 10;
 
bool visited[V];
int rGraph[V][V];
int parent[V];
int q[V];
int graph[V][V];
vi adj[V];
int pflow[V];


void init() {
    ini(graph, 0);
    ini(rGraph, 0);
    fo(i, V) adj[i].clear();
}
void addEdge(int u, int v, int cap) {
    rGraph[u][v] = graph[u][v] = cap;
    adj[u].push_back(v);
    adj[v].push_back(u);
}

/* Returns true if there is a path from source 's' to sink 't' in
  residual graph. Also fills parent[] to store the path */
bool bfs(int s, int t) {
    // Create a visited array and mark all vertices as not visited
    memset(visited, 0, sizeof(visited));
 
    // Create a queue, enqueue source vertex and mark source vertex
    // as visited
    int qidx = 0;
    q[qidx++] = s;;
    visited[s] = true;
    parent[s] = -1;
    pflow[s] = INT_MAX;
 
    // Standard BFS Loop
    while (qidx > 0) {
        int u = q[--qidx];
 
        for(int v: adj[u]) {
            if (!visited[v] && rGraph[u][v] > 0) {
                q[qidx++] = v;
                parent[v] = u;
                visited[v] = true;
                pflow[v] = min(rGraph[u][v], pflow[u]);
            }
        }
    }
 
    // If we reached sink in BFS starting from source, then return
    // true, else false
    return (visited[t] == true);
}
 
// Returns tne maximum flow from s to t in the given graph
int fordFulkerson(int s, int t) {
    int u, v;
 
    int max_flow = 0;  // There is no flow initially
 
    // Augment the flow while tere is path from source to sink
    while (bfs(s, t)) {
        // Find minimum residual capacity of the edges along the
        // path filled by BFS. Or we can say find the maximum flow
        // through the path found.
        int path_flow = pflow[t];;
 
        // update residual capacities of the edges and reverse edges
        // along the path
        for (v=t; v != s; v=parent[v])
        {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
 
        // Add path flow to overall flow
        max_flow += path_flow;
        //trace(max_flow, path_flow);
    }
 
    // Return the overall flow
    return max_flow;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int q;
#ifdef TEST
    q = 4;
#else
    cin  >> q;
#endif
    while(q--) {
#ifdef TEST
        n = 5000;
        m = 5000;
#else
        cin >> n >> m;
#endif
        trace(n, m);
        int s = n + m, t = n + m + 1;

        init();
        re(i, 1, n) {
            int p;
#ifdef TEST
            p = rand() % i;
#else
            cin >> p; --p;
#endif
            addEdge(p + m, i + m, mx_n);
        }
        fo(i, n) addEdge(i + m, t, 1);
        fo(i, m) {
            int c, p;
#ifdef TEST
            c = 2;
#else
            cin >> c;
#endif
            fo(j, c) {
#ifdef TEST
                p = rand() % n;
#else
                cin  >> p;
#endif
                --p;
                addEdge(i, p + m, 1);
            }
            addEdge(s, i, 1);
        }


        int ans = fordFulkerson(s, t);
        cout << ans << '\n';

    }

    
    
	return 0;
}

