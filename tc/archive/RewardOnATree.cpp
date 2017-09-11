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
constexpr int mx_n = 2103;
int dp[mx_n];

class RewardOnATree {
public:
    vi r, ch[mx_n], at[mx_n];
    int ans;
    int lvl[mx_n];
    int best[mx_n];

    int solve(int p) {
        int &ret = dp[p];
        if(ret != -1) return ret;
        int i = lvl[p];
        if(si(at[i]) == 0) return ret = 0;
        ret = best[i];

        for(int x: at[i]) {
            for(int y: ch[x]) {
                int cur = best[i] + solve(y);
                cur += min(r[y], 0);
                if(x != p)  cur += min(r[x], 0);
                ret = max(ret, cur);
            }
        }

        return ret;
    }

	int collect( vector <int> parent, vector <int> reward ) {
		int ret = 0;
        ini(lvl, 0);
        r = reward;
        at[0].push_back(0);
        int n = si(r);
        rep(i, 1, n - 1) {
            int p = parent[i-1];
            ch[p].push_back(i);
            lvl[i] = 1+lvl[p];
            at[lvl[i]].push_back(i);
        }

        int ml = *max_element(lvl, lvl + n);
        int f = r[0];
        r[0] = 0;

        ini(best, 0);
        rep(i, 0, ml+1) {
            int cp = 0;
            for(int x: at[i]) if(r[x] > 0) cp += r[x];
            best[i] = cp;
            //trace(i, best[i]);
        }

        ini(dp, -1);
        ans = solve(0);
        ret = ans + f;
		
		return ret;
	}
};



// Powered by FileEdit
// Powered by moj 4.18 [modified TZTester]
// Powered by CodeProcessor
