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
constexpr int mx = 20;
char dp[mx][mx][mx * mx][mx * mx];

class MovingCandies {
public:
    int n, m;
    vector<string> g;

    char solve(int i, int j, int used_rem, int move_rem) {
        if(used_rem < 0 || move_rem < 0) return 0;
        if(i == n - 1 && j == m - 1) return 1;
        char &ret = dp[i][j][used_rem][move_rem];
        if(ret != -1) return ret;
        ret = 0;

        fo(d, 4) {
            int ni = i + dx[d], nj = j + dy[d];
            if(ni < 0 || ni >= n || nj < 0 || nj >= m) continue;
            int pos = 0;
            if(g[ni][nj] == '#') {
                pos = solve(ni, nj, used_rem - 1, move_rem);
            }  else {
                pos = solve(ni, nj, used_rem, move_rem - 1);
            }
            if(pos) {
                ret = 1;
                break;
            }
        }

        return ret;
    }

    int solve(int urem, int mrem) {
        if(g[0][0] == '#') return solve(0, 0, urem - 1, mrem);
        else return solve(0, 0, urem, mrem - 1);
    }

	int minMoved( vector <string> t ) {
        g = t;
		int ret = -1;
		
        n = si(t); m = si(t[0]);
        int cnt = 0;
        fo(i, n) fo(j, m) if(g[i][j] == '#') ++cnt;
        ini(dp, -1);

        rep(i, 0, cnt) {
            if(solve(cnt - i, i)) {
                ret = i;
                break;
            }
        }

		return ret;
	}
};



// Powered by FileEdit
// Powered by moj 4.18 [modified TZTester]
// Powered by CodeProcessor
