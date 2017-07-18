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
constexpr int mx_n = 2503;
int dp[mx_n][mx_n];
int c1[mx_n], c2[mx_n];

class InterleavingParenthesis {
public:
    int n1, n2;
    string s1, s2;

    int getO(int i1, int i2) {
        int ret = 0;
        if(i1 > 0) ret += c1[i1-1];
        if(i2 > 0) ret += c2[i2-1];

        return ret;
    }

    int solve(int i1, int i2) {
        if(i1 > n1 || i2 > n2) return 0;
        int &ret = dp[i1][i2];
        if(ret != -1) return ret;
        ret = 0;

        int bo = getO(i1, i2);
        int bc = i1 + i2 - bo;
        if(bc > bo) return ret = 0;
        if(i1 == n1 && i2 == n2) {
            if(bo == bc) return ret = 1;
            return ret = 0;
        }

        ret += solve(i1 + 1, i2);
        if(ret >= mod) ret -= mod;

        ret += solve(i1, i2 + 1);
        if(ret >= mod) ret -= mod;

        return ret;
    }

	int countWays( string _s1, string _s2 ) {
		int ret;
        s1 = _s1; s2 = _s2;
        n1 = si(s1); n2 = si(s2);

        int c = 0;
        fo(i, n1) {
            c += (s1[i] == '(');
            c1[i] = c;
        }
        c1[n1] = c;
        c = 0;
        fo(i, n2) {
            c += (s2[i] == '(');
            c2[i] = c;
        }
        c2[n2] = c;

        ini(dp, -1);
        ret = solve(0, 0);
		
		return ret;
	}
};



// Powered by FileEdit
// Powered by moj 4.18 [modified TZTester]
// Powered by CodeProcessor
