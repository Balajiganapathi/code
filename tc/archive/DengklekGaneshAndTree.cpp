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
constexpr int mx_n = 1003;
int dp[mx_n][mx_n];

class DengklekGaneshAndTree {
public:
    vector<pi> ints;
    vi ch[mx_n];
    string lb;
    int lvl[mx_n];
    int maxl;


    void dfs(int x, char c, int l, int i) {
        maxl = max(maxl, l);
        //trace(x, c, l, i);
        if(lb[x] == c) {
            ints[i].se = max(ints[i].se, l);
        } else {
            ints.push_back(mp(l, l));
            i = si(ints) - 1;
        }

        for(int y: ch[x]) dfs(y, lb[x], l + 1, i);
    }

    int solve(int i, int till) {
        if(i == si(ints)) return (till == maxl? 1: 0);
        int &ret = dp[i][till+1];
        if(ret != -1) return ret;

        ret = solve(i + 1, till);
        auto cur = ints[i];
        if(cur.fi <= till + 1) {
            ret += solve(i + 1, max(till, cur.se));
            if(ret >= mod) ret -= mod;
        }

        return ret;
    }

	int getCount( string labels, vector <int> parents ) {
		int ret;
        lb = labels;
        int n = si(parents) + 1;
        //trace(parents);
        fo(i, n-1) ch[parents[i]].push_back(i+1);

        maxl = 0;
        dfs(0, '?', 0, -1);
        //trace(ints);
        sort(all(ints));

        ini(dp, -1);
        ret = solve(0, -1);
		
		return ret;
	}
};



// Powered by FileEdit
// Powered by moj 4.18 [modified TZTester]
// Powered by CodeProcessor
