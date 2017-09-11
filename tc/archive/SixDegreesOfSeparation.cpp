/* string coder = "Balajiganapathi S"; // Never give up!  */



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
constexpr int mx_n = 2003;

vi adj[mx_n];
int vis[mx_n];
int pres[mx_n][mx_n];
class SixDegreesOfSeparation {
public:
    vi connect;
    int c = 0;
    void dfs(int x, int l) {
        if(vis[x]) return;
        vis[x] = 1;
        if(c++ % 3 == 0) connect.push_back(x);
        for(int y: adj[x]) dfs(y, l + 1);
    }
	vector <int> getAdditionalEdges( int n, vector <int> a, vector <int> b ) {
		vector <int> ret;
        fo(i, mx_n) adj[i].clear();
        ini(vis, 0);
        ini(pres, 0);

        fo(i, si(a)) {
            adj[a[i]].push_back(b[i]);
            adj[b[i]].push_back(a[i]);
            pres[a[i]][b[i]] = pres[b[i]][a[i]] = 1;
        }
        dfs(0, 0);
        int root = connect[0];
        re(i, 1, si(connect)) if(!pres[root][connect[i]]) {
            ret.push_back(connect[i]);
            ret.push_back(root);
        }
        
        //trace(connect);
		
		return ret;
	}
};



// Powered by FileEdit
// Powered by moj 4.18 [modified TZTester]
// Powered by CodeProcessor
